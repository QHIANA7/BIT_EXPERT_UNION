//handler.cpp
#include "std.h"

void OnButtonJoin(HWND hDlg)
{
	MEMBER mem;
	view_GetControlData(hDlg, &mem);
	g_veclist.push_back(mem);
	//����Ʈ�� ��ü ���
	view_ListViewPrintAll(hDlg);
}

void OnFunSelect(HWND hDlg)
{
	DATA data;
	//=========================================================
	data = g_selectlist;
	//=========================================================
	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_DIALOGMODAL),	//��� ��ȭ���� ID
		hDlg,		// �θ�
		DlgModalProc, // �޼��� ó�� ���ν���
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
			//* ���õ� �׸��� �����ش�.
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
		//ȸ������(INSERT)
	case IDC_BUTTONJOIN: OnButtonJoin(hDlg); return 0;
		//�޴�-���α׷�����
	case ID_FILEEXIT: EndDialog(hDlg, IDOK); return 0;
		//�޴�-�˻�
	case ID_40003: OnFunSelect(hDlg); return 0;

	case IDCANCEL:
		EndDialog(hDlg, IDCANCEL);
		return 0;
	}
	return TRUE;
}
