#include "std.h"

//�ۼ����� ���� ���ҽ��� ����϶�. ���̾�α� ID ���� �� �����ϸ� rc���� ���ҽ������ �ڵ��߰���

SERVERINFO si;

CRITICAL_SECTION cs, cs_logmsg, cs_connection;

HANDLE hEventConnectionSuccess;

HWND g_hDlg, hEditID, hEditPW, hEditRecvMessage, hEditSendMessage,
hButtonSend, hButtonLogin, hButtonLogout, hButtonAddMember, hButtonDeleteMember,
hProgressBar, hEditForeGround, hStaticConnection;

BOOL ServerConnected, LoginState, ConnectProcessing;

TCHAR LoginNick[20];

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_TIMER:
		return OnTimer(hDlg, wParam, lParam);
	case WM_INITDIALOG:
		return OnInitDialog(hDlg, wParam, lParam);
	case WM_COMMAND:
		return OnCommand(hDlg, wParam, lParam);

	}
	return FALSE;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd) {

	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_MAINDLG),	// ���̾�α� ����
		0,			// �θ� ������
		DlgProc);			// Proc..
	return 0;
}
