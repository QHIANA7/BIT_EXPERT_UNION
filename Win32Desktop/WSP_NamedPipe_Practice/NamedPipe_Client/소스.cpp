#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

int main()
{
	HANDLE hPipe = CreateFile(TEXT("\\\\.\\pipe\\TimeServer"),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);

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
		_tprintf_s(TEXT("Can't access to Pipe Server : %s"), lpMsgBuf);
		LocalFree(lpMsgBuf);
		return err;
	}
	DWORD len;
	SYSTEMTIME st;
	BOOL bRet = ReadFile(hPipe, &st, sizeof(st), &len, 0);

	if (bRet) {
		// UTC 시간을 ->지역 시간으로
		SystemTimeToTzSpecificLocalTime(0, &st, &st);
		SetLocalTime(&st);
		printf("%d시 %d분\n", st.wHour, st.wMinute);
		TCHAR date[256];
		TCHAR time[256];
		GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, 0, date, 256);
		GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, 0, time, 256);
		_tprintf(TEXT("%s\n"), date);
		_tprintf(TEXT("%s\n"), time);
	}

	//ReadFile(hPipe, &st, sizeof(st), &len, 0);
	TCHAR buf[256];
	StringCbPrintf(buf, 256, TEXT("Receive Success!"));
	DWORD len1;
	WriteFile(hPipe, buf, sizeof(buf), &len1, 0);

	CloseHandle(hPipe);
}
