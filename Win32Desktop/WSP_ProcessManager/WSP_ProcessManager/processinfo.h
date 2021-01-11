#pragma once

//processinfo.h

typedef struct tagPROCESSINFO
{
	TCHAR name[256];
	HANDLE hProcess;
	SYSTEMTIME st;
}PROCESSINFO;

void ProcessInfoInit(PROCESSINFO *type);