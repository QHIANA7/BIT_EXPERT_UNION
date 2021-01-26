//view.cpp
#include "std.h"

TCHAR *Items[] = { TEXT("컴퓨터정보-보안전공"),TEXT("스마트IT"),TEXT("게임멀티미디어"),TEXT("방송미디어"),TEXT("철도전기시스템") };

void view_SelectPrint(HWND hwnd, int idx)
{
	MEMBER temp = g_veclist[idx];

	SetWindowText(hEditName, temp.name);	//에디트컨트롤에 내용을 빈공간으로 변경(윈도우 상으론 캡션바)
	SetDlgItemInt(hwnd, IDC_EDITNUMBER, (WPARAM)temp.number, 0);	//SetWindowText를 사용해도 된다.
	SendMessage(hComboSubject, CB_SETCURSEL, temp.subject, 0);
	if(temp.gender == TRUE)
		CheckRadioButton(hwnd, IDC_RADIOGENDER1, IDC_RADIOGENDER2, IDC_RADIOGENDER1);
	else
		CheckRadioButton(hwnd, IDC_RADIOGENDER1, IDC_RADIOGENDER2, IDC_RADIOGENDER2);
}

void view_ControlListBoxPrint(HWND hwnd)
{
	TCHAR buf[50];
	SendMessage(hListMember, LB_RESETCONTENT, 0, 0);
	//LB_DELETESTRING메시지 또한 가능하다 매개변수는 i,0이며 i인덱스를 지우는 메시지다.
	for (int i = 0; i < (int)g_veclist.size(); i++)
	{
		MEMBER temp = g_veclist[i];
		wsprintf(buf, TEXT("%s(%d)"), temp.name, temp.number);
		SendMessage(hListMember, LB_ADDSTRING, 0, (LPARAM)buf);
	}
	//LBN_SELCHANGE : 선택이 바뀌었을때 발생하는 메시지
	//LB_GETCURSEL : 리스트박스상의 인덱스를 반환한다.
}

void view_ControlListBoxPrint1(HWND hwnd)
{
	TCHAR buf[50];
	SendMessage(hListMember, LB_RESETCONTENT, 0, 0);
	//LB_DELETESTRING메시지 또한 가능하다 매개변수는 i,0이며 i인덱스를 지우는 메시지다.
	for (int i = 0; i < (int)g_veclist.size(); i++)
	{
		MEMBER temp = g_veclist[i];
		wsprintf(buf, TEXT("%s(%d)"), temp.name, temp.number);
		SendMessage(hListMember, LB_ADDSTRING, 0, (LPARAM)buf);
	}
}

