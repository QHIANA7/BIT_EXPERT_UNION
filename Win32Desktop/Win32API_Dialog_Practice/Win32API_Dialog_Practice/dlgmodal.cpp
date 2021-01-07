//dlgmodal.cpp
#include "std.h"

BOOL CALLBACK DlgModalProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	static DATA *pData;
	switch (msg)
	{
	case WM_INITDIALOG:	pData = (DATA*)lParam; 
		SetDlgItemText(hDlg, IDC_NAME, pData->name);
		SetDlgItemInt(hDlg, IDC_INDEX, pData->idx,0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return 0;
		}
	}
	return FALSE;
}