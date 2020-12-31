#include <windows.h> 
#include <tchar.h>
#include <math.h>
#define NUM 1000
#define TWOPI (2 * 3.14159)
#define PI 3.14159

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	HDC hdc;
	int i;
	PAINTSTRUCT ps;
	POINT apt[NUM];

	switch (msg)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		InvalidateRect(hwnd, 0, TRUE);
		return 0;
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);
		MoveToEx(hdc, cxClient/2, 0, NULL);
		LineTo(hdc, cxClient/2, cyClient);
		for (i = 0; i < NUM; i++)
		{
			int n = 0;

			//�糡�� -��(-3.14), ��(3.14)�� ����Ų��.
			//NUM�� 1000�̰� â�� 1280x720 ũ�� �� ��
			//i�� 0�� �� ��ǥ�� (0, 360)
			//i�� 250�� �� ��ǥ�� (320, 720)
			//i�� 500�� �� ��ǥ�� (640, 360)
			//i�� 750�� �� ��ǥ�� (960, 0)
			//i�� 1000�� �� ��ǥ�� (1280, 360)

			//sin(x)�� ����� �׻� (-1 ~ 1)�� ������ �츮�� �̸� (720 ~ 0)���� �����ؾ��Ѵ�.
			//(sin(x) - 1)�� �ϸ� (-2 ~ 0)�� ������ ���⿡ -360�� �����ָ� (720 ~ 0)�������ȴ�.
			//(sin(x) - 1)* (-cyClient / 2)�� ���� y��ǥ�� �ȴ�.

			//���� x�� �� ���� ���ؾ��Ѵ�.

			//sin(x) x�� (-�� ~ ��) �� ������ ���´�. �� ���������� i�� (0 ~ 1000)�� ������ �����Ѵ�.
			//i/NUM�� �ϸ� (0 ~ 1)�� �ȴ�. �̰� 2��� ���ִ°� ���ϰڴ�.
			//i/NUM*2�� �ϸ� (0 ~ 2)������ �ȴ�. ���� -1 �ϸ�ǳ�?
			//(i/NUM*2-1)���Ǹ� ������ (-1 ~ 1)�� �ǰ� ����ϸ� �ǰڴ�.
			//(i/NUM*2-1) * �� ���� x��ǥ �ǽðڴ�.

			apt[i].x = i * cxClient / NUM; // 0 ~ 1000
			apt[i].y = (int)((sin(((double)i / NUM * 2 - 1) * PI) - 1) * (-cyClient / 2));
			//apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
			n = apt[i].x;
		}
		Polyline(hdc, apt, NUM);
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