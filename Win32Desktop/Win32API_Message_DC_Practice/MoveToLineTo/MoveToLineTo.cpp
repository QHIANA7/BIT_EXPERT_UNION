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
			HPEN old = (HPEN)SelectObject(hdc, pen);	//SelectObject�� ���� pen�� ����ٸ� ������ ������ old�� ��ȯ�Ѵ�.
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
	// 1. ������ Ŭ���� ����� 
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

	// 2. ���(������Ʈ����) 
	RegisterClass(&wc);

	// 3. ������ â ����� 
	HWND hwnd = CreateWindowEx(0, // WS_EX_TOPMOST 
		TEXT("first"), // Ŭ���� �� 
		TEXT("Hello"), // ĸ�ǹ� ���� 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,// �ʱ� ��ġ 
		0, 0, // �θ� ������ �ڵ�, �޴� �ڵ� 
		hInst, // WinMain�� 1��° �Ķ���� (exe �ּ�) 
		0); // ���� ���� 

	// 4. ������ �����ֱ� 
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