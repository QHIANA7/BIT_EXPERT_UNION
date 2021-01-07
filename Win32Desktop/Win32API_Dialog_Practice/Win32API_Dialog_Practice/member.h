#pragma once
//member.h


typedef struct tagMEMBER
{
	TCHAR name[20];
	BOOL gender;
	TCHAR subject[20];
	int number;
}MEMBER;

void MemberInit(MEMBER *type);