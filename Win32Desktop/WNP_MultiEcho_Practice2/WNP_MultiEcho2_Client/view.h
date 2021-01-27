#pragma once
//view.h

void view_GetIpAndPort(HWND hDlg, PDWORD ip, PUSHORT port);


void view_GetControlHandle(HWND hDlg);
void view_InitControl(HWND hDlg);



void view_GetDelMemberData(HWND hDlg, PMEMBER data);
void view_GetAddMemberData(HWND hDlg, PMEMBER data);
void view_GetLoginData(HWND hDlg, PLOGIN data);
void view_GetMessageData(HWND hDlg, PMESSAGE data);



void view_GetSendMessage(LPTSTR msg);
void view_AddRecvMessage(LPTSTR msg);


void view_ControlEnableBeforeLogin();
void view_ControlEnableAfterLogin();
void view_ControlEnableBeforeConnection();
void view_ControlEnableAfterConnection();
void view_ControlVisibleOnConnection();
void view_ControlInvisibleOnConnection();



void view_ServerConnectionPrint(HWND hDlg);
