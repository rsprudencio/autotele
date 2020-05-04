#include "ArrayEx.h"
#include "D2Structs.h"

#ifdef _DEFINE_VARS

enum {DLLNO_D2CLIENT, DLLNO_D2COMMON, DLLNO_D2GFX, DLLNO_D2LANG, DLLNO_D2WIN, DLLNO_D2NET, DLLNO_D2GAME, DLLNO_D2LAUNCH, DLLNO_FOG, DLLNO_BNCLIENT, DLLNO_STORM, DLLNO_D2CMP, DLLNO_D2MULTI};

#define DLLOFFSET(a1,b1) ((DLLNO_##a1)|((b1)<<8))
#define FUNCPTR(d1,v1,t1,t2,o1)	typedef t1 d1##_##v1##_t t2; d1##_##v1##_t *d1##_##v1 = (d1##_##v1##_t *)DLLOFFSET(d1,o1);
#define VARPTR(d1,v1,t1,o1)		typedef t1 d1##_##v1##_t;    d1##_##v1##_t *p_##d1##_##v1 = (d1##_##v1##_t *)DLLOFFSET(d1,o1);
#define ASMPTR(d1,v1,o1)			DWORD d1##_##v1 = DLLOFFSET(d1,o1);

#else

#define FUNCPTR(d1,v1,t1,t2,o1)	typedef t1 d1##_##v1##_t t2; extern d1##_##v1##_t *d1##_##v1;
#define VARPTR(d1,v1,t1,o1)		typedef t1 d1##_##v1##_t;    extern d1##_##v1##_t *p_##d1##_##v1;
#define ASMPTR(d1,v1,o1)			extern DWORD d1##_##v1;

#endif
#define _D2PTRS_START	D2CLIENT_GetMonsterTxt

FUNCPTR(D2CLIENT, GetMonsterTxt, MonsterTxt * __fastcall, (DWORD monno), 0x1230) // Updated 1.13c
FUNCPTR(D2CLIENT, RecvCommand07, void __fastcall, (BYTE *cmdbuf), 0xAC3D0)  // Updated 1.13c
FUNCPTR(D2CLIENT, RecvCommand08, void __fastcall, (BYTE *cmdbuf), 0xAC440)  // Updated 1.13c
FUNCPTR(D2CLIENT, PrintGameString, void __stdcall, (wchar_t *wMessage, int nColor), 0x7D850) // Updated 1.13c
FUNCPTR(D2CLIENT, PrintPartyString, void __stdcall, (wchar_t *wMessage, int nColor), 0x7D610) // Updated 1.13c
FUNCPTR(D2CLIENT, PrintGameString2, void __stdcall, (char *szMessage), 0x7F780) // Updated 1.13c
FUNCPTR(BNCLIENT, SendBNMessage,void __fastcall,(LPSTR lpMessage),0xC400) //Updated 1.13c

FUNCPTR(D2CLIENT, GetPlayerXOffset, int __stdcall, (), 0x3F6C0) // Updated 1.13c
FUNCPTR(D2CLIENT, GetPlayerYOffset, int __stdcall, (), 0x3F6D0) // Updated 1.13c
FUNCPTR(D2CLIENT, GetUnitX, int __fastcall, (UnitAny* pUnit), 0x1630)
FUNCPTR(D2CLIENT, GetUnitY, int __fastcall, (UnitAny* pUnit), 0x1660)

FUNCPTR(D2WIN, TakeScreenshot, void __fastcall, (), 0x17EB0) // Updated 1.13c

