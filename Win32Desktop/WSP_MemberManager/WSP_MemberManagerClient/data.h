#pragma once


//data.h
#define NORMAL_TCHAR_LENGTH 32
#define MSG_LENGHT 50

typedef struct tagDATA
{
	int flag;	//1.���� 2.Ż�� 3.�α� 3.�ΰ�
	TCHAR id[NORMAL_TCHAR_LENGTH];
	TCHAR pw[NORMAL_TCHAR_LENGTH];
	TCHAR nickname[NORMAL_TCHAR_LENGTH];
}DATA;

typedef struct tagDATAMESSAGE
{
	int flag;
	TCHAR nickname[NORMAL_TCHAR_LENGTH];
	TCHAR msg[MSG_LENGHT];
}DATAMESSAGE;

extern HWND hEditID, hEditPW, hEditNickName, hButtonOk, hButtonInteractive, hButtonDeleteAccount;