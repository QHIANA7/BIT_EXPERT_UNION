#include <windows.h> 
#include <tchar.h> 

void PrintTime(const SYSTEMTIME* pst, HDC hdc, int y)
{
	TCHAR date[256] = { 0 };
	TCHAR time[256] = { 0 };

	GetDateFormat(LOCALE_USER_DEFAULT, 0, pst, TEXT("yyy년 M월 d일"), date, 50);//50크기의 date공간에 날짜의 정보를 문자열 형태로 대입
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, pst, TEXT("tt h시 m분 s초"), time, 50);

	TextOut(hdc, 10, y + 10, date, _tcslen(date));	//DC 핸들, X, Y, 문자열, 문자열 길이
	TextOut(hdc, 10, y + 30, time, _tcslen(time));
}

BOOL PrintFileTime(HANDLE hFile, HDC hdc)
{
	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stUTCCreate, stLocalCreate, stUTCAccess, stLocalAccess, stUTCWrite, stLocalWrite;

	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) return FALSE;
	//파일 또는 디렉터리의 만든/수정한/액세스한 시간정보를 획득하는 함수
	//획득받는 타입은 FILETIME 이다.

	FileTimeToSystemTime(&ftCreate, &stUTCCreate);	//파일 시간 타입을 시스템표준(UTC)시간 타입으로 변환
	SystemTimeToTzSpecificLocalTime(NULL, &stUTCCreate, &stLocalCreate);	//시스템표준(UTC)시간 타입을 지역시간으로 변환
	//첫 매개변수가 NULL이라면 현재 컴퓨터의 지역설정의 설정으로 변환됨

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
			//핸들 타입,	CreateFile : 파일 또는 I/O 장치를 열거나 만드는 함수
			HANDLE hFile = CreateFile(TEXT("C:\\Windows\\system32\\calc.exe"),		//열 파일의 주소 또는 만들파일명
				GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING,
				//접근 권한(저건 읽기권한), 다른 프로세스에서의 액세스 여부, 보안설정(기본는 0),	파일을 오픈/생성의 여부(5가지 존재)
				FILE_ATTRIBUTE_NORMAL, 0);	//파일의 속성 설정 플래그, 기존 파일의 핸들(기본은 0) <- 이 값은 아직은 중요하지않으나 필요시 찾아 볼것

			HDC hdc = GetDC(hwnd);
			PrintFileTime(hFile, hdc);
			ReleaseDC(hwnd, hdc);
		}
		else if (wParam & MK_SHIFT)
		{
			//타이머는 한번 설정해놓으면 윈도우가 파괴되어도 계속 남아있다.
			//사용자정의로 만든 타이머는 직접 파괴해야한다. WM_DESTROY 에 정의해도 된다.
			KillTimer(hwnd, 1);
		}
		else
		{
			SYSTEMTIME st;	//시간 정보를 담은 SYSTEMTIME 구조체
			GetSystemTime(&st);	//세계표준시간을 구해 st에 대입
			TCHAR buf[50];

			GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, TEXT("yyy년 M월 d일"), buf, 50);
			//50크기의 buf공간에 날짜의 정보를 문자열 형태로 대입
			SetWindowText(hwnd, buf);
		}
	}
	return 0;
	case WM_RBUTTONDOWN:
	{
		if (wParam & MK_CONTROL)
		{
			//운영체제는 부팅후의 경과시간을 '1ms 단위'로 기록하고 있는데 이를 TickCount라고 함
			DWORD count = GetTickCount();	//TickCount를 얻는 함수 받는 타입은 Double Word
			int second = count / 1000;		//1ms 단위 이므로 1000을 나누면 1s단위가 나온다.
			int minute = (second % 3600) / 60;
			//초단위에 3600을 나눈 나머지(시간단위 이상을 제외한 분)를 60으로 나누면(초단위->분단위) 순수한 분단위가 나옴
			int hour = (second % 86400) / 3600;	
			//초단위에 86400을 나눈 나머지(일단위 이상을 제외한 시간)를 3600으로 나누면(초단위->시간단위) 순수한 시간단위가 나옴 
			int day = second / 86400;
			//초단위에 86400을 나눈 몫이 일단위

			TCHAR buf[50];
			wsprintf(buf, TEXT("%d일 %d시간 %d분 %d초 가 경과하였습니다."), day, hour, minute, second%60);
			SetWindowText(hwnd, buf);

		}
		else
		{
			SYSTEMTIME st;
			GetLocalTime(&st);	//지역시간을 구해 st에 대입
			TCHAR buf[50];

			GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, TEXT("tt h시 m분 s초"), buf, 50);
			//50크기의 buf공간에 시간의 정보를 문자열 형태로 대입
			SetWindowText(hwnd, buf);
		}
	}
	return 0;
	case WM_TIMER:
	{
		if (wParam == 1)	//wParam에는 타이머 식별자가 담겨있다.
		{
			SYSTEMTIME st;
			GetLocalTime(&st);
			TCHAR buf[50];
			wsprintf(buf, TEXT("현재 시간 - %d:%d:%d"), st.wHour, st.wMinute, st.wSecond);
			SetWindowText(hwnd, buf);
		}
		//return 
	}
	return 0;
	case WM_CREATE:
		//WIN_TIMER : 사용자의 동작과는 상관없이 발생하는 메시지
		//한번 설정해놓으면 일정한 간격마다 연속적으로 메시지가 발생한다.
		SetTimer(hwnd, 1, 1000, NULL);	//타이머를 설정하는 함수
		//윈도우 핸들,	타이머ID(사용자정의),	주기(1ms단위),	주기마다 호출할 함수(기본 NULL)
		//윈도우 핸들이 NULL일시 타이머 식별값을 반환한다. 이를 가지고 Kill 가능

		SendMessage(hwnd, WM_TIMER, 1, NULL);	//실제로는 윈도우가 만들어지고 1초 후 부터 출력되는데 이를 강제적으로 윈도우 생성시 부터 작동
		//윈도우 핸들, WM_TIMER, 타이머ID, 호출함수
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
	// 1. 윈도우 클래스 만들기 
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

	// 2. 등록(레지스트리에) 
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0, // WS_EX_TOPMOST 
		TEXT("first"), // 클래스 명 
		TEXT("Hello"), // 캡션바 내용 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,// 초기 위치 
		0, 0, // 부모 윈도우 핸들, 메뉴 핸들 
		hInst, // WinMain의 1번째 파라미터 (exe 주소) 
		0); // 생성 인자 

	// 4. 윈도우 보여주기 
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