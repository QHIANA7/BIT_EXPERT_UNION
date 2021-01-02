//view.cpp
#include "std.h"

void view_ControlCreate(HWND hwnd)	//컨트롤 생성
{
	CreateWindow(TEXT("button"), TEXT("[ 설정 정보 ]"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 220, 300, hwnd, 0, 0, 0);
	CreateWindow(TEXT("static"), TEXT("- 타입"), WS_CHILD | WS_VISIBLE, 20, 40, 50, 20, hwnd, 0, 0, 0);
	hRadioRectangle = CreateWindow(TEXT("button"), TEXT("사각형"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
		80, 40, 70, 20, hwnd, (HMENU)IDC_RADIORECTANGLE, 0, 0);
	hRadioEllipse = CreateWindow(TEXT("button"), TEXT("타원"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		160, 40, 60, 20, hwnd, (HMENU)IDC_RADIOELLIPSE, 0, 0);
	CreateWindow(TEXT("static"), TEXT("- 좌표"), WS_CHILD | WS_VISIBLE, 20, 70, 50, 20, hwnd, 0, 0, 0);

	CreateWindow(TEXT("static"), TEXT("X"), WS_CHILD | WS_VISIBLE | SS_CENTER, 80, 70, 20, 20, hwnd, 0, 0, 0);
	hEditPosX = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 100, 70, 40, 20, hwnd, (HMENU)IDC_EDITPOSX, 0, 0);
	CreateWindow(TEXT("static"), TEXT("Y"), WS_CHILD | WS_VISIBLE | SS_CENTER, 150, 70, 20, 20, hwnd, 0, 0, 0);
	hEditPosY = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 170, 70, 40, 20, hwnd, (HMENU)IDC_EDITPOSY, 0, 0);

	CreateWindow(TEXT("static"), TEXT("- 색상"), WS_CHILD | WS_VISIBLE, 20, 100, 50, 20, hwnd, 0, 0, 0);
	CreateWindow(TEXT("static"), TEXT("R"), WS_CHILD | WS_VISIBLE | SS_CENTER, 80, 100, 20, 20, hwnd, 0, 0, 0);
	hEditColorR = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 100, 100, 40, 20, hwnd, (HMENU)IDC_EDITCOLORR, 0, 0);
	CreateWindow(TEXT("static"), TEXT("G"), WS_CHILD | WS_VISIBLE | SS_CENTER, 80, 130, 20, 20, hwnd, 0, 0, 0);
	hEditColorG = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 100, 130, 40, 20, hwnd, (HMENU)IDC_EDITCOLORG, 0, 0);
	CreateWindow(TEXT("static"), TEXT("B"), WS_CHILD | WS_VISIBLE | SS_CENTER, 80, 160, 20, 20, hwnd, 0, 0, 0);
	hEditColorB = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 100, 160, 40, 20, hwnd, (HMENU)IDC_EDITCOLORB, 0, 0);

	CreateWindow(TEXT("static"), TEXT("- 두께"), WS_CHILD | WS_VISIBLE, 20, 190, 50, 20, hwnd, 0, 0, 0);
	hComboPenWidth = CreateWindow(TEXT("combobox"), TEXT(""),
		WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | CBS_DROPDOWN
		, 80, 190, 60, 80, hwnd, (HMENU)IDC_COMBOPENWIDTH, 0, 0);
	SendMessage(hComboPenWidth, CB_ADDSTRING, 0, (LPARAM)TEXT("1"));
	SendMessage(hComboPenWidth, CB_ADDSTRING, 0, (LPARAM)TEXT("3"));
	SendMessage(hComboPenWidth, CB_ADDSTRING, 0, (LPARAM)TEXT("5"));

	CreateWindow(TEXT("static"), TEXT("- 모드"), WS_CHILD | WS_VISIBLE, 20, 270, 50, 20, hwnd, 0, 0, 0);
	hEditMode = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 80, 270, 40, 20, hwnd, (HMENU)IDC_EDITMODE, 0, 0);

	CreateWindow(TEXT("static"), TEXT("- 투명"), WS_CHILD | WS_VISIBLE, 130, 270, 50, 20, hwnd, 0, 0, 0);
	hEditTransparentMode = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 180, 270, 40, 20, hwnd, (HMENU)IDC_EDITTRANSPARENTMODE, 0, 0);

	CreateWindow(TEXT("button"), TEXT("[ 저장 정보 ]"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 240, 10, 170, 600, hwnd, 0, 0, 0);
	CreateWindow(TEXT("static"), TEXT("- 저장 개수"), WS_CHILD | WS_VISIBLE, 250, 40, 80, 20, hwnd, 0, 0, 0);

	hEditSaveCount = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT, 340, 40, 40, 20, hwnd, (HMENU)IDC_EDITSAVECOUNT, 0, 0);
	CreateWindow(TEXT("static"), TEXT("개"), WS_CHILD | WS_VISIBLE | SS_CENTER, 380, 40, 20, 20, hwnd, 0, 0, 0);

	hListSave = CreateWindow(TEXT("listbox"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL, 250, 70, 150, 540, hwnd, (HMENU)IDC_LISTSAVE, 0, 0);
}

