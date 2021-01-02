#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		BOOL bPresent = GetSystemMetrics(SM_MOUSEPRESENT);	//���콺 ���� ����
		BOOL bWheel = GetSystemMetrics(SM_MOUSEWHEELPRESENT);	//���콺 �� ���� ����
		int nBtn = GetSystemMetrics(SM_CMOUSEBUTTONS);	//���콺 ��ư�� ��
		int scx = GetSystemMetrics(SM_CXSCREEN);	//��ũ��(�ػ�) x��ǥ
		int scy = GetSystemMetrics(SM_CYSCREEN);	//��ũ��(�ػ�) y��ǥ
		TCHAR buf[255];
		wsprintf(buf, TEXT("%s %s is installed. (%d Buttons)\n"),
			(bWheel ? TEXT("Wheel") : TEXT("")), (bPresent ? TEXT("Mouse") : TEXT("No Mouse")), nBtn);

		TCHAR buf2[255];
		wsprintf(buf2, TEXT("Screen Resolution : %d x %d"), scx, scy);
		_tcscat_s(buf, buf2);	// ���� ���ڿ� ���� �Լ� buf �� buf2���ڿ��� ����
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