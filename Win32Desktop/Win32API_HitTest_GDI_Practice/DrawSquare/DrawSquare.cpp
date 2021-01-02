#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;	//���콺 �������� ������ ������

	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		start.x = 10; start.y = 10;
		end = MAKEPOINTS(lParam);	//�������� ������ L BT DOWN ������ ���콺 ��ǥ
		SetCapture(hwnd);	//���콺 ĸ�� ����
		HDC hdc = GetDC(hwnd);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));	//����� �귯���� ����
		Rectangle(hdc, start.x, start.y, end.x, end.y);	//ù��° �簢���� �׸�(������ǥ �簢��)
		ReleaseDC(hwnd, hdc);
	}
	return 0;
	case WM_LBUTTONUP:
	{
		if (GetCapture() == hwnd)	//hwnd �ڵ鿡�� ���콺 ĸ�����϶��� ������ ����
		{
			ReleaseCapture();	//���콺 ĸ�� ����
			HDC hdc = GetDC(hwnd);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));	//����� �귯���� ����
			Rectangle(hdc, start.x, start.y, end.x, end.y);
			ReleaseDC(hwnd, hdc);
		}
	}
	return 0;

	case WM_MOUSEMOVE:
	{
		if (GetCapture() == hwnd) //hwnd �ڵ鿡�� ���콺 ĸ�����϶��� ������ ����
		{
			POINTS pt = MAKEPOINTS(lParam);	//���콺�� ������ ������ ��ǥ�� ����
			HDC hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOTXORPEN);	//�׸����� : XOR���꿡 ���Ѱ��� ����
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			HPEN pen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
			HPEN oldpen = (HPEN)SelectObject(hdc, pen);
			Rectangle(hdc, start.x, start.y, end.x, end.y);	//ù��° �簢���� �׸�(������ǥ �簢��)
			Rectangle(hdc, start.x, start.y, pt.x, pt.y);	//�ι�° �簢���� �׸�(������ǥ �簢��)
			
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