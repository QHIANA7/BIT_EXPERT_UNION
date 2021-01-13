#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main()
{
	HANDLE hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\TimeServer"), // UNC
		PIPE_ACCESS_DUPLEX,	//오픈 모드
		PIPE_TYPE_BYTE,	//파이프 모드
		1,		//최대 생성 인스턴스 수
		1024,	//입력버퍼 Byte 수
		1024,	//출력버퍼 Byte 수
		1000,	//타임아웃 ms (값이 0일 때 기본값 : 50ms)
		NULL);	//보안특성 (NULL일 경우 기본 보안특성 : 서브 프로세스에서 이 함수로 만들어진 PIPE HANDLE를 상속받을 수 없음)

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
		BOOL bRet = ConnectNamedPipe(hPipe, 0); //클라이언트의 접속 대기

		if (bRet == FALSE && GetLastError() == ERROR_PIPE_CONNECTED)
			bRet = TRUE;

		if (bRet) {
			//PIPE로 현재시간을 클라이언트에 전송
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

					DisconnectNamedPipe(hPipe); //클라이언트 연결 해제
					_tprintf_s(TEXT("PIPE Communication Success, Disconnected\n"));
					break;
				}
			}			
		}
	}

	return 0;
}
