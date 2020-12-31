#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		TCHAR str[256];
		wsprintf(str, TEXT("10�� 32�п� ����� ���� KTX��õ-235 �����Դϴ�"));	//���ڿ�
		RECT rt = { 100, 100, 300, 300 };	//���� ����
		HDC hdc = GetDC(hwnd);
		//SetTextAlign(hdc, TA_UPDATECP);
		DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);	//DC�ڵ�, ���ڿ� �ּ�, ���ڿ� ���� (-1 : �ι��� ����), ����, �÷���
		ReleaseDC(hwnd, hdc);
	}
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);	//��ȿȭ������ ���� DC�ڵ��� ȹ���ϴ� �Լ� : ������ �ڵ�,	PAINTSTRUCT �ּ�
		SetTextAlign(hdc, TA_CENTER);	//�ؽ�Ʈ���� ��Ÿ�� ���� : DC�ڵ�,	�ɼ�
		//===================================
		HFONT font = (HFONT)GetStockObject(ANSI_FIXED_FONT);
		HFONT old = (HFONT)SelectObject(hdc, font);
		//===================================
		TextOut(hdc, 200, 60, TEXT("KTX-4010"), _tcslen(TEXT("KTX-4010")));	//DC�ڵ�,	��ǥx,	��ǥy,	���ڿ�,	���ڿ�����
		TextOut(hdc, 200, 80, TEXT("SRT-327"), _tcslen(TEXT("SRT-327")));

		DeleteObject(SelectObject(hdc, old));
		EndPaint(hwnd, &ps);	//��ȿȭ������ DC�ڵ� ������ ���� �Լ� : ������ �ڵ�,	PAINTSTRUCT �ּ�
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