#pragma once
//view.h

void view_ControlCreate(HWND hwnd);
void view_ControlInit(HWND hwnd);
void view_ControlListBoxPrint(HWND hwnd);
void view_GetControlData(HWND hwnd);
void view_SetControlData(HWND hwnd);

void view_DrawShape(HWND hwnd, DRAWTYPE * dt, WPARAM wParam, LPARAM lParam);

void view_SetTimer(HWND hwnd);
void view_SetTimeToWindowText(HWND hwnd);

void view_ShapePrint(HDC hdc, vector<DRAWTYPE> *g_veclist);
void view_PreviewColorPrint(HDC hdc);

void view_NewFile(HWND hwnd);
void view_RefreshSetting(HWND hwnd);

void view_UpdateShapeByLBControl(HWND hwnd);
void view_UpdateShapeByEditControl(HWND hwnd);