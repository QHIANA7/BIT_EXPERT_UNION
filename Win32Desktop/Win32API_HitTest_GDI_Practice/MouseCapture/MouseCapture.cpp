#include <windows.h> 
#include <tchar.h> 

void PrintWindowInfo(HWND hwnd)
{
	TCHAR info[1024] = { 0 };
	TCHAR temp[256];
	RECT rt;
	GetClassName(hwnd, temp, 256);	//hwnd 핸들의 클래스명을 temp에 저장함
	wsprintf(info, TEXT("Window Class : %s\n"), temp);
	GetWindowText(hwnd, temp, 256);	//hwnd 핸들의 윈도우명(캡션바)을 temp에 저장함
	wsprintf(info + _tcslen(info), TEXT("Window Caption : %s\n"), temp);	// 이건 뭐지?...
	GetWindowRect(hwnd, &rt);	//hwnd 핸들의 영역정보를 rt에 저장함
	wsprintf(info + _tcslen(info), TEXT("Window Position : (%d,%d) ~ (%d,%d)\n"), rt.left, rt.top, rt.right, rt.bottom);
	MessageBox(hwnd, info, TEXT("Window Info"), MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		SetCapture(hwnd);	//hwnd 핸들의 마우스 캡쳐 시작
		return 0;
	}
	return 0;
	case WM_LBUTTONUP:
	{
		if (GetCapture() == hwnd)	//현재 캡쳐중인 핸들이 hwnd 일경우
		{
			ReleaseCapture();	//캡쳐를 해제한다
			POINT pt;
			GetCursorPos(&pt);	//L BT를 땐 곳의 좌표를 pt에 저장	이 친구는 스크린 좌표로 나옵니다.
			HWND hwndDest = WindowFromPoint(pt);	//pt의 (스크린)좌표에 있는 윈도우 핸들을 얻는 함수를 사용해 hwndDest에 저장
			PrintWindowInfo(hwndDest);	//사용자 정의 함수에 핸들을 넘긴다.
		}
	}
	return 0;
	case WM_MOUSEMOVE:	//마우스를 움직일 때마다
	{
		short xPos, yPos;	//임시 좌표
		TCHAR temp[256];
		xPos = LOWORD(lParam);	//lParam에 있는 좌표 정보중 하위 16비트를 가져옴
		yPos = HIWORD(lParam);
		wsprintf(temp, TEXT("Cursor Position : (%d, %d)"), xPos, yPos);
		SetWindowText(hwnd, temp);	//캡션바를 temp 문자열과 같이 설정함
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
	wc.lpszMenuName = 0; wc.style = 0;

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