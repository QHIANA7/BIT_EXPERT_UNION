#pragma once
//member.h

typedef struct tagMEMBER
{
	TCHAR name[20];
	BOOL gender;
	int subject;
	int number;
}MEMBER;

void MemberInit(MEMBER *type);