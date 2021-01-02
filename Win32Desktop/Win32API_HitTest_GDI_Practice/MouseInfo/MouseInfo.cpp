#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{

		if (wParam & MK_CONTROL)
		{
			POINT pt = { LOWORD(lParam), HIWORD(lParam) };
			POINT pt1 = pt;

			ClientToScreen(hwnd, &pt);	//Ŭ���̾�Ʈ ��ǥ�� ��ũ�� ��ǥ�� ��ȯ

			TCHAR buf[256];
			wsprintf(buf, TEXT("Ŭ���̾�Ʈ ��ǥ = %d, %d\r\n��ũ�� ��ǥ = %d, %d"), pt1.x, pt1.y, pt.x, pt.y);
			MessageBox(hwnd, buf, TEXT("��ǥ �˸� + CTRL ����"), MB_OK);
		}
		else if (wParam & MK_SHIFT)
		{
			POINTS pt = MAKEPOINTS(lParam);	//SHORT Ÿ�� ������
			POINT pt1 = { LOWORD(lParam), HIWORD(lParam) };	//LONG Ÿ�� ������
			TCHAR buf[100];
			wsprintf(buf, TEXT("SHORT Type Position : (%d,%d)\nLONG Type Position : (%d,%d)"), pt.x, pt.y, pt1.x, pt1.y);
			MessageBox(hwnd, buf, TEXT("L BT DOWN ��ǥ + SHIFT"), MB_OK);
		}
	}
	return 0;
	case WM_RBUTTONDOWN:
	{
		if (wParam & MK_SHIFT)	// & : ��Ʈ ����ũ ���		| : �߰�	&~ : ����
			MessageBox(hwnd, TEXT("R BT + SHIFT"), TEXT("Notice"), MB_OK);
		else if (wParam & MK_CONTROL)
			MessageBox(hwnd, TEXT("R BT + CONTROL"), TEXT("Notice"), MB_OK);	//ALT�� �ȵ�
	}
	return 0;
	case WM_NCRBUTTONDOWN:	//��Ŭ���̾�Ʈ ���������� RBUTTONDOWN �޽��� ó����
		MessageBox(hwnd, TEXT("��Ŭ���̾�Ʈ ���� R BT DOWN"), TEXT("Notice"), MB_OK);
		return 0;

		//Ŀ���� ������,��ưŬ��,��ư���� �� System�� WM_NCHITTEST�޽����� ���ν����� �����Ѵ�.
		//WM_NCHITTEST�� DefWindowProc���� �������� ��� hit_test_code�� wParam�� ��ȯ�Ǿ� �´�.
		//hit_test_code���� Ŀ���� ����ִ����� ����ִ�. �̸� �̿��� hit_test_code�� ���� ����
	case WM_NCHITTEST:
	{
		DWORD code = DefWindowProc(hwnd, msg, wParam, lParam);
		if (code == HTCLIENT && GetKeyState(VK_CONTROL) && GetKeyState(VK_SHIFT) < 0)
			code = HTLEFT;	//Ŭ���̾�Ʈ �������� Ctrl+Shift�� �������� ���� �׵θ��� ���������� ó��

		if (code == HTRIGHT)
			code = HTLEFT;	//DefWindowProc�� ��ȯ�� ����� ��Ŭ���̾�Ʈ ������ ���� �׵θ���� ���� �׵θ��� ���������� ó��
		return code;
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