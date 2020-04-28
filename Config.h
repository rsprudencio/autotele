#ifndef _CONFIG_H
#define _CONFIG_H

#define CONFIG_BOOL 1
#define CONFIG_INT 2
#define CONFIG_STRING 3

struct ConfigEntry {
	char* pSection;
	char* pKey;
	char* pDefault;
	int nType;
	LPVOID nVar;
};

bool readConfig ();
bool getBool(char* pRet);
//VOID setConfig(char* pKey, char* pValue);

extern int cNextButton;
extern int cOtherButton;
extern int cWaypointButton;
extern int cPrevButton;
extern bool cMessages;
extern bool cColdToCave;
extern bool cDrawHook;
extern bool cReceivePacketHook;
extern char szPath[65535];

#endif