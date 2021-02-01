#include "stdafx.h"
#include "AccountList.h"

IMPLEMENT_SERIAL(AccountList,CObject,1)

AccountList::AccountList()
{
}

AccountList::AccountList(int _accid, int _balance, int _addmoney, int _minmoney)
	:accid(_accid),balance(_balance),addmoney(_addmoney),minmoney(_minmoney)
{
	date = CTime::GetCurrentTime();
}


AccountList::~AccountList()
{
}
