POINT FindPresetUnitXY(DWORD dwType, DWORD dwTxtFileNo, DWORD dwTxtFileNo2, DWORD Area);
extern void DoTele(int VECTOR);
int MakePath(int x, int y, DWORD Areas[], DWORD count, bool MoveThrough);
DWORD WINAPI TeleportThread(LPVOID P);

extern HANDLE TELEHANDLE;
DWORD GetUnitByXY(DWORD X, DWORD Y, Room2* pRoom);
extern Room2* InteractRoom;
extern POINT aPath[255];
extern CArrayEx <POINT, POINT> Path;
#define VALIDPTR(X) ( (X) && (!IsBadReadPtr(X,sizeof(X))) )

typedef struct Vector_t
{
	DWORD dwType;
	DWORD Id;
	DWORD Id2;
	DWORD Area;
} Vector;

extern Vector vVector[];
void ManageTele(Vector T);