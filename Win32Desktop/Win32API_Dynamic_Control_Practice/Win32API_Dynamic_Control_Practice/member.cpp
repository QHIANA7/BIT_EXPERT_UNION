//member.cpp
#include "std.h"

void MemberInit(MEMBER *type)
{
	wsprintf(type->name, TEXT(""));
	type->gender = TRUE;
	type->subject = 0;
	type->number = 0;
}