#include "stdafx.h"
#include "MyFile.h"


CMyFile::CMyFile()
{
}


CMyFile::~CMyFile()
{
}


void CMyFile::LoadAccount(CMyMFC_AccountManagerDoc* pDoc)
{
	CFile f;
	if (!f.Open(TEXT("account.rth"), CFile::modeRead))
		return;
	CArchive ar(&f, CArchive::load);

	int size;

	ar >> size;

	for (int i = 0; i < size; i++)
	{
		Account* pAcc;
		ar >> pAcc;
		pDoc->m_vecPAccount.push_back(pAcc);
	}

	ar.Close();
	f.Close();
}


void CMyFile::LoadAccountList(CMyMFC_AccountManagerDoc* pDoc)
{
	CFile f;
	if (!f.Open(TEXT("accountlist.rth"), CFile::modeRead))
		return;
	CArchive ar(&f, CArchive::load);

	int size;

	ar >> size;

	for (int i = 0; i < size; i++)
	{
		AccountList* pAcclist;
		ar >> pAcclist;
		pDoc->m_vecPAccountList.push_back(pAcclist);
	}

	ar.Close();
	f.Close();
}


void CMyFile::SaveAccount(CMyMFC_AccountManagerDoc* pDoc)
{
	CFile f;
	f.Open(TEXT("account.rth"), CFile::modeCreate | CFile::modeWrite);
	//C드라이브에 저장안됨 다른드라이브 선택하세요
	CArchive ar(&f, CArchive::store);
	//================================================
	int size = pDoc->m_vecPAccount.size();
	ar << size;

	for (int i = 0; i < size; i++)
	{
		ar << pDoc->m_vecPAccount[i];
	}

	ar.Close();
	f.Close();
}


void CMyFile::SaveAccountList(CMyMFC_AccountManagerDoc* pDoc)
{
	CFile f;
	f.Open(TEXT("accountlist.rth"), CFile::modeCreate | CFile::modeWrite);
	//C드라이브에 저장안됨 다른드라이브 선택하세요
	CArchive ar(&f, CArchive::store);
	//================================================
	int size = pDoc->m_vecPAccountList.size();
	ar << size;

	for (int i = 0; i < size; i++)
	{
		ar << pDoc->m_vecPAccountList[i];
	}

	ar.Close();
	f.Close();
}
