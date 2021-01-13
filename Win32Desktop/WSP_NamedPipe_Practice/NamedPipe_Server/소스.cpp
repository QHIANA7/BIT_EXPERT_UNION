#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main()
{
	HANDLE hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\TimeServer"), // UNC
		PIPE_ACCESS_DUPLEX,	//���� ���
		PIPE_TYPE_BYTE,	//������ ���
		1,		//�ִ� ���� �ν��Ͻ� ��
		1024,	//�Է¹��� Byte ��
		1024,	//��¹��� Byte ��
		1000,	//Ÿ�Ӿƿ� ms (���� 0�� �� �⺻�� : 50ms)
		NULL);	//����Ư�� (NULL�� ��� �⺻ ����Ư�� : ���� ���μ������� �� �Լ��� ������� PIPE HANDLE�� ��ӹ��� �� ����)

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		LPTSTR lpMsgBuf;
		DWORD err = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL);
		_tprintf_s(TEXT("%s"), lpMsgBuf);

		LocalFree(lpMsgBuf);
		return 0;
	}

	while (true)
	{
		BOOL bRet = ConnectNamedPipe(hPipe, 0); //Ŭ���̾�Ʈ�� ���� ���

		if (bRet == FALSE && GetLastError() == ERROR_PIPE_CONNECTED)
			bRet = TRUE;

		if (bRet) {
			//PIPE�� ����ð��� Ŭ���̾�Ʈ�� ����
			SYSTEMTIME st;
			GetSystemTime(&st);
			DWORD len;
			WriteFile(hPipe, &st, sizeof(st), &len, 0);
			FlushFileBuffers(hPipe);

			BOOL bRead = false;

			while (!bRead)
			{
				TCHAR buf[256];
				DWORD len1;
				BOOL bRead = ReadFile(hPipe, buf, sizeof(buf), &len1, 0);

				if (bRead)
				{
					_tprintf_s(TEXT("Client : %s\n"), buf);

					DisconnectNamedPipe(hPipe); //Ŭ���̾�Ʈ ���� ����
					_tprintf_s(TEXT("PIPE Communication Success, Disconnected\n"));
					break;
				}
			}			
		}
	}

	return 0;
}
