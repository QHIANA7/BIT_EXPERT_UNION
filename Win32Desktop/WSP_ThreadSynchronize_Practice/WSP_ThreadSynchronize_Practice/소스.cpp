#include <windows.h> 
#include <tchar.h> 

//�����ڿ�
int x;	//�����̹Ƿ� �ڵ� 0 �ʱ�ȭ
CRITICAL_SECTION g_cs;

DWORD WINAPI ThreadFun1(LPVOID param)
{
	HDC hdc = GetDC((HWND)param);
	for (int i = 0; i<100; i++)
	{
		EnterCriticalSection(&g_cs);
		x = 100;
		Sleep(1);
		TextOut(hdc, x, 100, TEXT("������"), 3);
		LeaveCriticalSection(&g_cs);
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}
DWORD WINAPI ThreadFun2(LPVOID param)
{
	HDC hdc = GetDC((HWND)param);
	for (int i = 0; i<100; i++)
	{
		EnterCriticalSection(&g_cs);
		x = 200;
		Sleep(1);
		TextOut(hdc, x, 200, TEXT("�����"), 3);
		LeaveCriticalSection(&g_cs);
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		InitializeCriticalSection(&g_cs);
		return 0;
	case WM_LBUTTONDOWN:
	{
		DWORD ThreadID;		
		HANDLE hThread = CreateThread(NULL, 0, ThreadFun1, hwnd, 0, &ThreadID);
		CloseHandle(hThread);			
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFun2, (LPVOID)hwnd, 0, &ThreadID);
		CloseHandle(hThread);
	}
	return 0;
	case WM_DESTROY:
		DeleteCriticalSection(&g_cs);
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