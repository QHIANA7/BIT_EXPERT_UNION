#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);
		SetROP2(hdc, R2_NOTXORPEN);	//그리기모드 : XOR연산에 의한것의 반전
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, 10, 10, 100, 100);	//첫번째 사각형을 그림(이전좌표 사각형)
		Rectangle(hdc, 10, 10, 101, 100);	//두번째 사각형을 그림(현재좌표 사각형)

		Rectangle(hdc, 10, 10, 101, 100);	//두번째 사각형을 그림(이전좌표 사각형)
		Rectangle(hdc, 10, 10, 101, 101);	//세번째 사각형을 그림(현재좌표 사각형)

		Rectangle(hdc, 10, 10, 101, 101);	//세번째 사각형을 그림(이전좌표 사각형)
		Rectangle(hdc, 10, 10, 102, 101);	//네번째 사각형을 그림(현재좌표 사각형)

		Rectangle(hdc, 10, 10, 102, 101);	//네번째 사각형을 그림(이전좌표 사각형)
		Rectangle(hdc, 10, 10, 102, 102);	//다섯번째 사각형을 그림(현재좌표 사각형)
		//겹친부분의 XOR결과는 빈공간이지만 NOT에의해 그대로 보존된다. 겹치지 않는 부분은 건드리지 않는다!
		//새로운 좌표쪽의 XOR결과는 ? -> 건드리지 않는다!
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