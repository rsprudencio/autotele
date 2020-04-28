void PrintText(DWORD Color, char *szText, ...);
BOOL	GameReady();
int		GetSkill(WORD wSkillId);
bool	SetSkill(WORD wSkillId, bool Left);
DWORD	GetPlayerArea();
Level*	GetLevel(DWORD dwLevelNo);
bool	IsTownLevel(int nLevel);

DWORD	GetDistance(DWORD x1, DWORD y1, DWORD x2, DWORD y2);
DWORD	GetDistanceSquared(DWORD x1, DWORD y1, DWORD x2, DWORD y2);
typedef bool (_stdcall *fp)(UnitAny* pUnit);
DWORD	GetTileLevelNo(Room2* lpRoom2, DWORD dwTileNo);
LONG WINAPI GameEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void __fastcall JoinGame(char *Gamename,char *Password);