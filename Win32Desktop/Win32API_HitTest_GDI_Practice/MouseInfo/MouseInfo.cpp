#include <windows.h> 
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{

		if (wParam & MK_CONTROL)
		{
			POINT pt = { LOWORD(lParam), HIWORD(lParam) };
			POINT pt1 = pt;

			ClientToScreen(hwnd, &pt);	//클라이언트 좌표를 스크린 좌표로 변환

			TCHAR buf[256];
			wsprintf(buf, TEXT("클라이언트 좌표 = %d, %d\r\n스크린 좌표 = %d, %d"), pt1.x, pt1.y, pt.x, pt.y);
			MessageBox(hwnd, buf, TEXT("좌표 알림 + CTRL 눌림"), MB_OK);
		}
		else if (wParam & MK_SHIFT)
		{
			POINTS pt = MAKEPOINTS(lParam);	//SHORT 타입 포지션
			POINT pt1 = { LOWORD(lParam), HIWORD(lParam) };	//LONG 타입 포지션
			TCHAR buf[100];
			wsprintf(buf, TEXT("SHORT Type Position : (%d,%d)\nLONG Type Position : (%d,%d)"), pt.x, pt.y, pt1.x, pt1.y);
			MessageBox(hwnd, buf, TEXT("L BT DOWN 좌표 + SHIFT"), MB_OK);
		}
	}
	return 0;
	case WM_RBUTTONDOWN:
	{
		if (wParam & MK_SHIFT)	// & : 비트 마스크 기법		| : 추가	&~ : 제거
			MessageBox(hwnd, TEXT("R BT + SHIFT"), TEXT("Notice"), MB_OK);
		else if (wParam & MK_CONTROL)
			MessageBox(hwnd, TEXT("R BT + CONTROL"), TEXT("Notice"), MB_OK);	//ALT는 안됨
	}
	return 0;
	case WM_NCRBUTTONDOWN:	//비클라이언트 영역에서의 RBUTTONDOWN 메시지 처리기
		MessageBox(hwnd, TEXT("비클라이언트 영역 R BT DOWN"), TEXT("Notice"), MB_OK);
		return 0;

		//커서를 움직임,버튼클릭,버튼놓을 시 System은 WM_NCHITTEST메시지를 프로시저로 전송한다.
		//WM_NCHITTEST가 DefWindowProc으로 보내졌을 경우 hit_test_code가 wParam에 반환되어 온다.
		//hit_test_code에는 커서가 어디에있는지를 담고있다. 이를 이용해 hit_test_code도 조작 가능
	case WM_NCHITTEST:
	{
		DWORD code = DefWindowProc(hwnd, msg, wParam, lParam);
		if (code == HTCLIENT && GetKeyState(VK_CONTROL) && GetKeyState(VK_SHIFT) < 0)
			code = HTLEFT;	//클라이언트 영역에서 Ctrl+Shift와 붙잡으면 왼쪽 테두리를 잡은것으로 처리

		if (code == HTRIGHT)
			code = HTLEFT;	//DefWindowProc가 반환한 결과가 비클라이언트 영역의 우측 테두리라면 왼쪽 테두리를 잡은것으로 처리
		return code;
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