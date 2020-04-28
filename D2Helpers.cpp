#include "injection.h"

void PrintText(DWORD Color, char *szText, ...)
{
	if(cMessages)
		if(GameReady())
		{
			char szBuffer[152] = {0};
			va_list Args;
			va_start(Args, szText);
			vsprintf_s(szBuffer,152, szText, Args);
			va_end(Args); 
			wchar_t Buffer[0x130];
			MultiByteToWideChar(0, 1, szBuffer, 152, Buffer, 304);
			D2CLIENT_PrintGameString(Buffer, Color);
		}
}

int GetSkill(WORD wSkillId)
{
	if(!D2CLIENT_GetPlayerUnit()) 
		return 0;

	for(Skill* pSkill = D2CLIENT_GetPlayerUnit()->pInfo->pFirstSkill; pSkill; pSkill = pSkill->pNextSkill)
		if(pSkill->pSkillInfo->wSkillId == wSkillId)
			return 1;//D2COMMON_GetSkillLevel(D2CLIENT_GetPlayerUnit(), pSkill, TRUE);

	return 0;
}

bool SetSkill(WORD wSkillId, bool Left)
{
	if(!D2CLIENT_GetPlayerUnit())
		return 0;
	
	BYTE PutSkill[9] = {0x3c,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
	if(GetSkill(wSkillId))
	{
		*(WORD*)&PutSkill[1] = wSkillId;
		if(Left)
			*(BYTE*)&PutSkill[4] = 0x80;
		D2NET_SendPacket(9,0,PutSkill);
	}
	else return 0;
	
	return 1;
}

BOOL GameReady(VOID)
{
	if(VALIDPTR(D2CLIENT_GetPlayerUnit()) && !*p_D2WIN_FirstControl)
		if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pInventory))
			if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath))
				if(D2CLIENT_GetPlayerUnit()->pPath->xPos)
					if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1))
						if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2))
							if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel))
								if(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel->dwLevelNo)
									if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pAct))
										return TRUE;
	return FALSE;
}

DWORD GetPlayerArea(VOID)
{
	if(VALIDPTR(D2CLIENT_GetPlayerUnit()))
	{
		if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath))
			if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1))
				if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2))
					if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel))
						return D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel->dwLevelNo;
	}
	
	return 0;
	//return *p_D2CLIENT_PlayerArea;
}

Level* GetLevel(DWORD dwLevelNo)
{
	for(Level* pLevel = D2CLIENT_GetPlayerUnit()->pAct->pMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
		if(pLevel->dwLevelNo == dwLevelNo)
			return pLevel;

	return D2COMMON_GetLevel(D2CLIENT_GetPlayerUnit()->pAct->pMisc, dwLevelNo);
}

bool IsTownLevel(int nLevel)
{
	if(nLevel == MAP_A1_ROGUE_ENCAMPMENT ||
		nLevel == MAP_A2_LUT_GHOLEIN || 
		nLevel == MAP_A3_KURAST_DOCKS ||
		nLevel == MAP_A4_THE_PANDEMONIUM_FORTRESS ||
		nLevel == MAP_A5_HARROGATH)
		return TRUE;
	return FALSE;
}

// Getting Distance from units.
DWORD GetDistance(DWORD x1, DWORD y1, DWORD x2, DWORD y2) {
	return (DWORD)sqrt((double)(( ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))))); }

DWORD GetDistanceSquared(DWORD x1, DWORD y1, DWORD x2, DWORD y2) {
 	return (DWORD)sqrt((double)( ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)))); }

DWORD GetTileLevelNo(Room2* lpRoom2, DWORD dwTileNo)
{
	for(RoomTile* pRoomTile = lpRoom2->pRoomTiles; pRoomTile; pRoomTile = pRoomTile->pNext)
	{
		if(*(pRoomTile->nNum) == dwTileNo)
			return pRoomTile->pRoom2->pLevel->dwLevelNo;
	}

	return NULL;
}

LONG WINAPI GameEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*if(uMsg == WM_LBUTTONDOWN)
	{
		if(GameReady())
		{
			if(GetAsyncKeyState(VK_CONTROL)& 0x8000)
			{
				POINT P;
				P.x = *p_D2CLIENT_MouseX;
				P.y = *p_D2CLIENT_MouseY;
				//ScreenToWorld(&P);
				ScreenToAutoMap(&P);
				//ManageTele(XY, P.x, P.y);
				PrintText(1, "Me: %d, %d, click: %d %d, offset: %d, %d", D2CLIENT_GetPlayerUnit()->pPath->xPos,D2CLIENT_GetPlayerUnit()->pPath->yPos, P.x, P.y, (*p_D2CLIENT_Offset).x, (*p_D2CLIENT_Offset).y);
				return NULL;
			}
		}
	}*/
	if(uMsg == WM_KEYDOWN)
	{
		if(GameReady())
		{
			if(wParam == cNextButton && ((lParam &0x4000) == 0))
			{
				Vector next = vVector[GetPlayerArea()*4+NEXT];
				ManageTele(next);
				return NULL;
			}
			if(wParam == cOtherButton && ((lParam &0x4000) == 0))
			{
				Vector other = vVector[GetPlayerArea()*4+OTHER];
				ManageTele(other);
				return NULL;
			}
			if(wParam == cPrevButton && ((lParam &0x4000) == 0))
			{
				Vector prev = vVector[GetPlayerArea()*4+PREV];
				ManageTele(prev);
				return NULL;
			}
			if(wParam == cWaypointButton && ((lParam &0x4000) == 0))
			{
				Vector wp = vVector[GetPlayerArea()*4+WAYPOINT];
				ManageTele(wp);
				return NULL;
			}
			/*if(wParam == VK_NUMPAD4)//temp for testing purpose
			{
				PrintText(FONTCOLOR_GOLD, "%d, %d", D2CLIENT_GetPlayerUnit()->pPath->xPos, D2CLIENT_GetPlayerUnit()->pPath->yPos);
				PrintText(4, "%d", *p_D2CLIENT_PlayerArea);	
				FindPresetUnitXY(NULL, NULL,NULL, GetPlayerArea());
			}*/
		}
		/*else if(TELEHANDLE && TELEHANDLE != INVALID_HANDLE_VALUE)
		{
			TerminateThread(TELEHANDLE, 0);
			CloseHandle(TELEHANDLE);
		}*/
	}
	return (LONG)CallWindowProcA(oldWNDPROC, hWnd, uMsg, wParam, lParam);
}

void __declspec(naked) __fastcall JoinGame(char *Gamename,char *Password)
{
   __asm{
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