void view_ControlCreate(HWND hwnd)
{
	CreateWindow(TEXT("button"), TEXT("[ 입력창 ]"), WS_CHILD | WS_VISIBLE| BS_GROUPBOX, 5, 5, 300, 300,hwnd,0,0,0);
	CreateWindow(TEXT("static"), TEXT("* 이름"), WS_CHILD | WS_VISIBLE, 20, 30, 60, 20, hwnd, 0, 0, 0);
	hEditName = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 90, 30, 200, 20, hwnd, (HMENU)IDC_EDITNAME, 0, 0);
	
	CreateWindow(TEXT("static"), TEXT("* 성별"), WS_CHILD | WS_VISIBLE, 20, 60, 60, 20, hwnd, 0, 0, 0);
	hRadioGender1 = CreateWindow(TEXT("button"), TEXT("남자"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 90, 60, 50, 20, hwnd, (HMENU)IDC_RADIOGENDER1, 0, 0);
	hRadioGender2 = CreateWindow(TEXT("button"), TEXT("여자"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 60, 50, 20, hwnd, (HMENU)IDC_RADIOGENDER2, 0, 0);
	
	CreateWindow(TEXT("static"), TEXT("* 학과"), WS_CHILD | WS_VISIBLE, 20, 90, 60, 20, hwnd, 0, 0, 0);
	hComboSubject = CreateWindow(TEXT("combobox"), TEXT(""),
		WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | CBS_DROPDOWN
		, 90, 90, 200, 200, hwnd, (HMENU)IDC_COMBOSUBJECT, 0, 0);
	for (int i = 0; i<5; i++) {
		SendMessage(hComboSubject, CB_ADDSTRING, 0, (LPARAM)Items[i]);
	}

	CreateWindow(TEXT("static"), TEXT("* 학번"), WS_CHILD | WS_VISIBLE, 20, 220, 60, 20, hwnd, 0, 0, 0);
	hEditNumber = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 90, 220, 200, 20, hwnd, (HMENU)IDC_EDITNUMBER, 0, 0);

	hButtonJoin = CreateWindow(TEXT("button"), TEXT("등록"), WS_CHILD | WS_VISIBLE, 60, 260, 60, 20, hwnd, (HMENU)IDC_BUTTONJOIN, 0, 0);
	hButtonCancle = CreateWindow(TEXT("button"), TEXT("취소"), WS_CHILD | WS_VISIBLE, 190, 260, 60, 20, hwnd, (HMENU)IDC_BUTTONCANCLE, 0, 0);

	CreateWindow(TEXT("button"), TEXT("[ 멤버리스트 ]"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 320, 5, 220, 300, hwnd, 0, 0, 0);
	hListMember = CreateWindow(TEXT("listbox"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY, 330, 30, 200, 270, hwnd, (HMENU)IDC_LISTMEMBER, 0, 0);
	//listbox 스타일에 LBS_NOTIFY를 추가해줘야 LBN_# 메시지가 발생한다. (중요)

	hButtonUpdate = CreateWindow(TEXT("button"), TEXT("갱신"), WS_CHILD | WS_VISIBLE | BS_MULTILINE, 545, 40, 30, 50, hwnd, (HMENU)IDC_BUTTONUPDATE, 0, 0);
	hButtonDelete = CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_MULTILINE, 545, 200, 30, 50, hwnd, (HMENU)IDC_BUTTONDELETE, 0, 0);
}

void view_ControlInit(HWND hwnd)
{
	SetFocus(hEditName);	//입력받으려고 깜빢깜빢 하는곳이 포커스라고 한다.
	//매개변수에 넘겨준 핸들에 포커스를 준다. 계산기 핸들을 넘겨줬다면 계산기에 포커스가 가있는다.
	CheckRadioButton(hwnd, IDC_RADIOGENDER1, IDC_RADIOGENDER2, IDC_RADIOGENDER1);	//라디오버튼 선택
	SendMessage(hComboSubject, CB_SETCURSEL, 0, 0);	//콤보박스 핸들에 메시지를 보냄
	//CB_SETCURSEL은 콤보박스중 wParam로 넘어간 인덱스의 목록을 선택하라는 것	lParam은 미사용
	//반대로 CB_GETCURSEL은 콤보박스 핸들의 현재 선택된 인덱스의 값을 얻어온다 w,l Param 둘다 0으로 해야한다.
}

void view_GetControlData(HWND hwnd, MEMBER * mem)
{
	GetWindowText(hEditName, mem->name, sizeof(mem->name));
	//핸들값에 컨트롤을 넘겨주면 해당 핸들의 캡션바명을 가져온다-> 컨트롤의 경우 값
	//컨트롤 핸들,담을 장소,담을 장소 크기

	mem->number = GetDlgItemInt(hwnd, IDC_EDITNUMBER, 0, 0);
	//하나의 부모의 창이 있고 그안의 ID아이템의 정수값을 가져옴
	//부모핸들, 컨트롤ID,0,0

	mem->subject = SendMessage(hComboSubject, CB_GETCURSEL, 0, 0);

	if (SendMessage(hRadioGender1, BM_GETCHECK, 0, 0) == BST_CHECKED)	//버튼 핸들의 채크정보를 가져오는 메시지
		mem->gender = TRUE;
	else
		mem->gender = FALSE;
}

void view_SetControlData(HWND hwnd)
{
	SetWindowText(hEditName, TEXT(""));	//에디트컨트롤에 내용을 빈공간으로 변경(윈도우 상으론 캡션바)
	SetDlgItemInt(hwnd, IDC_EDITNUMBER, 0, 0);	//SetWindowText를 사용해도 된다.
	SendMessage(hComboSubject, CB_SETCURSEL, 0, 0);
	CheckRadioButton(hwnd, IDC_RADIOGENDER1, IDC_RADIOGENDER2, IDC_RADIOGENDER1);
}

void view_PrintMemberInfoToMessageBox(HWND hwnd,MEMBER * mem)
{
	TCHAR buf[256];
	wsprintf(buf, TEXT("이름 : %s\n"), mem->name);
	wsprintf(buf + _tcslen(buf), TEXT("학번 : %d\n"), mem->number);
	wsprintf(buf + _tcslen(buf), TEXT("학과코드 : %d\n"), mem->subject);
	wsprintf(buf + _tcslen(buf), TEXT("성별 : %s\n"), mem->gender ? TEXT("남성") : TEXT("여성"));
	MessageBox(hwnd, buf, TEXT("등록된 멤버 정보"), MB_OK);
}
