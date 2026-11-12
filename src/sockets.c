#include "poweroff.h"
#include <winsock2.h>

void ShowSocketError(PowerSettings *ps,char *function)
{
  char str[100],error[100];

  Log("ShowSocketError start");
  switch (WSAGetLastError())
  {
    case WSAEINTR:
      strcpy(error,"Interrupted function call");
      break;
    case WSAEBADF:
      strcpy(error,"WSAEBADF");
      break;
    case WSAEACCES:
      strcpy(error,"Permission denied");
      break;
    case WSAEFAULT:
      strcpy(error,"Bad address");
      break;
    case WSAEINVAL:
      strcpy(error,"Invalid argument");
      break;
    case WSAEMFILE:
      strcpy(error,"Too many open files");
      break;
    case WSAEWOULDBLOCK:
      strcpy(error,"Resource temporarily unavailable");
      break;
    case WSAEINPROGRESS:
      strcpy(error,"Operation now in progress");
      break;
    case WSAEALREADY:
      strcpy(error,"Operation already in progress");
      break;
    case WSAENOTSOCK:
      strcpy(error,"Socket operation on non-socket");
      break;
    case WSAEDESTADDRREQ:
      strcpy(error,"Destination address required");
      break;
    case WSAEMSGSIZE:
      strcpy(error,"Message too long");
      break;
    case WSAEPROTOTYPE:
      strcpy(error,"Protocol wrong type for socket");
      break;
    case WSAENOPROTOOPT:
      strcpy(error,"Bad protocol option");
      break;
    case WSAEPROTONOSUPPORT:
      strcpy(error,"Protocol not supported");
      break;
    case WSAESOCKTNOSUPPORT:
      strcpy(error,"Socket type not supported");
      break;
    case WSAEOPNOTSUPP:
      strcpy(error,"Operation not supported");
      break;
    case WSAEPFNOSUPPORT:
      strcpy(error,"Protocol family not supported");
      break;
    case WSAEAFNOSUPPORT:
      strcpy(error,"Address family not supported by protocol family");
      break;
    case WSAEADDRINUSE:
      strcpy(error,"Address already in use");
      break;
    case WSAEADDRNOTAVAIL:
      strcpy(error,"Cannot assign requested address");
      break;
    case WSAENETDOWN:
      strcpy(error,"Network is down");
      break;
    case WSAENETUNREACH:
      strcpy(error,"Network is unreachable");
      break;
    case WSAENETRESET:
      strcpy(error,"Network dropped connection on reset");
      break;
    case WSAECONNABORTED:
      strcpy(error,"Software caused connection abort");
      break;
    case WSAECONNRESET:
      strcpy(error,"Connection reset by peer");
      break;
    case WSAENOBUFS:
      strcpy(error,"No buffer space available");
      break;
    case WSAEISCONN:
      strcpy(error,"Socket is already connected");
      break;
    case WSAENOTCONN:
      strcpy(error,"Socket is not connected");
      break;
    case WSAESHUTDOWN:
      strcpy(error,"Cannot send after socket shutdown");
      break;
    case WSAETOOMANYREFS:
      strcpy(error,"WSAETOOMANYREFS");
      break;
    case WSAETIMEDOUT:
      strcpy(error,"Connection timed out");
      break;
    case WSAECONNREFUSED:
      strcpy(error,"Connection refused");
      break;
    case WSAELOOP:
      strcpy(error,"WSAELOOP");
      break;
    case WSAENAMETOOLONG:
      strcpy(error,"WSAENAMETOOLONG");
      break;
    case WSAEHOSTDOWN:
      strcpy(error,"Host is down");
      break;
    case WSAEHOSTUNREACH:
      strcpy(error,"No route to host");
      break;
    case WSAENOTEMPTY:
      strcpy(error,"WSAENOTEMPTY");
      break;
    case WSAEPROCLIM:
      strcpy(error,"Too many processes");
      break;
    case WSAEUSERS:
      strcpy(error,"WSAEUSERS");
      break;
    case WSAEDQUOT:
      strcpy(error,"WSAEDQUOT");
      break;
    case WSAESTALE:
      strcpy(error,"WSAESTALE");
      break;
    case WSAEREMOTE:
      strcpy(error,"WSAEREMOTE");
      break;
    case WSASYSNOTREADY:
      strcpy(error,"Network subsystem is unavailable");
      break;
    case WSAVERNOTSUPPORTED:
      strcpy(error,"WINSOCK.DLL version out of range");
      break;
    case WSANOTINITIALISED:
      strcpy(error,"Successful WSAStartup not yet performed");
      break;
    case WSAEDISCON:
      strcpy(error,"Graceful shutdown in progress");
      break;
    case WSAENOMORE:
      strcpy(error,"WSAENOMORE");
      break;
    case WSAECANCELLED:
      strcpy(error,"WSAECANCELLED");
      break;
    case WSAEINVALIDPROCTABLE:
      strcpy(error,"WSAEINVALIDPROCTABLE");
      break;
    case WSAEINVALIDPROVIDER:
      strcpy(error,"WSAEINVALIDPROVIDER");
      break;
    case WSAEPROVIDERFAILEDINIT:
      strcpy(error,"WSAEPROVIDERFAILEDINIT");
      break;
    case WSASYSCALLFAILURE:
      strcpy(error,"System call failure");
      break;
    case WSASERVICE_NOT_FOUND:
      strcpy(error,"WSASERVICE_NOT_FOUND");
      break;
    case WSATYPE_NOT_FOUND:
      strcpy(error,"Class type not found");
      break;
    case WSA_E_NO_MORE:
      strcpy(error,"WSA_E_NO_MORE");
      break;
    case WSA_E_CANCELLED:
      strcpy(error,"WSA_E_CANCELLED");
      break;
    case WSAEREFUSED:
      strcpy(error,"WSAEREFUSED");
      break;
    case WSAHOST_NOT_FOUND:
      strcpy(error,"Host not found");
      break;
    case WSATRY_AGAIN:
      strcpy(error,"Non-authoritative host not found");
      break;
    case WSANO_RECOVERY:
      strcpy(error,"This is a non-recoverable error");
      break;
    case WSANO_DATA:
      strcpy(error,"Valid name, no data record of requested type");
      break;
    case WSA_QOS_RECEIVERS:
      strcpy(error,"WSA_QOS_RECEIVERS");
      break;
    case WSA_QOS_SENDERS:
      strcpy(error,"WSA_QOS_SENDERS");
      break;
    case WSA_QOS_NO_SENDERS:
      strcpy(error,"WSA_QOS_NO_SENDERS");
      break;
    case WSA_QOS_NO_RECEIVERS:
      strcpy(error,"WSA_QOS_NO_RECEIVERS");
      break;
    case WSA_QOS_REQUEST_CONFIRMED:
      strcpy(error,"WSA_QOS_REQUEST_CONFIRMED");
      break;
    case WSA_QOS_ADMISSION_FAILURE:
      strcpy(error,"WSA_QOS_ADMISSION_FAILURE");
      break;
    case WSA_QOS_POLICY_FAILURE:
      strcpy(error,"WSA_QOS_POLICY_FAILURE");
      break;
    case WSA_QOS_BAD_STYLE:
      strcpy(error,"WSA_QOS_BAD_STYLE");
      break;
    case WSA_QOS_BAD_OBJECT:
      strcpy(error,"WSA_QOS_BAD_OBJECT");
      break;
    case WSA_QOS_TRAFFIC_CTRL_ERROR:
      strcpy(error,"WSA_QOS_TRAFFIC_CTRL_ERROR");
      break;
    case WSA_QOS_GENERIC_ERROR:
      strcpy(error,"WSA_QOS_GENERIC_ERROR");
      break;
    default:
      strcpy(error,"Unknown error");
      break;
  }
  sprintf(str,"%s(): %s (%d)",function,error,WSAGetLastError());
  Error(ps,NULL,str);
  Log("ShowSocketError end");
}

