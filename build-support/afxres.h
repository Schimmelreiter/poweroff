/* Stand-in for MFC's afxres.h so poweroff.rc compiles without MFC (MinGW, VS without MFC). */
#ifndef POWEROFF_AFXRES_H
#define POWEROFF_AFXRES_H
#include <winresrc.h>
#ifndef IDC_STATIC
#define IDC_STATIC (-1)
#endif
#endif
