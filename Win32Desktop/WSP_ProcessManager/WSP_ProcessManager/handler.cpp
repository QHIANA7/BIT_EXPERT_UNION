//handler.cpp
#include "std.h"

void OnCreateProcess(HWND hDlg)
{
	TCHAR temp[TCHAR_LENGTH];
	HANDLE hProcess;
	view_GetProcessName(hDlg, temp);
	hProcess = pro_CreateProcess(temp);
	if (hProcess)
	{
		pro_InsertProcessInfo(temp, hProcess);
		view_PrintAllProcessInfo(hDlg);
	}
}

void OnButtonGetProcessStatus(HWND hDlg)
{
	HANDLE hProcess = (HANDLE)GetDlgItemInt(hDlg, IDC_EDITPROCESSHANDLE, 0, 0);

	DWORD code = pro_GetProcessState(hProcess);

	view_SetProcessState(hDlg, code);
	if (code != STILL_ACTIVE)
	{
		view_DeleteProcessListByHandle(hProcess);
		view_PrintAllProcessInfo(hDlg);
	}
}

void OnButtonTerminateProcess(HWND hDlg)
{
	HANDLE hProcess = (HANDLE)GetDlgItemInt(hDlg, IDC_EDITPROCESSHANDLE, 0, 0);

	pro_ExitProcess(hProcess);
	view_DeleteProcessListByHandle(hProcess);
	view_PrintAllProcessInfo(hDlg);
	view_SetProcessInfoInit(hDlg);
}

void OnListProcessInfo(HWND hDlg, WPARAM wParam)
{
	
	switch (HIWORD(wParam))
	{
	case LBN_SELCHANGE:	//리스트박스 알림 : 리스트 박스 내부 선택이 변경된 경우
		view_ListProcessInfoSelectChange(hDlg);
		break;
		//	case LBN_SETFOCUS:
		//	case LBN_KILLFOCUS:
		//	ShapeUpdateMode = FALSE;
		//	SetWindowText(hEditMode, TEXT("입력"));
		//	break;
	}
}


BOOL OnLButtonDown(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	
	return TRUE;
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();
	view_GetControlHandle(hDlg);
	view_InitControl(hDlg);
	pro_GetTotalCurrentProcessList(hDlg);
	view_ListViewPrintAll(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BUTTONCREATEPROCESS: OnCreateProcess(hDlg); break;
	case IDCANCEL: EndDialog(hDlg, IDCANCEL);	break;
	case IDC_BUTTONGETPROCESSSTATUS: OnButtonGetProcessStatus(hDlg); break;
	case IDC_BUTTONTERMINATEPROCESS: OnButtonTerminateProcess(hDlg); break;
	case IDC_LISTPROCESSINFO: OnListProcessInfo(hDlg, wParam); break;
	}
	return TRUE;
}
