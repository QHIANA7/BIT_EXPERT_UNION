#include <windows.h> 
#include <tchar.h> 
#include "resource.h"

static int submenu1 = ID_MENU1_TEST1;	//����޴�1�� �⺻���� test1�ε��� ��
static int submenu2 = ID_MENU2_TEST6;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static HMENU hmenu1 = 0;	//�޴��ڵ� �ӽú���
	switch (msg)
	{
		//���3. API�Լ��� �޴��� ����ϱ� ���ؼ��� SetMenu(������ �ڵ�, �޴� �ڵ�)�� �̿��Ѵ�.

		//�Ʒ��� �������� �޴�����
		//�޴� �ڵ��� ��� ���.1 : GetMenu(�������ڵ�)�� ����ϸ� HMENU�� ��ȯ�Ѵ�.
		//����޴��ڵ��� ��� ��� : GetSubMenu(�޴��ڵ�,pos)�� ����ϸ� ����޴� �ڵ� ��ȯ.
		//�޴� �߰� �ϴ� ��� : AppendMenu(�޴��ڵ�,�÷���,��ID,���ڿ�) BOOL ��ȯ
		//�޴� ���� �ϴ� ��� : DeleteMenu(�޴��ڵ�, ID, �÷���)
	case WM_LBUTTONDOWN:
	{
		if (wParam & MK_CONTROL)
		{
			hmenu1 = GetMenu(hwnd);
			SetMenu(hwnd, 0);	//������ �ڵ��� �޴��ڵ��� 0���� �����ϴ� �Լ�
		}
		else
		{
			HMENU h = GetMenu(hwnd);
			AppendMenu(h, MF_POPUP,40005, TEXT("�߰��޴�"));
			HMENU h1 = GetSubMenu(h, 0);	//���� �ҽ��� ����޴� �ڵ��� ���޾ƿ����ִ�.
			AppendMenu(h1, MF_STRING, 40006, TEXT("BBB"));
			AppendMenu(h1, MF_SEPARATOR, 40007, TEXT(""));
			//�������� �޴��� �������� ��� �޴��� �ٽñ׷�����
			DrawMenuBar(hwnd);	//������ �ڵ��� �޴��� �ٽ� �׸�
		}
	}
		return 0;
	case WM_RBUTTONDOWN:
	{
		if (wParam & MK_CONTROL)
		{
			if (hmenu1 != 0)
			{
				SetMenu(hwnd, hmenu1);
				hmenu1 = 0;
			}
		}
		else
		{
			HMENU h = GetMenu(hwnd);
			HMENU hSub = GetSubMenu(h, 0);
			DeleteMenu(hSub, ID_40002, MF_BYCOMMAND);
			//����޴����� : ����޴��ڵ�, ID, �÷���
		}
	}
	return 0;

	case WM_INITMENUPOPUP:
	{
		HMENU hMenu = (HMENU)wParam;
		CheckMenuItem(hMenu, ID_MENU1_TEST1, submenu1 == ID_MENU1_TEST1 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_MENU1_TEST2, submenu1 == ID_MENU1_TEST2 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_MENU1_TEST3, submenu1 == ID_MENU1_TEST3 ? MF_CHECKED : MF_UNCHECKED);
		//������ �޴� �׸��� üũ���¸� ���� �Ǵ� ������ �����մϴ�.
		//�޴��ڵ�, �޴�ID, ���¼���

		EnableMenuItem(hMenu, ID_MENU2_TEST4, submenu2 == ID_MENU2_TEST4 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST5, submenu2 == ID_MENU2_TEST5 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST6, submenu2 == ID_MENU2_TEST6 ? MF_GRAYED : MF_ENABLED);
		//������ �޴� �׸��� Ȱ��ȭ, ��Ȱ��ȭ �Ǵ� ȸ������ ǥ��
		//�޴��ڵ�, �޴�ID, ���¼���
	}
	return 0;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_MENU1_TEST1:
			SetWindowText(hwnd, TEXT("ID_MENU1_TEST1"));
			submenu1 = ID_MENU1_TEST1;			break;
		case ID_MENU1_TEST2:
			SetWindowText(hwnd, TEXT("ID_MENU1_TEST2"));
			submenu1 = ID_MENU1_TEST2;			break;
		case ID_MENU1_TEST3:
			SetWindowText(hwnd, TEXT("ID_MENU1_TEST3"));
			submenu1 = ID_MENU1_TEST3;			break;
		case ID_MENU2_TEST4:
			SetWindowText(hwnd, TEXT("ID_MENU2_TEST4"));
			submenu2 = ID_MENU2_TEST4;			break;
		case ID_MENU2_TEST5:
			SetWindowText(hwnd, TEXT("ID_MENU2_TEST5"));
			submenu2 = ID_MENU2_TEST5;			break;
		case ID_MENU2_TEST6:
			SetWindowText(hwnd, TEXT("ID_MENU2_TEST6"));
			submenu2 = ID_MENU2_TEST6;			break;
		}
	}
	return 0;
	case WM_CONTEXTMENU:
	{
		HMENU h = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));

		HMENU hSub = GetSubMenu(h, 1);
		//����޴��ڵ��� ��´�. �޴��ڵ�, pos
		POINT pt = { LOWORD(lParam),HIWORD(lParam) };
		
		TrackPopupMenu(hSub, TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, 0);
		//������ ��ġ�� �޴��� ǥ���ϰ� �޴����� �׸� ���� ����
		//����޴��ڵ�, �÷���, x, y, 0, ������ �ڵ�, 0
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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	//���1. Ŭ�����ۼ����� �� �޴��� ����ϱ����ؼ��� lpszMenuName�� MAKEINTRESOURCE(�޴� ID);�� �ؾ��Ѵ�.
	wc.style = 0;

	// 2. ���(������Ʈ����) 
	RegisterClass(&wc);

	// 3. ������ â ����� 
	HMENU hmenu = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU1));//���2
	HWND hwnd = CreateWindowEx(0, // WS_EX_TOPMOST 
		TEXT("first"), // Ŭ���� �� 
		TEXT("Hello"), // ĸ�ǹ� ���� 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,// �ʱ� ��ġ 
		0, 0, // �θ� ������ �ڵ�, �޴� �ڵ� 
		//���2. ������������� �� �޴��� ����ϱ� ���ؼ��� �޴��ڵ鰪�� �Ѱ��ָ�ȴ�.
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