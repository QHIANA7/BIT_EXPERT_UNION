#pragma once
//view.h

void view_GetProcessName(HWND hDlg, TCHAR *temp);
void view_PrintAllProcessInfo(HWND hDlg);
void view_ListProcessInfoSelectChange(HWND hDlg);
void view_SetProcessState(HWND hDlg, DWORD code);
void view_DeleteProcessListByHandle(HANDLE hProcess);
void view_SetProcessInfoInit(HWND hDlg);

void view_GetControlHandle(HWND hDlg);
void view_InitControl(HWND hDlg);
void view_ListViewPrintAll(HWND hDlg);