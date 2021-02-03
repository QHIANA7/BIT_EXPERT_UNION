# BIT_EXPERT_MFC_MultiEcho_Practice
MFC : Socket�� �����带 �̿��� ���� ���� �ǽ�

## ����
* ��Ʈ ��ް��� - MFC : [BIT_EXPERT_WNP_MultiEcho_Practice2](https://github.com/QHIANA7/BIT_EXPERT_WNP_MultiEcho_Practice2) ������Ʈ�� MFC�� ���̱׷��̼��� ������Ʈ
* ���� ���α׷��� ��Ʈ�� ���Ƿ� ������ �� �ְ� Ŭ���̾�Ʈ ���α׷��� ������ ����� �� �ֽ��ϴ�.
* Ŭ���̾�Ʈ ���α׷��� ������ IP, Port�� �Է��Ͽ� ������ ������ �� �ֽ��ϴ�.
* Ŭ���̾�Ʈ���� ȸ�������� �����ϸ� ȸ�������� �������� �����˴ϴ�.
* Ŭ���̾�Ʈ ���α׷��� ������ �޽����� ������ �� �ְ� ���� ���α׷��� ���ӵ� ��� Ŭ���̾�Ʈ ���α׷��� �ٽ� �����մϴ�.

## ���� �Ⱓ
* 2017.03.30

## ��� ����
* C++, MFC

## ���� ȯ��
* OS : Windows 8.1
* IDE : Visul Studio 2017

## ���� ȭ��
* ���� ȭ��  
![����ȭ��](./Images/run1.png)

* Ŭ���̾�Ʈ ȭ��  
![����ȭ��](./Images/run2.png)

* ȸ������ ȭ��  
![����ȭ��](./Images/run3.png)

## ���� ���
1. �ַ���� ���� 'F7'�� ���� ����
2. ����� ������ Ŭ���̾�Ʈ ���α׷��� ��� ����
3. ���� ���α׷��� [���] - [��������...] �޴��� �����ϰ� ��ȭ���ڿ��� ��Ʈ�� �Է��ϰ� '����' ��ư�� Ŭ���մϴ�.
4. Ŭ���̾�Ʈ ���α׷����� [����] - [���� ����...] �޴��� �����ϰ� ��ȭ���ڿ��� ���� ������ �Է��ϰ� '����' ��ư�� ���� ������ �����մϴ�.
5. [�α��� ���� �Է�] �׷�ڽ����� 'ȸ������' ��ư�� ������ ��ȭ���ڿ��� ȸ�������� �Է��ϰ� 'ȸ������' ��ư�� ���� ������ ȸ������ �����͸� �����մϴ�.
6. [�α��� ���� �Է�] �׷�ڽ��� ȸ�������� �Է��ϰ� '�α���' ��ư�� Ŭ���մϴ�.
7. Ŭ���̾�Ʈ ���α׷� �ϴ��� �ؽ�Ʈ �ڽ��� �޽����� �Է��ϰ� '����' ��ư�� ���� ������ �����ϰ� �����κ��� ���ڸ� �޽��ϴ�.

## API ����
* AfxBeginThread : <https://docs.microsoft.com/en-us/previous-versions/s3w9x78e(v=vs.140)?redirectedfrom=MSDN>
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