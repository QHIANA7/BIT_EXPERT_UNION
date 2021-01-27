#pragma once
//handler.h

void OnButtonConnect(HWND hDlg);
void OnButtonSend(HWND hDlg);
void OnButtonAddMember(HWND hDlg);
void OnButtonLogin(HWND hDlg);
void OnButtonLogout(HWND hDlg);
void OnButtonClose();

void OnServerClosed();
void OnServerMessage(LPTSTR msg);


void OnLogMessage(LPTSTR msg);
void OnSpecialMessage(LPTSTR msg);

void OnServerConfig(HWND hDlg);
void OnTryServerConnect();

void OnAddMember(HWND hDlg);
void OnButtonDeleteMember(HWND hDlg);


void OnRecvData(LPTSTR data);

BOOL OnTimer(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);