//drawtype.cpp
#include "std.h"

void DrawInit(DRAWTYPE *type)
{
	type->color = RGB(0,0,0);
	type->penwidth = 1;
	type->pt.x = 0;
	type->pt.y = 0;
	type->transparentFlag = FALSE;
	type->type = 1;	//	1.rect	2.ellipse
}
