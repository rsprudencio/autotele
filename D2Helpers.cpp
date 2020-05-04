#include "injection.h"
#include <fstream>
#include <stdio.h>

void PrintText(DWORD Color, char *szText, ...)
{
	if (cMessages)
		if (GameReady())
		{
			char szBuffer[152] = {0};
			va_list Args;
			va_start(Args, szText);
			vsprintf_s(szBuffer, 152, szText, Args);
			va_end(Args);
			wchar_t Buffer[0x130];
			MultiByteToWideChar(0, 1, szBuffer, 152, Buffer, 304);
			D2CLIENT_PrintGameString(Buffer, Color);
		}
}

int GetSkill(WORD wSkillId)
{
	if (!D2CLIENT_GetPlayerUnit())
		return 0;

	for (Skill *pSkill = D2CLIENT_GetPlayerUnit()->pInfo->pFirstSkill; pSkill; pSkill = pSkill->pNextSkill)
		if (pSkill->pSkillInfo->wSkillId == wSkillId)
			return 1; //D2COMMON_GetSkillLevel(D2CLIENT_GetPlayerUnit(), pSkill, TRUE);

	return 0;
}

bool SetSkill(WORD wSkillId, bool Left)
{
	if (!D2CLIENT_GetPlayerUnit())
		return 0;

	BYTE PutSkill[9] = {0x3c, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF};
	if (GetSkill(wSkillId))
	{
		*(WORD *)&PutSkill[1] = wSkillId;
		if (Left)
			*(BYTE *)&PutSkill[4] = 0x80;
		D2NET_SendPacket(9, 0, PutSkill);
	}
	else
		return 0;

	return 1;
}

BOOL GameReady(VOID)
{
	if (VALIDPTR(D2CLIENT_GetPlayerUnit())) // && !*p_D2WIN_FirstControl)  <- bug do chat maldito
		if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pInventory))
			if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath))
				if (D2CLIENT_GetPlayerUnit()->pPath->xPos)
					if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1))
						if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2))
							if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel))
								if (D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel->dwLevelNo)
									if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pAct))
										return TRUE;
	return FALSE;
}

DWORD GetPlayerArea(VOID)
{
	if (VALIDPTR(D2CLIENT_GetPlayerUnit()))
		if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath))
			if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1))
				if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2))
					if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel))
						return D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel->dwLevelNo;

	return 0;
	//return *p_D2CLIENT_PlayerArea;
}

Level *GetLevel(DWORD dwLevelNo)
{
	for (Level *pLevel = D2CLIENT_GetPlayerUnit()->pAct->pMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
		if (pLevel->dwLevelNo == dwLevelNo)
			return pLevel;

	return D2COMMON_GetLevel(D2CLIENT_GetPlayerUnit()->pAct->pMisc, dwLevelNo);
}

bool IsTownLevel(int nLevel)
{
	if (nLevel == MAP_A1_ROGUE_ENCAMPMENT ||
		nLevel == MAP_A2_LUT_GHOLEIN ||
		nLevel == MAP_A3_KURAST_DOCKS ||
		nLevel == MAP_A4_THE_PANDEMONIUM_FORTRESS ||
		nLevel == MAP_A5_HARROGATH)
		return TRUE;
	return FALSE;
}

// Getting Distance from units.
DWORD GetDistance(DWORD x1, DWORD y1, DWORD x2, DWORD y2)
{
	return (DWORD)sqrt((double)((((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)))));
}

DWORD GetDistanceSquared(DWORD x1, DWORD y1, DWORD x2, DWORD y2)
{
	return (DWORD)sqrt((double)(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))));
}

DWORD GetTileLevelNo(Room2 *lpRoom2, DWORD dwTileNo)
{
	for (RoomTile *pRoomTile = lpRoom2->pRoomTiles; pRoomTile; pRoomTile = pRoomTile->pNext)
	{
		if (*(pRoomTile->nNum) == dwTileNo)
			return pRoomTile->pRoom2->pLevel->dwLevelNo;
	}

	return NULL;
}

