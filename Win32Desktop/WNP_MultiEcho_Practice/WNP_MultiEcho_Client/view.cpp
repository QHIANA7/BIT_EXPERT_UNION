//view.cpp
#include "std.h"



void view_GetControlHandle(HWND hDlg)
{
	hIpadress = GetDlgItem(hDlg, IDC_IPADDRESS);
	hEditPort = GetDlgItem(hDlg, IDC_EDITPORT);
	hEditRecvMessage = GetDlgItem(hDlg, IDC_EDITRECVMESSAGE);
	hEditSendMessage = GetDlgItem(hDlg, IDC_EDITSENDMESSAGE);
	hButtonConnect = GetDlgItem(hDlg, IDC_BUTTONCONNECT);
	hButtonClose = GetDlgItem(hDlg, IDC_BUTTONCLOSE);
	hButtonSend = GetDlgItem(hDlg, IDC_BUTTONSEND);
	hEditForeGround = GetDlgItem(hDlg, IDC_EDITFOREGROUND);
	hProgressBar = GetDlgItem(hDlg, IDC_PROGRESS1);
	hStaticConnection = GetDlgItem(hDlg, IDC_STATICCONNECTION);
}

void view_InitControl(HWND hDlg)
{
	view_ControlEnableBeforeConnection();
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
	SendMessage(hEditRecvMessage, EM_REPLACESEL, 0, (LPARAM)msg);
	SendMessage(hEditRecvMessage, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
}

void view_ControlDisableAll()
{
	//Button_SetState(hButtonClose, FALSE);
	Button_Enable(hButtonConnect, FALSE);
	Button_Enable(hButtonClose, FALSE);
	Button_Enable(hButtonSend, FALSE);

	SendMessage(hIpadress, WM_ENABLE, (WPARAM)FALSE, 0);

	Edit_Enable(hEditPort, FALSE);
	Edit_Enable(hEditRecvMessage, FALSE);
	Edit_Enable(hEditSendMessage, FALSE);
}

void view_ControlEnableBeforeConnection()
{
	Button_Enable(hButtonConnect, TRUE);
	Button_Enable(hButtonClose, FALSE);
	Button_Enable(hButtonSend, FALSE);

	SendMessage(hIpadress, WM_ENABLE, (WPARAM)TRUE, 0);

	Edit_Enable(hEditPort, TRUE);
	Edit_Enable(hEditRecvMessage, FALSE);
	Edit_Enable(hEditSendMessage, FALSE);
}

void view_ControlEnableAfterConnection()
{

	Button_Enable(hButtonConnect, FALSE);
	Button_Enable(hButtonClose, TRUE);
	Button_Enable(hButtonSend, TRUE);

	SendMessage(hIpadress, WM_ENABLE, (WPARAM)FALSE, 0);
	
	Edit_Enable(hEditPort, FALSE);
	Edit_Enable(hEditRecvMessage, TRUE);
	Edit_Enable(hEditSendMessage, TRUE);
	
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
	*port = GetDlgItemInt(hDlg, IDC_EDITPORT, 0, 0);
	SendMessage(hIpadress, IPM_GETADDRESS, 0, (LPARAM)ip);
}
