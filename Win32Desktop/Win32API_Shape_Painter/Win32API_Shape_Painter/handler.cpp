//handler.cpp
#include "std.h"

BOOL IsContainPos(POINT pt, RECT rt)	// pt좌표가 rt영역 내부에 있습니까?
{
	if (pt.x > rt.left && pt.x < rt.right)
		if (pt.y > rt.top && pt.y < rt.bottom)
			return TRUE;

	return FALSE;
}

void OnEditPos(HWND hwnd, WPARAM wParam)	//좌표를 표시하는 EDIT 컨트롤의 메시지
{
	switch (HIWORD(wParam))	//무슨 메시지인가?
	{
	case EN_CHANGE:	//에디트 알림 : 값이 변경되었다.
		if (ShapeUpdateMode)	//수정모드가 활성화 되어있는가?
			view_UpdateShapeByEditControl(hwnd);	//Control -> cur_data -> c_veclist[idx]
		else
			view_GetControlData(hwnd);				//Control -> cur_data
		break;
	}
}

void OnEditColor(HWND hwnd, WPARAM wParam)
{
	switch (HIWORD(wParam))	//무슨 메시지인가?
	{
	case EN_CHANGE:	//에디트 알림 : 값이 변경되었다.
		cur_data.transparentFlag = FALSE;
		SetWindowText(hEditTransparentMode, TEXT("FALSE"));
		if (ShapeUpdateMode)	//수정모드가 활성화 되어있는가?
			view_UpdateShapeByEditControl(hwnd);	//Control -> cur_data -> c_veclist[idx]
		else
		{
			view_GetControlData(hwnd);				//Control -> cur_data		
		}
		break;
	}	
}

void OnRadioDrawType(HWND hwnd, WPARAM wParam)
{
	switch (HIWORD(wParam))	//무슨 메시지인가?
	{
	case BN_CLICKED:	//버튼 알림 : 버튼이 클릭되었다.
		if (ShapeUpdateMode)	//수정모드가 활성화 되어있는가?
			view_UpdateShapeByEditControl(hwnd);	//Control -> cur_data -> c_veclist[idx]
		else
			view_GetControlData(hwnd);				//Control -> cur_data
		break;
	}
}

void OnComboPenWidth(HWND hwnd, WPARAM wParam)
{
	switch (HIWORD(wParam))	//무슨 메시지인가?
	{
	case CBN_SELCHANGE:	//콤보박스 알림 : 콤보박스 내부 목록상자에서 선택이 변경되었다.
		if (ShapeUpdateMode)	//수정모드가 활성화 되어있는가?
			view_UpdateShapeByEditControl(hwnd);	//Control -> cur_data -> c_veclist[idx]
		else
			view_GetControlData(hwnd);				//Control -> cur_data
		break;
	}
}

void OnListSave(HWND hwnd, WPARAM wParam)
{

	switch (HIWORD(wParam))
	{
	case LBN_SELCHANGE:	//리스트박스 알림 : 리스트 박스 내부 선택이 변경된 경우
		view_UpdateShapeByLBControl(hwnd);		//g_veclist[idx] -> cur_data -> Control
		ShapeUpdateMode = TRUE;					//그림 수정모드 활성화
		SetWindowText(hEditMode, TEXT("수정"));	//Edit컨트롤 텍스트 변경
		break;
		//	case LBN_SETFOCUS:
		//	case LBN_KILLFOCUS:
		//	ShapeUpdateMode = FALSE;
		//	SetWindowText(hEditMode, TEXT("입력"));
		//	break;
	}
}

LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT  pt = { LOWORD(lParam),HIWORD(lParam) };	//현재 마우스 좌표를 pt에 대입
	if (PtInRect(&InvalidArea,pt))		//pt좌표가 무효화영역내부일경우만 수행 
	{
		view_DrawShape(hwnd, &cur_data, wParam, lParam);	//Control 값에 의한 그림을 vector에 삽입후 WM_PAINT 발생
		view_ControlListBoxPrint(hwnd);					//vector에 저장된 요소들의 정보를 리스트박스에 출력
	}
	return 0;
}

LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;	//클라 영역을 그리는데 필요한 정보를 가짐
	HDC hdc = BeginPaint(hwnd, &ps);	//DC핸들을 획득함 그려야할 영역정보를 PAINTSTRUCT타입에 대입함

	//==============================
	view_PreviewColorPrint(hdc);		//RGB EDIT컨트롤 값의 색을 가진 사각형을 그림
	view_ShapePrint(hdc, &g_veclist);	//view소스에 vector에 저장된 모든그림 출력
	//==============================

	EndPaint(hwnd, &ps);				//DC핸들 소멸
	return 0;
}

LRESULT OnMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT  pt = { LOWORD(lParam),HIWORD(lParam) };	//현재 마우스 좌표를 pt에 대입
	if (IsContainPos(pt, InvalidArea))	//pt좌표가 무효화영역내부일경우만 수행 
	{
		ShapeUpdateMode = FALSE;	//그림 수정모드를 끔
		SetDlgItemInt(hwnd, IDC_EDITPOSX, pt.x, NULL);	//EDIT 컨트롤에 현재 마우스의 X,Y 좌표를 대입
		SetDlgItemInt(hwnd, IDC_EDITPOSY, pt.y, NULL);
	}

	if (ShapeUpdateMode)	//현재 그림 수정모드가 켜져있을 경우
	{
		SetWindowText(hEditMode, TEXT("수정"));	//EDIT 컨트롤에 수정 출력
	}
	else
		SetWindowText(hEditMode, TEXT("입력"));
	return 0;
}