int InitializeSockets(void)
{
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;
 
  Log("InitializeSockets start");
  wVersionRequested=MAKEWORD(1,1);
 
  err=WSAStartup(wVersionRequested,&wsaData);
  if (err!=0) 
  {
    Log("InitializeSockets end because WSAStartup failed");
    return -1;
  }
  
  if (LOBYTE(wsaData.wVersion)!=1 ||
      HIBYTE(wsaData.wVersion)!=1) 
  {
    WSACleanup( );
    Log("InitializeSockets end, version=%d.%d",HIBYTE(wsaData.wVersion),LOBYTE(wsaData.wVersion));
    return -2; 
  }
  Log("InitializeSockets end");
  return 0;
}

void DestroySockets(HWND hWnd,PowerSettings *ps)
{
  Log("DestroySockets start");
  if (ps)
  {
    CloseServerSocket(hWnd,ps);
    CloseClientSocket(hWnd,ps);
  }
  WSACleanup();
  Log("DestroySockets end");
}
 
int CreateServerSocket(HWND hWnd,PowerSettings *ps)
{
  struct sockaddr_in sa;
  struct sockaddr_in6 sa6; /* IPv6 (3.0.2) */
  DWORD v6only=0;

  Log("CreateServerSocket start");
  if (ps->serversocket!=INVALID_SOCKET)
    CloseServerSocket(hWnd,ps);

  /* IPv6 (3.0.2): one dual-stack socket answers IPv6 and IPv4 (as ::ffff:a.b.c.d).
     Without dual stack (Windows XP, IPv6 disabled) the original IPv4 code below runs. */
  ps->serversocket=socket(AF_INET6,SOCK_STREAM,IPPROTO_TCP);
  if (ps->serversocket!=INVALID_SOCKET)
  {
    memset(&sa6,0,sizeof(sa6));
    sa6.sin6_family = AF_INET6;
    sa6.sin6_port = htons((unsigned short)ps->remote_control.port);
    sa6.sin6_addr = in6addr_any;
    if (setsockopt(ps->serversocket,IPPROTO_IPV6,IPV6_V6ONLY,(char*)&v6only,sizeof(v6only))==SOCKET_ERROR ||
        bind(ps->serversocket,(struct sockaddr*)&sa6,sizeof(sa6))==SOCKET_ERROR)
    {
      Log("No dual-stack socket (error %d), using IPv4 only",WSAGetLastError());
      closesocket(ps->serversocket);
      ps->serversocket=INVALID_SOCKET;
    }
  }
  if (ps->serversocket==INVALID_SOCKET)
  { /* original IPv4 code, unchanged */
  ps->serversocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if (ps->serversocket==INVALID_SOCKET)
  {
    ShowSocketError(ps,"socket");
    return -1;
  }

  sa.sin_family = AF_INET;
  sa.sin_port = htons((unsigned short)ps->remote_control.port);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);   
  if (bind(ps->serversocket,(struct sockaddr*)&sa,sizeof(sa))==SOCKET_ERROR)
  {
    ShowSocketError(ps,"bind");
    return -1;
  }
  } /* end of original IPv4 code */
  if (listen(ps->serversocket,LISTEN_CLIENTS)==SOCKET_ERROR)
  {
    ShowSocketError(ps,"listen");
    return -1;
  }
  if (WSAAsyncSelect(ps->serversocket,hWnd,UWM_ACCEPT,FD_ACCEPT)==SOCKET_ERROR)
  {
    ShowSocketError(ps,"WSAAsyncSelect");
    return -1;
  }
  Log("CreateServerSocket end");
  return 0;
}

