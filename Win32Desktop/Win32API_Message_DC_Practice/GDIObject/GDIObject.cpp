#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static POINTS pt;
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);	//��ȿȭ������ ��������� DC�ڵ� ȹ�� ����
		HBRUSH brush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);	//�ý��ۿ� �̸� ���ǵ� DKGRAY_BRUSH�� ������ brush�� ����
		HBRUSH old = (HBRUSH)SelectObject(hdc, brush);
		//SelectObject�� ���� ��� ������ brush�� ����� ������ �ٲٰ� �ٷ� ������ ��� ������ old�� �����Ѵ�.
		Rectangle(hdc, 10, 10, 200, 200);
		//DeleteObject(SelectObject(hdc, old));
		//GetStockObject �� �ý����� ������ ������Ʈ�� �Ҹ��� �ʿ䰡����.
		//CreatePen,CreateBrush,CreateFont�� ���ظ�����ٸ� �Ҹ��ؾ���.

		HPEN pen = CreatePen(PS_DASH, 1, RGB(255, 145, 164));
		HPEN oldp = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush1 = CreateHatchBrush(HS_DIAGCROSS, RGB(68, 51, 170));
		HBRUSH oldb1 = (HBRUSH)SelectObject(hdc, brush1);
		//�������� �ڵ��� �ߺ� ����� �� �ִ�.
		Ellipse(hdc, 300, 300, 700, 700);
		DeleteObject(SelectObject(hdc, oldp));
		DeleteObject(SelectObject(hdc, oldb1));

		EndPaint(hwnd, &ps);
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