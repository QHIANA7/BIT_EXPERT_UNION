//dlgmodal.cpp

#include "std.h"

BOOL CALLBACK DlgModalProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PUINT port;
	switch (msg)
	{
	case WM_INITDIALOG:	//대화상자가 생성시 수행
	{
		port = (PUINT)lParam;
		SetDlgItemInt(hDlg, IDC_EDITPORT, *port, 0);
	}
	return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:	//실행을 눌렀구나!
		{
			*port = GetDlgItemInt(hDlg, IDC_EDITPORT, 0, 0);
			EndDialog(hDlg, IDOK);	//대화상자를 닫고 IDOK를 반환
		}
		return TRUE;

		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return TRUE;
		}
	}
	return FALSE;
}
