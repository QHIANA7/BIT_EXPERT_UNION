#pragma once
//test.h

#ifdef DLL_SOURCE	//DLL_SOURCE가 정의 되어있느냐
	#define DLLFUNC	__declspec(dllexport)   
#else
	#define DLLFUNC __declspec(dllimport)
#endif

#include <windows.h>
#include <tchar.h>

//dll의 함수 선언부에서 반드시 외부로 노출되는 함수를 처리해야 한다.

//=====================================DLL에 포함될 함수 선언부 ==============
EXTERN_C DLLFUNC LPTSTR getMessage();
EXTERN_C DLLFUNC void setMessage(LPTSTR msg);
void setMessage1(LPTSTR msg);
//============================================================================

//EXTERN_C 라는것은 C기반으로 컴파일 한다는 것
//C기반으로 컴파일 한것과 C++기반으로 컴파일한 함수명은 다르다!