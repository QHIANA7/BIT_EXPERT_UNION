#include <windows.h> 
#include <tchar.h> 
#include "resource.h"

static int submenu1 = ID_MENU1_TEST1;	//서브메뉴1은 기본으로 test1인덱스 값
static int submenu2 = ID_MENU2_TEST6;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static HMENU hmenu1 = 0;	//메뉴핸들 임시변수
	switch (msg)
	{
		//방법3. API함수중 메뉴를 등록하기 위해서는 SetMenu(윈도우 핸들, 메뉴 핸들)을 이용한다.

		//아래는 동적으로 메뉴제어
		//메뉴 핸들을 얻는 방법.1 : GetMenu(윈도우핸들)을 사용하면 HMENU를 반환한다.
		//서브메뉴핸들을 얻는 방법 : GetSubMenu(메뉴핸들,pos)를 사용하면 서브메뉴 핸들 반환.
		//메뉴 추가 하는 방법 : AppendMenu(메뉴핸들,플래그,새ID,문자열) BOOL 반환
		//메뉴 삭제 하는 방법 : DeleteMenu(메뉴핸들, ID, 플래그)
	case WM_LBUTTONDOWN:
	{
		if (wParam & MK_CONTROL)
		{
			hmenu1 = GetMenu(hwnd);
			SetMenu(hwnd, 0);	//윈도우 핸들의 메뉴핸들을 0으로 설정하는 함수
		}
		else
		{
			HMENU h = GetMenu(hwnd);
			AppendMenu(h, MF_POPUP,40005, TEXT("추가메뉴"));
			HMENU h1 = GetSubMenu(h, 0);	//현재 소스가 서브메뉴 핸들을 못받아오고있다.
			AppendMenu(h1, MF_STRING, 40006, TEXT("BBB"));
			AppendMenu(h1, MF_SEPARATOR, 40007, TEXT(""));
			//동적으로 메뉴를 수정했을 경우 메뉴를 다시그려야함
			DrawMenuBar(hwnd);	//윈도우 핸들의 메뉴를 다시 그림
		}
	}
		return 0;
	case WM_RBUTTONDOWN:
	{
		if (wParam & MK_CONTROL)
		{
			if (hmenu1 != 0)
			{
				SetMenu(hwnd, hmenu1);
				hmenu1 = 0;
			}
		}
		else
		{
			HMENU h = GetMenu(hwnd);
			HMENU hSub = GetSubMenu(h, 0);
			DeleteMenu(hSub, ID_40002, MF_BYCOMMAND);
			//서브메뉴삭제 : 서브메뉴핸들, ID, 플래그
		}
	}
	return 0;

	case WM_INITMENUPOPUP:
	{
		HMENU hMenu = (HMENU)wParam;
		CheckMenuItem(hMenu, ID_MENU1_TEST1, submenu1 == ID_MENU1_TEST1 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_MENU1_TEST2, submenu1 == ID_MENU1_TEST2 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_MENU1_TEST3, submenu1 == ID_MENU1_TEST3 ? MF_CHECKED : MF_UNCHECKED);
		//지정된 메뉴 항목의 체크상태를 선택 또는 해제로 설정합니다.
		//메뉴핸들, 메뉴ID, 상태설정

		EnableMenuItem(hMenu, ID_MENU2_TEST4, submenu2 == ID_MENU2_TEST4 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST5, submenu2 == ID_MENU2_TEST5 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST6, submenu2 == ID_MENU2_TEST6 ? MF_GRAYED : MF_ENABLED);
		//지정된 메뉴 항목을 활성화, 비활성화 또는 회색으로 표시
		//메뉴핸들, 메뉴ID, 상태설정
	}
	return 0;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_MENU1_TEST1:
			SetWindowText(hwnd, TEXT("ID_MENU1_TEST1"));
			submenu1 = ID_MENU1_TEST1;			break;
		case ID_MENU1_TEST2:
			SetWindowText(hwnd, TEXT("ID_MENU1_TEST2"));
			submenu1 = ID_MENU1_TEST2;			break;
		case ID_MENU1_TEST3:
			SetWindowText(hwnd, TEXT("ID_MENU1_TEST3"));
			submenu1 = ID_MENU1_TEST3;			break;
		case ID_MENU2_TEST4:
			SetWindowText(hwnd, TEXT("ID_MENU2_TEST4"));
			submenu2 = ID_MENU2_TEST4;			break;
		case ID_MENU2_TEST5:
			SetWindowText(hwnd, TEXT("ID_MENU2_TEST5"));
			submenu2 = ID_MENU2_TEST5;			break;
		case ID_MENU2_TEST6:
			SetWindowText(hwnd, TEXT("ID_MENU2_TEST6"));
			submenu2 = ID_MENU2_TEST6;			break;
		}
	}
	return 0;
	case WM_CONTEXTMENU:
	{
		HMENU h = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));

		HMENU hSub = GetSubMenu(h, 1);
		//서브메뉴핸들을 얻는다. 메뉴핸들, pos
		POINT pt = { LOWORD(lParam),HIWORD(lParam) };
		
		TrackPopupMenu(hSub, TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, 0);
		//지정된 위치에 메뉴를 표시하고 메뉴에서 항목 선택 가능
		//서브메뉴핸들, 플래그, x, y, 0, 윈도우 핸들, 0
	}
		return 0;
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPTSTR lpCmdLine, int nShowCmd)
{
	// 1. 윈도우 클래스 만들기 
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	//방법1. 클래스작성과정 중 메뉴를 등록하기위해서는 lpszMenuName에 MAKEINTRESOURCE(메뉴 ID);를 해야한다.
	wc.style = 0;

	// 2. 등록(레지스트리에) 
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기 
	HMENU hmenu = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU1));//방법2
	HWND hwnd = CreateWindowEx(0, // WS_EX_TOPMOST 
		TEXT("first"), // 클래스 명 
		TEXT("Hello"), // 캡션바 내용 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,// 초기 위치 
		0, 0, // 부모 윈도우 핸들, 메뉴 핸들 
		//방법2. 윈도우생성과정 중 메뉴를 등록하기 위해서는 메뉴핸들값을 넘겨주면된다.
		hInst, // WinMain의 1번째 파라미터 (exe 주소) 
		0); // 생성 인자 

			// 4. 윈도우 보여주기 
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	} return 0;
}