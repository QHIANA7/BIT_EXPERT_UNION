#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{

	static int	cxClient, cyClient;
	switch (msg)
	{
	case WM_MOVE:
		InvalidateRect(hwnd, 0, TRUE);
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		SetCapture(hwnd);
		return 0;
	case WM_LBUTTONUP:
		if (GetCapture() == hwnd)
			ReleaseCapture();
		return 0;
	case WM_MOUSEMOVE:
		if (GetCapture() == hwnd)
		{
			//IDB_BITMAP1
			HDC hdcDisplay, hdcClient;
			POINT pt;
			GetCursorPos(&pt);
			hdcDisplay = CreateDC(TEXT("DISPLAY"), 0, 0, 0);

			hdcClient = GetDC(hwnd);

			StretchBlt(hdcClient, 0, 0, cxClient, cyClient,
				hdcDisplay, pt.x, pt.y, 100, 100,
				SRCCOPY);
			DeleteDC(hdcDisplay);
			ReleaseDC(hwnd, hdcClient);
		}
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdcDisplay, hdcClient;
		hdcDisplay = CreateDC(TEXT("DISPLAY"), 0, 0, 0);
		hdcClient = BeginPaint(hwnd, &ps);
		BitBlt(hdcClient,
			0, 0, cxClient, cyClient,	//기준점
			hdcDisplay, 0, 0, SRCCOPY);	//시작점	SRCCOPY는 원본을 복사하겠다는 뜻
		DeleteDC(hdcDisplay);

		EndPaint(hwnd, &ps);
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