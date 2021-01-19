#pragma once
//handler.h

DWORD WINAPI ModalessThread(LPVOID data);

void OnButtonConnect(HWND hDlg);
void OnButtonSend(HWND hDlg);
void OnButtonClose();

void OnServerClosed();
void OnServerMessage(LPTSTR msg);
void OnLogMessage(LPTSTR msg);
void OnSpecialMessage(LPTSTR msg);

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);