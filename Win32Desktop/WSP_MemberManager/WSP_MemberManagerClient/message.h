#pragma once

//message.h

typedef struct tagMESSAGE {

}MESSAGE;

BOOL msg_DataSend(HWND hDlg, int flag, DATA data);

BOOL msg_ShootMessage(HWND hDlg, TCHAR *nickname, TCHAR *msg, int flag);