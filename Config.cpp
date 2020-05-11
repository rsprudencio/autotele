#include "injection.h"

int cNextButton = 0;
int cOtherButton = 0;
int cWaypointButton = 0;
int cPrevButton = 0;
int cDebug = 0;

bool cMessages = 1;
bool cColdToCave = 0;

bool cDrawHook = 0;
bool cReceivePacketHook = 0;

char szPath[65535] = "";

ConfigEntry pEntries[] = {

	{"Keys", "Next", "96", CONFIG_INT, &cNextButton},
	{"Keys", "Other", "97", CONFIG_INT, &cOtherButton},
	{"Keys", "Waypoint", "98", CONFIG_INT, &cWaypointButton},
	{"Keys", "Prev", "99", CONFIG_INT, &cPrevButton},
#ifdef _DEBUG
	{"Keys", "Debug", "100", CONFIG_INT, &cDebug},
#endif
	{"Settings", "DisplayMessages", "1", CONFIG_BOOL, &cMessages},
	{"Settings", "ColdToCave", "0", CONFIG_BOOL, &cColdToCave},

	{"Hooks", "DrawHook", "1", CONFIG_BOOL, &cDrawHook},
	{"Hooks", "ReceivePacketHook", "0", CONFIG_BOOL, &cReceivePacketHook}
};

bool readConfig ()
{
	char pFile[65535];
	strncpy_s(pFile, sizeof(pFile), szPath, sizeof(pFile));
	strcat_s(pFile, "\\AutoTele.ini");
	
	char nRet[65535];
	for (int i = 0; i < ArraySize(pEntries); i++)
	{
		GetPrivateProfileString(pEntries[i].pSection, pEntries[i].pKey, pEntries[i].pDefault, nRet, sizeof(nRet), pFile);
		if (pEntries[i].nType == CONFIG_BOOL)
			*(PBOOL)pEntries[i].nVar = getBool(nRet);
		else if (pEntries[i].nType == CONFIG_INT)
			*(PINT)pEntries[i].nVar = atoi(nRet);
		else if (pEntries[i].nType == CONFIG_STRING)
			strncpy_s((PCHAR)pEntries[i].nVar, sizeof((PCHAR)pEntries[i].nVar), nRet, sizeof(nRet));
	}
	return true;
}

bool getBool(char* pLower)
{
	if ((_stricmp(pLower, "1") == 0) || (_stricmp(pLower, "y") == 0) || (_stricmp(pLower, "yes") == 0) || (_stricmp(pLower, "true") == 0))
		return true;
	return false;
}

/*VOID setConfig(char* pKey, char* pValue)
{
	if (strlen(pKey) == 0 || strlen(pValue) == 0)
		return;

	for (int i = 0; i < ArraySize(pEntries); i++)
	{
		if (_strcmpi(pKey, pEntries[i].pKey) == 0)
		{
			if (pEntries[i].nType == CONFIG_BOOL)
			{
				*(PBOOL)pEntries[i].nVar = getBool(pValue);
				Print("�c4[mMap]: �c0%s is now set to %i", pEntries[i].pKey, ((*(PBOOL)pEntries[i].nVar) ? "true" : "false"));
			} else if (pEntries[i].nType == CONFIG_INT) {
				*(PINT)pEntries[i].nVar = atoi(pValue);
				Print("�c4[mMap]: �c0%s is now set to %d", pEntries[i].pKey, *(PINT)pEntries[i].nVar);
			} else if (pEntries[i].nType == CONFIG_STRING) {
				strncpy_s((PCHAR)pEntries[i].nVar, sizeof((PCHAR)pEntries[i].nVar), pValue, sizeof(pValue));
				Print("�c4[mMap]: �c0%s is now set to %s", pEntries[i].pKey, (PCHAR)pEntries[i].nVar);
			}
				
		}
	}
}*/