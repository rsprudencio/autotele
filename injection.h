#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500

#define ArraySize(x) (sizeof(x) / sizeof(x[0]))
#define _CRT_SECURE_NO_DEPRECATE
extern char szModulePath[260];

#include <windows.h>
#include <shlwapi.h>
#include <math.h>
// header files
//#include "Intercepts.h"
#include "D2Structs.h"
#include "SendPacket.h"
#include "CMapIncludes.h"
//#include "KeyHook.h"
#include "D2Helpers.h"
#include "Offset.h"
#include "D2Ptrs.h"
#include "Constants.h"
#include "Config.h"
#include "Matrix.h"
#include "AutoTele.h"
#include "ArrayEx.h"

extern bool EndThread;
extern WNDPROC oldWNDPROC;
#define CToW(szString, wString)				(MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szString, (int)strlen(szString), wString, (int)strlen(szString)+1));
#define	WToC(wString, szString)				(WideCharToMultiByte(CP_ACP, 0, wString, -1, szString, (int)sizeof(szString), 0, 0));

#define FONTCOLOR_WHITE		0
#define FONTCOLOR_RED		1
#define FONTCOLOR_GREEN		2
#define FONTCOLOR_BLUE		3
#define FONTCOLOR_GOLD		4
#define FONTCOLOR_GREY		5
#define FONTCOLOR_BLACK		6
#define FONTCOLOR_BROWN		7
#define FONTCOLOR_ORANGE	8
#define FONTCOLOR_YELLOW	9
#define FONTCOLOR_PURPLE	10

#define NEXT 0
#define OTHER 1
#define WAYPOINT 2
#define PREV 3