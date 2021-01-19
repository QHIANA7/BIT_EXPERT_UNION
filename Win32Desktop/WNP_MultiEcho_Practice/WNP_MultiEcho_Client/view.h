#pragma once
//view.h

void view_GetIpAndPort(HWND hDlg, PDWORD ip, PUSHORT port);
void view_GetControlHandle(HWND hDlg);
void view_InitControl(HWND hDlg);

void view_GetSendMessage(LPTSTR msg);

void view_AddRecvMessage(LPTSTR msg);

void view_ControlDisableAll();
void view_ControlEnableBeforeConnection();
void view_ControlEnableAfterConnection();

void view_ControlVisibleOnConnection();
void view_ControlInvisibleOnConnection();