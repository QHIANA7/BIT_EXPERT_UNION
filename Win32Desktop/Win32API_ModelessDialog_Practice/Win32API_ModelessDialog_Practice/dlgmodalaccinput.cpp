//dlgmodalaccinput.cpp
#include "std.h"

//��� ��ȭ���ڿ��� �߻��ϴ� �޽����� ó���� ���ν���
BOOL CALLBACK DlgModalAccInputProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	static ACCOUNT *pData;
	switch (msg)
	{
	case WM_INITDIALOG:	//��ȭ���ڰ� ������ ����
	{
		pData = (ACCOUNT*)lParam; //������ LPARAM�� �����Ͱ� �ѰܿԴ�.
		//SetDlgItemText(hDlg, IDC_EDITNAME, pData->name);//��Ʈ�� -> Data
		//SetDlgItemInt(hDlg, IDC_EDITACCOUNTNUM, pData->accountnumber, 0);
		//Get/SetDlgItem ���� �Լ��� ������ �ڵ��� �ʿ���ٴ� ���Դϴ�.
	}
	return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:	//����� ��������!
		{
			pData->accountnumber = GetDlgItemInt(hDlg, IDC_EDITACCOUNTNUM, 0, 0);
			GetDlgItemText(hDlg, IDC_EDITNAME, pData->name, sizeof(pData->name));
			pData->balance = 0;
			EndDialog(hDlg, IDOK);	//��ȭ���ڸ� �ݰ� IDOK�� ��ȯ
		}
		return TRUE;

		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return TRUE;
		}
	}
	return FALSE;
}