FUNCPTR(D2CLIENT, SetSelectedUnit_I, void __fastcall, (UnitAny *pUnit), 0x51860) // Updated 1.13c
FUNCPTR(D2CLIENT, GetSelectedUnit, UnitAny * __stdcall, (), 0x51A80) // Updated 1.13c
FUNCPTR(D2CLIENT, GetDifficulty, BYTE __stdcall, (), 0x41930) // Updated 1.13c
FUNCPTR(D2CLIENT, GetUnknownFlag, DWORD __fastcall, (), 0x37A60) // Updated 1.13c
FUNCPTR(D2CLIENT, GetGameInfo, GameStructInfo *__stdcall, (), 0x108B0) // Updated 1.13c
FUNCPTR(D2CLIENT, GetAutomapSize, DWORD __stdcall, (), 0x5F970) // Updated 1.13c
FUNCPTR(D2CLIENT, NewAutomapCell, AutomapCell * __fastcall, (), 0x5F6B0) // Updated 1.13c
FUNCPTR(D2CLIENT, AddAutomapCell, void __fastcall, (AutomapCell *aCell, AutomapCell **node), 0x61320) // Updated 1.13c
FUNCPTR(D2CLIENT, RevealAutomapRoom, void __stdcall, (Room1 *pRoom1, DWORD dwClipFlag, AutomapLayer *aLayer), 0x62580) // Updated 1.13c
FUNCPTR(D2CLIENT, InitAutomapLayer_I, AutomapLayer* __fastcall, (DWORD nLayerNo), 0x62710) // Updated 1.13c
FUNCPTR(D2CLIENT, GetMonsterOwner, DWORD __fastcall, (DWORD nMonsterId), 0x216A0) // Updated 1.13c
FUNCPTR(D2CLIENT, GetUiVar_I, DWORD __fastcall, (DWORD dwVarNo), 0xBE400) // Updated 1.13c
FUNCPTR(D2CLIENT, SetUIState, DWORD __fastcall, (DWORD varno, DWORD howset, DWORD unknown1), 0xC2794) // Updated 1.13c
FUNCPTR(D2CLIENT, GetItemNameString, void __stdcall, (UnitAny *pItem, wchar_t *wItemName, int nLen), 0x914F0) // Updated 1.13c
FUNCPTR(D2CLIENT, CalculateShake, void __stdcall, (DWORD *dwPosX, DWORD *dwPosY), 0x8AFD0) // Updated 1.13c
FUNCPTR(D2CLIENT, GetPlayerUnit, UnitAny*  __stdcall,(),0xA4D60) // Updated 1.13c
FUNCPTR(D2CLIENT, DrawRectFrame, VOID __fastcall, (DWORD Rect), 0xBE4C0) // Updated 1.13c
FUNCPTR(D2CLIENT, ExitGame, VOID __fastcall, (VOID), 0x42850) // Updated 1.13c
FUNCPTR(D2CLIENT, Attack, VOID __stdcall, (AttackStruct* Attack, BOOL AttackingUnit), 0x1A060) // Updated 1.13c
FUNCPTR(D2CLIENT, GetItemName, BOOL __stdcall, (UnitAny* pItem, wchar_t* wBuffer, DWORD dwSize), 0x914F0) // Updated 1.13c
FUNCPTR(D2CLIENT, AcceptTrade, VOID __fastcall, (VOID), 0x59600) // Updated 1.13c
FUNCPTR(D2CLIENT, DrawPartyName ,void __stdcall, (LPSTR pR,DWORD yPos,DWORD Col,DWORD UNK), 0x75780)//Updated 1.13c
FUNCPTR(D2CLIENT, CancelTrade, VOID __fastcall, (VOID), 0x8CB90) // Updated 1.13c
FUNCPTR(D2CLIENT, GetMouseXOffset, DWORD __fastcall, (VOID), 0x3F6C0) // Updated 1.13c
FUNCPTR(D2CLIENT, GetMouseYOffset, DWORD __fastcall, (VOID), 0x3F6D0) // Updated 1.13c
FUNCPTR(D2CLIENT, GameShowAttack, DWORD __stdcall, (UnitAny* pUnit, DWORD dwSpell, DWORD dwSkillLevel, DWORD _1), 0xA2C90) //Updated 1.13c
FUNCPTR(D2CLIENT, xGetNextPartyPlayer, PartyPlayer * __fastcall, (PartyPlayer *pla), 0x9D2B0) //Updated 1.13c
FUNCPTR(D2COMMON, AbsScreenToMap, void __stdcall, (long *pX, long *pY), -10474)
//extra
FUNCPTR(D2CLIENT, ClearScreen, VOID __fastcall, (VOID), 0x492F0) // Updated 1.13c
FUNCPTR(D2CLIENT, GetQuestInfo, VOID* __stdcall, (VOID), 0x45A00) // Updated 1.13c
FUNCPTR(D2CLIENT, UnitTestSelect, DWORD __stdcall, (UnitAny* pUnit, DWORD _1, DWORD _2, DWORD _3), 0xA68E0) // Updated 1.13c
FUNCPTR(D2CLIENT, FindServerSideUnit, UnitAny* __fastcall, (DWORD dwId, DWORD dwType), 0x19438) // Updated 1.13c
FUNCPTR(D2CLIENT, FindClientSideUnit, UnitAny* __fastcall, (DWORD dwId, DWORD dwType), 0xA5B20) // Updated 1.13c
FUNCPTR(D2CLIENT, SetUIVar, DWORD __fastcall, (DWORD varno, DWORD howset, DWORD unknown1), 0xC2790) // Updated 1.13c
FUNCPTR(D2CLIENT, clickMap, VOID __stdcall, (DWORD MouseFlag, DWORD x, DWORD y, DWORD Type), 0x1BF20) // Updated 1.13c
FUNCPTR(D2CLIENT, GetCursorItem, UnitAny* __fastcall, (VOID), 0x16020) // Updated 1.13c
FUNCPTR(D2CLIENT, LeftClickItem, VOID __stdcall, (UnitAny* pPlayer, Inventory* pInventory, INT x, INT y, DWORD dwClickType, InventoryLayout* pLayout, DWORD Location), 0x96AA0) // Updated 1.13c
FUNCPTR(D2CLIENT, CloseNPCInteract, VOID __fastcall, (VOID), 0x48350) // Updated 1.13c
FUNCPTR(D2CLIENT, CloseInteract, VOID __fastcall, (VOID), 0x43870) // Updated 1.13c
FUNCPTR(D2CLIENT, ChatBoxHandler, DWORD __stdcall, (MSG* pMsg), 0x70C40) // Updated 1.13c
FUNCPTR(D2CLIENT, InitInventory, VOID __fastcall, (VOID), 0x908C0) // Updated 1.13c
FUNCPTR(D2CLIENT, FixShopActions, VOID __fastcall, (VOID), 0x47AB0) // Updated 1.13c
FUNCPTR(D2CLIENT, submitItem, VOID __fastcall, (DWORD dwItemId), 0x45FB0) // Updated 1.13c
FUNCPTR(D2CLIENT, GetUnitHPPercent, DWORD __fastcall, (DWORD dwUnitId), 0x21590) // Updated 1.13c
FUNCPTR(D2CLIENT, GetMercUnit, UnitAny* __fastcall, (VOID), 0x97CD0) // Updated 1.13c
FUNCPTR(D2CLIENT, ShopAction, VOID __fastcall, (UnitAny* pItem, UnitAny* pNpc, UnitAny* pNpc2, DWORD dwSell, DWORD dwItemCost, DWORD dwMode, DWORD _2, DWORD _3), 0x47D60) // Updated 1.13c
FUNCPTR(D2CLIENT, GetCurrentInteractingNPC, UnitAny* __fastcall, (VOID), 0x7C5C0) // Updated 1.13c
FUNCPTR(D2CLIENT, PerformGoldDialogAction, VOID __fastcall, (VOID), 0xBFDF0)//Updated 1.13c
FUNCPTR(D2CLIENT, LeaveParty, VOID __fastcall, (VOID), 0x9E5D0)//Updated 1.13c
FUNCPTR(D2CLIENT, Transmute, VOID __fastcall, (VOID), 0x595C0)//Updated 1.13c
FUNCPTR(D2CLIENT, CalcShake, void __stdcall, (DWORD *xpos, DWORD *ypos), 0x8AFD0) //Updated 1.13c
FUNCPTR(D2GFX, GetHwnd, HWND __stdcall, (), -10048)
FUNCPTR(D2NET, SendPacket, void __stdcall, (DWORD aLen, DWORD arg1, BYTE* aPacket), -10024) //updated
FUNCPTR(D2NET, ReceivePacket, void __stdcall, (BYTE *aPacket, DWORD aLen), 0x6BD0) //updated
FUNCPTR(D2NET, ReceivePacket_I, void __stdcall, (BYTE *aPacket, DWORD aLen), -10033) //updated

