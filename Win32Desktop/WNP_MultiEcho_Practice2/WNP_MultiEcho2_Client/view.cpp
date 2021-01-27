//view.cpp
#include "std.h"



void view_GetControlHandle(HWND hDlg)
{
	//==================== 기존 ==============================
	hEditID = GetDlgItem(hDlg, IDC_EDITID);
	hEditPW = GetDlgItem(hDlg, IDC_EDITPW);
	hButtonLogin = GetDlgItem(hDlg, IDC_BUTTONLOGIN);
	hButtonLogout = GetDlgItem(hDlg, IDC_BUTTONLOGOUT);
	hButtonAddMember = GetDlgItem(hDlg, IDC_BUTTONADDMEMBER);
	hButtonDeleteMember = GetDlgItem(hDlg, IDC_BUTTONDELETEMEMBER);
	hEditRecvMessage = GetDlgItem(hDlg, IDC_EDITRECVMESSAGE);
	hEditSendMessage = GetDlgItem(hDlg, IDC_EDITSENDMESSAGE);
	hButtonSend = GetDlgItem(hDlg, IDC_BUTTONSEND);
	hEditForeGround = GetDlgItem(hDlg, IDC_EDITFOREGROUND);
	hProgressBar = GetDlgItem(hDlg, IDC_PROGRESS1);
	hStaticConnection = GetDlgItem(hDlg, IDC_STATICCONNECTION);
	//=========================================================	
}

void view_InitControl(HWND hDlg)
{
	view_ControlEnableBeforeConnection();
}

void view_GetDelMemberData(HWND hDlg, PMEMBER data)
{
	GetDlgItemText(hDlg, IDC_EDITID, data->id, sizeof(data->id));
}

void view_GetAddMemberData(HWND hDlg, PMEMBER data)	//회원가입 모달에서 사용
{
	GetDlgItemText(hDlg, IDC_ADDMEMBEREDITID, data->id, sizeof(data->id));
	GetDlgItemText(hDlg, IDC_ADDMEMBEREDITPW, data->pw, sizeof(data->pw));
	GetDlgItemText(hDlg, IDC_ADDMEMBEREDITNICK, data->nickname, sizeof(data->nickname));
}

void view_GetLoginData(HWND hDlg, PLOGIN data)
{
	GetDlgItemText(hDlg, IDC_EDITID, data->id, sizeof(data->id));
	GetDlgItemText(hDlg, IDC_EDITPW, data->pw, sizeof(data->pw));
}

void view_GetMessageData(HWND hDlg, PMESSAGE data)
{
	wsprintf(data->nickname, LoginNick);
	GetDlgItemText(hDlg, IDC_EDITSENDMESSAGE, data->msg, sizeof(data->msg));
	//TCHAR msg[MAX_MESSAGE_LENGHT];
	//GetDlgItemText(hDlg, IDC_EDITSENDMESSAGE, msg, sizeof(msg));
	//wsprintf(data->msg, TEXT("[%s] %s"), data->nickname, msg);
	//wsprintf(data->msg, msg);
}

void view_GetSendMessage(LPTSTR msg)
{
	//================ 컨트롤로 부터 문자열을 받기위한 초기화 ========================
	memset(msg, 0, MAX_BUFFER_USE_SIZE);
	//================================================================================
	GetWindowText(hEditSendMessage, msg, MAX_BUFFER_USE_SIZE);	//획득 : 여기까지는 유니코드
}

