//drawtype.h
#include <Windows.h>

typedef struct tagDRAWTYPE
{
	int type;	//1. rect	2. ellipse
	POINT pt;	//��ǥ��
	COLORREF color;	//����
	int penwidth;	//�� �β�
}DRAWTYPE;

void DrawInit(DRAWTYPE *type);