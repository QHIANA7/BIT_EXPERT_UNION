//dlgmodal.cpp

#include "std.h"

BOOL CALLBACK DlgModalProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PUINT port;
	switch (msg)
	{
	case WM_INITDIALOG:	//��ȭ���ڰ� ������ ����
	{
		port = (PUINT)lParam;
		SetDlgItemInt(hDlg, IDC_EDITPORT, *port, 0);
	}
	return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:	//������ ��������!
		{
			*port = GetDlgItemInt(hDlg, IDC_EDITPORT, 0, 0);
			EndDialog(hDlg, IDOK);	//��ȭ���ڸ� �ݰ� IDOK�� ��ȯ
		}
		return TRUE;

		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return TRUE;
		}
	}
	return FALSE;
}
