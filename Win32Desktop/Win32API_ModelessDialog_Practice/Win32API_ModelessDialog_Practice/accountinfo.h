#pragma once
//accountinfo.h

typedef struct tagACCOUNTINFO
{
	TCHAR name[20];		//�̸�
	int deposit;	//�Աݾ�
	int withdraw;	//��ݾ�
	int balance;	//�ܾ�
	SYSTEMTIME st;	//�ŷ�����/�Ͻ�
}ACCOUNTINFO;

void AccountInfoInit(ACCOUNTINFO *type);