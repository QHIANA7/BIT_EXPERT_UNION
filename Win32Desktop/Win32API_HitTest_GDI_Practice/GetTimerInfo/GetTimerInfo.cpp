#include <windows.h> 
#include <tchar.h> 

void PrintTime(const SYSTEMTIME* pst, HDC hdc, int y)
{
	TCHAR date[256] = { 0 };
	TCHAR time[256] = { 0 };

	GetDateFormat(LOCALE_USER_DEFAULT, 0, pst, TEXT("yyy�� M�� d��"), date, 50);//50ũ���� date������ ��¥�� ������ ���ڿ� ���·� ����
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, pst, TEXT("tt h�� m�� s��"), time, 50);

	TextOut(hdc, 10, y + 10, date, _tcslen(date));	//DC �ڵ�, X, Y, ���ڿ�, ���ڿ� ����
	TextOut(hdc, 10, y + 30, time, _tcslen(time));
}

BOOL PrintFileTime(HANDLE hFile, HDC hdc)
{
	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stUTCCreate, stLocalCreate, stUTCAccess, stLocalAccess, stUTCWrite, stLocalWrite;

	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) return FALSE;
	//���� �Ǵ� ���͸��� ����/������/�׼����� �ð������� ȹ���ϴ� �Լ�
	//ȹ��޴� Ÿ���� FILETIME �̴�.

	FileTimeToSystemTime(&ftCreate, &stUTCCreate);	//���� �ð� Ÿ���� �ý���ǥ��(UTC)�ð� Ÿ������ ��ȯ
	SystemTimeToTzSpecificLocalTime(NULL, &stUTCCreate, &stLocalCreate);	//�ý���ǥ��(UTC)�ð� Ÿ���� �����ð����� ��ȯ
	//ù �Ű������� NULL�̶�� ���� ��ǻ���� ���������� �������� ��ȯ��

	FileTimeToSystemTime(&ftAccess, &stUTCAccess);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTCAccess, &stLocalAccess);

	FileTimeToSystemTime(&ftWrite, &stUTCWrite);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTCWrite, &stLocalWrite);

	PrintTime(&stLocalCreate, hdc, 0);
	PrintTime(&stLocalAccess, hdc, 50);
	PrintTime(&stLocalWrite, hdc, 100);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		if (wParam & MK_CONTROL)
		{
			//�ڵ� Ÿ��,	CreateFile : ���� �Ǵ� I/O ��ġ�� ���ų� ����� �Լ�
			HANDLE hFile = CreateFile(TEXT("C:\\Windows\\system32\\calc.exe"),		//�� ������ �ּ� �Ǵ� �������ϸ�
				GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING,
				//���� ����(���� �б����), �ٸ� ���μ��������� �׼��� ����, ���ȼ���(�⺻�� 0),	������ ����/������ ����(5���� ����)
				FILE_ATTRIBUTE_NORMAL, 0);	//������ �Ӽ� ���� �÷���, ���� ������ �ڵ�(�⺻�� 0) <- �� ���� ������ �߿����������� �ʿ�� ã�� ����

			HDC hdc = GetDC(hwnd);
			PrintFileTime(hFile, hdc);
			ReleaseDC(hwnd, hdc);
		}
		else if (wParam & MK_SHIFT)
		{
			//Ÿ�̸Ӵ� �ѹ� �����س����� �����찡 �ı��Ǿ ��� �����ִ�.
			//��������Ƿ� ���� Ÿ�̸Ӵ� ���� �ı��ؾ��Ѵ�. WM_DESTROY �� �����ص� �ȴ�.
			KillTimer(hwnd, 1);
		}
		else
		{
			SYSTEMTIME st;	//�ð� ������ ���� SYSTEMTIME ����ü
			GetSystemTime(&st);	//����ǥ�ؽð��� ���� st�� ����
			TCHAR buf[50];

			GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, TEXT("yyy�� M�� d��"), buf, 50);
			//50ũ���� buf������ ��¥�� ������ ���ڿ� ���·� ����
			SetWindowText(hwnd, buf);
		}
	}
	return 0;
	case WM_RBUTTONDOWN:
	{
		if (wParam & MK_CONTROL)
		{
			//�ü���� �������� ����ð��� '1ms ����'�� ����ϰ� �ִµ� �̸� TickCount��� ��
			DWORD count = GetTickCount();	//TickCount�� ��� �Լ� �޴� Ÿ���� Double Word
			int second = count / 1000;		//1ms ���� �̹Ƿ� 1000�� ������ 1s������ ���´�.
			int minute = (second % 3600) / 60;
			//�ʴ����� 3600�� ���� ������(�ð����� �̻��� ������ ��)�� 60���� ������(�ʴ���->�д���) ������ �д����� ����
			int hour = (second % 86400) / 3600;	
			//�ʴ����� 86400�� ���� ������(�ϴ��� �̻��� ������ �ð�)�� 3600���� ������(�ʴ���->�ð�����) ������ �ð������� ���� 
			int day = second / 86400;
			//�ʴ����� 86400�� ���� ���� �ϴ���

			TCHAR buf[50];
			wsprintf(buf, TEXT("%d�� %d�ð� %d�� %d�� �� ����Ͽ����ϴ�."), day, hour, minute, second%60);
			SetWindowText(hwnd, buf);

		}
		else
		{
			SYSTEMTIME st;
			GetLocalTime(&st);	//�����ð��� ���� st�� ����
			TCHAR buf[50];

			GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, TEXT("tt h�� m�� s��"), buf, 50);
			//50ũ���� buf������ �ð��� ������ ���ڿ� ���·� ����
			SetWindowText(hwnd, buf);
		}
	}
	return 0;
	case WM_TIMER:
	{
		if (wParam == 1)	//wParam���� Ÿ�̸� �ĺ��ڰ� ����ִ�.
		{
			SYSTEMTIME st;
			GetLocalTime(&st);
			TCHAR buf[50];
			wsprintf(buf, TEXT("���� �ð� - %d:%d:%d"), st.wHour, st.wMinute, st.wSecond);
			SetWindowText(hwnd, buf);
		}
		//return 
	}
	return 0;
	case WM_CREATE:
		//WIN_TIMER : ������� ���۰��� ������� �߻��ϴ� �޽���
		//�ѹ� �����س����� ������ ���ݸ��� ���������� �޽����� �߻��Ѵ�.
		SetTimer(hwnd, 1, 1000, NULL);	//Ÿ�̸Ӹ� �����ϴ� �Լ�
		//������ �ڵ�,	Ÿ�̸�ID(���������),	�ֱ�(1ms����),	�ֱ⸶�� ȣ���� �Լ�(�⺻ NULL)
		//������ �ڵ��� NULL�Ͻ� Ÿ�̸� �ĺ����� ��ȯ�Ѵ�. �̸� ������ Kill ����

		SendMessage(hwnd, WM_TIMER, 1, NULL);	//�����δ� �����찡 ��������� 1�� �� ���� ��µǴµ� �̸� ���������� ������ ������ ���� �۵�
		//������ �ڵ�, WM_TIMER, Ÿ�̸�ID, ȣ���Լ�
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