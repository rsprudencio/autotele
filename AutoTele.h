//POINT FindPresetUnitXY(DWORD dwType, DWORD dwTxtFileNo, DWORD dwTxtFileNo2, DWORD Area);
extern void DoTele(int VECTOR);
void MakePath(int x, int y, DWORD Areas[], DWORD count, bool MoveThrough, DWORD InteractType, Room2 *InteractRoom);
void MakePathObject(DWORD dwType, DWORD dwTxtFileNo, DWORD dwTxtFileNo2, DWORD Area);
DWORD WINAPI TeleportThread(LPVOID P);
DWORD WINAPI ManageTeleThread(LPVOID P);

extern HANDLE TELEHANDLE;
extern HANDLE TeleThread;
DWORD GetUnitByXY(DWORD X, DWORD Y, Room2* pRoom);
extern Room2* InteractRoom;
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