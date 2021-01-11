//handler.cpp

#include "std.h"

void OnAddMember(HWND hDlg)
{
	DATA data;
	view_GetAddMemberData(hDlg, &data);
	msg_DataSend(hDlg, 1, data);	//1. 회원가입
}

void OnButtonInteractive(HWND hDlg)
{
	DATA data;
	TCHAR buf[32];
	GetDlgItemText(hDlg, IDC_BUTTONINTERACTIVE, buf, sizeof(buf));
	if (_tcscmp(buf, TEXT("로그인")) == (long)0)
	{
		view_GetAddMemberData(hDlg, &data);
		msg_DataSend(hDlg, 3, data);
	}
	else
	{
		view_GetAddMemberData(hDlg, &data);
		msg_DataSend(hDlg, 4, data);	
	}
}

void OnButtonDeleteAccount(HWND hDlg)
{
	DATA data;
	view_GetAddMemberData(hDlg, &data);
	msg_DataSend(hDlg, 2, data);	//2. 회원 탈퇴
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();
	SetTimer(hDlg, 2, 10, 0);
	SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETMARQUEE, (WPARAM)TRUE, (LPARAM)50);
	SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETSTATE, (WPARAM)PBST_NORMAL, 0);
	//SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETRANGE32, 0, 100);
	//SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETPOS, 100, 0);
	//SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETBARCOLOR, 0, (LPARAM)RGB(255, 145, 169));
	
	view_GetControlHandle(hDlg);
	view_SetControlInit(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BUTTONDELETEACCOUNT: OnButtonDeleteAccount(hDlg); break;
	case IDC_BUTTONINTERACTIVE: OnButtonInteractive(hDlg); break;
	case IDOK: OnAddMember(hDlg); break;
	case IDCANCEL: KillTimer(hDlg, 2); EndDialog(hDlg, IDCANCEL);	break;
	}
	return TRUE;
}

BOOL OnCopyData(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	// 여기까지 왔다면 lParam에는 전송된 데이터포인터가 들어있다.
	COPYDATASTRUCT *ps = (COPYDATASTRUCT*)lParam;

	if (ps->dwData == 1)	//회원 정보 DATA
	{
		DATA *pdata = (DATA*)ps->lpData;
		//이런식으로 형변환하여 주면된다. 단, 반드시 구조체의 순서,크기가 동일해야함

	}
	else if (ps->dwData == 2)	//메시지 DATAMESSAGE
	{
		DATAMESSAGE *pdatamsg = (DATAMESSAGE*)ps->lpData;
		//if (pdatamsg->flag == 11)	//회원 가입 - 성공
		//{
		//	MessageBox(hDlg, pdatamsg->msg, TEXT("알림"), MB_OK);
		//	//view_PopUpMessageBox()
		//}
		//else if (pdatamsg->flag == 12)	//회원 가입 - 실패
		//{
		//	MessageBox(hDlg, pdatamsg->msg, TEXT("알림"), MB_OK);
		//	//view_PopUpMessageBox()
		//}
		MessageBox(hDlg, pdatamsg->msg, TEXT("알림"), MB_OK);
		if (pdatamsg->flag == 21)
		{
			view_SetControlInit(hDlg);
			SendMessage(hEditID, EM_SETREADONLY, (WPARAM)FALSE, 0);
			SendMessage(hEditPW, EM_SETREADONLY, (WPARAM)FALSE, 0);
			SendMessage(hEditNickName, EM_SETREADONLY, (WPARAM)FALSE, 0);
			Button_Enable(hButtonOk, TRUE);
			SetDlgItemText(hDlg, IDC_BUTTONINTERACTIVE, TEXT("로그인"));
			ShowWindow(hButtonDeleteAccount, SW_HIDE);
		}
		else if (pdatamsg->flag == 31)	//로그인 성공
		{
			SendMessage(hEditID, EM_SETREADONLY, (WPARAM)TRUE, 0);
			SendMessage(hEditPW, EM_SETREADONLY, (WPARAM)TRUE, 0);
			SendMessage(hEditNickName, EM_SETREADONLY, (WPARAM)TRUE, 0);
			Button_Enable(hButtonOk, FALSE);
			SetDlgItemText(hDlg, IDC_BUTTONINTERACTIVE, TEXT("로그아웃"));
			ShowWindow(hButtonDeleteAccount, SW_SHOW);
			
		}
		else if (pdatamsg->flag == 41)
		{
			view_SetControlInit(hDlg);
			SendMessage(hEditID, EM_SETREADONLY, (WPARAM)FALSE, 0);
			SendMessage(hEditPW, EM_SETREADONLY, (WPARAM)FALSE, 0);
			SendMessage(hEditNickName, EM_SETREADONLY, (WPARAM)FALSE, 0);
			Button_Enable(hButtonOk, TRUE);
			SetDlgItemText(hDlg, IDC_BUTTONINTERACTIVE, TEXT("로그인"));
			ShowWindow(hButtonDeleteAccount, SW_HIDE);
		}
		//view_PopUpMessageBox()
	}

	return TRUE;
}