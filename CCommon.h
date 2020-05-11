//////////////////////////////////////////////////////////
// Common.h
//--------------------------------------------------------
// Common algorithms for general uses.
//
// Abin (abinn32@yahoo.com)
//////////////////////////////////////////////////////////

#include <windows.h>

long CalculateDistance(const POINT& pt1, const POINT& pt2);
long CalculateDistance(long x1, long y1, long x2, long y2);
void debug(char fmt[], ...);

#include <fstream>
extern std::ofstream dbg_file;