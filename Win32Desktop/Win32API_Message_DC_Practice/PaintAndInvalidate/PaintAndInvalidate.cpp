#include <windows.h> 
#include <tchar.h>
#include <vector>
using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static vector<POINTS> ptlist;	//���콺�� ��ǥ ����� ��� ���� ���� ���� ����
	switch (msg)
	{
	case WM_PAINT:	//��ȿȭ������ �߻�������� WM_PAINT�޽���(��ť)�� �ٷ� ���ν����� ���۵ȴ�.
	{
		PAINTSTRUCT ps;	//��ȿȭ������ ������� ����Ұ�� PAINTSTRUCT�� �ʿ��ϴ�.
		HDC hdc = BeginPaint(hwnd, &ps);	//��ȿȭ������ ������� DC �ڵ��� ������� BeginPaint�� �����
		//BeginPaint���� �� ��ȿȭ���� ���ΰ� ��������.
		for (int i = 0; i < (int)ptlist.size(); i++)
		{
			POINTS pt = ptlist[i];	//���Ϳ� ��ϵǾ��ִ� ��ǥ�� �ϳ��� ���ͼ�
			Ellipse(hdc, pt.x, pt.y, pt.x + 50, pt.y + 50);	//�Ű������� �ش��ϴ� Ÿ���� �׷�����.
		}
		EndPaint(hwnd, &ps);	//BeginPaint�� ���� DC�ڵ��� ������ EndPaint�� �����
	}
		return 0;
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);	//���� ���콺�� ��ǥ�� pt�� ����
		//Ÿ��Ʋ�ٿ� ��ǥ ���
		TCHAR str[20];
		wsprintf(str, TEXT("(%d,%d)"), pt.x, pt.y);
		SetWindowText(hwnd, str);	//�������̸�(ĸ�ǹ�)�� �̸� ����

		ptlist.push_back(pt);	//pt���� ���Ϳ� insert
		//������ ��ȿȭ������ ���� ����
		InvalidateRect(hwnd, 0, true);		//true�� ��� ������ �����, false�� ������ �����Ѵ�.

		//==================================
		HDC hdc = GetDC(hwnd);		//Ŭ���̾�Ʈ ������ DC�� ���´�.
		Rectangle(hdc, pt.x, pt.y, pt.x + 50, pt.y + 50);	//�Ű������� �ش��ϴ� Ÿ���� �׷�����.
		ReleaseDC(hwnd, hdc);	//DC�� �����ϴ� ����.
		//==================================
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

	//�̴� ����� ������ �翬�� ������ ����� �ϳ� ���α׷� ����� �ڵ����� �����ȴ�.

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