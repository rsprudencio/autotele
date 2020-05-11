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

#ifdef _DEBUG
std::ofstream dbg_file;
void debug(char fmt[], ...)
{
    va_list args;
    va_start(args, fmt);
    size_t len;
    char buf[1024];
    len = _vsnprintf(buf, 1024, fmt, args);

	dbg_file << buf;
 
    va_end(args);
}
#else
void debug(char fmt[], ...)
{
	return;
}
#endif