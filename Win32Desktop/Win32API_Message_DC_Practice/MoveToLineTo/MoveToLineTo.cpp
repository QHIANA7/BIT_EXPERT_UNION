#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static boolean drawon = FALSE;
	static boolean eraseon = FALSE;
	static POINTS pt;
	switch (msg)
	{
	case WM_RBUTTONUP:	eraseon = FALSE;	return 0;
	case WM_LBUTTONUP:	drawon = FALSE;		return 0;
	case WM_RBUTTONDOWN:	eraseon = TRUE;	return 0;
	case WM_LBUTTONDOWN:	drawon = TRUE;		return 0;
	case WM_MOUSEMOVE:
	{	
		POINTS pt1 = MAKEPOINTS(lParam);
		HDC hdc = GetDC(hwnd);
		if (drawon)
		{
			HPEN pen = CreatePen(PS_SOLID, 20, RGB(rand() % 256, rand() % 256, rand() % 256));
			//HPEN pen = (HPEN)GetStockObject(DC_PEN);
			HPEN old = (HPEN)SelectObject(hdc, pen);	//SelectObject를 통해 pen을 들었다면 이전의 설정을 old에 반환한다.
			MoveToEx(hdc, pt.x, pt.y, NULL);
			LineTo(hdc, pt1.x, pt1.y);
			DeleteObject(SelectObject(hdc, old));
			
		}
		else if(eraseon)
		{
			HPEN pen = CreatePen(PS_SOLID, 20, RGB(255, 255, 255));
			HPEN old = (HPEN)SelectObject(hdc, pen);
			MoveToEx(hdc, pt.x, pt.y, NULL);
			LineTo(hdc, pt1.x, pt1.y);
			DeleteObject(SelectObject(hdc, old));
		}
		pt = pt1;
			ReleaseDC(hwnd, hdc);
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