//test.cpp

#define DLL_SOURCE


#include "test.h"



//============== DLL에 포함될 함수 구현부 ==============
TCHAR g_msg[20];

LPTSTR getMessage()
{
	return g_msg;
}

void setMessage(LPTSTR msg)
{
	_tcscpy_s(g_msg, msg);
}

void setMessage1(LPTSTR msg)
{
	_tcscpy_s(g_msg, msg);
}
//===========================================
