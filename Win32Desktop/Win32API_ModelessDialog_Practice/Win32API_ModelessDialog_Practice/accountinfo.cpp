//accountinfo.cpp

#include "std.h"

void AccountInfoInit(ACCOUNTINFO *type)
{
	type->deposit = 0;
	type->withdraw = 0;
	type->balance = 0;
	GetSystemTime(&(type->st));
}