FUNCPTR(D2WIN, DrawText, void __fastcall, (wchar_t *wStr, int xPos, int yPos, DWORD dwColor, DWORD dwUnk), -10150)
FUNCPTR(D2WIN, GetTextSize, DWORD __fastcall, (wchar_t *wStr, DWORD* dwWidth, DWORD* dwFileNo), -10177)
FUNCPTR(D2WIN, SetFont, DWORD __fastcall, (DWORD dwSize), -10184)
FUNCPTR(D2GFX, DrawLine, void __stdcall, (int X1, int Y1, int X2, int Y2, DWORD dwColor, DWORD dwUnk), -10010)
FUNCPTR(D2COMMON, AddRoomData, void __stdcall, (Act * ptAct, int LevelId, int Xpos, int Ypos, Room1 * pRoom), -10401)
FUNCPTR(D2COMMON, RemoveRoomData, void __stdcall, (Act * ptAct, int LevelId, int Xpos, int Ypos, Room1 * pRoom), -11099)
FUNCPTR(D2COMMON, GetLayer, AutomapLayer2* __fastcall, (DWORD dwLevelNo), -10749)
FUNCPTR(D2COMMON, GetLevel, Level * __fastcall, (ActMisc *pMisc, DWORD dwLevelNo), -10207)
FUNCPTR(D2COMMON, GetLevelTxt, LevelTxt * __stdcall, (DWORD levelno), -10014)
FUNCPTR(D2COMMON, GetObjectTxt, ObjectTxt * __stdcall, (DWORD objno), -10688)
FUNCPTR(D2COMMON, InitLevel, void __stdcall, (Level *pLevel), -10322) 
FUNCPTR(D2COMMON, GetUnitStat, DWORD __stdcall, (UnitAny* pUnit, DWORD dwStat, DWORD dwStat2), -10973) //Updated 1.13c
FUNCPTR(D2COMMON, GetRoomFromUnit,  Room1* __stdcall, (UnitAny * ptUnit), -10331)