void view_ControlInit(HWND hwnd)	//cur_data -> Control
{
	if (cur_data.type == 1)
		CheckRadioButton(hwnd, IDC_RADIORECTANGLE, IDC_RADIOELLIPSE, IDC_RADIORECTANGLE);
	else
		CheckRadioButton(hwnd, IDC_RADIORECTANGLE, IDC_RADIOELLIPSE, IDC_RADIOELLIPSE);
	SetDlgItemInt(hwnd, IDC_EDITPOSX, cur_data.pt.x, 0);
	SetDlgItemInt(hwnd, IDC_EDITPOSY, cur_data.pt.y, 0);
	SetDlgItemInt(hwnd, IDC_EDITCOLORR, GetRValue(cur_data.color), 0);
	SetDlgItemInt(hwnd, IDC_EDITCOLORG, GetGValue(cur_data.color), 0);
	SetDlgItemInt(hwnd, IDC_EDITCOLORB, GetBValue(cur_data.color), 0);
	SendMessage(hComboPenWidth, CB_SETCURSEL, cur_data.penwidth/2, 0);
	SetDlgItemInt(hwnd, IDC_EDITSAVECOUNT, g_veclist.size(), 0);

	if (cur_data.transparentFlag)
		SetWindowText(hEditTransparentMode, TEXT("TRUE"));
	else
		SetWindowText(hEditTransparentMode, TEXT("FALSE"));

	InvalidateRect(hwnd, &ExtraInvalidArea, TRUE);
}

void view_ControlListBoxPrint(HWND hwnd) //리스트박스 내용 삭제 -> g_veclist에 있는 모든 내용 추가
{
	TCHAR buf[50];	//임시 범용 문자열 변수
	SendMessage(hListSave, LB_RESETCONTENT, 0, 0);
	//LB_DELETESTRING메시지 또한 가능하다 매개변수는 i,0이며 i인덱스를 지우는 메시지다. (반복문 필요)
	for (int i = 0; i < (int)g_veclist.size(); i++)	//vector에 저장된 수만큼 반복
	{
		DRAWTYPE temp = g_veclist[i];	
		wsprintf(buf, TEXT("%02d|%s(%3d,%3d)"),i+1 , temp.type == 1 ? TEXT("사각형") : TEXT("타　원"), temp.pt.x, temp.pt.y);
		SendMessage(hListSave, LB_ADDSTRING, 0, (LPARAM)buf);	//ListBox에 문자열을 추가
		//주의 : 이 시점에서 문자열이 추가되진 않는다. 현재메시지 처리후 LB_ADDSTRING 처리시 추가된다.
	}
	//LB_ADDSTRING : ListBox에 문자열을 추가하라는 메시지 - lParam에 문자열을 넘겨줘야함
	//LBN_SELCHANGE : 선택이 바뀌었을때 발생하는 메시지
	//LB_GETCURSEL : 리스트박스상의 인덱스를 반환한다.
}