int AcceptClientSocket(HWND hWnd,PowerSettings *ps)
{
  Log("AcceptClientSocket start");
  if (ps->clientsocket!=INVALID_SOCKET)
    CloseClientSocket(hWnd,ps);
  if ((ps->clientsocket=accept(ps->serversocket,NULL,NULL))==INVALID_SOCKET)
  {
    ShowSocketError(ps,"accept");
    return -1;
  }
  if (ps->remote_control.password[0]=='\0')
    ps->authenticated=1;
  else
    ps->authenticated=0;
  if (WSAAsyncSelect(ps->clientsocket,hWnd,UWM_READ,FD_READ|FD_CLOSE)==SOCKET_ERROR)
  {
    ShowSocketError(ps,"WSAAsyncSelect");
    return -1;
  }
  ReturnClientInfo(hWnd,ps,"Welcome to Poweroff %s created by Jorgen Bosman",POWEROFF_VERSION);
  Log("AcceptClientSocket end");
  return 0;
}

int ReadFromClientSocket(HWND hWnd,PowerSettings *ps)
{
  char buf[101]="",tmp[2];
  static char command[501]="";
  int bytes_received,x;

  Log("ReadFromClientSocket start");
  bytes_received=recv(ps->clientsocket,buf,100,0);
  if (bytes_received==0)
    CloseClientSocket(hWnd,ps);
  else if (bytes_received==SOCKET_ERROR)
  {
    ShowSocketError(ps,"send");
    CloseClientSocket(hWnd,ps);
    return -1;
  }
  else
  {
    buf[bytes_received]=0;
    Log("Received data from client: %s",buf);
    for (x=0;x<bytes_received;x++)
    {
      if (buf[x]=='\n')
      {
        ProcessClientCommand(hWnd,ps,command);
        command[0]='\0';
      }
      else if (buf[x]=='\r')
        continue;
      else
      {
        if (strlen(command)>=500)
        {
          ReturnClientError(hWnd,ps,"Command too long");
          command[0]='\0';
        }
        else
        {
          tmp[0]=buf[x];
          tmp[1]='\0';
          strcat(command,tmp);
        }
      }
    }
  }
  Log("ReadFromClientSocket end");
  return 0;
}

