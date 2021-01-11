#pragma once
//process.h
HANDLE pro_CreateProcess(TCHAR *proName);
void pro_InsertProcessInfo(TCHAR *proName, HANDLE hProcess);
DWORD pro_GetProcessState(HANDLE hProcess);
void pro_ExitProcess(HANDLE hProcess);


void pro_GetTotalCurrentProcessList(HWND hDlg);
void pro_PrintProcessNameAndID(DWORD processID);