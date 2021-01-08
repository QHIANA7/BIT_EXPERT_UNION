//account.cpp

#include "std.h"

void AccountInit(ACCOUNT *type)
{
	wsprintf(type->name, TEXT(""));
	type->accountnumber = 0;
	type->balance = 0;
}