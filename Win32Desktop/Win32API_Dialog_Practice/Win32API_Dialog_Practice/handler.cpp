//handler.cpp
#include "std.h"

void OnButtonJoin(HWND hDlg)
{
	MEMBER mem;
	view_GetControlData(hDlg, &mem);
	g_veclist.push_back(mem);
	//리스트에 전체 출력
	view_ListViewPrintAll(hDlg);
}

void OnFunSelect(HWND hDlg)
{
	DATA data;
	//=========================================================
	data = g_selectlist;
	//=========================================================
	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_DIALOGMODAL),	//모달 대화상자 ID
		hDlg,		// 부모
		DlgModalProc, // 메세지 처리 프로시저
		(LPARAM)&data);
	if (ret == IDOK)
	{

	}
}

BOOL OnNotify(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	LPNMHDR hdr;
	LPNMLISTVIEW nlv;
	LPNMITEMACTIVATE nia;
	hdr = (LPNMHDR)lParam;
	nlv = (LPNMLISTVIEW)lParam;
	TCHAR Caption[255], Temp[255];
	if (hdr->hwndFrom == hListView) {
		switch (hdr->code) {
			//* 선택된 항목을 보여준다.
		case LVN_ITEMCHANGED:
			if (nlv->uChanged == LVIF_STATE && nlv->uNewState ==
				(LVIS_SELECTED | LVIS_FOCUSED)) {
				ListView_GetItemText(hListView, nlv->iItem, 0, Caption, 255);
				g_selectlist.idx = nlv->iSubItem;
				_tcscpy_s(g_selectlist.name, Caption);
			}
			break;
		}
	}

	return TRUE;
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();
	view_GetControlHandle(hDlg);
	view_InitControl(hDlg);
	return 0;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
		//회원가입(INSERT)
	case IDC_BUTTONJOIN: OnButtonJoin(hDlg); return 0;
		//메뉴-프로그램종료
	case ID_FILEEXIT: EndDialog(hDlg, IDOK); return 0;
		//메뉴-검색
	case ID_40003: OnFunSelect(hDlg); return 0;

	case IDCANCEL:
		EndDialog(hDlg, IDCANCEL);
		return 0;
	}
	return TRUE;
}
