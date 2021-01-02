//�ҽ�.cpp
#include "std.h"

//=====================================================================
//���� ��Ʈ�� �ڵ�
HWND hRadioRectangle, hRadioEllipse, hEditPosX, hEditPosY, hEditColorR, hEditColorG, hEditColorB, hComboPenWidth,
hEditSaveCount, hListSave, hEditMode, hEditTransparentMode;
//=====================================================================

//=====================================================================
//���� ��������
vector<DRAWTYPE> g_veclist;
DRAWTYPE cur_data;
//=====================================================================

//=====================================================================
//���� �޴�ID ����		���� DC �ڵ� ����
int submenu2 = ID_40003;
int submenu3 = ID_40005;
int submenu4 = ID_40009;
HDC g_hdc;
//=====================================================================

//=====================================================================
//���� ��ȿȭ���� ����			
RECT InvalidArea = { 410,0,1280,720 };
RECT ExtraInvalidArea = {150, 100, 210, 180};

//=====================================================================

//==============================================================================
//X,Y��ǥ RGB �÷�, PenWidth ���� ��ȭ�� ���� OnCommand �޽���ó�� ��ȿȭ �÷���
BOOL OnCommandInvalid = FALSE;
//�׸� ���� ��� �÷���
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
	case WM_INITMENUPOPUP:	//�޴��� ��������
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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); wc.style = 0;

	// 2. ���(������Ʈ����) 
	RegisterClass(&wc);

	// 3. ������ â ����� 
	HWND hwnd = CreateWindowEx(0, // WS_EX_TOPMOST 
		TEXT("first"), // Ŭ���� �� 
		TEXT("Hello"), // ĸ�ǹ� ���� 
		WS_OVERLAPPEDWINDOW &~ WS_THICKFRAME,
		CW_USEDEFAULT, 0, 1280, 720,// �ʱ� ��ġ 
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