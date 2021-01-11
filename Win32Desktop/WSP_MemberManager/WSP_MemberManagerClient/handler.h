#pragma once

//handler.h

void OnAddMember(HWND hDlg);
void OnButtonInteractive(HWND hDlg);
void OnButtonDeleteAccount(HWND hDlg);

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

BOOL OnCopyData(HWND hDlg, WPARAM wParam, LPARAM lParam);
