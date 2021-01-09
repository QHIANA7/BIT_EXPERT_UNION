//handler.h


void OnCreatePipe(HWND hDlg);

void OnSendData(HWND hDlg);

void OnRecvData(HWND hDlg, TCHAR * msg);

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

BOOL OnUserMessage(HWND hDlg, WPARAM wParam, LPARAM lParam);