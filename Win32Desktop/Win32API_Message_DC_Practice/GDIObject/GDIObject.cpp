#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static POINTS pt;
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);	//무효화영역을 대상으로한 DC핸들 획득 구문
		HBRUSH brush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);	//시스템에 미리 정의된 DKGRAY_BRUSH을 가져와 brush에 대입
		HBRUSH old = (HBRUSH)SelectObject(hdc, brush);
		//SelectObject를 통해 사용 도구를 brush에 저장된 정보로 바꾸고 바로 이전에 썼던 정보는 old에 대입한다.
		Rectangle(hdc, 10, 10, 200, 200);
		//DeleteObject(SelectObject(hdc, old));
		//GetStockObject 등 시스템이 생성한 오브젝트는 소멸할 필요가없다.
		//CreatePen,CreateBrush,CreateFont를 통해만들었다면 소멸해야함.

		HPEN pen = CreatePen(PS_DASH, 1, RGB(255, 145, 164));
		HPEN oldp = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush1 = CreateHatchBrush(HS_DIAGCROSS, RGB(68, 51, 170));
		HBRUSH oldb1 = (HBRUSH)SelectObject(hdc, brush1);
		//여러개의 핸들을 중복 사용할 수 있다.
		Ellipse(hdc, 300, 300, 700, 700);
		DeleteObject(SelectObject(hdc, oldp));
		DeleteObject(SelectObject(hdc, oldb1));

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