#include <windows.h> 
#include <tchar.h> 
#include "resource.h"

POINTS pt = { 100, 100 };
static int submenu = ID_40001;
static int g_curoption = 1;

void option1(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	TCHAR temp[128];
	wsprintf(temp, TEXT("Scan Code : %d\nVirtual Key Code : %d"), (lParam >> 16 & 0x00FF), wParam);
	//	lParam �� 16~23��Ʈ�� ��ĵ�ڵ� ���� �ִ�.
	//	lParam = 0x00'00'0000 �ڸ��� �ִµ� 0x00FF0000�� &��Ʈ ������ �ϸ� ���� �� �ִ�.
	MessageBox(hwnd, temp, TEXT(""), MB_OK);
	//	�̰� ����� �� �ҹ��� ��� ���� �Ȱ���. a�� 30,65 A�� 30,65
	//	���� Ű�ڵ�� wParam�� ��� ����ִ�. �׳� �״�� �����
	//	���� Ű�ڵ�� �ý��ۿ� ������ Ű���忡 ������� Ű�� �Է¹ޱ����� ��
}

void option2(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	
	switch (wParam)
	{
	case VK_LEFT: pt.x -= 10; break;
	case VK_RIGHT: pt.x += 10; break;
	case VK_UP: pt.y -= 10; break;
	case VK_DOWN: pt.y += 10; break;
	}	//�� Ű�� ���� ��ǥ�� �����Ѵ�.
	HDC hdc = GetDC(hwnd);
	TextOut(hdc, pt.x, pt.y, TEXT("%"), 1);	//DC �ڵ�,	��ǥx, ��ǥy,	���ڿ�,	����
	ReleaseDC(hwnd, hdc);
}

void option3(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	if ((wParam == VK_F1) && (GetKeyState(VK_CONTROL)) & 0xFF00)
		//GetKeyState�� ����� 0x00FF & ������ ����� ��ۿ��θ� ����. Ű�� �ѹ� ������ ���ٸ� On ���� �ѹ��� ������ ���� Off ����
		//GetKeyState�� ����� 0xFF00 & ������ ����� ���� ���ȴ����� ���θ� ����.
	{
		MessageBox(hwnd, TEXT("CTRL + F1"), TEXT(""), MB_OK);
	}
	//GetKeyState�� ����� 4������.	0x0000, 0x0001,0x8000,0x8001
	//�ֻ��� ��Ʈ�� 1�̸� �������� 0�̸� �ȴ�������
	//������ ��Ʈ�� 1�̸� ��� ON  0�̸� ��� OFF ����
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITMENUPOPUP: {
		HMENU hMenu = (HMENU)wParam;
		CheckMenuItem(hMenu, ID_40001, submenu == ID_40001 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_40002, submenu == ID_40002 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_40003, submenu == ID_40003 ? MF_CHECKED : MF_UNCHECKED);
		return 0;
	}
	case WM_COMMAND:
		switch ((wParam)) {
		case ID_40001: submenu = ID_40001;  g_curoption = 1; break;
		case ID_40002: submenu = ID_40002;  g_curoption = 2; break;
		case ID_40003: submenu = ID_40003;  g_curoption = 3; break;
		}
		return 0;
	case WM_KEYDOWN:	//�ƹ�Ű�� ������ ���
	{
		switch (g_curoption)
		{
		case 1:
			option1(hwnd, wParam, lParam); break;
		case 2:
			option2(hwnd, wParam, lParam); break;
		case 3:
			option3(hwnd, wParam, lParam); break;
		default: break;
		}
	}
	return 0;
	case WM_CHAR:	//���� WM_KEYDOWN �޽����� WinMain�� TranslateMessage �Լ��� ���޵Ǹ� WM_CHAR �޽����� ������
		//WM_CHAR �޽����� wParam���� ASCII�ڵ尡 �������,	Caps, NumLock, ����Ű�� ����Ű�� �ƴϹǷ� WM_CHAR�� �������� ����
	{
		TCHAR buf[128];
		wsprintf(buf, TEXT("Character Code : %d"), wParam);	//��� ��,�ҹ��ڰ� �ٸ��� �����Եȴ� ASCII�ϱ�
		MessageBox(hwnd, buf, TEXT(""), MB_OK);
	}
	return 0;

	//WM_CHAR : ����Ű
	//WM_KEYDOWN : ���Ű
	//WM_KEYDOWN : ����Ű�� ���ʿ����� �߻�!

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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = 0;

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