#pragma once
//handler.h
void OnACInputSelect(HWND hDlg);
void OnACDeleteSelect(HWND hDlg);
void OnBankingButtonSelect(HWND hDlg);

BOOL OnNotify(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnInitDialogAtModaless(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnMouseMove(HWND hDlg, WPARAM wParam, LPARAM lParam);
LRESULT OnInitMenuPopUp(HWND hDlg, WPARAM wParam, LPARAM lParam);