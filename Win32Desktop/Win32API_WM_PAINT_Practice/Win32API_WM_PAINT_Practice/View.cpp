//view.cpp
#include "drawtype.h"	// ��������� ����� h���Ͽ� ��Ŭ����ϸ� �ߺ������� �ٹ��Ѵ�. cpp�� ��Ŭ����ص� ��������.
#include "view.h"

void view_ShapePrint(HDC hdc, vector<DRAWTYPE> *g_veclist)
{
	for (int i = 0; i < (int)g_veclist->size(); i++)
	{
		DRAWTYPE dt = (*g_veclist)[i];	//���������ؾ� ���ʿ� �迭�� �����Ѵ�. ���� g_veclist�� �������� ���� �ε����� ã�´�.
		
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
	wsprintf(buf, TEXT("���尳�� : %2d ��    |    (%4d, %4d)"), size,x,y);
	SetWindowText(hwnd, buf);
}