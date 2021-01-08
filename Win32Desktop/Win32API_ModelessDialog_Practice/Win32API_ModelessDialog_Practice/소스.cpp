//�ҽ�.cpp
#include "std.h"

//�ۼ����� ���� ���ҽ��� ����϶�. ���̾�α� ID ���� �� �����ϸ� rc���� ���ҽ������ �ڵ��߰���

WNDPROC old;	//���� ���ν����� ������� ���� ���������ν��� ����

//===================================================================
//���� �ڵ�
HWND hListView, hEditName, hEditNum, hButtonBanking;
HWND g_hDlg;
//===================================================================

//===================================================================
vector<ACCOUNTINFO> g_veclist;	//�ŷ��������� ������� ����
ACCOUNT cur_data;	//������ ����
BOOL account_exist = FALSE;	//���°� �����Ǿ��ִ°�.
//===================================================================

//����Ʈ ��Ʈ�ѿ��� ������ ����

//edit ��Ʈ�ѿ� ���� ���ν��� ���Ǹ� �Ͻʽÿ�
LRESULT CALLBACK EditProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CHAR:
		if ((wParam >= '0' && wParam <= '9' || wParam == 8))
			return CallWindowProc(old, hDlg, msg, wParam, lParam);
		return 0;	//���� ( DlgProc���� ���� ����)
	}
	// ó������ ���� �޽����� DlgProc���� ����
	return CallWindowProc(old, hDlg, msg, wParam, lParam);
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_NOTIFY:	    return OnNotify(hDlg, wParam, lParam);
	case WM_INITDIALOG: return OnInitDialog(hDlg, wParam, lParam);
	case WM_COMMAND:	return OnCommand(hDlg, wParam, lParam);
	case WM_MOUSEMOVE: return OnMouseMove(hDlg, wParam, lParam);
	case WM_INITMENUPOPUP:	return OnInitMenuPopUp(hDlg, wParam, lParam);
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd)
{
	UINT ret = DialogBox(hInst,// instance 
		MAKEINTRESOURCE(IDD_MAINDIALOG), // ���̾�α� ���� 
		0, // �θ� ������ 
		DlgProc); // Proc.. 
	return 0;
}
