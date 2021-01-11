
//소스.cpp
#include "std.h"

//작성전에 먼저 리소스를 등록하라. 다이얼로그 ID 설정 후 저장하면 rc파일 리소스헤더에 자동추가됨
HWND hEditID, hEditPW, hEditNickName, hButtonOk, hButtonInteractive,hButtonDeleteAccount;

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_TIMER:
		view_ServerConnectionPrint(hDlg); return TRUE;
		 break;
	case WM_COPYDATA:
		return OnCopyData(hDlg, wParam, lParam);
	case WM_INITDIALOG:
		return OnInitDialog(hDlg, wParam, lParam);
	case WM_COMMAND:
		return OnCommand(hDlg, wParam, lParam);
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd) {

	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_MAINDLG),	// 다이얼로그 선택
		0,			// 부모 윈도우
		DlgProc);			// Proc..
	return 0;
}
