
// MFC_MultiEcho_ServerDoc.cpp : CMyMFC_MultiEcho_ServerDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFC_MultiEcho_Server.h"
#endif

#include "MFC_MultiEcho_ServerDoc.h"
#include "MFC_MultiEcho_ServerView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyMFC_MultiEcho_ServerDoc

IMPLEMENT_DYNCREATE(CMyMFC_MultiEcho_ServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyMFC_MultiEcho_ServerDoc, CDocument)
END_MESSAGE_MAP()


// CMyMFC_MultiEcho_ServerDoc ����/�Ҹ�

CMyMFC_MultiEcho_ServerDoc::CMyMFC_MultiEcho_ServerDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	m_IsServerRun = FALSE;
	pMyNet = new CMyNet();
	port = 9000;
	InitializeCriticalSection(&cs1);
}

CMyMFC_MultiEcho_ServerDoc::~CMyMFC_MultiEcho_ServerDoc()
{
	DeleteCriticalSection(&cs1);

}

BOOL CMyMFC_MultiEcho_ServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CMyMFC_MultiEcho_ServerDoc serialization

void CMyMFC_MultiEcho_ServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CMyMFC_MultiEcho_ServerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CMyMFC_MultiEcho_ServerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMyMFC_MultiEcho_ServerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyMFC_MultiEcho_ServerDoc ����

#ifdef _DEBUG
void CMyMFC_MultiEcho_ServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyMFC_MultiEcho_ServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyMFC_MultiEcho_ServerDoc ���


BOOL CMyMFC_MultiEcho_ServerDoc::doc_RemoveSocketInfo(SOCKET s)
{
	EnterCriticalSection(&cs1);
	for (int i = 0; i < (int)m_SocketInfo.size(); i++)
	{
		Data* dt = m_SocketInfo[i];

		if (dt->getSocket() == s)
		{
			m_SocketInfo.erase(m_SocketInfo.begin() + i);
			LeaveCriticalSection(&cs1);
			return TRUE;
		}
	}
	LeaveCriticalSection(&cs1);
	return FALSE;
}


void CMyMFC_MultiEcho_ServerDoc::doc_OnRecvData(LPTSTR data)
{
	POSITION pos = GetFirstViewPosition();	//�� ������
	PINT p = (PINT)data;
	
	switch (*p)
	{
	case PACK_ADDMEMBER:
	{
		//============= ���Ϻκ��� data.cpp �� �����϶� =========
		PMEMBER mem = (PMEMBER)data;
		if (doc_AddMember(mem))	//����
		{
			((CMyMFC_MultiEcho_ServerView*)GetNextView(pos))->view_ListViewPrintAll();
			mem->flag = ACK_ADDMEMBERS;
		}
		else
		{
			mem->flag = ACK_ADDMEMBERF;
		}
	}
	break;
	case PACK_DELMEMBER:
	{
		PMEMBER mem = (PMEMBER)data;
		if (doc_DeleteMember(mem))	//����
		{
			((CMyMFC_MultiEcho_ServerView*)GetNextView(pos))->view_ListViewPrintAll();
			mem->flag = ACK_DELMEMBERS;
		}
		else
		{
			mem->flag = ACK_DELMEMBERF;
		}

	}
	break;
	case PACK_LOGIN:
	{
		PLOGIN log = (PLOGIN)data;
		if (doc_Login(log))	//����
		{
			log->flag = ACK_LOGINS;
			((CMyMFC_MultiEcho_ServerView*)GetNextView(pos))->view_ListViewPrintAll();
		}
		else
			log->flag = ACK_LOGINF;
	}
	break;
	case PACK_LOGOUT:
	{
		PLOGIN log = (PLOGIN)data;
		if (doc_Logout(log))	//����
		{
			log->flag = ACK_LOGOUTS;
			((CMyMFC_MultiEcho_ServerView*)GetNextView(pos))->view_ListViewPrintAll();
		}
		else
			log->flag = ACK_LOGOUTF;
	}
	break;
	case PACK_MESSAGE:
	{
		PMESSAGE msg = (PMESSAGE)data;
		msg->flag = ACK_MESSAGE;
	}
	break;
	}
}

BOOL CMyMFC_MultiEcho_ServerDoc::doc_AddMember(PMEMBER pdata)
{
	MEMBER data = *pdata;
	if (_tcslen(data.id) == 0)
		return FALSE;
	for (int i = 0; i < (int)m_Memberlist.size(); i++)
	{
		MEMBER temp_data = m_Memberlist[i];
		if (_tcscmp(data.id, temp_data.id) == 0)
		{
			return FALSE;
		}
		else
			break;
	}
	data.flag = 0;
	m_Memberlist.push_back(data);
	return TRUE;
}




BOOL CMyMFC_MultiEcho_ServerDoc::doc_DeleteMember(PMEMBER pdata)
{
	PMEMBER data = pdata;
	for (int i = 0; i < (int)m_Memberlist.size(); i++)
	{
		MEMBER temp_data = m_Memberlist[i];
		if (_tcscmp(data->id, temp_data.id) == 0)
			if (_tcscmp(data->pw, temp_data.pw) == 0)
			{
				_tcscpy_s(pdata->nickname, m_Memberlist[i].nickname);
				m_Memberlist.erase(m_Memberlist.begin() + i);
				return TRUE;
			}
			else
				return FALSE;
	}

	return FALSE;
}


BOOL CMyMFC_MultiEcho_ServerDoc::doc_Login(PLOGIN pdata)
{
	PLOGIN data = pdata;

	for (int i = 0; i < (int)m_Memberlist.size(); i++)
	{
		MEMBER temp_data = m_Memberlist[i];
		if (_tcscmp(data->id, temp_data.id) == 0)
			if (_tcscmp(data->pw, temp_data.pw) == 0)
			{
				m_Memberlist[i].flag = 1;
				wsprintf(pdata->pw, m_Memberlist[i].nickname);
				return TRUE;
			}
			else
				return FALSE;
	}

	return FALSE;
}


BOOL CMyMFC_MultiEcho_ServerDoc::doc_Logout(PLOGIN pdata)
{
	PLOGIN data = pdata;

	for (int i = 0; i < (int)m_Memberlist.size(); i++)
	{
		MEMBER temp_data = m_Memberlist[i];
		if (_tcscmp(data->id, temp_data.id) == 0)
			if (_tcscmp(data->pw, temp_data.pw) == 0)
			{
				m_Memberlist[i].flag = 0;
				wsprintf(pdata->pw, m_Memberlist[i].nickname);
				return TRUE;
			}
			else
				return FALSE;
	}

	return FALSE;
}
