//data.cpp
#include "std.h"

BOOL data_AddMember(DATA * pdata)
{
	DATA data = *pdata;
	if (_tcslen(data.id) == 0)
		return FALSE;
	for (int i = 0; i < (int)g_datalist.size(); i++)
	{
		DATA temp_data = g_datalist[i];
		if (_tcscmp(data.id, temp_data.id) == 0)
		{
			return FALSE;
		}
		else
			break;
	}
	g_datalist.push_back(data);
	return TRUE;
}

BOOL data_CompareMember(DATA * pdata)
{
	
	DATA data = *pdata;
	
	for (int i = 0; i < (int)g_datalist.size(); i++)
	{
		DATA temp_data = g_datalist[i];
		if (_tcscmp(data.id, temp_data.id) == 0)
			if (_tcscmp(data.pw, temp_data.pw) == 0)
			{
				_tcscpy_s(pdata->nickname, g_datalist[i].nickname);
				return TRUE;
			}
			else
				return FALSE;
	}

	return FALSE;
}

BOOL data_DeleteMember(DATA * pdata)
{
	DATA data = *pdata;
	for (int i = 0; i < (int)g_datalist.size(); i++)
	{
		DATA temp_data = g_datalist[i];
		if (_tcscmp(data.id, temp_data.id) == 0)
			if (_tcscmp(data.pw, temp_data.pw) == 0)
			{
				_tcscpy_s(pdata->nickname, g_datalist[i].nickname);
				g_datalist.erase(g_datalist.begin() + i);
				return TRUE;
			}
			else
				return FALSE;
	}

	return FALSE;
}