void view_GetControlData(HWND hwnd)	//Control -> cur_data
{
	if (SendMessage(hRadioRectangle, BM_GETCHECK, 0, 0) == BST_CHECKED)	//버튼 컨트롤의 채크정보를 가져오는 메시지
		cur_data.type = 1;
	else
		cur_data.type = 2;

	cur_data.pt.x =	GetDlgItemInt(hwnd, IDC_EDITPOSX, 0, 0);	//EDIT 컨트롤 텍스트의 정수형을 가져옴
	cur_data.pt.y = GetDlgItemInt(hwnd, IDC_EDITPOSY, 0, 0);	//Pos 부분

	cur_data.color = RGB(
		(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORR, 0, 0),	//EDIT 컨트롤 텍스트의 정수형을 가져옴
		(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORG, 0, 0),	//RGB부분
		(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORB, 0, 0));

	//GetDlgItemInt : 하나의 부모의 창이 있고 그안의 ID아이템의 정수값을 가져옴
	//부모핸들, 컨트롤ID,NULL,NULL

	cur_data.penwidth = SendMessage(hComboPenWidth, CB_GETCURSEL, 0, 0) * 2 + 1;
	//ComboBox 컨트롤의 선택된 인덱스를 달라는 메시지

	TCHAR buf[50];
	GetWindowText(hEditTransparentMode, buf, sizeof(buf));
	if (!_tcscmp(buf, TEXT("TRUE")))
		cur_data.transparentFlag = TRUE;
	else
		cur_data.transparentFlag = FALSE;

	InvalidateRect(hwnd, &ExtraInvalidArea, TRUE);	//PrivewColor부분 무효화영역을 지운다 WM_Paint발생
}

void view_SetControlData(HWND hwnd)
{
	view_ControlInit(hwnd);
}

void view_DrawShape(HWND hwnd, DRAWTYPE * dt, WPARAM wParam, LPARAM lParam)
{
	cur_data.pt.x = LOWORD(lParam);	//LOWORD는 lParam의 하위 16비트 값을 가져오는것.
	cur_data.pt.y = HIWORD(lParam);	//HIWORD는 상위16비트를 가져옴

	TCHAR buf[50];
	GetWindowText(hEditTransparentMode, buf, sizeof(buf));
	//(submenu3 == ID_40008 && cur_data.color == RGB(255,255,255)) ?
	_tcscmp(buf,TEXT("TURE")) ?
		cur_data.transparentFlag = TRUE : cur_data.transparentFlag = FALSE;
		//메뉴에 투명이 선택되있고 cur_data의 RGB가 흰색인경우 cur_data의 투명을 활성화

	
	view_GetControlData(hwnd);		//Control -> cur_data
	

	if (wParam & MK_CONTROL)	//컨트롤이 눌려있을 경우
	{
		if ((int)g_veclist.size() > 0)	//vector에 하나라도 적재되어있을 경우
			g_veclist.pop_back();		//마지막에 삽입된 요소 제거
	}
	else
	{
		g_veclist.push_back(cur_data);	//cur_data를 vector에 삽입
	}

	InvalidateRect(hwnd, &InvalidArea, TRUE);	//그리기 영역을 무효화 -> WM_PAINT 발생
	//주의 : 위 함수 수행후 OnPaint함수가 수행되는게 맞긴하나 현재 메시지가 끝난후에 수행되어
	//이 시점에는 그려지지 않는다.

	OnCommandInvalid = TRUE;
	view_ControlInit(hwnd);			//cur_data -> Control
	OnCommandInvalid = FALSE;
}

void view_SetTimer(HWND hwnd)	//OnCreate에서 사용됨 : 타이머 설정
{
	SetTimer(hwnd, 1, 1000, NULL);	//ID가 1인 1000ms단위의 타이머를 설정하고 주기마다 WM_TIMER 호출
	SendMessage(hwnd, WM_TIMER, 1, NULL);
	//이 메시지를 전송하는 이유는 현재 WM_CREATE메시지 처리중이므로 WM_TIMER 메시지를 좀 나중에 처리한다.
	//ShowWindow함수 수행 직후 GetMessage - DispatchMessage를 만나 메시지를 처리하는 시점부터 처리된다.
	//WM_TIMER를 OnCreate 당시에 큐에 전송하여 강제로 발생시켜 수행한다.
}

void view_SetTimeToWindowText(HWND hwnd)
{
	SYSTEMTIME st;	//
	TCHAR buf[256];
	GetLocalTime(&st);
	wsprintf(buf, TEXT("현재 시간 - %04d년 %02d월 %02d일"), st.wYear, st.wMonth, st.wDay);
	wsprintf(buf + _tcslen(buf), TEXT("  %02d:%02d:%02d"), st.wHour, st.wMinute, st.wSecond);
	SetWindowText(hwnd, buf);
}

