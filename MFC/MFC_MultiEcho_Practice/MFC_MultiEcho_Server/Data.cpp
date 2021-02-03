#include "stdafx.h"
#include "Data.h"


Data::Data()
{
}

Data::Data(UINT _socket, CString _c_ip, USHORT _c_port, CString _t_ip, USHORT _t_port)
	:socket(_socket),c_ip(_c_ip),c_port(_c_port),t_ip(_t_ip),t_port(_t_port)
{
}


Data::~Data()
{
}
