# BIT_EXPERT_WNP_MultiEcho_Practice
Windows Network Programming : Socket�� �����带 �̿��� ���� ���� �ǽ�

## ����
* ��Ʈ ��ް��� - Windows Network Programming : Socket�� �����带 �̿��Ͽ� ���� Ŭ���̾�Ʈ���� ������ �����ϰ� �ϰ� Ŭ���̾�Ʈ���� ���� �����͸� ������ ��� Ŭ���̾�Ʈ�� �۽��ϴ� ���α׷��Դϴ�.
* ���� ���α׷��� ��Ʈ�� ���Ƿ� ������ �� �ְ� '��������' �޴��� ���Ͽ� Ŭ���̾�Ʈ�� ������ ����� �� �ֽ��ϴ�.
* Ŭ���̾�Ʈ ���α׷��� ������ IP, Port�� �Է��ϰ� '����' ��ư�� ���� ������ ������ �õ��մϴ�.
* Ŭ���̾�Ʈ ���α׷��� ������ �޽����� ������ �� �ְ� ���� ���α׷��� �޽����� ��� ���ӵ� Ŭ���̾�Ʈ�� �ٽ� �����մϴ�.

## ���� �Ⱓ
* 2017.03.22

## ��� ����
* C++, Win32 API

## ���� ȯ��
* OS : Windows 8.1
* IDE : Visul Studio 2017

## ���� ȭ��
* ���� ȭ��  
![����ȭ��](./Images/run1.png)

* Ŭ���̾�Ʈ ȭ��  
![����ȭ��](./Images/run2.png)

## ���� ���
1. �ַ���� ���� 'F7'�� ���� ����
2. ����� ������ Ŭ���̾�Ʈ ���α׷��� ��� ����
3. ���� ���α׷��� [���] - [��������...] �޴��� �����ϰ� ��ȭ���ڿ��� ��Ʈ�� �Է��ϰ� '����' ��ư�� Ŭ���մϴ�.
4. Ŭ���̾�Ʈ ���α׷����� [���� ���� ����] �׷�ڽ��� ���� ������ �Է��ϰ� '����' ��ư�� ���� ������ �����մϴ�.
5. ����� ���¿��� Ŭ���̾�Ʈ ���α׷� �ϴ��� �ؽ�Ʈ �ڽ��� �޽����� �Է��ϰ� '����' ��ư�� ���� ������ �����ϰ� �����κ��� ���ڸ� �޽��ϴ�.

## API ����
* CreateThread : <https://docs.microsoft.com/ko-kr/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread>
* WSAStartup : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-wsastartup>
* WSACleanup : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-wsacleanup>
* socket : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-socket>
* closesocket : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-closesocket>
* htons : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-htons>
* ntohs : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-ntohs>
* accept : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-accept>
* bind : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-bind>
* listen : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-listen>
* recv : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-recv>
* send : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-send>
* getsockname : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-getsockname>
* getpeername : <https://docs.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-getpeername>
* InetNtcp : <https://docs.microsoft.com/ko-kr/windows/win32/api/ws2tcpip/nf-ws2tcpip-inetntopw>