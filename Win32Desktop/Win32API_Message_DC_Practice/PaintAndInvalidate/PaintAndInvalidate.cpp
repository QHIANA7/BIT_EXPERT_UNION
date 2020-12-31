#include <windows.h> 
#include <tchar.h>
#include <vector>
using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static vector<POINTS> ptlist;	//마우스의 좌표 기록을 담기 위한 정적 벡터 선언
	switch (msg)
	{
	case WM_PAINT:	//무효화영역이 발생했을경우 WM_PAINT메시지(비큐)가 바로 프로시저로 전송된다.
	{
		PAINTSTRUCT ps;	//무효화영역을 대상으로 사용할경우 PAINTSTRUCT가 필요하다.
		HDC hdc = BeginPaint(hwnd, &ps);	//무효화영역을 대상으로 DC 핸들을 얻을경우 BeginPaint를 사용함
		//BeginPaint실행 후 무효화영역 내부가 지워진다.
		for (int i = 0; i < (int)ptlist.size(); i++)
		{
			POINTS pt = ptlist[i];	//벡터에 기록되어있던 좌표를 하나씩 빼와서
			Ellipse(hdc, pt.x, pt.y, pt.x + 50, pt.y + 50);	//매개변수에 해당하는 타원을 그려낸다.
		}
		EndPaint(hwnd, &ps);	//BeginPaint로 얻은 DC핸들의 해제는 EndPaint를 사용함
	}
		return 0;
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);	//현재 마우스의 좌표를 pt에 대입
		//타이틀바에 좌표 출력
		TCHAR str[20];
		wsprintf(str, TEXT("(%d,%d)"), pt.x, pt.y);
		SetWindowText(hwnd, str);	//윈도우이름(캡션바)의 이름 변경

		ptlist.push_back(pt);	//pt값을 벡터에 insert
		//강제로 무효화영역을 생성 가능
		InvalidateRect(hwnd, 0, true);		//true의 경우 영역을 지우며, false는 영역을 유지한다.

		//==================================
		HDC hdc = GetDC(hwnd);		//클라이언트 영역의 DC를 얻어온다.
		Rectangle(hdc, pt.x, pt.y, pt.x + 50, pt.y + 50);	//매개변수에 해당하는 타원을 그려낸다.
		ReleaseDC(hwnd, hdc);	//DC를 제거하는 구문.
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

	//이는 사용이 끝나면 당연히 해제를 해줘야 하나 프로그램 종료시 자동으로 해제된다.

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