//data.cpp

#include "std.h"

BOOL data_RemoveSocketInfo(SOCKET sk)
{
	EnterCriticalSection(&cs);	//도중에 삭제하는 친구는 한명만 있도록하는 크리티컬 섹션
	for (int i = 0; i < (int)g_SocketInfo.size(); i++)
	{
		DATA dt = g_SocketInfo[i];

		if (dt.socket == sk)
		{
			g_SocketInfo.erase(g_SocketInfo.begin() + i);
			LeaveCriticalSection(&cs);
			return TRUE;
		}
	}
	LeaveCriticalSection(&cs);
	return FALSE;
}

BOOL data_AddMember(PMEMBER pdata)
{
	MEMBER data = *pdata;
	if (_tcslen(data.id) == 0)
		return FALSE;
	for (int i = 0; i < (int)g_Memberlist.size(); i++)
	{
		MEMBER temp_data = g_Memberlist[i];
		if (_tcscmp(data.id, temp_data.id) == 0)
		{
			return FALSE;
		}
		else
			break;
	}
	data.flag = 0;
	g_Memberlist.push_back(data);
	return TRUE;
}

BOOL data_UserCompareMember(PLOGIN pdata)
{
	PLOGIN data = pdata;

	for (int i = 0; i < (int)g_Memberlist.size(); i++)
	{
		MEMBER temp_data = g_Memberlist[i];
		if (_tcscmp(data->id, temp_data.id) == 0)
			if (_tcscmp(data->pw, temp_data.pw) == 0)
			{
				wsprintf(pdata->pw, g_Memberlist[i].nickname);
				return TRUE;
			}
			else
				return FALSE;
	}

	return FALSE;
}

BOOL data_DeleteMember(PMEMBER pdata)
{
	PMEMBER data = pdata;
	for (int i = 0; i < (int)g_Memberlist.size(); i++)
	{
		MEMBER temp_data = g_Memberlist[i];
		if (_tcscmp(data->id, temp_data.id) == 0)
			if (_tcscmp(data->pw, temp_data.pw) == 0)
			{
				_tcscpy_s(pdata->nickname, g_Memberlist[i].nickname);
				g_Memberlist.erase(g_Memberlist.begin() + i);
				return TRUE;
			}
			else
				return FALSE;
	}

	return FALSE;
}

BOOL data_Login(PLOGIN pdata)
{
	PLOGIN data = pdata;

	for (int i = 0; i < (int)g_Memberlist.size(); i++)
	{
		MEMBER temp_data = g_Memberlist[i];
		if (_tcscmp(data->id, temp_data.id) == 0)
			if (_tcscmp(data->pw, temp_data.pw) == 0)
			{
				g_Memberlist[i].flag = 1;
				wsprintf(pdata->pw, g_Memberlist[i].nickname);
				return TRUE;
			}
			else
				return FALSE;
	}

	return FALSE;
}

BOOL data_Logout(PLOGIN pdata)
{
	PLOGIN data = pdata;

	for (int i = 0; i < (int)g_Memberlist.size(); i++)
	{
		MEMBER temp_data = g_Memberlist[i];
		if (_tcscmp(data->id, temp_data.id) == 0)
			if (_tcscmp(data->pw, temp_data.pw) == 0)
			{
				g_Memberlist[i].flag = 0;
				wsprintf(pdata->pw, g_Memberlist[i].nickname);
				return TRUE;
			}
			else
				return FALSE;
	}

	return FALSE;
}
