#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		start = MAKEPOINTS(lParam);
		end = start;
		SetCapture(hwnd);	//해당 윈도우 핸들에서 마우스를 캡쳐한다.
	}
		return 0;
	case WM_LBUTTONUP:
	{
		if (GetCapture() == hwnd)	//현재 캡쳐중인 윈도우 핸들이 현재 윈도우 일경우
			ReleaseCapture();	//마우스 캡쳐를 해제, 마우스 입력처리 정상 복원
		HDC hdc = GetDC(hwnd);
		MoveToEx(hdc, start.x, start.y, NULL);
		LineTo(hdc, end.x, end.y);
		ReleaseDC(hwnd, hdc);
	}
	return 0;
	case WM_MOUSEMOVE:
	{
		if (GetCapture() == hwnd)
		{
			HDC hdc = GetDC(hwnd);
			HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 149, 164));
			HPEN oldpen = (HPEN)SelectObject(hdc, pen);
			SetROP2(hdc, R2_NOTXORPEN); //반전
			MoveToEx(hdc, start.x, start.y, NULL);
			LineTo(hdc, end.x, end.y);

			end = MAKEPOINTS(lParam);
			MoveToEx(hdc, start.x, start.y, NULL);
			LineTo(hdc, end.x, end.y);

			DeleteObject(SelectObject(hdc, oldpen));
			ReleaseDC(hwnd, hdc);	
		}
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