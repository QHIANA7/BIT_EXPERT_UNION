#pragma once
//drawtype.h

typedef struct tagDRAWTYPE
{
	int type;	//1. rect	2. ellipse
	POINT pt;	//��ǥ��
	COLORREF color;	//����
	BOOL transparentFlag;
	int penwidth;	//�� �β�
}DRAWTYPE;

void DrawInit(DRAWTYPE *type);