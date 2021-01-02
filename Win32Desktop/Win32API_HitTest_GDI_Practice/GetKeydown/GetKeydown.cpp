#include <windows.h> 
#include <tchar.h> 
#include "resource.h"

POINTS pt = { 100, 100 };
static int submenu = ID_40001;
static int g_curoption = 1;

void option1(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	TCHAR temp[128];
	wsprintf(temp, TEXT("Scan Code : %d\nVirtual Key Code : %d"), (lParam >> 16 & 0x00FF), wParam);
	//	lParam 의 16~23비트에 스캔코드 값이 있다.
	//	lParam = 0x00'00'0000 자리에 있는데 0x00FF0000과 &비트 연산을 하면 얻을 수 있다.
	MessageBox(hwnd, temp, TEXT(""), MB_OK);
	//	이게 결과가 대 소문자 모두 값이 똑같다. a도 30,65 A도 30,65
	//	가상 키코드는 wParam에 모두 담겨있다. 그냥 그대로 쓰면됨
	//	가상 키코드는 시스템에 장착된 키보드에 관계없이 키를 입력받기위한 것
}

void option2(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	
	switch (wParam)
	{
	case VK_LEFT: pt.x -= 10; break;
	case VK_RIGHT: pt.x += 10; break;
	case VK_UP: pt.y -= 10; break;
	case VK_DOWN: pt.y += 10; break;
	}	//각 키에 따라 좌표를 증감한다.
	HDC hdc = GetDC(hwnd);
	TextOut(hdc, pt.x, pt.y, TEXT("%"), 1);	//DC 핸들,	좌표x, 좌표y,	문자열,	길이
	ReleaseDC(hwnd, hdc);
}

void option3(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	if ((wParam == VK_F1) && (GetKeyState(VK_CONTROL)) & 0xFF00)
		//GetKeyState의 결과에 0x00FF & 연산의 결과는 토글여부를 본다. 키를 한번 누르고 땠다면 On 상태 한번더 누르고 때면 Off 상태
		//GetKeyState의 결과에 0xFF00 & 연산의 결과는 지금 눌렸는지의 여부를 본다.
	{
		MessageBox(hwnd, TEXT("CTRL + F1"), TEXT(""), MB_OK);
	}
	//GetKeyState의 결과는 4가지다.	0x0000, 0x0001,0x8000,0x8001
	//최상위 비트가 1이면 눌린상태 0이면 안눌린상태
	//최하위 비트가 1이면 토글 ON  0이면 토글 OFF 상태
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITMENUPOPUP: {
		HMENU hMenu = (HMENU)wParam;
		CheckMenuItem(hMenu, ID_40001, submenu == ID_40001 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_40002, submenu == ID_40002 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_40003, submenu == ID_40003 ? MF_CHECKED : MF_UNCHECKED);
		return 0;
	}
	case WM_COMMAND:
		switch ((wParam)) {
		case ID_40001: submenu = ID_40001;  g_curoption = 1; break;
		case ID_40002: submenu = ID_40002;  g_curoption = 2; break;
		case ID_40003: submenu = ID_40003;  g_curoption = 3; break;
		}
		return 0;
	case WM_KEYDOWN:	//아무키나 눌렸을 경우
	{
		switch (g_curoption)
		{
		case 1:
			option1(hwnd, wParam, lParam); break;
		case 2:
			option2(hwnd, wParam, lParam); break;
		case 3:
			option3(hwnd, wParam, lParam); break;
		default: break;
		}
	}
	return 0;
	case WM_CHAR:	//위의 WM_KEYDOWN 메시지가 WinMain의 TranslateMessage 함수에 전달되면 WM_CHAR 메시지를 생성함
		//WM_CHAR 메시지의 wParam에는 ASCII코드가 들어있음,	Caps, NumLock, 방향키는 문자키가 아니므로 WM_CHAR를 생성하지 않음
	{
		TCHAR buf[128];
		wsprintf(buf, TEXT("Character Code : %d"), wParam);	//얘는 대,소문자가 다르게 나오게된다 ASCII니까
		MessageBox(hwnd, buf, TEXT(""), MB_OK);
	}
	return 0;

	//WM_CHAR : 문자키
	//WM_KEYDOWN : 기능키
	//WM_KEYDOWN : 방향키는 이쪽에서만 발생!

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
	wc.style = 0;

	// 2. 등록(레지스트리에) 
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0, // WS_EX_TOPMOST 
		TEXT("first"), // 클래스 명 
		TEXT("Hello"), // 캡션바 내용 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,// 초기 위치 
		0, 0, // 부모 윈도우 핸들, 메뉴 핸들 
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