//�ҽ�.cpp
#include "std.h"
#include "�ҽ�.h"

//�ۼ����� ���� ���ҽ��� ����϶�. ���̾�α� ID ���� �� �����ϸ� rc���� ���ҽ������ �ڵ��߰���

//���� �����Ų ���μ��� ���
vector<PROCESSINFO> g_veclist;
//�ý��ۿ��� �������� ��ü ���μ��� ���
vector<PROCESSINFO> g_allveclist;

PROCESSINFO cur_data;

HWND hListView;

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		return OnLButtonDown(hDlg, wParam, lParam);
	case WM_INITDIALOG: 	//��ȭ���� ǥ�� ���� ȣ��
		return OnInitDialog(hDlg, wParam, lParam);
	case WM_COMMAND:
		return OnCommand(hDlg, wParam, lParam);
	}
	return FALSE;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd) {

	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_MAINDLG),	// ���̾�α� ����
		0,			// �θ� ������
		DlgProc);			// Proc..
	return 0;
}