bool is_telethread_running()
{
	DWORD exitCode;
	if (GetExitCodeThread(TeleThread, &exitCode))
		if (exitCode == STILL_ACTIVE)
		{
			// PrintText(FONTCOLOR_WHITE, "Teleport still running, bailing out!");
			return true;
		}

	return false;
}

void start_telethread(DWORD arg)
{
	if (is_telethread_running())
		TerminateThread(TeleThread, 0);

	TeleThread = CreateThread(0, 0, ManageTeleThread, (LPVOID)arg, 0, 0);
}

int bad_txtfileno[] = {580};

void dumpObjects()
{
	Level *pLevel;
	std::ofstream file;
	bool bAddedRoom = false;
	bool stoploop = false;
	char newentry[] = "------------------------------";

	PrintText(FONTCOLOR_WHITE, "Dumping objects in current level to dump.log");

	file.open("./dump.log", std::ios::out | std::ios::app);
	if (file.fail())
	{
		PrintText(FONTCOLOR_RED, "dumpObjects: Failed to open dump.log");
		return;
	}

	file << newentry << std::endl;

	pLevel = GetLevel(GetPlayerArea());
	if (!VALIDPTR(pLevel))
	{
		PrintText(FONTCOLOR_RED, "dumpObjects: Invalid pLevel");
		file << "dumpObjects: Invalid pLevel" << std::endl;
		return;
	}

	if (!VALIDPTR(pLevel->pRoom2First))
	{
		PrintText(FONTCOLOR_RED, "ERROR dumpObjects: Invalid pLevel->pRoom2First");
		file << "ERROR dumpObjects: Invalid pLevel->pRoom2First" << std::endl;
		return;
	}

	for (Room2 *pRoom = pLevel->pRoom2First; pRoom; pRoom = pRoom->pRoom2Next)
	{
		// bAddedRoom = false;
		// if (!VALIDPTR(pRoom->pPreset) && !VALIDPTR(pRoom->pRoomTiles) && !VALIDPTR(pRoom->pRoom1))
		// {
		// 	D2COMMON_AddRoomData(D2CLIENT_GetPlayerUnit()->pAct, pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, D2CLIENT_GetPlayerUnit()->pPath->pRoom1);
		// 	bAddedRoom = true;
		// }

		for (PresetUnit *pUnit = pRoom->pPreset; pUnit; pUnit = pUnit->pPresetNext)
		{
			char line[512] = {0};
			char unit_txt[128] = "N/A";
			int lvlno = -1;
			bool bad = false;

			for (int i = 0; i < sizeof(bad_txtfileno); i++)
			{
				if (pUnit->dwTxtFileNo == bad_txtfileno[i])
				{
					bad = true;
					break;
				}
			}

			if (pUnit->dwType == UNIT_OBJECT && !bad)
			{
				debug("Trying D2COMMON_GetObjectTxt(%d,%d) pUnit %x ... ", pUnit->dwType, pUnit->dwTxtFileNo, pUnit);
				ObjectTxt *o = D2COMMON_GetObjectTxt(pUnit->dwTxtFileNo);
				if (o)
					strncpy(unit_txt, o->szName, 127);
				debug("SUCCESS!\n");
			}
			else if (pUnit->dwType == UNIT_MONSTER && !bad)
			{
				debug("Trying D2CLIENT_GetMonsterTxt(%d,%d) pUnit %x ... ", pUnit->dwType, pUnit->dwTxtFileNo, pUnit);
				MonsterTxt *m = D2CLIENT_GetMonsterTxt(pUnit->dwTxtFileNo);
				if (m)
					wcstombs(unit_txt, m->szDescriptor, 127);
				debug("SUCCESS!\n");
			}
			// file << "SUCCESS!" << std::endl;

			// // pUnit
			// file << pUnit << pUnit->_1 << ", " << pUnit->dwTxtFileNo << ", " << pUnit->dwPosX << ", " << pUnit->dwPosY << ", " << pUnit->_2 << ", ";
			// file << pUnit->dwType << ", " << unit_txt << ", ";

			// // pRoom
			// file << pRoom << ", " << pRoom->dwPosX << ", " << pRoom->dwPosY << ", " << lvlno;

			// file << std::endl;

			if (VALIDPTR(pRoom->pLevel))
				lvlno = pRoom->pLevel->dwLevelNo;

			_snprintf(line, 512, "pUnit(%x) _1: %x  TxtFileNo: %d\tX: %d\tY: %d\t_2: %8x  Type: %d  ObjTxt: %12s | Room2: %8x  Room2X: %d\tRoom2Y: %d\tdwLevelNo: %x",
					  pUnit, pUnit->_1, pUnit->dwTxtFileNo, pUnit->dwPosX, pUnit->dwPosY, pUnit->_2, pUnit->dwType, unit_txt,
					  pRoom, pRoom->dwPosX, pRoom->dwPosY, lvlno);

			file << line << std::endl;
		}

		// if (bAddedRoom)
		// {
		// 	D2COMMON_RemoveRoomData(D2CLIENT_GetPlayerUnit()->pAct, pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, D2CLIENT_GetPlayerUnit()->pPath->pRoom1);
		// 	bAddedRoom = false;
		// }
	}

	PrintText(FONTCOLOR_WHITE, "Done");
	return;
}

