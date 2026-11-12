#define _WIN32_WINNT 0x0501 /* getaddrinfo (Windows XP and newer) */
#ifndef ISOLATION_AWARE_ENABLED /* CMake sets 0: the manifest (resource 24) already activates the common controls */
#define ISOLATION_AWARE_ENABLED 1
#endif
#define SIDEBYSIDE_COMMONCONTROLS 1 



#include <winsock2.h> /* before windows.h; IPv6 */
#include <ws2tcpip.h>
#include <windows.h>
#include <commctrl.h>
#include <shlobj.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include "resource.h"

#define POWEROFF_VERSION "3.1.0.0"

#define NMESSAGE 1234
#define SHUTDOWN_TIMER 0
#define TIME_TIMER 1

#define ID_SCHEDULE_TIMER 0
#define ID_PROCESS_TIMER  1
#define ID_TRAY_TIMER     2
#define ID_STOP_TIMER     3
#define ID_TIME_TIMER     4
#define ID_HIDE_TIMER     4

#define LISTEN_PORT      3210
#define LISTEN_CLIENTS      1
#define UWM_ACCEPT       1000
#define UWM_READ         1001

#define COMMAND_ERROR    501
#define COMMAND_INFO     201
#define COMMAND_OK       250

#define ADD_DAY(d) { if (str[0]) { strcat(str,","); strcat(str,d);} else strcpy(str,d); }


typedef BOOL (CALLBACK *PROCENUMPROC)( DWORD, WORD, LPSTR, LPARAM ) ;
typedef BOOLEAN (WINAPI *SETSUSPENDSTATEPROC)(BOOL,BOOL,BOOL);

typedef enum { LOCAL_COMPUTER, REMOTE_COMPUTER } Computer;
typedef enum { IMMEDIATE, SCHEDULED, PROCESS } When;
typedef enum { FIXED_DAY, DAILY, DAY_OF_MONTH, AFTER_X_SECONDS } Schedule;
typedef enum { LOGOFF, REBOOT, SHUTDOWN, POWEROFF, STANDBY, HIBERNATE, LOCK, WAKE_ON_LAN, MONITOR_OFF, MONITOR_ON, NO_ACTION } Action;
typedef enum { NOTHING, SAVE_SETTINGS, REMOVE_SETTINGS, SAVE_SERVICE_SETTINGS, REMOVE_SERVICE_SETTINGS, CREATE_SERVICE, REMOVE_SERVICE } CommandLineAction;

typedef struct {
  Action   action;
  Computer who;
  When     when;
  short    interactive;
  UINT     active_timer;
  short    simulate;
  short    start_minimized;
  short    run_as_service;
  char     executable[MAX_PATH];
  SOCKET   serversocket;
  SOCKET   clientsocket;
  short    authenticated;
  short    quiet;
  unsigned remaining_seconds;
  struct {
    char  computer_name[100];
    char  mac_address[14];
    char  ip_address[20];
    char  subnet_mask[20];
    short use_nt;
    int   port;
    short save_password;
    char  password[40];
    short schedule_remote;
    short current_credentials;
    char  username[40];
  } remote;
  struct {
    int   port;
    char  password[40];
  } remote_control;
  struct {
    unsigned seconds;
    char     message[200];
    short    play_sound;
    char     sound_file[MAX_PATH];
  } warning;
  struct {
    char program[MAX_PATH];
    char directory[MAX_PATH];
  } program;
  struct {
    Schedule   schedule;
    SYSTEMTIME time;
    SYSTEMTIME date;
    short      monday;
    short      tuesday;
    short      wednesday;
    short      thursday;
    short      friday;
    short      saturday;
    short      sunday;
    short      week1;
    short      week2;
    short      week3;
    short      week4;
    short      week5;
    unsigned   day;
    unsigned   seconds;
    int        wait;
  } schedule;
  struct {
    char process[200];
  } process;
  OSVERSIONINFO windowsversion;
  struct {
    short warning;
    short run_program;
    short force;
    short in_tray;
    short allow_cancel;
    short allow_remote_control;
  } options;
} PowerSettings;



extern HINSTANCE hInst;
extern UINT g_tid,g_time_tid;
HWND g_hWnd;
extern short debug;

