//message.cpp

#include "std.h"

BOOL msg_ShootMessage(HWND hDlg, TCHAR * nickname, TCHAR * msg, int flag)
{
	DATAMESSAGE dm;
	dm.flag = flag;
	_tcscpy_s(dm.nickname, NORMAL_TCHAR_LENGTH, nickname);
	_tcscpy_s(dm.msg, MSG_LENGHT, msg);

	COPYDATASTRUCT cds;
	cds.cbData = sizeof(DATAMESSAGE);
	cds.dwData = 2;	//1. ȸ������ 2. �޽���
	cds.lpData = &dm;

	HWND hwnd = FindWindow(0, TEXT("CLIENT"));
	if (hwnd == 0)	//�ڵ� ���޾� �Դܴ�.
	{
		MessageBox(hDlg, TEXT("CLIENT�� ã�� �� �����ϴ�."), TEXT("�˸�"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//SendMessage(hwnd, WM_COPYDATA, (WPARAM)hDlg, (LPARAM)&cds);
	//WM_COPYDATA�� PostMessage�� ����� �� �����ϴ�.
	//���� �������� Ŭ���̾�Ʈ �� ������ ��Ⱓ ��ٸ��°��� �����ϱ����ؼ���
	//SendMessageTimeout�� ����ؾ��մϴ�.
	DWORD result;
	SendMessageTimeout(hwnd, WM_COPYDATA, (WPARAM)hDlg, (LPARAM)&cds, SMTO_NORMAL, 1000, &result);
		return TRUE;
}

