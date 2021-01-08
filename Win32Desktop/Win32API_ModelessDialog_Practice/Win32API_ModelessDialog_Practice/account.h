#pragma once
//account.h

typedef struct tagACCOUNT
{
	TCHAR name[20];
	int accountnumber;
	int balance;
}ACCOUNT;

void AccountInit(ACCOUNT *type);