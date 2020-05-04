#ifndef D2INTERCEPTS_H
#define D2INTERCEPTS_H

#include "D2Structs.h"

extern CArrayEx <POINT, POINT> DrawPath;

void GameDraw_Intercept();
void GamePacketReceived_Intercept();

#endif