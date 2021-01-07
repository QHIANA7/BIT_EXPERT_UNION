//data.h

typedef struct tagDATA
{
	TCHAR name[20];
	int idx;
}DATA;

//================================================
extern HWND hListView, hEditName, hEditNum,
hRadioM, hRadioF, hComboSubject;
//================================================
extern WNDPROC old;
//================================================
extern vector<MEMBER> g_veclist;
//================================================
extern DATA g_selectlist;

extern LRESULT CALLBACK EditProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);