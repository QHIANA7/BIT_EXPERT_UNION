#pragma once
//view.h

void view_SelectPrint(HWND hwnd, int idx);
void view_ControlListBoxPrint(HWND hwnd);
void view_ControlListBoxPrint1(HWND hwnd);
void view_ControlCreate(HWND hwnd);	//Create�� ���ؼ� �θ��ڵ鰪�� �ʿ���
void view_ControlInit(HWND hwnd);
void view_GetControlData(HWND hwnd, MEMBER *mem);
void view_SetControlData(HWND hwnd);



void view_PrintMemberInfoToMessageBox(HWND hwnd, MEMBER * mem);