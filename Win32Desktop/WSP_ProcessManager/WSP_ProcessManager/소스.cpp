//소스.cpp
#include "std.h"
#include "소스.h"

//작성전에 먼저 리소스를 등록하라. 다이얼로그 ID 설정 후 저장하면 rc파일 리소스헤더에 자동추가됨

//내가 실행시킨 프로세스 목록
vector<PROCESSINFO> g_veclist;
//시스템에서 동작중인 전체 프로세스 목록
vector<PROCESSINFO> g_allveclist;

PROCESSINFO cur_data;

HWND hListView;

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		return OnLButtonDown(hDlg, wParam, lParam);
	case WM_INITDIALOG: 	//대화상자 표시 직전 호출
		return OnInitDialog(hDlg, wParam, lParam);
	case WM_COMMAND:
		return OnCommand(hDlg, wParam, lParam);
	}
	return FALSE;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd) {

	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_MAINDLG),	// 다이얼로그 선택
		0,			// 부모 윈도우
		DlgProc);			// Proc..
	return 0;
}
