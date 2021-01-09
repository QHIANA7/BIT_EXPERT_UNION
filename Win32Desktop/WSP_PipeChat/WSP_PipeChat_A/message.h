#pragma once
//message.h

void msg_CreatePipe(HWND hDlg);
void msg_SendData(TCHAR * msg);

//수신함수 (스레드)
DWORD WINAPI msg_RecvThread(void* p);
