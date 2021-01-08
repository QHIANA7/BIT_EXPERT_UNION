//dlgmodaless.cpp
#include "std.h"

BOOL CALLBACK DlgModalessProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	static ACCOUNTINFO temp;
	static ACCOUNT *pData;

	HWND hRadioDeposit = GetDlgItem(hDlg, IDC_RADIODEPOSIT);
	HWND hRadioWithdraw = GetDlgItem(hDlg, IDC_RADIOWHITDRAW);
	
	//HWND Ÿ�Կ� static�� �ٿ��� �� SendMessage�� ���۵��Ͽ���.

	switch (msg)
	{
	case WM_INITDIALOG:
		pData = (ACCOUNT*)lParam;
		SetDlgItemText(hDlg, IDC_EDITBANKINGUSER, pData->name);
		CheckRadioButton(hDlg, IDC_RADIODEPOSIT, IDC_RADIOWHITDRAW,
			IDC_RADIODEPOSIT);
		SetDlgItemInt(hDlg, IDC_EDITBANKINGMONEY, 0, 0);
		//SetDlgItemInt(hDlg, IDC_INDEX, pData->idx,0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDITBANKINGUSER, temp.name, sizeof(temp.name));

			if (SendMessage(hRadioDeposit, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				temp.deposit = GetDlgItemInt(hDlg, IDC_EDITBANKINGMONEY, 0, 0);
				temp.withdraw = 0;
				temp.balance = cur_data.balance + temp.deposit;
				cur_data.balance = temp.balance;
			}
			else
			{
				temp.deposit = 0;
				temp.withdraw = GetDlgItemInt(hDlg, IDC_EDITBANKINGMONEY, 0, 0);
				temp.balance = cur_data.balance - temp.withdraw;
				cur_data.balance = temp.balance;
			}
			GetLocalTime(&(temp.st));
			g_veclist.push_back(temp);
			//�Ʒ��κ��� �θ��� ���ν��� WM_COMMAND���� ó���ϰ� ����(�ݹ�)
			view_ListViewPrintAll(GetParent(hDlg));
			//EndDialog(hDlg, IDCANCEL);	��޸����� ������ ��������
			//��ſ� �θ𿡰� �����Ѵ�

			return 0;
		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	g_hDlg = 0; return 0;
		}
	}
	return FALSE;
}