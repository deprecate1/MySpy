// MySpyDoc.cpp : implementation of the CMySpyDoc class
//

#include "stdafx.h"
#include "MySpy.h"
#include "MySpyDoc.h"
#include "MyCntrItem.h"
#include "MainFrm.h"
#include "MyEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

sWindowInfo*	CMySpyDoc::m_pWinInfo=NULL;
CMyOptions&     CMySpyDoc::m_rOptions(CMyOptions::GetMyOptions());
const LPCTSTR	CMySpyDoc::m_pstrHexString=_T("0x%08X");
const LPCTSTR	CMySpyDoc::m_pstrDecString=_T("%08lu");


// CMySpyDoc

IMPLEMENT_DYNCREATE(CMySpyDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CMySpyDoc, CRichEditDoc)
	ON_COMMAND(ID_VISIBILITY_ALL, OnVisibilityAll)
	ON_COMMAND(ID_VISIBILITY_VISIBLEONLY, OnVisibilityVisibleonly)
	ON_COMMAND(ID_VISIBILITY_NONVISIBLEONLY, OnVisibilityNonvisibleonly)
	ON_COMMAND(ID_PARENT_ALL, OnParentAll)
	ON_COMMAND(ID_PARENT_PARENTSONLY, OnParentParentsonly)
	ON_COMMAND(ID_PARENT_CHILDONLY, OnParentChildonly)
END_MESSAGE_MAP()


// CMySpyDoc construction/destruction

CMySpyDoc::CMySpyDoc():
m_hCurrentlySelectedHwnd(NULL)
{
	Refresh();
}

CMySpyDoc::~CMySpyDoc()
{
}

CRichEditCntrItem* CMySpyDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CMyCntrItem(preo, (CMySpyDoc*)this);
}


BOOL CMySpyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void CMySpyDoc::GetFullWindowInfoString(CString& strText) 
{
	const CString strLineFeed = _T("\r\n");
	const CString strTab = _T("\t: ");
	CString strTmp;

	for( int i=0; i<m_rOptions.m_aWinInfosOnInfoPane.GetSize(); i++)
	{
		strTmp.Empty();
		if(m_rOptions.m_aWinInfosOnInfoPane.GetAt(i)->m_bVisible)
		{
			if(m_hCurrentlySelectedHwnd)
				(*pCallBackFns[m_rOptions.m_aWinInfosOnInfoPane.GetAt(i)->m_nTitleId])(m_hCurrentlySelectedHwnd,strTmp);
			if(strTmp.IsEmpty())
				strTmp=_T("N/A");
			strText+=  pstrTitleStrings[m_rOptions.m_aWinInfosOnInfoPane.GetAt(i)->m_nTitleId]+strTab
						+strTmp+strLineFeed;
		}
	}
}

void CMySpyDoc::GetWindowInfoData(int i, CString& strText)
{
	if(i<=m_rOptions.m_aWinInfosOnInfoPane.GetUpperBound())
	{
		CString strTmp;
		if(m_hCurrentlySelectedHwnd)
			(*pCallBackFns[m_rOptions.m_aWinInfosOnInfoPane.GetAt(i)->m_nTitleId])
			(m_hCurrentlySelectedHwnd,strTmp);
		if(strTmp.IsEmpty())
			strTmp=_T("N/A");

		strText=strTmp;
	}
	else
		strText.Empty();
}


void CMySpyDoc::GetWindowInfoTitle(int i, CString& strText)
{
	if(i<=m_rOptions.m_aWinInfosOnInfoPane.GetUpperBound())
		strText=pstrTitleStrings[m_rOptions.m_aWinInfosOnInfoPane.GetAt(i)->m_nTitleId];
	else
		strText.Empty();
}

void CMySpyDoc::SetCurrentlySelectedHwnd(HWND hWnd)
{
	m_pWinInfo=m_oEnumWins.GetWindowInfo(hWnd);
	m_hCurrentlySelectedHwnd = hWnd;
}

LPCTSTR CMySpyDoc::GetNumberFormat()
{
	if(m_rOptions.m_bDisplayInHex) 
		return m_pstrHexString;
	else
		return m_pstrDecString;
}

void CMySpyDoc::GetHWNDString(HWND hWnd, CString& strOutput)
{
	strOutput.Format(GetNumberFormat(),hWnd);
}

void CMySpyDoc::GetRECTString(HWND hWnd, CString& strOutput)
{
	CRect rc;
    ::GetWindowRect(hWnd,&rc);
	strOutput.Format(_T("(%d, %d)-(%d, %d) %dx%d"), rc.left, rc.top, rc.right, rc.bottom, rc.Width(), rc.Height());
}

void CMySpyDoc::GetPIDString(HWND hWnd, CString& strOutput)
{
	if(m_pWinInfo)
		strOutput.Format(GetNumberFormat(),m_pWinInfo->dwPID);
}

void CMySpyDoc::GetWindowIdentifierString(HWND hWnd, CString& strOutput)
{
	int nID = GetWindowLongPtr(hWnd, GWL_ID);
	strOutput.Format(GetNumberFormat(),nID);
}

