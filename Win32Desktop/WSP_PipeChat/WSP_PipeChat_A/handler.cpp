//handler.cpp

#include "std.h"
//����������
void OnCreatePipe(HWND hDlg)
{
	//1.������ ����
	msg_CreatePipe(hDlg);

	//2.��ư�� ���°��� ����(������ ���� ������)
	view_ButtonState(FALSE, TRUE);

	//3. ���ۿ���Ʈ �ʱ�ȭ& ��Ŀ��
	view_SendEditInitFocus(hDlg);

	//4. ������ �۵�
	CreateThread(0, 0, msg_RecvThread, hDlg, 0, 0);
}

//������ ����
void OnSendData(HWND hDlg)
{
	TCHAR msg[256];

	//1.������ ȹ��
	view_GetSendData(hDlg, msg);

	//2. ������ ����(IPC_Pie)
	msg_SendData(msg);

	//3. ���ۿ���Ʈ �ʱ�ȭ& ��Ŀ��
	view_SendEditInitFocus(hDlg);

	//4. �ڽ��� ��ȭâ�� ���
	view_ChatMessagePrint(hDlg,msg);
}
void OnRecvData(HWND hDlg,TCHAR * msg)
{
	view_ChatMessagePrint(hDlg, msg);
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{	
	view_GetControlHandle(hDlg);
	view_ButtonState(TRUE, FALSE);
	SendMessage(hDlg, WM_SETFOCUS, (WPARAM)hEdit3, 0);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
		//����������
	case IDC_BUTTON1: OnCreatePipe(hDlg);	break;
		//������ ����
	case IDC_BUTTON2: OnSendData(hDlg);		break;
	case IDCANCEL: EndDialog(hDlg, IDCANCEL);
		return 0;
	}
	
	return TRUE;
}

BOOL OnUserMessage(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	hRead = (HANDLE)wParam;
	hWrite = (HANDLE)lParam;

	CreateThread(0, 0, msg_RecvThread, hDlg, 0, 0);
	return TRUE;
}