bool chat_closed()
{
	// For some reason, whenever chat is closed, ChatBox points to 0xad5affff
	if (VALIDPTR(p_D2CLIENT_ChatMsg))
		if ((int)*p_D2CLIENT_ChatMsg == 0xad5affff)
			return false;

	return true;
}

LONG WINAPI GameEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN)
	{
		if (GameReady() && chat_closed()) 
		{
			if (wParam == cNextButton)
			{
				start_telethread(GetPlayerArea() * 4 + NEXT);
				return NULL;
			}
			if (wParam == cOtherButton)
			{
				start_telethread(GetPlayerArea() * 4 + OTHER);
				return NULL;
			}
			if (wParam == cPrevButton)
			{
				start_telethread(GetPlayerArea() * 4 + PREV);
				return NULL;
			}
			if (wParam == cWaypointButton)
			{
				start_telethread(GetPlayerArea() * 4 + WAYPOINT);
				return NULL;
			}
			if (wParam == cDebug)
			{
				PrintText(FONTCOLOR_WHITE, "CurX: %d   CurY: %d", D2CLIENT_GetPlayerUnit()->pPath->xPos, D2CLIENT_GetPlayerUnit()->pPath->yPos);
				Level *l = GetLevel(GetPlayerArea());
				PrintText(FONTCOLOR_WHITE, "Lvl _1: %x   _2: %x   _3: %x   _4: %d   _5: %x   _6: %d", l->_1, l->_2, l->_3, l->_4, l->_5, l->_6);
				PrintText(FONTCOLOR_WHITE, "Lvl PosX: %d   PosY: %d   SizeX: %d   SizeY: %d   LvlNo: %x", l->dwPosX, l->dwPosY, l->dwSizeX, l->dwSizeY, l->dwLevelNo);
				PrintText(FONTCOLOR_WHITE, "Lvl *PosX: %d   *PosY: %d   SizeX: %d   SizeY: %d   LvlNo: %x", l->dwPosX * 5, l->dwPosY * 5, l->dwSizeX, l->dwSizeY, l->dwLevelNo);
				PrintText(FONTCOLOR_WHITE, "Room2First: %x   NextLevel: %x   Misc: %x   Seed: %x", l->pRoom2First, l->pNextLevel, l->pMisc, l->dwSeed);
				dumpObjects();
				return NULL;
			}
		}
	}
	return (LONG)CallWindowProcA(oldWNDPROC, hWnd, uMsg, wParam, lParam);
}

void __declspec(naked) __fastcall JoinGame(char *Gamename, char *Password)
{
	__asm {
      push ebx
      push edi

      push 0
      push 0
      lea ebx,dword ptr ss:[edx]
      lea edi,dword ptr ss:[ecx]
      call [D2MULTI_JoinGame_I]

      call [D2MULTI_JoinGame_II]

      mov ecx,0x147b
      call D2LANG_GetLocaleText

      push eax
      xor ebx,ebx
      call [D2MULTI_WaitBox]

      pop edi
      pop ebx
      retn
	}
}