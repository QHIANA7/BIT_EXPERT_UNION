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
