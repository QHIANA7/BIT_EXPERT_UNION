//handler.cpp

#include "std.h"
//파이프생성
void OnCreatePipe(HWND hDlg)
{
	//1.파이프 생성
	msg_CreatePipe(hDlg);

	//2.버튼의 상태값을 변경(파이프 생성 성공시)
	view_ButtonState(FALSE, TRUE);

	//3. 전송에디트 초기화& 포커스
	view_SendEditInitFocus(hDlg);

	//4. 스레드 작동
	CreateThread(0, 0, msg_RecvThread, hDlg, 0, 0);
}

//데이터 전송
void OnSendData(HWND hDlg)
{
	TCHAR msg[256];

	//1.데이터 획득
	view_GetSendData(hDlg, msg);

	//2. 데이터 전송(IPC_Pie)
	msg_SendData(msg);

	//3. 전송에디트 초기화& 포커스
	view_SendEditInitFocus(hDlg);

	//4. 자신의 대화창에 출력
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
		//파이프생성
	case IDC_BUTTON1: OnCreatePipe(hDlg);	break;
		//데이터 전송
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