LRESULT OnInitMenuPopUp(HWND hwnd, WPARAM wParam, LPARAM lParam)	//메뉴가 열렸을 때
{
	HMENU hMenu = (HMENU)wParam;	//임시 메뉴핸들 변수에 드롭다운 메뉴 핸들 대입

	if (cur_data.type == 1)	//cur_data가 1일 경우
		submenu2 = ID_40003;
	else
		submenu2 = ID_40004;

	CheckMenuItem(hMenu, ID_40003, submenu2 == ID_40003 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40004, submenu2 == ID_40004 ? MF_CHECKED : MF_UNCHECKED);
	//지정된 메뉴 항목의 체크상태를 선택 또는 해제로 설정합니다.
	//메뉴핸들, 메뉴ID, 상태설정


	TCHAR buf[50];
	GetWindowText(hEditTransparentMode, buf, sizeof(buf));
	//cur_data의 color가 다음과 같을 경우 submenu3의 기본선택값을 변경
	if (GetRValue(cur_data.color) == 255 && GetGValue(cur_data.color) == 0 && GetBValue(cur_data.color) == 0)
		submenu3 = ID_40005;
	else if (GetRValue(cur_data.color) == 0 && GetGValue(cur_data.color) == 255 && GetBValue(cur_data.color) == 0)
		submenu3 = ID_40006;
	else if (GetRValue(cur_data.color) == 0 && GetGValue(cur_data.color) == 0 && GetBValue(cur_data.color) == 255)
		submenu3 = ID_40007;
	else if (!_tcscmp(buf, TEXT("TRUE")))
		submenu3 = ID_40008;
	else
		submenu3 = NULL;


	CheckMenuItem(hMenu, ID_40005, submenu3 == ID_40005 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40006, submenu3 == ID_40006 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40007, submenu3 == ID_40007 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40008, submenu3 == ID_40008 ? MF_CHECKED : MF_UNCHECKED);


	//cur_data의 penwidth가 다음과 같을 경우 submenu4의 기본석택값을 변경
	if (cur_data.penwidth == 1)
		submenu4 = ID_40009;
	else if (cur_data.penwidth == 3)
		submenu4 = ID_40010;
	else if (cur_data.penwidth == 5)
		submenu4 = ID_40011;
	else
		submenu4 = NULL;

	CheckMenuItem(hMenu, ID_40009, submenu4 == ID_40009 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40010, submenu4 == ID_40010 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40011, submenu4 == ID_40011 ? MF_CHECKED : MF_UNCHECKED);
	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)	//컨트롤에서 메시지 발생 시
{
	switch (LOWORD(wParam))	//WM_COMMAND 발생시 wParam중 하위 16비트에 ID가 담겨온다.
	{
	case IDC_EDITPOSX:
	case IDC_EDITPOSY:
		OnEditPos(hwnd, wParam);
		break;
	case IDC_EDITCOLORR:
	case IDC_EDITCOLORG:
	case IDC_EDITCOLORB:
		OnEditColor(hwnd, wParam);
		break;
	case IDC_RADIORECTANGLE:
	case IDC_RADIOELLIPSE:
		OnRadioDrawType(hwnd, wParam);
		break;
	case IDC_COMBOPENWIDTH:
		OnComboPenWidth(hwnd, wParam);
		break;
	case IDC_LISTSAVE:
		OnListSave(hwnd, wParam);
		break;
	case ID_40001:	view_NewFile(hwnd);		break;
	case ID_40002:	SendMessage(hwnd, WM_CLOSE, 0, 0);		break;
	case ID_40003:	submenu2 = ID_40003; cur_data.type = 1; view_RefreshSetting(hwnd); break;
	case ID_40004:	submenu2 = ID_40004; cur_data.type = 2; view_RefreshSetting(hwnd); break;
	case ID_40005:	submenu3 = ID_40005; cur_data.color = RGB(255, 0, 0);
		cur_data.transparentFlag = FALSE; SetWindowText(hEditTransparentMode, TEXT("FALSE")); view_RefreshSetting(hwnd); break;
	case ID_40006:	submenu3 = ID_40006; cur_data.color = RGB(0, 255, 0);
		cur_data.transparentFlag = FALSE; SetWindowText(hEditTransparentMode, TEXT("FALSE")); view_RefreshSetting(hwnd); break;
	case ID_40007:	submenu3 = ID_40007; cur_data.color = RGB(0, 0, 255);
		cur_data.transparentFlag = FALSE; SetWindowText(hEditTransparentMode, TEXT("FALSE")); view_RefreshSetting(hwnd); break;
	case ID_40008:	submenu3 = ID_40008; cur_data.color = RGB(255, 255, 255);
		cur_data.transparentFlag = TRUE;
		SetWindowText(hEditTransparentMode, TEXT("TRUE"));
		view_RefreshSetting(hwnd); break;
	case ID_40009:	submenu4 = ID_40009; cur_data.penwidth = 1; view_RefreshSetting(hwnd); break;
	case ID_40010:	submenu4 = ID_40010; cur_data.penwidth = 3; view_RefreshSetting(hwnd); break;
	case ID_40011:	submenu4 = ID_40011; cur_data.penwidth = 5; view_RefreshSetting(hwnd); break;
	}

	return 0;
}

LRESULT OnTimer(HWND hwnd, WPARAM wParam, LPARAM lParam)
{

	view_SetTimeToWindowText(hwnd);	//캡션바에 로컬 시간 출력
	return 0;
}

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	view_SetTimer(hwnd);		//타이머 설정
	view_ControlCreate(hwnd);	//컨트롤 생성
	DrawInit(&cur_data);		//cur_data 초기화
	view_ControlInit(hwnd);		//cur_data -> Control
	return 0;
}

LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	KillTimer(hwnd, 1);	//ID가 1인 타이머 삭제
	PostQuitMessage(0);	//WM_QUIT 메시지
	return 0;
}
