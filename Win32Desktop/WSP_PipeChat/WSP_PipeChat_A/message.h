#pragma once
//message.h

void msg_CreatePipe(HWND hDlg);
void msg_SendData(TCHAR * msg);

//�����Լ� (������)
DWORD WINAPI msg_RecvThread(void* p);
