//소스.cpp
#include "std.h"

//=====================================================================
//전역 컨트롤 핸들
HWND hRadioRectangle, hRadioEllipse, hEditPosX, hEditPosY, hEditColorR, hEditColorG, hEditColorB, hComboPenWidth,
hEditSaveCount, hListSave, hEditMode, hEditTransparentMode;
//=====================================================================

//=====================================================================
//전역 도형정보
vector<DRAWTYPE> g_veclist;
DRAWTYPE cur_data;
//=====================================================================

//=====================================================================
//전역 메뉴ID 정보		전역 DC 핸들 정보
int submenu2 = ID_40003;
int submenu3 = ID_40005;
int submenu4 = ID_40009;
HDC g_hdc;
//=====================================================================

//=====================================================================
//전역 무효화영역 정보			
RECT InvalidArea = { 410,0,1280,720 };
RECT ExtraInvalidArea = {150, 100, 210, 180};

//=====================================================================

//==============================================================================
//X,Y좌표 RGB 컬러, PenWidth 값의 변화에 따른 OnCommand 메시지처리 무효화 플래그
BOOL OnCommandInvalid = FALSE;
//그림 수정 모드 플래그
BOOL ShapeUpdateMode = FALSE;
//===============================================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		return OnLButtonDown(hwnd, wParam, lParam);
	case WM_PAINT:
		return OnPaint(hwnd, wParam, lParam);
	case WM_MOUSEMOVE:
		return OnMouseMove(hwnd, wParam, lParam);
	case WM_INITMENUPOPUP:	//메뉴를 열었을때
		return OnInitMenuPopUp(hwnd, wParam, lParam);
	case WM_COMMAND:
		if (OnCommandInvalid) return DefWindowProc(hwnd, msg, wParam, lParam);
		else return OnCommand(hwnd, wParam, lParam);
	case WM_TIMER:
		return OnTimer(hwnd, wParam, lParam);
	case WM_CREATE:
		return OnCreate(hwnd,wParam,lParam);
	case WM_DESTROY:
		return OnDestroy(hwnd,wParam,lParam);
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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); wc.style = 0;

	// 2. 등록(레지스트리에) 
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0, // WS_EX_TOPMOST 
		TEXT("first"), // 클래스 명 
		TEXT("Hello"), // 캡션바 내용 
		WS_OVERLAPPEDWINDOW &~ WS_THICKFRAME,
		CW_USEDEFAULT, 0, 1280, 720,// 초기 위치 
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