int CloseClientSocket(HWND hWnd,PowerSettings *ps)
{
  Log("CloseClientSocket start");
  if (ps->clientsocket!=INVALID_SOCKET)
  {
    shutdown(ps->clientsocket,SD_BOTH);
    closesocket(ps->clientsocket);
    ps->clientsocket=INVALID_SOCKET;
    ps->authenticated=0;
  }
  Log("CloseClientSocket end");
  return 0;
}

int CloseServerSocket(HWND hWnd,PowerSettings *ps)
{
  Log("CloseServerSocket start");
  if (ps->serversocket!=INVALID_SOCKET)
  {
    shutdown(ps->serversocket,SD_BOTH);
    closesocket(ps->serversocket);
    ps->serversocket=INVALID_SOCKET;
  }
  CloseClientSocket(hWnd,ps);
  Log("CloseServerSocket end");
  return 0;
}

int OpenServerConnection(HWND hWnd,PowerSettings *ps,char *server,char *errormsg)
{
  struct addrinfo hints,*res=NULL,*ai;
  char port[16];
  char str[500],*value;
  int ret,err=0;

  Log("OpenServerConnection start, server=%s",server);
  if (ps->clientsocket!=INVALID_SOCKET)
    CloseClientSocket(hWnd,ps);

  /* IPv6 (3.0.2): resolve names and addresses of both families, try each address in turn */
  memset(&hints,0,sizeof(hints));
  hints.ai_family=AF_UNSPEC;
  hints.ai_socktype=SOCK_STREAM;
  hints.ai_protocol=IPPROTO_TCP;
  sprintf(port,"%d",ps->remote.port);
  if ((err=getaddrinfo(server,port,&hints,&res))!=0 || res==NULL)
  {
    WSASetLastError(err);
    ShowSocketError(ps,"getaddrinfo");
    return -1;
  }
  for (ai=res;ai!=NULL;ai=ai->ai_next)
  {
    ps->clientsocket=socket(ai->ai_family,ai->ai_socktype,ai->ai_protocol);
    if (ps->clientsocket==INVALID_SOCKET)
    {
      err=WSAGetLastError();
      continue;
    }
    if (connect(ps->clientsocket,ai->ai_addr,(int)ai->ai_addrlen)!=SOCKET_ERROR)
      break;
    err=WSAGetLastError();
    closesocket(ps->clientsocket);
    ps->clientsocket=INVALID_SOCKET;
  }
  freeaddrinfo(res);
  if (ps->clientsocket==INVALID_SOCKET)
  {
    WSASetLastError(err);
    ShowSocketError(ps,"connect");
    return -1;
  }
  Log("Waiting from response from server");
  if ((ret=recv(ps->clientsocket,str,500,0))==SOCKET_ERROR || ret<=0)
  {
    ShowSocketError(ps,"recv");
    CloseClientSocket(hWnd,ps);
    return -1;
  }
  str[ret]=0;
  Log("response=%s",str);
  while (strlen(str)>0 && (str[strlen(str)-1]=='\n' || str[strlen(str)-1]=='\r'))
    str[strlen(str)-1]='\0';
  value=strchr(str,' ');
  if (value)
  {
    *value='\0';
    value++;
    Trim(value);
  }
  if (str[0]=='2')
    return 0;
  else if (str[0]=='5')
  {
    strcpy(errormsg,value);
    return -2;
  }
  else
  {
    strcpy(errormsg,"Unknown response received");
    return -2;
  }
  Log("OpenServerConnection end");
  return 0;
}