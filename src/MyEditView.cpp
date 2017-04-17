#include "StdAfx.h"
#include "MySpy.h"
#include ".\myeditview.h"
//#include "MySpyDoc.h"
#include "MainFrm.h"
#include "MyOptions.h"


// CMyEditView


IMPLEMENT_DYNCREATE(CMyEditView, CRichEditView)

BEGIN_MESSAGE_MAP(CMyEditView, CRichEditView)
ON_WM_DESTROY()
ON_REGISTERED_MESSAGE(MYMSG_SELECTION_CHANGED,OnMySelChanged)
ON_CONTROL_REFLECT(EN_SETFOCUS, OnEnSetfocus)
ON_COMMAND(ID_WININFO_OPTIONS, OnWininfoOptions)
END_MESSAGE_MAP()



CMyEditView::CMyEditView(void)
{
	m_pDoc=NULL;
}

CMyEditView::~CMyEditView(void)
{
}

#ifdef _DEBUG
void CMyEditView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CMyEditView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CMySpyDoc* CMyEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySpyDoc)));
	return (CMySpyDoc*)m_pDocument;
}
#endif //_DEBUG

void CMyEditView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   //COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   //if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   //{
   //   pActiveItem->Deactivate();
   //   ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   //}
}




void CMyEditView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// Turn on the horizontal scroll bar
	m_nWordWrap = WrapNone;
	WrapChanged();

	PARAFORMAT2 pf;
	pf=GetParaFormatSelection();
	pf.cTabCount=1;
	pf.rgxTabs[0]=1600;
	pf.dwMask = PFM_TABSTOPS;
    SetParaFormat(pf);

	CHARFORMAT2 cf;
	cf=GetCharFormatSelection();
	cf.crBackColor=GetSysColor(COLOR_INFOBK);
	cf.crTextColor=GetSysColor(COLOR_INFOTEXT);

	CString str=_T("Arial");
	lstrcpyn(cf.szFaceName, str, LF_FACESIZE);
	cf.bCharSet = DEFAULT_CHARSET;
	cf.bPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;


	cf.dwMask |= CFM_BACKCOLOR;
	cf.dwMask |= CFM_COLOR;
	cf.dwMask |= CFM_FACE;
	
	cf.dwEffects &= ~CFE_AUTOBACKCOLOR;
	cf.dwEffects &= ~CFE_AUTOCOLOR;
	cf.dwEffects &= ~CFE_BOLD;
	
	GetRichEditCtrl().SetDefaultCharFormat(cf);
	GetRichEditCtrl().SetBackgroundColor(FALSE,cf.crBackColor);

	GetRichEditCtrl().SetReadOnly(TRUE);

	m_pDoc = (CMySpyDoc*)GetDocument();
	ASSERT_VALID(m_pDoc);

}

LRESULT CMyEditView::UpdateWindowInfo(WPARAM wParam,LPARAM lParam)
{
	return OnMySelChanged(wParam,lParam);
}

DWORD __stdcall MEditStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
  //LPCTSTR pszMsg = reinterpret_cast<LPCTSTR>(dwCookie);

  //// number of bytes to copy
  //*pcb = (LONG)_tcslen( pszMsg ) * sizeof(TCHAR);

  //// limiting it up to the buffer's size
  //if( *pcb > cb )
  //   *pcb = cb;

  //// copying the string to the buffer
  //memcpy( pbBuff, pszMsg, *pcb );

  //// advancing to the end of the string
  //pszMsg += *pcb / sizeof(TCHAR);

  //// if it's the end of the string, returns NULL;
  //// otherwise, returns a pointer to the next char to transfer as the cookie
  return /*( *pszMsg != '\0' ) ? reinterpret_cast<DWORD>(pszMsg) :*/ NULL;
}

