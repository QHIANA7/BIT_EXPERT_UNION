//processinfo.cpp

#include "std.h"

void ProcessInfoInit(PROCESSINFO * type)
{
	type->hProcess = NULL;
	wsprintf(type->name, TEXT(""));
	GetLocalTime(&(type->st));
}
