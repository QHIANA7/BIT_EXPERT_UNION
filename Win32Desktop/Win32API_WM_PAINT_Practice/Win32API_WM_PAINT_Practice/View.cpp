//view.cpp
#include "drawtype.h"	// 사용자정의 헤더를 h파일에 인클루드하면 중복문제가 다발한다. cpp에 인클루드해도 문제없다.
#include "view.h"

void view_ShapePrint(HDC hdc, vector<DRAWTYPE> *g_veclist)
{
	for (int i = 0; i < (int)g_veclist->size(); i++)
	{
		DRAWTYPE dt = (*g_veclist)[i];	//역참조를해야 그쪽에 배열이 존재한다. 먼저 g_veclist의 역참조를 한후 인덱스를 찾는다.
		
		HBRUSH br = CreateSolidBrush(dt.color);
		HBRUSH oldbr = (HBRUSH)SelectObject(hdc, br);

		HPEN pn = CreatePen(PS_SOLID, dt.penwidth, RGB(82,119,241));
		HPEN oldpn = (HPEN)SelectObject(hdc, pn);

		if (dt.type == 1)
			Rectangle(hdc, dt.pt.x, dt.pt.y, dt.pt.x + 50, dt.pt.y + 50);
		else if (dt.type == 2)
			Ellipse(hdc, dt.pt.x, dt.pt.y, dt.pt.x + 50, dt.pt.y + 50);
		DeleteObject(SelectObject(hdc, oldbr));
		DeleteObject(SelectObject(hdc, oldpn));
	}
}

void view_WindowTextPrint(HWND hwnd, int size, int x, int y)
{
	TCHAR buf[50];
	wsprintf(buf, TEXT("저장개수 : %2d 개    |    (%4d, %4d)"), size,x,y);
	SetWindowText(hwnd, buf);
}