//////////////////////////////////////////////////////////
// Common.cpp
//--------------------------------------------------------
// Common algorithms for general uses.
//
// Abin (abinn32@yahoo.com)
//////////////////////////////////////////////////////////

#include "injection.h"
#include <fstream>

long CalculateDistance(const POINT& pt1, const POINT& pt2)
{
	return CalculateDistance(pt1.x, pt1.y, pt2.x, pt2.y);
}

long CalculateDistance(long x1, long y1, long x2, long y2)
{
	return (long)::sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

#if 0
void debug(char fmt[], ...)
{
	std::ofstream file;

	file.open("./debug.log", std::ios::out | std::ios::app);
	if (file.fail())
	{
		PrintText(FONTCOLOR_RED, "dumpObjects: Failed to open debug.log");
		return;
	}

    va_list args;
    va_start(args, fmt);
    size_t len;
    char buf[1024];
    len = _vsnprintf(buf, 1024, fmt, args);

	file << buf;
 
    va_end(args);
}
#else
void debug(char fmt[], ...)
{
	return;
}
#endif