void view_AddRecvMessage(LPTSTR msg)
{
	EnterCriticalSection(&cs_logmsg);
	SendMessage(hEditRecvMessage, EM_REPLACESEL, 0, (LPARAM)msg);
	SendMessage(hEditRecvMessage, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
	LeaveCriticalSection(&cs_logmsg);
}

void view_ControlEnableBeforeLogin()
{
	Edit_Enable(hEditID, TRUE);
	Edit_Enable(hEditPW, TRUE);
	Edit_Enable(hEditRecvMessage, FALSE);
	Edit_Enable(hEditSendMessage, FALSE);

	Button_Enable(hButtonDeleteMember, FALSE);
	Button_Enable(hButtonLogout, FALSE);
	Button_Enable(hButtonAddMember, TRUE);
	Button_Enable(hButtonLogin, TRUE);
	Button_Enable(hButtonSend, FALSE);

	ShowWindow(hButtonLogin, SW_SHOW);
	ShowWindow(hButtonAddMember, SW_SHOW);
	ShowWindow(hButtonLogout, SW_HIDE);
	ShowWindow(hButtonDeleteMember, SW_HIDE);

	SetWindowText(hEditID, TEXT(""));
	SetWindowText(hEditPW, TEXT(""));
}
void view_ControlEnableAfterLogin()
{
	Edit_Enable(hEditID, FALSE);
	Edit_Enable(hEditPW, FALSE);
	Edit_Enable(hEditRecvMessage, TRUE);
	Edit_Enable(hEditSendMessage, TRUE);

	Button_Enable(hButtonDeleteMember, TRUE);
	Button_Enable(hButtonLogout, TRUE);
	Button_Enable(hButtonAddMember, FALSE);
	Button_Enable(hButtonLogin, FALSE);
	Button_Enable(hButtonSend, TRUE);

	ShowWindow(hButtonLogin, SW_HIDE);
	ShowWindow(hButtonAddMember, SW_HIDE);
	ShowWindow(hButtonLogout, SW_SHOW);
	ShowWindow(hButtonDeleteMember, SW_SHOW);
}
void view_ControlEnableBeforeConnection()
{
	Button_Enable(hButtonDeleteMember, FALSE);
	Button_Enable(hButtonLogin, FALSE);
	Button_Enable(hButtonLogout, FALSE);
	Button_Enable(hButtonAddMember, FALSE);
	Button_Enable(hButtonSend, FALSE);

	Edit_Enable(hEditID, FALSE);
	Edit_Enable(hEditPW, FALSE);
	Edit_Enable(hEditRecvMessage, FALSE);
	Edit_Enable(hEditSendMessage, FALSE);

	ShowWindow(hButtonLogout, SW_HIDE);
	ShowWindow(hButtonLogin, SW_SHOW);
	ShowWindow(hButtonAddMember, SW_SHOW);
}
void view_ControlEnableAfterConnection()
{
	Button_Enable(hButtonLogin, TRUE);
	Button_Enable(hButtonAddMember, TRUE);

	Edit_Enable(hEditID, TRUE);
	Edit_Enable(hEditPW, TRUE);
}
void view_ControlVisibleOnConnection()
{
	ShowWindow(hEditForeGround, SW_SHOW);
	ShowWindow(hProgressBar, SW_SHOW);
	ShowWindow(hStaticConnection, SW_SHOW);
}
void view_ControlInvisibleOnConnection()
{
	ShowWindow(hEditRecvMessage, SW_SHOW);
	ShowWindow(hEditForeGround, SW_HIDE);
	ShowWindow(hProgressBar, SW_HIDE);
	ShowWindow(hStaticConnection, SW_HIDE);
}

void view_GetIpAndPort(HWND hDlg, PDWORD ip, PUSHORT port)
{
	//미사용
	//*port = GetDlgItemInt(hDlg, IDC_EDITPORT, 0, 0);
	//SendMessage(hIpadress, IPM_GETADDRESS, 0, (LPARAM)ip);
}

void view_ServerConnectionPrint(HWND hDlg)
{
	if (!ServerConnected)
	{
		ShowWindow(hEditForeGround, SW_SHOW);
		ShowWindow(hStaticConnection, SW_SHOW);
		ShowWindow(hProgressBar, SW_SHOW);

		ShowWindow(hEditID, SW_HIDE);
		ShowWindow(hEditPW, SW_HIDE);
		ShowWindow(hEditRecvMessage, SW_HIDE);
		ShowWindow(hEditSendMessage, SW_HIDE);
		ShowWindow(hButtonLogin, SW_HIDE);
		ShowWindow(hButtonLogout, SW_HIDE);
		ShowWindow(hButtonAddMember, SW_HIDE);
		ShowWindow(hButtonDeleteMember, SW_HIDE);
		ShowWindow(hButtonSend, SW_HIDE);

		ShowWindow(GetDlgItem(hDlg, IDC_STATICGROUPBOX), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_STATICID), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_STATICPW), SW_HIDE);

		ShowWindow(hDlg, SW_RESTORE);
	}

	else
	{
		ShowWindow(hEditForeGround, SW_HIDE);
		ShowWindow(hStaticConnection, SW_HIDE);
		ShowWindow(hProgressBar, SW_HIDE);

		ShowWindow(hEditID, SW_SHOW);
		ShowWindow(hEditPW, SW_SHOW);
		ShowWindow(hEditRecvMessage, SW_SHOW);
		ShowWindow(hEditSendMessage, SW_SHOW);
		ShowWindow(hButtonLogin, SW_SHOW);
		ShowWindow(hButtonLogout, SW_SHOW);
		ShowWindow(hButtonAddMember, SW_SHOW);
		ShowWindow(hButtonDeleteMember, SW_SHOW);
		ShowWindow(hButtonSend, SW_SHOW);

		ShowWindow(GetDlgItem(hDlg, IDC_STATICGROUPBOX), SW_SHOW);
		ShowWindow(GetDlgItem(hDlg, IDC_STATICID), SW_SHOW);
		ShowWindow(GetDlgItem(hDlg, IDC_STATICPW), SW_SHOW);
		ShowWindow(hDlg, SW_RESTORE);
	}
}