void CMySpyDoc::GetStylesString(HWND hWnd, CString& strOutput)
{
	DWORD dwStyle = (DWORD)::GetWindowLongPtr (hWnd, GWL_STYLE);

	for(int i=0; i<sizeof(WINSTYLES)/sizeof(sNamesAndValues); i++)
		if(dwStyle&WINSTYLES[i].uValue)
			strOutput+=_T(" | ")+CString(WINSTYLES[i].strName);

	strOutput.TrimLeft(_T("| "));

	if(!strOutput.IsEmpty())
         strOutput.Append(_T(" = "));
	strOutput.AppendFormat(GetNumberFormat(),dwStyle);
}
void CMySpyDoc::GetExStylesString(HWND hWnd, CString& strOutput)
{
	DWORD dwStyle = (DWORD)::GetWindowLongPtr (hWnd, GWL_EXSTYLE);

	for(int i=0; i<sizeof(WINEXSTYLES)/sizeof(sNamesAndValues); i++)
		if(dwStyle&WINEXSTYLES[i].uValue)
			strOutput+=_T(" | ")+CString(WINEXSTYLES[i].strName);

	strOutput.TrimLeft(_T("| "));

	if(!strOutput.IsEmpty())
		strOutput.Append(_T(" = "));
	strOutput.AppendFormat(GetNumberFormat(),dwStyle);

}
void CMySpyDoc::GetThreadIdString(HWND hWnd, CString& strOutput)
{
	DWORD dwProcessId;
	DWORD dwThreadID = ::GetWindowThreadProcessId (hWnd, &dwProcessId);
	strOutput.Format(GetNumberFormat(),dwThreadID);
}
void CMySpyDoc::GetTitleString(HWND hWnd, CString& strOutput)
{
	if(m_pWinInfo)
		strOutput=m_pWinInfo->strWindowTitle;
}
void CMySpyDoc::GetModuleNameString(HWND hWnd, CString& strOutput)
{
	if(m_pWinInfo)
		strOutput=m_pWinInfo->strModuleName;
}
void CMySpyDoc::GetClassNameString(HWND hWnd, CString& strOutput)
{
	if(m_pWinInfo)
		strOutput=m_pWinInfo->strClassName;
}

void CMySpyDoc::GetClassStyleString(HWND hWnd, CString& strOutput)
{
	DWORD dwStyle = (DWORD)::GetClassLong (hWnd, GCL_STYLE);
	for(int i=0; i<sizeof(CLASS_STYLES)/sizeof(sNamesAndValues); i++)
		if(dwStyle&CLASS_STYLES[i].uValue)
			strOutput+=_T(" | ")+CString(CLASS_STYLES[i].strName);

	strOutput.TrimLeft(_T("| "));
}


// CMySpyDoc serialization

void CMySpyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMySpyDoc diagnostics

#ifdef _DEBUG
void CMySpyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMySpyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMySpyDoc commands

void CMySpyDoc::OnVisibilityAll()
{
	m_rOptions.m_eVisibility = VISIBILITY_ALL;
	Refresh();
}

void CMySpyDoc::OnVisibilityVisibleonly()
{
	m_rOptions.m_eVisibility = VISIBILITY_VISIBLE_ONLY;
	Refresh();
}

void CMySpyDoc::OnVisibilityNonvisibleonly()
{
	m_rOptions.m_eVisibility = VISIBILITY_NON_VISIBLE_ONLY;
	Refresh();
}

void CMySpyDoc::OnParentAll()
{
	m_rOptions.m_eParent = PARENT_ALL;
	Refresh();
}

void CMySpyDoc::OnParentParentsonly()
{
	m_rOptions.m_eParent = PARENT_PARENTS_ONLY;
	Refresh();
}

void CMySpyDoc::OnParentChildonly()
{
	m_rOptions.m_eParent = PARENT_CHILDREN_ONLY;
	Refresh();
}

void CMySpyDoc::Refresh(bool bRefreshView)
{
	int nFilter=0;

	switch(m_rOptions.m_eParent)
	{
	case PARENT_ALL:
		break;
	case PARENT_PARENTS_ONLY:
		nFilter|=FILTER_PARENTONLY;
		break;
	case PARENT_CHILDREN_ONLY:
		nFilter|=FILTER_CHILDONLY;
		break;
	}

	switch(m_rOptions.m_eVisibility)
	{
	case VISIBILITY_ALL:
		break;
	case VISIBILITY_VISIBLE_ONLY:
		nFilter|=FILTER_VISIBLEONLY;
		break;
	case VISIBILITY_NON_VISIBLE_ONLY:
		nFilter|=FILTER_NONVISIBLEONLY;
		break;
	}

	m_oEnumWins.Process(nFilter);
	
	if(bRefreshView)
		UpdateAllViews(NULL);

}


BOOL CMySpyDoc::SaveModified(void)
{
	//Nonzero if it is safe to continue and close the document;
	return TRUE;
}


CString CMySpyDoc::GetFilterString()
{
	return m_oEnumWins.m_strFilter;
}

void CMySpyDoc::SetFilterString(CString filter)
{
	m_oEnumWins.m_strFilter = filter;
}