void view_ShapePrint(HDC hdc, vector<DRAWTYPE> *g_veclist) //OnPaint에서 사용됨 : 벡터에 저장된 모든 그림을 그림
{
	for (int i = 0; i < (int)g_veclist->size(); i++)	//vector에 저장된 수만큼 반복
	{
		DRAWTYPE dt = (*g_veclist)[i];	//역참조를해야 그쪽에 배열이 존재한다. 먼저 g_veclist의 역참조를 한후 인덱스를 찾는다.

		HBRUSH br;	//임시 브러쉬 핸들 변수
		if (dt.transparentFlag)		//현재 요소의 투명여부
			br = (HBRUSH)GetStockObject(NULL_BRUSH);	//미리정의된 투명브러쉬의 정보를 br에대입
		else
			br = CreateSolidBrush(dt.color);			//현재 요소의 RGB값 브러쉬를 생성하여 br에 대입

		HBRUSH oldbr = (HBRUSH)SelectObject(hdc, br);	//위에서 설정한 브러쉬로 변경후 이전정보는 oldbr에 대입

		HPEN pn = CreatePen(PS_SOLID, dt.penwidth, RGB(255,145,169));	//현재요소의 선굵기의 실선을 생성
		HPEN oldpn = (HPEN)SelectObject(hdc, pn);		//위에서 설정한 팬으로 변경후 이전정보는 oldpn에 대입

		if (dt.type == 1)	//현재요소의 type이 1인 경우
			Rectangle(hdc, dt.pt.x-25, dt.pt.y-25, dt.pt.x + 25, dt.pt.y + 25);	//사각형을 그림
		else if (dt.type == 2)
			Ellipse(hdc, dt.pt.x-25, dt.pt.y-25, dt.pt.x + 25, dt.pt.y + 25);	//타원을 그림

		DeleteObject(SelectObject(hdc, oldbr));	//위에서 사용했던 브러쉬, 팬을 이전정보로 변경후 소멸
		DeleteObject(SelectObject(hdc, oldpn));
	}
}

void view_PreviewColorPrint(HDC hdc)	//OnPaint에서 사용됨 : RGB EDIT컨트롤 값의 색을 가진 사각형을 그림
{
	HBRUSH br;	//임시 브러쉬 핸들 변수
	//if ((submenu3 == ID_40008 || cur_data.transparentFlag == TRUE) && cur_data.color == RGB(255, 255, 255))
	if(cur_data.transparentFlag)
			//메뉴에 투명이 선택되있거나 cur_data의 투명이 활성화 되있고 RGB가 흰색인경우
		br = (HBRUSH)GetStockObject(NULL_BRUSH);	//미리정의된 투명브러쉬의 정보를 br에대입
	else
		br = CreateSolidBrush(cur_data.color);	//cur_data의 RGB값의 브러쉬를 생성하여 br에 대입

	HBRUSH oldbr = (HBRUSH)SelectObject(hdc, br);	//위에서 설정한 브러쉬로 변경후 이전정보는 oldbr에 대입

	MoveToEx(hdc, 150, 100, NULL);	//선을 그림
	LineTo(hdc, 210, 180);
	MoveToEx(hdc, 150, 180, NULL);
	LineTo(hdc, 210, 100);

	Rectangle(hdc, 150, 100, 210, 180);	//사각형을 그림

	DeleteObject(SelectObject(hdc, oldbr));	//위에서 사용했던 브러시를 이전걸로 변경후 사용했던 브러쉬를 소멸
}

void view_NewFile(HWND hwnd)
{
	OnCommandInvalid = TRUE;	//값을 수정하는동안 OnCommand 무효화
	DrawInit(&cur_data);		//cur_data를 초기상태로 변경
	g_veclist.clear();			//vector리스트를 초기화
	view_ControlInit(hwnd);		//Control을 초기화한다.(cur_data로 부터 읽는다.)
	InvalidateRect(hwnd, &InvalidArea, TRUE);	//InvalidArea영역을 무효화시키고 지운다.
	view_ControlListBoxPrint(hwnd);			//ListBox컨트롤을 출력한다
	OnCommandInvalid = FALSE;	//값 초기화가 완료되어 OnCommand 유효화
}

