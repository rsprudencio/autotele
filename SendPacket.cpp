#include "injection.h"

bool TeleOnMap(WORD x, WORD y, bool Left);
bool Interact(DWORD UnitId, DWORD UnitType);

bool TeleOnMap(WORD x, WORD y, bool Left)
{
	if(!GameReady())
		return 0;

	if(D2CLIENT_GetPlayerUnit()->pInfo->pRightSkill->pSkillInfo->wSkillId != D2S_TELEPORT)
	{
		PrintText(1, "Aborting teleport, deselected teleport");
		return 0;
	}
	
	return(CastOnMap(x, y, Left));
}

bool CastOnMap(WORD x, WORD y, bool Left)
{
	if(!GameReady())
		return 0;

	LPBYTE aPacket = new BYTE[5];	//create packet
	*(BYTE*)&aPacket[0] = Left ? (BYTE)0x08 : (BYTE)0x0F;	//casting with left or right?
	*(WORD*)&aPacket[1] = x;	//x
	*(WORD*)&aPacket[3] = y;	//y
	D2NET_SendPacket(5, 0, aPacket);

	delete [] aPacket;	//clearing up data

	return 1;
}

bool Interact(DWORD UnitId, DWORD UnitType)
{
	if(!GameReady())
		return 0;

	LPBYTE aPacket = new BYTE[9];
	*(BYTE*)&aPacket[0] = (BYTE)0x13;
	*(DWORD*)&aPacket[1] = UnitType;
	*(DWORD*)&aPacket[5] = UnitId;
	D2NET_SendPacket(9, 1, aPacket);

	delete [] aPacket;

	return 1;
}
