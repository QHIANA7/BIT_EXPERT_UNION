#pragma once
//#include "afxwin.h"
#include "MFC_Basic_PracticeDoc.h"

class CPaneView : public CView
{
protected:
	CPaneView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPaneView)	//동적 생성 선언(이거 해줘야한답니다)
	 ~CPaneView();
public:
		CMyMFC_Basic_PracticeDoc* GetDocument();
protected:
	virtual void OnDraw(CDC* pDC);
};

