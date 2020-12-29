//handler.cpp
//이것을 왜만들었냐면 메시지 핸들러라는 기능이 있는데
//메시지 핸들러 : 메시지를 처리하는 함수
//WM_CREATE <- 이런걸 메시지라고 하는데, 이게 OnCreate 등으로 대응된다.
//WM_LBUTTONDOWN -> OnLButtonDown

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include "handler.h"
#include "drawtype.h"
#include "view.h"
#include "resource.h"
using namespace std;

extern vector<DRAWTYPE> g_veclist;
extern DRAWTYPE g_curdata;
static int submenu1 = ID_40001;
static int submenu2 = ID_40003;
LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	DrawInit(&g_curdata);
	return 0;	//핸들러 함수는 성공시 0을 리턴한다고 했었다.
}

LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;	
}

LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	g_curdata.pt.x = LOWORD(lParam);	//LOWORD는 lParam의 하위 16비트 값을 가져오는것.
	g_curdata.pt.y = HIWORD(lParam);	//HIWORD는 상위16비트를 가져옴
	//=================================
	if (wParam & MK_CONTROL)
	{
		if ((int)g_veclist.size() > 0)
			g_veclist.pop_back();
	}
	else
	{
		RECT rt;
		GetWindowRect(hwnd, &rt);
		g_curdata.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		//g_curdata.penwidth = rand() % 10;
		//g_curdata.pt.x = //rand() % (rt.right - rt.left);
		//g_curdata.pt.y = rand() % (rt.bottom - rt.top);
		g_veclist.push_back(g_curdata);
	}
	InvalidateRect(hwnd, 0, TRUE);	//TRUE와 FALSE의 결과가 똑같다.
			//다만 지우는 기능을 사용할시 TRUE로 해야 지워지는게 보인다.
	//=================================
	return 0;
}
LRESULT OnWM_Initmenupopup(HWND hwnd, WPARAM wParam, LPARAM lParam){
	HMENU hMenu = (HMENU)wParam;
	CheckMenuItem(hMenu, ID_40001, submenu1 == ID_40001 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40002, submenu1 == ID_40002 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40003, submenu2 == ID_40003 ? MF_CHECKED : MF_UNCHECKED);	
	CheckMenuItem(hMenu, ID_40004, submenu2 == ID_40004 ? MF_CHECKED : MF_UNCHECKED);	
	CheckMenuItem(hMenu, ID_40005, submenu2 == ID_40005 ? MF_CHECKED : MF_UNCHECKED);
	
	return 0;
}
LRESULT OnWM_Command(HWND hwnd, WPARAM wParam, LPARAM lParam){
	switch ((wParam)){
	case ID_40001: submenu1 = ID_40001;  g_curdata.type = 1; break;
	case ID_40002: submenu1 = ID_40002;  g_curdata.type = 2; break;
	case ID_40003: submenu2 = ID_40003;  g_curdata.penwidth = 1; break;
	case ID_40004: submenu2 = ID_40004;  g_curdata.penwidth = 3; break;
	case ID_40005: submenu2 = ID_40005;  g_curdata.penwidth = 5; break;
	}
	return 0;
}

LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam)

{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	//==============================
	view_ShapePrint(hdc, &g_veclist);	//view소스의 vector에 저장된 모든 그림을 출력하게 하자.
	view_WindowTextPrint(hwnd, g_veclist.size(),g_curdata.pt.x,g_curdata.pt.y);
	//==============================
	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT OnKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case '1':
	case VK_NUMPAD1:
		SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_40003, 0), NULL);
		break;
	case '3':
	case VK_NUMPAD3:
		SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_40004, 0), NULL);
		break;
	case '5':
	case VK_NUMPAD5:
		SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_40005, 0), NULL);
		break;
	case 'R':
		SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_40001, 0), NULL);
		break;
	case 'E':
		SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_40002, 0), NULL);
		break;
	case VK_F1:
		g_veclist.clear();
		//지웠기 때문에 화면갱신이 필요하다.
		InvalidateRect(hwnd, 0, TRUE);
		break;
	}
	return 0;
}

LRESULT OnMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//OnLButtonDown(hwnd, wParam, lParam);
	return 0;
}