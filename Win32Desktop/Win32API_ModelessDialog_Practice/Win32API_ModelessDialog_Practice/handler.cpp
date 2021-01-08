//handler.cpp
#include "std.h"

void OnACInputSelect(HWND hDlg)
{
	ACCOUNT data;
	//=========================================================
	//DialogBoxParam : ��� ��ȭ���ڸ� ���
	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_MODALACCOUNTINPUT),	//��� ��ȭ���� ID
		hDlg,		// �θ�
		DlgModalAccInputProc,	// �޼��� ó�� ���ν���
		(LPARAM)&data);			//��ȭ���ڿ� �ѱ� ������ �ּ� LPARAMŸ��
	//����� ��� ��ȭ���ڰ� ������ ������ �� ���ķ� ������� ����
	//��ȭ���ڰ� ������ �� UINT ret�� ���� ID ���� ��
	//=========================================================

	if (ret == IDOK)	//��Ͽ� ���� ���ῴ�� ���
	{
		cur_data = data;
		account_exist = TRUE;
	}
}

void OnACDeleteSelect(HWND hDlg)
{
	ACCOUNT data = cur_data;
	//=========================================================
	//DialogBoxParam : ��� ��ȭ���ڸ� ���
	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_MODALACCOUNTDELETE),	//��� ��ȭ���� ID
		hDlg,		// �θ�
		DlgModalAccDeleteProc,	// �޼��� ó�� ���ν���
		(LPARAM)&data);		// ��� ��ȭ���ڿ� �ѱ� ������ �ּ� LPARAMŸ��
	//����� ��� ��ȭ���ڰ� ������ ������ �� ���ķ� ������� ����
	//��ȭ���ڰ� ������ �� UINT ret�� ���� ID ���� ��
	//=========================================================
	
	if (ret == IDOK)	//������ư�� ���� ���� ���� ���
	{
		account_exist = FALSE;
		AccountInit(&cur_data);			//���� �ʱ�ȭ
		g_veclist.clear();				//����ݳ����� ���� ���� �ʱ�ȭ
		view_ListViewPrintAll(hDlg);	//����Ʈ�� �����
	}
}

void OnBankingButtonSelect(HWND hDlg)
{
	if (g_hDlg == 0)
	{
		//=========================================================
		//static�� ������ ���� ���Ͽ����� ����Ұ�
		//��޸��� ��ȭ���ڿ����� ���������� ����ϴ°��� �ٶ������� ����
		//-> ��޸����� ��� �ٷ� �Լ��� ����Ǳ� ������ ���������� �Ҹ�ȴ�.
		//��å : ���������� ������.
		//=========================================================
		g_hDlg = CreateDialogParam(GetModuleHandle(0),// hinstance
			MAKEINTRESOURCE(IDD_MODALESSBANKING),	//��� ��ȭ���� ID
			hDlg,		// �θ�
			DlgModalessProc, // �޼��� ó�� ���ν���
			(LPARAM)&cur_data);
		ShowWindow(g_hDlg, SW_SHOW);
	}
	else
		SetFocus(g_hDlg);	//�̹� ���������� ��Ŀ���� 
}

BOOL OnNotify(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	
	return TRUE;
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();
	view_GetControlHandle(hDlg);
	view_InitControl(hDlg);
	AccountInit(&cur_data);
	return 0;
}

BOOL OnInitDialogAtModaless(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	
	return 0;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
		//��/��� ��ư
	case IDC_BUTTONBANKING: OnBankingButtonSelect(hDlg); return 0;	
	case ID_ACCOUNTDELETE: OnACDeleteSelect(hDlg); return 0;
	case ID_ACCOUNTINPUT: OnACInputSelect(hDlg); return 0;
	case IDCANCEL:	EndDialog(hDlg, IDCANCEL);return 0;
		//�޴�-���α׷�����
	case ID_PROGEXIT: EndDialog(hDlg, IDCANCEL); return 0;
	}
	return TRUE;
}

BOOL OnMouseMove(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	if (account_exist)
		Button_Enable(hButtonBanking, TRUE);
	else
		Button_Enable(hButtonBanking, FALSE);



	return TRUE;
}

LRESULT OnInitMenuPopUp(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu = (HMENU)wParam;	//�ӽ� �޴��ڵ� ������ ��Ӵٿ� �޴� �ڵ� ����

	if (account_exist)	//���°� �����Ǿ� �ִ� ���
	{
		EnableMenuItem(hMenu, ID_ACCOUNTINPUT, MF_GRAYED);
		EnableMenuItem(hMenu, ID_ACCOUNTDELETE, MF_ENABLED);
	}
	else
	{
		EnableMenuItem(hMenu, ID_ACCOUNTDELETE, MF_GRAYED);
		EnableMenuItem(hMenu, ID_ACCOUNTINPUT, MF_ENABLED);
	}
	return TRUE;
}
