#pragma once
//std.h
#define WIN32_LEAN_AND_MEAN	//헤더파일 충돌에대한 처리

#define MAX_IPADDR_LENGTH 32
#define MAX_MESSAGE_LENGHT 256
#define MAX_BUFFER_DECLARE_SIZE 1024

#ifdef UNICODE
#define MAX_BUFFER_USE_SIZE 2048
#else
#define MAX_BUFFER_USE_SIZE 1024
#endif // UNICODE


#include <stdio.h>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windowsx.h>
#include <tchar.h>
#include <commctrl.h>
#include <vector>
#pragma comment(lib, "comctl32.lib") //?
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#include "packet.h"
#include "data.h"
#include "resource.h"
#include "view.h"
#include "handler.h"
#include "mynet.h"
#include "dlgmodal.h"