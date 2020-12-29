#include "drawtype.h"

void DrawInit(DRAWTYPE *type)
{
	type->color = RGB(255, 149, 164);
	type->penwidth = 1;
	type->pt.x = 0;
	type->pt.y = 0;
	type->type = 1;	//	1.rect	2.ellipse
}