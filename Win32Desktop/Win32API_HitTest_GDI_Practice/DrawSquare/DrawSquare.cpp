#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;	//마우스 시작점과 끝점의 포지션

	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		start.x = 10; start.y = 10;
		end = MAKEPOINTS(lParam);	//시작점과 끝점은 L BT DOWN 시점의 마우스 좌표
		SetCapture(hwnd);	//마우스 캡쳐 설정
		HDC hdc = GetDC(hwnd);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));	//투명색 브러쉬로 변경
		Rectangle(hdc, start.x, start.y, end.x, end.y);	//첫번째 사각형을 그림(이전좌표 사각형)
		ReleaseDC(hwnd, hdc);
	}
	return 0;
	case WM_LBUTTONUP:
	{
		if (GetCapture() == hwnd)	//hwnd 핸들에서 마우스 캡쳐중일때만 다음을 수행
		{
			ReleaseCapture();	//마우스 캡쳐 해제
			HDC hdc = GetDC(hwnd);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));	//투명색 브러쉬로 변경
			Rectangle(hdc, start.x, start.y, end.x, end.y);
			ReleaseDC(hwnd, hdc);
		}
	}
	return 0;

	case WM_MOUSEMOVE:
	{
		if (GetCapture() == hwnd) //hwnd 핸들에서 마우스 캡쳐중일때만 다음을 수행
		{
			POINTS pt = MAKEPOINTS(lParam);	//마우스를 움직인 시점의 좌표를 대입
			HDC hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOTXORPEN);	//그리기모드 : XOR연산에 의한것의 반전
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			HPEN pen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
			HPEN oldpen = (HPEN)SelectObject(hdc, pen);
			Rectangle(hdc, start.x, start.y, end.x, end.y);	//첫번째 사각형을 그림(이전좌표 사각형)
			Rectangle(hdc, start.x, start.y, pt.x, pt.y);	//두번째 사각형을 그림(현재좌표 사각형)
			
			end = pt;
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