//data.cpp

#include "std.h"

BOOL data_RemoveSocketInfo(SOCKET sk)
{
	EnterCriticalSection(&cs);	//���߿� �����ϴ� ģ���� �Ѹ� �ֵ����ϴ� ũ��Ƽ�� ����
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
