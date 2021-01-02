#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		BOOL bPresent = GetSystemMetrics(SM_MOUSEPRESENT);	//마우스 연결 여부
		BOOL bWheel = GetSystemMetrics(SM_MOUSEWHEELPRESENT);	//마우스 휠 존재 여부
		int nBtn = GetSystemMetrics(SM_CMOUSEBUTTONS);	//마우스 버튼의 수
		int scx = GetSystemMetrics(SM_CXSCREEN);	//스크린(해상도) x좌표
		int scy = GetSystemMetrics(SM_CYSCREEN);	//스크린(해상도) y좌표
		TCHAR buf[255];
		wsprintf(buf, TEXT("%s %s is installed. (%d Buttons)\n"),
			(bWheel ? TEXT("Wheel") : TEXT("")), (bPresent ? TEXT("Mouse") : TEXT("No Mouse")), nBtn);

		TCHAR buf2[255];
		wsprintf(buf2, TEXT("Screen Resolution : %d x %d"), scx, scy);
		_tcscat_s(buf, buf2);	// 범용 문자열 연결 함수 buf 에 buf2문자열을 붙임
		MessageBox(hwnd, buf, TEXT(""), MB_OK);
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