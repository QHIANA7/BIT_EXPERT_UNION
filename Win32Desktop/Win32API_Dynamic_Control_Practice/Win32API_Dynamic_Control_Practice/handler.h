#pragma once
//handler.h
void OnButtonJoin(HWND hwnd);
void OnButtonCancle(HWND hwnd);
void OnButtonUpdate(HWND hwnd);
void OnButtonDelete(HWND hwnd);
void OnListBox(HWND hwnd, WPARAM wParam);

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);