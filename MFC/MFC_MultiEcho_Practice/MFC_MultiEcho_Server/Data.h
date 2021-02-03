#pragma once
class Data
{
	UINT socket;
	CString c_ip;
	USHORT c_port;
	CString t_ip;
	USHORT t_port;
public:
	Data();
	Data(UINT _socket, CString _c_ip, USHORT _c_port, CString _t_ip, USHORT _t_port);
	~Data();
public:
	UINT getSocket() { return socket; }
	CString getCIp() { return c_ip; }
	USHORT getCPort() { return c_port; }
	CString getTIp() { return t_ip; }
	USHORT getTPort() { return t_port; }
	void setSocket(UINT value) { socket = value; }
	void setCIp(CString value) { c_ip = value; }
	void setCPort(USHORT value) { c_port = value; }
	void setTIp(CString value) { t_ip = value; }
	void setTPort(USHORT value) { t_port = value; }
};

