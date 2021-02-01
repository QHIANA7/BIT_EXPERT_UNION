#pragma once
#include "MFC_AccountManagerDoc.h"
class CMyFile
{
public:
	CMyFile();
	~CMyFile();
public:
	static void LoadAccount(CMyMFC_AccountManagerDoc* pDoc);
	static void LoadAccountList(CMyMFC_AccountManagerDoc* pDoc);
	static void SaveAccount(CMyMFC_AccountManagerDoc* pDoc);
	static void SaveAccountList(CMyMFC_AccountManagerDoc* pDoc);
};

