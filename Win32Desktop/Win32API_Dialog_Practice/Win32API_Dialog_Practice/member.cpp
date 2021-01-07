//member.cpp

#include "std.h"

void MemberInit(MEMBER *type)
{
	wsprintf(type->name, TEXT(""));
	type->gender = TRUE;
	wsprintf(type->subject, TEXT(""));
	type->number = 0;
}