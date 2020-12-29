//drawtype.h
#include <Windows.h>

typedef struct tagDRAWTYPE
{
	int type;	//1. rect	2. ellipse
	POINT pt;	//좌표값
	COLORREF color;	//색상
	int penwidth;	//선 두께
}DRAWTYPE;

void DrawInit(DRAWTYPE *type);