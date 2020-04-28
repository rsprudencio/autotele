//#include "D2Helpers.h"
#include "D2Ptrs.h"
#include "AutoTele.h"
#include "constants.h"
bool ThreadStarted = 0;

wchar_t* AnsiToUnicode(const char* str)
{
        wchar_t* buf = NULL;
        int len = MultiByteToWideChar(CP_ACP, 0, str, -1, buf, 0);
        buf = new wchar_t[len];
        MultiByteToWideChar(CP_ACP, 0, str, -1, buf, len);
        return buf;
}

void myDrawText(const char* szwText, int x, int y, int color, int font) 
{
	wchar_t* text = AnsiToUnicode(szwText);

	DWORD dwOld = D2WIN_SetFont(font);
	D2WIN_DrawText(text, x, y, color, 0);
	D2WIN_SetFont(dwOld);

	delete[] text;
}

VOID ScreenToAutomap(POINT *pPos, INT nX, INT nY) //works
{
	pPos->x = ((nX - nY) / 2 / (*p_D2CLIENT_Divisor)) - (*p_D2CLIENT_Offset).x + 8;
	pPos->y = ((nX + nY) / 4 / (*p_D2CLIENT_Divisor)) - (*p_D2CLIENT_Offset).y - 8;

	if(D2CLIENT_GetAutomapSize())
	{
		--pPos->x;
		pPos->y += 5;
	}
}

void DrawCross(int x, int y, DWORD Color)
{
	char szLines[][2] = {0,-2, 4,-4, 8,-2, 4,0, 8,2, 4,4, 0,2, -4,4, -8,2, -4,0, -8,-2, -4,-4, 0,-2};
	for(int i = 0; i < 12; i++)
		D2GFX_DrawLine(x + szLines[i][0], y + szLines[i][1], x + szLines[i+1][0], y + szLines[i+1][1], Color, -1);
}

void GameDraw()
{
	if(ThreadStarted == 0)
	{
		ThreadStarted = 1;
		TELEHANDLE = CreateThread(0,0,TeleportThread,0,0,0);
	}

	if(*p_D2CLIENT_ScreenSizeX == 800)
		myDrawText("AutoTele 1.4.1", 280, *p_D2CLIENT_ScreenSizeY - 12, 1, 13);
	else
		myDrawText("AutoTele 1.4.1", 200, *p_D2CLIENT_ScreenSizeY - 12, 1, 13);
	if(Path.GetSize() && *p_D2CLIENT_AutomapOn)
	{
		CArrayEx <POINT, POINT> DrawPath;
		POINT Pos;
		ScreenToAutomap(&Pos, D2CLIENT_GetUnitX(D2CLIENT_PlayerUnit) * 32, D2CLIENT_GetUnitY(D2CLIENT_PlayerUnit) * 32);
		DrawPath.Add(Pos, 1);
		for(int i = 0;i<Path.GetSize();i++)
		{
			ScreenToAutomap(&Pos, Path.ElementAt(i).x * 32, Path.ElementAt(i).y * 32);
			DrawPath.Add(Pos, 1);
		}
		for(int i = 0;i<(DrawPath.GetSize()-1);i++)
		{
			D2GFX_DrawLine(DrawPath.ElementAt(i).x,DrawPath.ElementAt(i).y,DrawPath.ElementAt(i+1).x, DrawPath.ElementAt(i+1).y, 97, -1);
			DrawCross(DrawPath.ElementAt(i+1).x, DrawPath.ElementAt(i+1).y, 97);
		}
	}
}

DWORD __fastcall GamePacketReceived(BYTE* data, DWORD dwSize)
{
	if(data[0] == 0x15) 
	{ 
		if(*(DWORD*)&data[2] == D2CLIENT_GetPlayerUnit()->dwUnitId) 
		{
			data[10] = 0;  

			UnitAny* Me = D2CLIENT_GetPlayerUnit();

			if(Me->dwMode == PLAYER_MODE_DEATH || Me->dwMode == PLAYER_MODE_STAND_OUTTOWN ||
					Me->dwMode == PLAYER_MODE_WALK_OUTTOWN || Me->dwMode == PLAYER_MODE_RUN || 
					Me->dwMode == PLAYER_MODE_STAND_INTOWN || Me->dwMode == PLAYER_MODE_WALK_INTOWN ||
					Me->dwMode == PLAYER_MODE_DEAD || Me->dwMode == PLAYER_MODE_SEQUENCE ||
					Me->dwMode == PLAYER_MODE_BEING_KNOCKBACK)
					return TRUE;

				Me->dwFrameRemain = 0;
		}
	}
	return true;
}

void __declspec(naked) GamePacketReceived_Intercept()
{
        __asm
        {
                pop ebp;
                pushad;

                call GamePacketReceived;
                test eax, eax;

                popad;
                jnz OldCode;

                mov edx, 0;

OldCode:
                call D2NET_ReceivePacket_I;

                push ebp;
                ret;
        }
}

void __declspec(naked) GameDraw_Intercept()
{
		__asm
		{
			pushad;
			call GameDraw;
			popad;
			call D2CLIENT_DrawHook_I;
			ret;
		}
}

