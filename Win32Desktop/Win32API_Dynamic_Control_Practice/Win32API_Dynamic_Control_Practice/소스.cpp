#include "std.h"

vector<MEMBER> g_veclist;	//입력기능을 사용해 그려진 그림의 정보를 담을 자료구조
MEMBER curmember;

//==============================================
//전역 컨트롤 핸들
HWND hEditName, hRadioGender1, hRadioGender2, hComboSubject, hEditNumber, hButtonJoin, hButtonCancle, hListMember
, hButtonUpdate, hButtonDelete;
//==============================================

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//case WM_PAINT:
	//	return OnPaint(hwnd, wParam, lParam);
	case WM_LBUTTONDOWN:
		return OnLButtonDown(hwnd, wParam, lParam);
	case WM_COMMAND:	//컨트롤은 WM_COMMAND메시지에 wParam 하위 16비트에 ID, 상위16비트에 메시지로 전달됨
		return OnCommand(hwnd, wParam, lParam);
	case WM_CREATE:	 //생성시점
		return OnCreate(hwnd, wParam, lParam);
	case WM_DESTROY:	//소멸시점
		return OnDestroy(hwnd, wParam, lParam);
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
		CW_USEDEFAULT, 0, 600, 350,// 초기 위치 
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