#pragma once
//packet.h

#define PACK_ADDMEMBER	1
#define PACK_DELMEMBER	2
#define PACK_LOGIN		3
#define PACK_LOGOUT		4
#define PACK_MESSAGE	5

#define ACK_ADDMEMBERS	11
#define ACK_ADDMEMBERF	12
#define ACK_DELMEMBERS	21
#define ACK_DELMEMBERF	22
#define ACK_LOGINS		31  //: pw->nickname으로 변경해서
#define ACK_LOGINF		32
#define ACK_LOGOUTS		41  
#define ACK_LOGOUTF		42
#define ACK_MESSAGE		51


typedef struct tagMEMBER
{
	int flag;
	TCHAR nickname[20];
	TCHAR id[20];
	TCHAR pw[20];
}MEMBER, *PMEMBER;

//로그인/로그아웃(id)
typedef struct tagLOGIN
{
	int flag;
	TCHAR id[20];
	TCHAR pw[20];
}LOGIN, *PLOGIN;

//메시지
typedef struct tagMESSAGE
{
	int flag;
	TCHAR nickname[20];
	TCHAR msg[50];
}MESSAGE, *PMESSAGE;