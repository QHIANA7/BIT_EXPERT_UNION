//dlgmodalaccinput.cpp
#include "std.h"

//모달 대화상자에서 발생하는 메시지를 처리할 프로시저
BOOL CALLBACK DlgModalAccInputProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	static ACCOUNT *pData;
	switch (msg)
	{
	case WM_INITDIALOG:	//대화상자가 생성시 수행
	{
		pData = (ACCOUNT*)lParam; //현재블록 LPARAM에 데이터가 넘겨왔다.
		//SetDlgItemText(hDlg, IDC_EDITNAME, pData->name);//컨트롤 -> Data
		//SetDlgItemInt(hDlg, IDC_EDITACCOUNTNUM, pData->accountnumber, 0);
		//Get/SetDlgItem 범주 함수의 장점은 핸들이 필요없다는 점입니다.
	}
	return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:	//등록을 눌렀구나!
		{
			pData->accountnumber = GetDlgItemInt(hDlg, IDC_EDITACCOUNTNUM, 0, 0);
			GetDlgItemText(hDlg, IDC_EDITNAME, pData->name, sizeof(pData->name));
			pData->balance = 0;
			EndDialog(hDlg, IDOK);	//대화상자를 닫고 IDOK를 반환
		}
		return TRUE;

		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return TRUE;
		}
	}
	return FALSE;
}