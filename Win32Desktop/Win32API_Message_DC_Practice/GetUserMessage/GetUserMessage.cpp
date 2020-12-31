#include <Windows.h>
#include <tchar.h>

#define WM_MYMESSAGE WM_USER+100	//����� ���� �޽��� WM_USER�̸��� �̹� ����� �޽��� �̱⶧���� ��������
#define WM_MYMESSAGE1 WM_USER+200	//�ű⿡ +���� �ϸ� ��ĥ���� ���� ��������� �޽����� ����ϱ⿡ �˸´�.

void FindTest01(HWND hwindow)
{
	HWND hwnd = FindWindow(0, TEXT("����"));	//�������ڵ��� ã�� �Լ� :	Ŭ���� ��,	������ �̸�
	SetWindowText(hwindow, TEXT("Hello"));	//������ �̸�(ĸ�ǹ�)�� ������ �ٲٴ� �Լ� : �������ڵ�,	���ڿ�

	if (hwnd == 0)	//FindWindow�� ������ �ڵ��� ã�� ���ߴٸ� 0�� ��ȯ�Ѵ�. ã�Ҵٸ� �� ������ �ڵ��� ��ȯ�Ѵ�.
	{
		MessageBox(hwindow, TEXT("���� �ڵ� ȹ�濡 �����߽��ϴ�. ���Ⱑ �����ִ��� Ȯ���ϼ���"), TEXT("�˸�"), MB_OK | MB_ICONERROR);
		//���� �޽����ڽ���� �Լ� : ������ �ڵ�,	�޽��� ����,	�޽����ڽ� ����,	�ɼǵ�
		return;
	}
	else	//FindWindow�Լ��� ������ �ڵ��� ã���� ���
	{
		TCHAR temp[20];	//���� ���ڿ� �����
		wsprintf(temp, TEXT("���� �ڵ� : %d"), hwnd);	//ù��° �Ű������� ����ϴ� �����Լ� :	���� ����,	��� ����(ǥ��printf)
		MessageBox(hwindow, temp, TEXT("�˸�"), MB_OK);	//�޽����ڽ� ����
		return;
	}
}

void MoveTest01(HWND hwindow)
{
	HWND hwnd = FindWindow(0, TEXT("����"));
	SetWindowText(hwindow, TEXT("Hello"));

	if (hwnd == 0)
	{
		MessageBox(hwindow, TEXT("���� �ڵ� ȹ�濡 �����߽��ϴ�. ���Ⱑ �����ִ��� Ȯ���ϼ���"), TEXT("�˸�"), MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		TCHAR temp[256];
		ShowWindow(hwnd, SW_SHOW);	//�����츦 ǥ���ϴ� �Լ� : ������ �ڵ�,	�ɼ�
		MoveWindow(hwnd, 100, 300, 300, 300, TRUE);	//�����츦 �̵� �Ǵ� ũ������ �ϴ� �Լ� : ������ �ڵ�,	��ǥ, ũ��, ����¿���
		wsprintf(temp, TEXT("���� â �̵� : X = 100  Y = 100 / W = 300  H = 300"), hwnd);
		MessageBox(hwindow, temp, TEXT("�˸�"), MB_OK);
		return;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MYMESSAGE://����� ���� �޽��� ó�� �κ�
		TCHAR str[30];
		wsprintf(str, TEXT("%d+%d ������ ����� �߽�ó�� ��ȯ�߽��ϴ�."), wParam, lParam);
		MessageBox(hwnd, str, TEXT("WM_MYMESSAGE Received"), MB_OK);
		return wParam + lParam;	//�� ���� ���� �޽����� ȣ���� �κ����� ��ȯ�Ѵ�. ��ȯ�ΰ� ����ŷ �Լ��� ��� �ǹ�X
	case WM_MYMESSAGE1:
		TCHAR str1[30];
		wsprintf(str1, TEXT("�߽�ó�κ��� %d ����� �޾Ҵٰ� ���� �޾ҽ��ϴ�."), wParam);
		MessageBox(hwnd, str1, TEXT("WM_MYMESSAGE1 Received"), MB_OK);
		return wParam + lParam;	//�� ���� ���� �޽����� ȣ���� �κ����� ��ȯ�Ѵ�. ��ȯ�ΰ� ����ŷ �Լ��� ��� �ǹ�X
	case WM_LBUTTONDOWN:
		//MessageBox(hwnd, TEXT("���콺 �޹�ư ����"), TEXT("�˸�"), MB_OK);
		FindTest01(hwnd);
		return 0;
	case WM_RBUTTONDOWN:
		MoveTest01(hwnd);
		return 0;
	case WM_CREATE:	
		return 0;
	case WM_DESTROY: 
		PostQuitMessage(0); 
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	// 1. ������ �ۼ�
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("first");
	wc.lpszMenuName = 0;
	wc.style = 0;

	// 2. Ŭ���� ���
	RegisterClass(&wc);

	// 3. ������ ����
	HWND hwnd = CreateWindowEx(0,
		TEXT("first"), TEXT("Hello"),	//	Ŭ������ / ĸ�ǹٸ�
		WS_OVERLAPPEDWINDOW,	// ������ ����
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	//x,y, �ʺ�, ���� //CW_USEDEFAULT�� �����Ȱ�� y�� ũ��, nHeight�� ���õȴ�
		0, 0,	//�θ� ������ �ڵ�, �޴� �ڵ�
		hInst,	//�ν��Ͻ�
		0);	//��������

	// 4. ������ ���
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. �޽��� ����
	MSG msg;

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}