void Log(char *fmt,...);
void Error(PowerSettings *ps,HWND hWnd,char *str);
void DisplayLastError(PowerSettings *ps,HWND hWnd);
void DisplayInformation(PowerSettings *ps,HWND hWnd,char *str);
void WriteEvent(PowerSettings *ps,WORD event_type,char *fmt,...);
char *GetModeStr(PowerSettings *ps);
void MinimizePoweroff(HWND hWnd,PowerSettings *ps);
void RemoveFromTray(HWND hWnd);

void InitializeSettings(PowerSettings *ps);
void ReadDefaultSettings(PowerSettings *ps);
int SaveSettings(HKEY hive,char *base,PowerSettings *ps);
int ReadSettings(HKEY hive,char *base,PowerSettings *ps);
void DisplaySettings(HWND hWnd,PowerSettings *ps);
void DebugSettings(PowerSettings *ps);
int SanityCheck(HWND hWnd,PowerSettings *ps,char *str);

int ParseCommandLine(char *commandline,PowerSettings * ps);
int PowerOff(HWND hWnd,PowerSettings *ps);
int DoIt(HWND hWnd,PowerSettings *ps);
int WakeOnLan(PowerSettings *ps,char *ip_address,char *mask,char *mac_address);
void DoQuickAction(PowerSettings *ps,Action action);
void Cleanup(PowerSettings *ps);

int ShowWarningMessage(HWND hWnd,PowerSettings *ps);
void ShowRemoteDialog(HWND hWnd,PowerSettings *ps);
void ShowMessageDialog(HWND hWnd,PowerSettings *ps);
void ShowProcessDialog(HWND hWnd,PowerSettings *ps);
void ShowProgramDialog(HWND hWnd,PowerSettings *ps);
void ShowScheduleDialog(HWND hWnd,PowerSettings *ps);
void ShowRemoteControlDialog(HWND hWnd,PowerSettings *ps);
void CheckScheduleTimer(HWND hWnd,PowerSettings *ps);
void CheckProcessTimer(HWND hWnd,PowerSettings *ps);
int IsValidMACAddress(char *str);
int IsValidIPAddress(char *str);


BOOL WINAPI EnumProcs( PROCENUMPROC lpProc, LPARAM lParam );

BOOLEAN WriteRegistryString(HKEY hive,char *key,char *subkey,char *value);
BOOLEAN WriteRegistryInteger(HKEY hive,char *key,char *subkey,DWORD value);
BOOLEAN WriteRegistryBytes(HKEY hive,char *key,char *subkey,void *value,int sz);
BOOLEAN ReadRegistryString(HKEY hive,char *key,char *subkey,char *value,int sz);
BOOLEAN ReadRegistryInteger(HKEY hive,char *key,char *subkey,DWORD *value);
BOOLEAN ReadRegistryShort(HKEY hive,char *key,char *subkey,short *value);
BOOLEAN DeleteRegistryValue(HKEY hive,char *key,char *subkey);
BOOLEAN DeleteRegistryKey(HKEY hive,char *key);

void CreatePoweroffService(HWND hWnd,PowerSettings *ps);
void RemovePoweroffService(HWND hWnd,PowerSettings *ps);
DWORD WINAPI CheckService(PowerSettings *ps);
int IsPoweroffServiceRunning(HWND hWnd,PowerSettings *ps);
void StartPoweroffService(HWND hWnd,PowerSettings *ps);
void StopPoweroffService(HWND hWnd,PowerSettings *ps);

int InitializeSockets(void);
void DestroySockets(HWND hWnd,PowerSettings *ps);
int CreateServerSocket(HWND hWnd,PowerSettings *ps);
int AcceptClientSocket(HWND hWnd,PowerSettings *ps);
int ReadFromClientSocket(HWND hWnd,PowerSettings *ps);
int CloseClientSocket(HWND hWnd,PowerSettings *ps);
int CloseServerSocket(HWND hWnd,PowerSettings *ps);
void ShowSocketError(PowerSettings *ps,char *function);
void ReturnClientError(HWND hWnd,PowerSettings *ps, char *error);
void ReturnClientInfo(HWND hWnd,PowerSettings *ps, char *info, ...);
void ReturnClientOK(HWND hWnd,PowerSettings *ps);
void ProcessClientCommand(HWND hWnd,PowerSettings *ps,char *command);
int OpenServerConnection(HWND hWnd,PowerSettings *ps,char *server,char *errormsg);
int SendRemoteCommand(HWND hWnd,PowerSettings *ps,char *errorstr);
char *EncodePassword(char *password);

char *Trim(char *str);
int ReplaceString(char *str,char *srch,char *repl);

extern SETSUSPENDSTATEPROC MySetSuspendState;