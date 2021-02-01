#include "stdafx.h"
#include "Account.h"

IMPLEMENT_SERIAL(Account,CObject,1)

Account::Account()
{
}

Account::Account(CString _name, int _accid, int _balance) : name(_name),accid(_accid),balance(_balance)
{
	date = CTime::GetCurrentTime();
}


Account::~Account()
{
}
