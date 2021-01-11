#pragma once
//handler.h
void OnCreateProcess(HWND hDlg);
void OnButtonGetProcessStatus(HWND hDlg);
void OnButtonTerminateProcess(HWND hDlg);
void OnListProcessInfo(HWND hDlg, WPARAM wParam);


BOOL OnLButtonDown(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);
