//dlgmodalaccdelete.cpp
#include "std.h"

BOOL CALLBACK DlgModalAccDeleteProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	static ACCOUNT *pData;
	HWND hName = GetDlgItem(hDlg, IDC_EDITNAMEDEL);
	HWND hAccountNumber = GetDlgItem(hDlg, IDC_EDITACCOUNTNUMDEL);
	switch (msg)
	{
	case WM_INITDIALOG:	pData = (ACCOUNT*)lParam;
		Edit_SetReadOnly(hName, TRUE);
		Edit_SetReadOnly(hAccountNumber, TRUE);
		SetDlgItemText(hDlg, IDC_EDITNAMEDEL, pData->name);
		SetDlgItemInt(hDlg, IDC_EDITACCOUNTNUMDEL, pData->accountnumber, 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:	//삭제를 눌렀구나!
			EndDialog(hDlg, IDOK);
			return TRUE;
		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return 0;
		}
	}
	return FALSE;
}