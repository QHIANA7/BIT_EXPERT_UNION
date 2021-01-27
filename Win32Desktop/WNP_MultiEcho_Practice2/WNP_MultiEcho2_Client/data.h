#pragma once

typedef struct tagSERVERINFO
{
	DWORD s_ip = 0;
	USHORT s_port = 0;
}SERVERINFO, * PSERVERINFO;


extern SERVERINFO si;
extern CRITICAL_SECTION cs, cs_logmsg, cs_connection;
extern HANDLE hEventConnectionSuccess;
extern HWND g_hDlg, hEditID, hEditPW, hEditRecvMessage, hEditSendMessage,
	hButtonSend, hButtonLogin, hButtonLogout, hButtonAddMember, hButtonDeleteMember,
	hProgressBar, hEditForeGround, hStaticConnection;

extern BOOL ServerConnected, LoginState, ConnectProcessing;

extern TCHAR LoginNick[20];