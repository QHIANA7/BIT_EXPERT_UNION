#pragma once
//#define PACCOUNT Account*

class Account : public CObject
{
	CString		name;
	int			accid;
	int			balance;
	CTime		date;

public:
	Account();
	Account(CString _name, int _accid, int _balance = 0);
	~Account();
public:
	CString GetName() { return name; }
	int getAccId() { return accid; }
	int getBalance() { return balance; }
	CTime getDate() { return date; }

	void setName(CString value) { name = value; }
	void setAccID(int value) { accid = value; }
	void setBalance(int value) { balance = value; }
	void setDate(CTime value) { date = value; }

public:
	void Serialize(CArchive &ar)
	{
		CObject::Serialize(ar);
		if (ar.IsStoring())
		{
			ar << name << accid << balance << date;
		}
		else
		{
			ar >> name >> accid >> balance >> date;
		}

	}
		DECLARE_SERIAL(Account)

};

