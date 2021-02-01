
// MFC_AccountManagerDoc.h : CMyMFC_AccountManagerDoc 클래스의 인터페이스
//


#pragma once
#include "Account.h"
#include "AccountList.h"

//typedef struct tagACCOUNT
//{
//	TCHAR		name[20];
//	int			accid;
//	int			balance;
//	SYSTEMTIME	date;
//}ACCOUNT, *PACCOUNT;

//typedef struct tagACCOUNTLIST
//{
//	int			accid;
//	int			balance;
//	SYSTEMTIME	date;
//	int			addmoney;
//	int			minmoney;
//}ACCOUNTLIST, *PACCOUNTLIST;


class CMyMFC_AccountManagerDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMyMFC_AccountManagerDoc();
	DECLARE_DYNCREATE(CMyMFC_AccountManagerDoc)

// 특성입니다.
public:

// 작업입니다.
public:
	

	BOOL  m_bInsert;
	//ACCOUNT m_acc;
	//ACCOUNTLIST m_acclist;
	//Account m_account;
	//AccountList m_accountlist;
	vector<Account*> m_vecPAccount;
	//vector<ACCOUNTLIST> m_vecAcclist;
	vector<AccountList*> m_vecPAccountList;

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMyMFC_AccountManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void doc_AccListInsert(int id, int amoney, int mmoney, int balance);
};
