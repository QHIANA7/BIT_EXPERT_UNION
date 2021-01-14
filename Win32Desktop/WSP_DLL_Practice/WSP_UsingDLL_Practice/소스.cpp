//소스.cpp

#include <iostream>

//암시적으로 접근하여 사용하는 방법	- 
#include "test.h"	//DLL 생성시 사용했던 DLL 인클루드
#pragma comment(lib,"WSP_DLL_Practice.lib")
//dll을 사용하기위한 기본적인 코드(이거를 공통 컨트롤을 사용할때도 썼다)

// 그렇다면 명시적인 사용방법은?...
//loadlibrary/freelibrary 를 사용하는 방법인데 나중에 본다.

using namespace std;

void main()
{
	setMessage(TEXT("홍길동"));
	_tcprintf_s(TEXT("%s\n"),getMessage());
	// setMessage1(TEXT("???")); //error
}