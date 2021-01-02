#include <windows.h> 
#include <tchar.h> 

void PrintWindowInfo(HWND hwnd)
{
	TCHAR info[1024] = { 0 };
	TCHAR temp[256];
	RECT rt;
	GetClassName(hwnd, temp, 256);	//hwnd �ڵ��� Ŭ�������� temp�� ������
	wsprintf(info, TEXT("Window Class : %s\n"), temp);
	GetWindowText(hwnd, temp, 256);	//hwnd �ڵ��� �������(ĸ�ǹ�)�� temp�� ������
	wsprintf(info + _tcslen(info), TEXT("Window Caption : %s\n"), temp);	// �̰� ����?...
	GetWindowRect(hwnd, &rt);	//hwnd �ڵ��� ���������� rt�� ������
	wsprintf(info + _tcslen(info), TEXT("Window Position : (%d,%d) ~ (%d,%d)\n"), rt.left, rt.top, rt.right, rt.bottom);
	MessageBox(hwnd, info, TEXT("Window Info"), MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		SetCapture(hwnd);	//hwnd �ڵ��� ���콺 ĸ�� ����
		return 0;
	}
	return 0;
	case WM_LBUTTONUP:
	{
		if (GetCapture() == hwnd)	//���� ĸ������ �ڵ��� hwnd �ϰ��
		{
			ReleaseCapture();	//ĸ�ĸ� �����Ѵ�
			POINT pt;
			GetCursorPos(&pt);	//L BT�� �� ���� ��ǥ�� pt�� ����	�� ģ���� ��ũ�� ��ǥ�� ���ɴϴ�.
			HWND hwndDest = WindowFromPoint(pt);	//pt�� (��ũ��)��ǥ�� �ִ� ������ �ڵ��� ��� �Լ��� ����� hwndDest�� ����
			PrintWindowInfo(hwndDest);	//����� ���� �Լ��� �ڵ��� �ѱ��.
		}
	}
	return 0;
	case WM_MOUSEMOVE:	//���콺�� ������ ������
	{
		short xPos, yPos;	//�ӽ� ��ǥ
		TCHAR temp[256];
		xPos = LOWORD(lParam);	//lParam�� �ִ� ��ǥ ������ ���� 16��Ʈ�� ������
		yPos = HIWORD(lParam);
		wsprintf(temp, TEXT("Cursor Position : (%d, %d)"), xPos, yPos);
		SetWindowText(hwnd, temp);	//ĸ�ǹٸ� temp ���ڿ��� ���� ������
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