LRESULT CMyEditView::OnMySelChanged(WPARAM wParam,LPARAM lParam)
{
  
/*	CString sWriteText; //Where the text will be streamed from

	sWriteText="{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang2057{\\fonttbl{\\f0\froman\\fprq2\\fcharset0 Times New Roman;}{\\f1\\fswiss\\fprq2\\fcharset0 System;}}{\\colortbl ;\\red255\\green0\\blue0;\\red51\\green153\\blue102;\\red0\\green0\\blue255;}\\viewkind4\\uc1\\pard\\cf1\\i\\f0\\fs24 Inputted\\cf0\\i0  \\cf2\\b rich\\cf0\\b0  \\cf3 text\\cf0 !\\b\\f1\\fs20 \\par }";
	// This is hard-coded for example purposes. It is likely this would
	// be read from file or another source.

	EDITSTREAM es;

	es.dwCookie = (DWORD)&sWriteText; // Pass a pointer to the CString to the callback function
	es.pfnCallback = MEditStreamInCallback; // Specify the pointer to the callback function
											// Function defined in RichEg.cpp

	GetRichEditCtrl().StreamIn(SF_RTF,es); // Perform the streaming
*/

	HWND hWnd = (HWND)wParam;

	if(!m_pDoc)
		m_pDoc = (CMySpyDoc*)GetDocument();
	ASSERT_VALID(m_pDoc);
	if (!m_pDoc)
		return 0;

	CMyOptions& rOptions = CMyOptions::GetMyOptions();
	
	//m_pDoc->SetDisplayInHex((bool) lParam);
	m_pDoc->SetCurrentlySelectedHwnd(hWnd);

	m_strDisplayText.Empty();

	m_pDoc->GetFullWindowInfoString(m_strDisplayText);

	SetWindowText((LPCTSTR)m_strDisplayText);

  	CRichEditCtrl& ctl=GetRichEditCtrl();

	CString strText;
	FINDTEXTEX ft;
	ft.chrg.cpMin = 0;
	ft.chrg.cpMax = -1;
	for(int i=0;i<rOptions.m_aWinInfosOnInfoPane.GetSize();i++)
	{	
		ctl.SetSel(0,0);
		
		m_pDoc->GetWindowInfoTitle(i,strText);
        
		ft.lpstrText = strText;
		long n = ctl.FindText(FR_MATCHCASE|FR_DOWN, &ft);
		
		if (n != -1)
		{
			ctl.SetSel(ft.chrgText);
			CHARFORMAT2 cf;
			ctl.GetSelectionCharFormat(cf);
			cf.dwEffects|=CFE_BOLD;
			ctl.SetSelectionCharFormat(cf);
		}
	}
	ctl.SetSel(0,0);

	ctl.SetModify(FALSE);
	m_pDoc->SetModifiedFlag(FALSE);

	return 0;

}



HMENU CMyEditView::GetContextMenu(WORD seltyp, LPOLEOBJECT lpoleobj, CHARRANGE* lpchrg)
{
	CRichEditCntrItem* pItem = GetSelectedItem();
	if (pItem == NULL || !pItem->IsInPlaceActive())
	{
		CMenu menuText;	
		menuText.LoadMenu(IDR_POPUP_WININFO);
		CMenu* pMenuPopup = menuText.GetSubMenu(0);
		menuText.RemoveMenu(0, MF_BYPOSITION);
		return pMenuPopup->Detach();
	}
	return NULL;
}

void CMyEditView::OnTextNotFound(LPCTSTR lpszFind)
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT_VALID(this);
	MessageBeep(0);
	AfxMessageBox(IDS_TEXT_NOT_FOUND,MB_OK|MB_ICONINFORMATION);

	CRichEditView::OnTextNotFound(lpszFind);
}

void CMyEditView::OnEnSetfocus()
{
	 CMainFrame* mf = (CMainFrame*) GetParentFrame();
	 //mf->EnableActionToolbar(FALSE);
}

void CMyEditView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	PARAFORMAT2 pf;
	pf=GetParaFormatSelection();
	pf.cTabCount=1;
	pf.rgxTabs[0]=1600;
	pf.dwMask = PFM_TABSTOPS;
	SetParaFormat(pf);

	UpdateWindowInfoView();
}

void CMyEditView::OnWininfoOptions()
{
	if(IDOK==ShowWinInfoOpDlg(this))
	{
		//UpdateWindowInfoView();
	}
}