VARPTR(D2CLIENT, PlayerArea, int, 0x11C34C)
VARPTR(D2WIN, FirstControl, Control*, 0x214A0)
VARPTR(D2WIN, ChatInputBox, DWORD*, 0x12A0D0)
VARPTR(D2CLIENT, ChatMsg, wchar_t*, 0x11EC80)
//VARPTR(D2MULTI, ChatInputBox, DWORD*, 0x3A0B0)
VARPTR(D2CLIENT, ScreenSizeX, DWORD, 0xDBC48)
VARPTR(D2CLIENT, ScreenSizeY, DWORD, 0xDBC4C)

ASMPTR(D2CLIENT, DrawHook_I, 0x52D90)

ASMPTR(D2MULTI,JoinGame_I,0xCBD0)
ASMPTR(D2MULTI,JoinGame_II,0x11DA0)
ASMPTR(D2MULTI,WaitBox,0xAA60)
FUNCPTR(D2LANG, GetLocaleText, wchar_t* __fastcall, (WORD nLocaleTxtNo), -10003)

VARPTR(D2CLIENT, MouseOffsetY, int, 0x11995C) // Updated 1.13c
VARPTR(D2CLIENT, MouseOffsetX, int, 0x119960) // Updated 1.13c
VARPTR(D2CLIENT, Divisor, int, 0xF16B0) // Updated 1.13c
VARPTR(D2CLIENT, yShake, int, 0x10B9DC) // Updated 1.13c
VARPTR(D2CLIENT, GameInfo, GameStructInfo *, 0x11B980); // Updated 1.13c
VARPTR(D2CLIENT, Ping, DWORD, 0x119804) // Updated 1.13c
VARPTR(D2CLIENT, Skip, DWORD, 0x119810) // Updated 1.13c
VARPTR(D2CLIENT, FPS, DWORD, 0x11C2AC) // Updated 1.13c
VARPTR(D2CLIENT, WaypointTab, DWORD, 0xFCDD6) // Updated 1.13c
VARPTR(D2CLIENT, xShake, int, 0x11BF00) // Updated 1.13c
VARPTR(D2CLIENT, SelectedInvItem, UnitAny*, 0x11BC38) // Updated 1.13c
VARPTR(D2CLIENT, AutomapMode, int, 0xF16B0)
VARPTR(D2CLIENT, Offset, POINT, 0x11C1F8) // Updated 1.13c
VARPTR(D2CLIENT, FirstAutomapLayer, AutomapLayer *, 0x11C1C0) // Updated 1.13c
VARPTR(D2CLIENT, AutomapLayer, AutomapLayer *, 0x11C1C4) // Updated 1.13c
VARPTR(D2CLIENT, AutomapYPosition, int, 0x11C21C) // Updated 1.13c
VARPTR(D2CLIENT, PlayerUnit, UnitAny *, 0x11BBFC) // Updated 1.13c
VARPTR(D2CLIENT, PlayerUnitList, RosterUnit *, 0x11BC14) // Updated 1.13c
VARPTR(D2CLIENT, QuestTab, DWORD, 0x123395) // Updated 1.13c
VARPTR(D2CLIENT, MouseX, DWORD, 0x11B828)// Updated 1.13c
VARPTR(D2CLIENT, MouseY, DWORD, 0x11B824) // Updated 1.13c
VARPTR(D2CLIENT, MapId, DWORD, 0x11C3BC)// Updated 1.13c
VARPTR(D2CLIENT, AutomapOn, DWORD, 0xFADA8)
VARPTR(D2CLIENT, bWeapSwitch, DWORD, 0x11BC94) // Updated 1.13c 


#define D2CLIENT_PlayerUnit *p_D2CLIENT_PlayerUnit
#define D2CLIENT_Ping *p_D2CLIENT_Ping

#define _D2PTRS_END	p_D2CLIENT_bWeapSwitch