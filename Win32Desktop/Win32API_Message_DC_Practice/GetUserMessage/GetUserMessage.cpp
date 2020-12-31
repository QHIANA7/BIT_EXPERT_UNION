#include <Windows.h>
#include <tchar.h>

#define WM_MYMESSAGE WM_USER+100	//사용자 정의 메시지 WM_USER미만은 이미 예약된 메시지 이기때문에 못쓰지만
#define WM_MYMESSAGE1 WM_USER+200	//거기에 +몇을 하면 겹칠일이 없어 사용자정의 메시지로 사용하기에 알맞다.

void FindTest01(HWND hwindow)
{
	HWND hwnd = FindWindow(0, TEXT("계산기"));	//윈도우핸들을 찾는 함수 :	클래스 명,	윈도우 이름
	SetWindowText(hwindow, TEXT("Hello"));	//윈도우 이름(캡션바)의 구문을 바꾸는 함수 : 윈도우핸들,	문자열

	if (hwnd == 0)	//FindWindow가 윈도우 핸들을 찾지 못했다면 0을 반환한다. 찾았다면 그 윈도우 핸들을 반환한다.
	{
		MessageBox(hwindow, TEXT("계산기 핸들 획득에 실패했습니다. 계산기가 켜져있는지 확인하세요"), TEXT("알림"), MB_OK | MB_ICONERROR);
		//범용 메시지박스출력 함수 : 윈도우 핸들,	메시지 내용,	메시지박스 제목,	옵션들
		return;
	}
	else	//FindWindow함수가 윈도우 핸들을 찾았을 경우
	{
		TCHAR temp[20];	//범용 문자열 저장소
		wsprintf(temp, TEXT("계산기 핸들 : %d"), hwnd);	//첫번째 매개변수에 출력하는 범용함수 :	담을 변수,	출력 내용(표준printf)
		MessageBox(hwindow, temp, TEXT("알림"), MB_OK);	//메시지박스 동일
		return;
	}
}

void MoveTest01(HWND hwindow)
{
	HWND hwnd = FindWindow(0, TEXT("계산기"));
	SetWindowText(hwindow, TEXT("Hello"));

	if (hwnd == 0)
	{
		MessageBox(hwindow, TEXT("계산기 핸들 획득에 실패했습니다. 계산기가 켜져있는지 확인하세요"), TEXT("알림"), MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		TCHAR temp[256];
		ShowWindow(hwnd, SW_SHOW);	//윈도우를 표시하는 함수 : 윈도우 핸들,	옵션
		MoveWindow(hwnd, 100, 300, 300, 300, TRUE);	//윈도우를 이동 또는 크기조정 하는 함수 : 윈도우 핸들,	좌표, 크기, 재출력여부
		wsprintf(temp, TEXT("계산기 창 이동 : X = 100  Y = 100 / W = 300  H = 300"), hwnd);
		MessageBox(hwindow, temp, TEXT("알림"), MB_OK);
		return;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MYMESSAGE://사용자 정의 메시지 처리 부분
		TCHAR str[30];
		wsprintf(str, TEXT("%d+%d 수식의 결과를 발신처로 반환했습니다."), wParam, lParam);
		MessageBox(hwnd, str, TEXT("WM_MYMESSAGE Received"), MB_OK);
		return wParam + lParam;	//이 리턴 값은 메시지를 호출한 부분으로 반환한다. 반환부가 논블록킹 함수의 경우 의미X
	case WM_MYMESSAGE1:
		TCHAR str1[30];
		wsprintf(str1, TEXT("발신처로부터 %d 결과를 받았다고 보고 받았습니다."), wParam);
		MessageBox(hwnd, str1, TEXT("WM_MYMESSAGE1 Received"), MB_OK);
		return wParam + lParam;	//이 리턴 값은 메시지를 호출한 부분으로 반환한다. 반환부가 논블록킹 함수의 경우 의미X
	case WM_LBUTTONDOWN:
		//MessageBox(hwnd, TEXT("마우스 왼버튼 눌림"), TEXT("알림"), MB_OK);
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
	// 1. 윈도우 작성
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

	// 2. 클래스 등록
	RegisterClass(&wc);

	// 3. 윈도우 생성
	HWND hwnd = CreateWindowEx(0,
		TEXT("first"), TEXT("Hello"),	//	클래스명 / 캡션바명
		WS_OVERLAPPEDWINDOW,	// 윈도우 구성
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	//x,y, 너비, 높이 //CW_USEDEFAULT가 설정된경우 y의 크기, nHeight는 무시된다
		0, 0,	//부모 윈도우 핸들, 메뉴 핸들
		hInst,	//인스턴스
		0);	//생성인자

	// 4. 윈도우 출력
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. 메시지 전달
	MSG msg;

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}