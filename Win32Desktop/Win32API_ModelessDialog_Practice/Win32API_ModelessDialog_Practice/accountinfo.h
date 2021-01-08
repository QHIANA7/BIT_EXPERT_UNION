#pragma once
//accountinfo.h

typedef struct tagACCOUNTINFO
{
	TCHAR name[20];		//이름
	int deposit;	//입금액
	int withdraw;	//출금액
	int balance;	//잔액
	SYSTEMTIME st;	//거래일자/일시
}ACCOUNTINFO;

void AccountInfoInit(ACCOUNTINFO *type);