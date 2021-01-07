//소스.cpp
#include "std.h"

//작성전에 먼저 리소스를 등록하라. 다이얼로그 ID 설정 후 저장하면 rc파일 리소스헤더에 자동추가됨

WNDPROC old;	//이전 프로시저를 담기위한 전역 윈도우프로시저 변수

//===================================================================
//전역 핸들
HWND hListView, hEditName, hEditNum, hRadioM, hRadioF, hComboSubject;
//===================================================================

vector<MEMBER> g_veclist;	//요소들을 담기위한 벡터

//리스트 컨트롤에서 선택한 정보
DATA g_selectlist;


//edit 컨트롤에 대한 프로시저 정의를 하십시오
LRESULT CALLBACK EditProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CHAR:
		if ((wParam >= '0' && wParam <= '9' || wParam == 8))
			return CallWindowProc(old, hDlg, msg, wParam, lParam);
		return 0;	//종료 ( DlgProc으로 가지 않음)
	}
	// 처리하지 않은 메시지는 DlgProc으로 보냄
	return CallWindowProc(old, hDlg, msg, wParam, lParam);
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_NOTIFY:	    return OnNotify(hDlg, wParam, lParam);
	case WM_INITDIALOG: return OnInitDialog(hDlg, wParam, lParam);
	case WM_COMMAND:	return OnCommand(hDlg, wParam, lParam);
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd)
{
	UINT ret = DialogBox(hInst,// instance 
		MAKEINTRESOURCE(IDD_MAINDLG), // 다이얼로그 선택 
		0, // 부모 윈도우 
		DlgProc); // Proc.. 
	return 0;
}
