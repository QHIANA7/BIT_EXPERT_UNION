//view.cpp

#include "std.h"
#include "view.h"

void view_GetAddMemberData(HWND hDlg, DATA * data)
{
	GetDlgItemText(hDlg, IDC_EDITID, data->id, sizeof(data->id));
	GetDlgItemText(hDlg, IDC_EDITPW, data->pw, sizeof(data->pw));
	GetDlgItemText(hDlg, IDC_EDITNICKNAME, data->nickname, sizeof(data->nickname));
}
void view_GetControlHandle(HWND hDlg)
{
	hEditID = GetDlgItem(hDlg, IDC_EDITID);
	hEditPW = GetDlgItem(hDlg, IDC_EDITPW);
	hEditNickName = GetDlgItem(hDlg, IDC_EDITNICKNAME);
	hButtonOk = GetDlgItem(hDlg, IDOK);
	hButtonInteractive = GetDlgItem(hDlg, IDC_BUTTONINTERACTIVE);
	hButtonDeleteAccount = GetDlgItem(hDlg, IDC_BUTTONDELETEACCOUNT);
}
void view_SetControlInit(HWND hDlg)
{
	SetDlgItemText(hDlg, IDC_EDITID, TEXT(""));
	SetDlgItemText(hDlg, IDC_EDITPW, TEXT(""));
	SetDlgItemText(hDlg, IDC_EDITNICKNAME, TEXT(""));
}
void view_ServerConnectionPrint(HWND hDlg)
{

	HWND hwnd = FindWindow(0, TEXT("SERVER"));
	if (hwnd == 0)
	{
		ShowWindow(hEditID, SW_HIDE);
		ShowWindow(hEditPW, SW_HIDE);
		ShowWindow(hEditNickName, SW_HIDE);
		ShowWindow(hButtonOk, SW_HIDE);
		ShowWindow(hButtonInteractive, SW_HIDE);
		ShowWindow(hButtonDeleteAccount, SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC1), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC2), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC3), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC4), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC5), SW_SHOW);
		ShowWindow(GetDlgItem(hDlg, IDC_PROGRESS1), SW_SHOW);
		//SendMessage(GetDlgItem(hDlg, IDC_PROGRESS1), PBM_SETMARQUEE, (WPARAM)TRUE, (LPARAM)0);
	}

	else
	{
		ShowWindow(GetDlgItem(hDlg, IDC_PROGRESS1), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC5), SW_HIDE);
		ShowWindow(hEditID, SW_SHOW);
		ShowWindow(hEditPW, SW_SHOW);
		ShowWindow(hEditNickName, SW_SHOW);
		ShowWindow(hButtonOk, SW_SHOW);
		ShowWindow(hButtonInteractive, SW_SHOW);
		//ShowWindow(hButtonDeleteAccount, SW_SHOW);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC1), SW_SHOW);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC2), SW_SHOW);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC3), SW_SHOW);
		ShowWindow(GetDlgItem(hDlg, IDC_STATIC4), SW_SHOW);
	}
}