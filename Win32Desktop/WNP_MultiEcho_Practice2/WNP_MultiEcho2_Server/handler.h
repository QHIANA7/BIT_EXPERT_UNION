#pragma once

//handler.h


//mynet -> handler
void OnLogMessage(LPTSTR msg);
void OnClientMessage(LPTSTR msg);
void OnClientConnect(DATA dt);
void OnClientClose(SOCKET sk);

void OnServerRun(HWND hDlg);
void OnServerExit(HWND hDlg);


//===== 리시브 데이터 제어 ======
void OnRecvData(LPTSTR data);

BOOL OnInitMenuPopUp(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);
