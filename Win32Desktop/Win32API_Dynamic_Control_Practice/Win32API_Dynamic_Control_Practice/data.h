#pragma once
//data.h

//��Ʈ�� ID �κ� - �θ� �ڽ���Ʈ�ѷ� ���� �����޽����� �ޱ�����
#define IDC_EDITNAME	1
#define IDC_RADIOGENDER1	2
#define IDC_RADIOGENDER2	3
#define IDC_COMBOSUBJECT	4
#define IDC_EDITNUMBER	5
#define IDC_BUTTONJOIN 6
#define IDC_BUTTONCANCLE 7
#define IDC_LISTMEMBER 8
#define IDC_BUTTONUPDATE 9
#define IDC_BUTTONDELETE 10

extern HWND hEditName, hRadioGender1, hRadioGender2, hComboSubject, hEditNumber, hButtonJoin, hButtonCancle,
hListMember, hButtonUpdate, hButtonDelete;
extern vector<MEMBER>g_veclist;