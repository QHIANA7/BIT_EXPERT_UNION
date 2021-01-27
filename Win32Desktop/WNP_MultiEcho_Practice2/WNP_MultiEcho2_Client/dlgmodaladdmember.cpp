//dlgmodalserverconfig.cpp

#include "std.h"

HWND hEditAddMemberID, hEditAddMemberPW, hEditAddMemberNick , hButtonIDCheck;

BOOL CALLBACK DlgModalAddMemberProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static SERVERINFO *pData;

	switch (msg)
	{
	case WM_INITDIALOG:	//대화상자가 생성시 수행
	{
		//==================== 초기화 ===========================
		hEditAddMemberID = GetDlgItem(hDlg, IDC_ADDMEMBEREDITID);
		hEditAddMemberPW = GetDlgItem(hDlg, IDC_ADDMEMBEREDITPW);
		hEditAddMemberNick = GetDlgItem(hDlg, IDC_ADDMEMBEREDITNICK);
		hButtonIDCheck = GetDlgItem(hDlg, IDC_ADDMEMBERBUTTONIDCHECK);
		//==========================================================
		pData = (PSERVERINFO)lParam;


	}
	return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:	//등록을 눌렀구나!
		{
			OnAddMember(hDlg);
			EndDialog(hDlg, IDOK);	//대화상자를 닫고 IDOK를 반환
		}
		return TRUE;

		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return TRUE;
		}
	}
	return FALSE;
}