void view_RefreshSetting(HWND hwnd)
{
	OnCommandInvalid = TRUE;	//값을 수정하는동안 OnCommand 무효화
	if (ShapeUpdateMode)
	{
		view_ControlInit(hwnd);						//cur_data -> Control
		view_UpdateShapeByEditControl(hwnd);	//Control -> cur_data -> c_veclist[idx]
	}
	else
	{
		view_ControlInit(hwnd);		//cur_data -> Control
		view_GetControlData(hwnd);	//Control -> cur_data
	}
	OnCommandInvalid = FALSE;	//값 수정이 완료되어 OnCommand 유효화
}

void view_UpdateShapeByLBControl(HWND hwnd)	//g_veclist[idx] -> cur_data -> Control
{
	OnCommandInvalid = TRUE;	//이 함수를 수행하는동안 OnCommand 메시지는 처리하지 않음

	int idx = SendMessage(hListSave, LB_GETCURSEL, 0, 0);	//리스트박스의 커서를 달라는 메시지 보냄

	cur_data = g_veclist[idx];	//vector의 idx 인덱스 요소를 cur_data에 대입

	view_ControlInit(hwnd);		//cur_data -> Control

	//if (dt.type == 1)	//버튼 핸들의 채크정보를 가져오는 메시지
	//{
	//	SendMessage(hRadioRectangle, BM_SETCHECK, BST_CHECKED, 0);
	//	SendMessage(hRadioEllipse, BM_SETCHECK, BST_UNCHECKED, 0);
	//}
	//else
	//{
	//	SendMessage(hRadioRectangle, BM_SETCHECK,BST_UNCHECKED, 0);
	//	SendMessage(hRadioEllipse, BM_SETCHECK, BST_CHECKED, 0);
	//}

	//SetDlgItemInt(hwnd, IDC_EDITPOSX, dt.pt.x, 0);
	//SetDlgItemInt(hwnd, IDC_EDITPOSY, dt.pt.y, 0);

	//SetDlgItemInt(hwnd, IDC_EDITCOLORR, GetRValue(dt.color), 0);
	//SetDlgItemInt(hwnd, IDC_EDITCOLORG, GetGValue(dt.color), 0);
	//SetDlgItemInt(hwnd, IDC_EDITCOLORB, GetBValue(dt.color), 0);

	//SendMessage(hComboPenWidth, CB_SETCURSEL, dt.penwidth / 2, 0);
	//InvalidateRect(hwnd, &ExtraInvalidArea, TRUE);

	OnCommandInvalid = FALSE; //지금부터 OnCommand 메시지는 처리
}

void view_UpdateShapeByEditControl(HWND hwnd)	//Control -> cur_data -> c_veclist[idx]
{
	int i = SendMessage(hListSave, LB_GETCURSEL, 0, 0);	//리스트박스의 커서를 달라는 메시지 보냄

	if (i == LB_ERR)	//위 메시지의 반환값이 에러값일 경우
		return;
	else
	{

		view_GetControlData(hwnd);	//Control -> cur_data
		g_veclist[i] = cur_data;	//vector의 i번째 요소는 cur_data로 대체
		
		
		//if (SendMessage(hRadioRectangle, BM_GETCHECK, 0, 0) == BST_CHECKED)	//버튼 핸들의 채크정보를 가져오는 메시지
		//	g_veclist[i].type = 1;
		//else
		//	g_veclist[i].type = 2;

		//g_veclist[i].pt.x = GetDlgItemInt(hwnd, IDC_EDITPOSX, 0, 0);
		//g_veclist[i].pt.y = GetDlgItemInt(hwnd, IDC_EDITPOSY, 0, 0);

		//g_veclist[i].color = RGB(
		//	(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORR, 0, 0),
		//	(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORG, 0, 0),
		//	(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORB, 0, 0));

		//(submenu3 == ID_40008 && cur_data.color == RGB(255, 255, 255)) ?
		//	g_veclist[i].transparentFlag = TRUE : g_veclist[i].transparentFlag = FALSE;

		//g_veclist[i].penwidth = SendMessage(hComboPenWidth, CB_GETCURSEL, 0, 0) * 2 + 1;

		view_ControlListBoxPrint(hwnd);	//vector에 저장된 요소들의 정보를 리스트박스에 출력

		SendMessage(hListSave, LB_SETCURSEL, i, 0);	//리스트박스가 갱신되었으므로 원래 선택되있던 인덱스를 다시 선택

		InvalidateRect(hwnd, &InvalidArea, TRUE);	//그리기 영역 무효화
		InvalidateRect(hwnd, &ExtraInvalidArea, TRUE);

		return;
	}
}

