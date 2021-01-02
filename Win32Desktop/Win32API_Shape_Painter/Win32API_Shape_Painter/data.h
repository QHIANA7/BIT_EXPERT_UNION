#pragma once
//data.h
#define IDC_RADIORECTANGLE	1
#define IDC_RADIOELLIPSE	2
#define IDC_EDITPOSX		3
#define IDC_EDITPOSY		4
#define IDC_EDITCOLORR		5
#define IDC_EDITCOLORG		6
#define IDC_EDITCOLORB		7
#define IDC_COMBOPENWIDTH	8
#define IDC_EDITSAVECOUNT	9
#define IDC_LISTSAVE		10
#define IDC_EDITMODE		11
#define IDC_EDITTRANSPARENTMODE	12


extern HWND hRadioRectangle, hRadioEllipse, hEditPosX, hEditPosY, hEditColorR, hEditColorG, hEditColorB, hComboPenWidth,
hEditSaveCount, hListSave,hEditMode, hEditTransparentMode;

extern vector<DRAWTYPE> g_veclist;
extern DRAWTYPE cur_data;

extern int submenu2;
extern int submenu3;
extern int submenu4;
extern HDC g_hdc;

extern RECT InvalidArea;
extern RECT ExtraInvalidArea;
extern BOOL OnCommandInvalid;
extern BOOL ShapeUpdateMode;