//dlgmodalserverconfig.cpp

#include "std.h"

HWND hEditAddMemberID, hEditAddMemberPW, hEditAddMemberNick , hButtonIDCheck;

BOOL CALLBACK DlgModalAddMemberProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static SERVERINFO *pData;

	switch (msg)
	{
	case WM_INITDIALOG:	//��ȭ���ڰ� ������ ����
	{
		//==================== �ʱ�ȭ ===========================
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
		case IDOK:	//����� ��������!
		{
			OnAddMember(hDlg);
			EndDialog(hDlg, IDOK);	//��ȭ���ڸ� �ݰ� IDOK�� ��ȯ
		}
		return TRUE;

		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return TRUE;
		}
	}
	return FALSE;
}