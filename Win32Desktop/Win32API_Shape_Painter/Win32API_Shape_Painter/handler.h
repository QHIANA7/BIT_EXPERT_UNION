#pragma once
//handler.h

BOOL IsContainPos(POINT pt, RECT rt);

void OnEditPos(HWND hwnd, WPARAM wParam);
void OnEditColor(HWND hwnd, WPARAM wParam);
void OnRadioDrawType(HWND hwnd, WPARAM wParam);
void OnComboPenWidth(HWND hwnd, WPARAM wParam);
void OnListSave(HWND hwnd, WPARAM wParam);

LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnInitMenuPopUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnTimer(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam);