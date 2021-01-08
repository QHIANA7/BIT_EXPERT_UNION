//data.h

#define WM_APPLY WM_USER + 100

//================================================
extern HWND hListView, hEditName, hEditNum, hButtonBanking;
extern HWND g_hDlg;
//================================================
extern WNDPROC old;
//================================================
extern vector<ACCOUNTINFO> g_veclist;
extern ACCOUNT cur_data;
extern BOOL account_exist;
//================================================

extern LRESULT CALLBACK EditProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);