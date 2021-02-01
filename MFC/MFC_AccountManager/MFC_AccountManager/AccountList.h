#pragma once


class AccountList : public CObject
{
	int			accid;
	int			balance;
	int			addmoney;
	int			minmoney;
	CTime	date;
public:
	AccountList();
	AccountList(int _accid, int _balance, int _addmoney, int _minmoney);
	~AccountList();
public:
	int getAccId() { return accid; }
	int getBalance() { return balance; }
	int getAddMoney() { return addmoney; }
	int getMinMoney() { return minmoney; }
	CTime getDate() { return date; }

	void setAccID(int value) { accid = value; }
	void setBalance(int value) { balance = value; }
	void setAddMoney(int value) { addmoney = value; }
	void setMinMoney(int value) { minmoney = value; }
	void setDate(CTime value) { date = value; }

	void Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);
		if (ar.IsStoring())
		{
			ar << accid << balance << addmoney << minmoney << date;
		}
		else
		{
			ar >> accid >> balance >> addmoney >> minmoney >> date;
		}
	}

	DECLARE_SERIAL(AccountList)
	
};

