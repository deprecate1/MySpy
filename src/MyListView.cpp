// MyListView.cpp : implementation file
//

#include "stdafx.h"
#include "MySpy.h"
#include "MyListView.h"
#include "MySpyDoc.h"
#include "MyOptions.h"
// CMyListView

IMPLEMENT_DYNCREATE(CMyListView, CListView)

CMyListView::CMyListView()
{
	m_pDoc=NULL;
}

CMyListView::~CMyListView()
{
}

BEGIN_MESSAGE_MAP(CMyListView, CListView)
ON_REGISTERED_MESSAGE(MYMSG_SELECTION_CHANGED,OnMySelChanged)
ON_COMMAND(ID_WININFO_OPTIONS, OnWininfoOptions)
ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRclick)
END_MESSAGE_MAP()


// CMyListView diagnostics

#ifdef _DEBUG
void CMyListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG


// CMyListView message handlers

void CMyListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// Gain a reference to the list control itself
	CListCtrl& theCtrl = GetListCtrl();

	DWORD fgColor=GetSysColor(COLOR_INFOTEXT);
	DWORD bgColor=GetSysColor(COLOR_INFOBK);
	
	COLORREF bg=RGB(GetRValue(bgColor),GetGValue(bgColor),GetBValue(bgColor));
	COLORREF fg=RGB(GetRValue(fgColor),GetGValue(fgColor),GetBValue(fgColor));

	theCtrl.SetBkColor(bg);
	theCtrl.SetTextBkColor(bg);
	theCtrl.SetTextColor(fg);

	CRect clientRect;
	GetClientRect(&clientRect);

	// Insert a column. This override is the most convenient.
	theCtrl.InsertColumn(0, _T("Title"), LVCFMT_LEFT,clientRect.Width()*20/100);
	theCtrl.InsertColumn(1, _T("Value"), LVCFMT_LEFT,clientRect.Width()*80/100);

	theCtrl.ModifyStyle(0, LVS_REPORT|LVS_NOCOLUMNHEADER);

	ListView_SetExtendedListViewStyle(theCtrl.m_hWnd, 
		LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_GRIDLINES );
	
	m_pDoc = (CMySpyDoc*)GetDocument();
	ASSERT_VALID(m_pDoc);
}

void CMyListView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	UpdateWindowInfoView();
}

LRESULT CMyListView::UpdateWindowInfo(WPARAM wParam,LPARAM lParam)
{
	return OnMySelChanged(wParam,lParam);
}

LRESULT CMyListView::OnMySelChanged(WPARAM wParam,LPARAM lParam)
{
	if(!m_pDoc)
		m_pDoc = (CMySpyDoc*)GetDocument();
	ASSERT_VALID(m_pDoc);
	if (!m_pDoc)
		return 0;


	LPCTSTR strNumFormat; 
	if((BOOL) lParam) //bDisplayInHex
		strNumFormat=m_pDoc->m_pstrHexString;
	else
		strNumFormat=m_pDoc->m_pstrDecString;



	//m_pDoc->SetDisplayInHex((bool) lParam);
	m_pDoc->SetCurrentlySelectedHwnd((HWND) wParam);

	CListCtrl& theCtrl = GetListCtrl();

	theCtrl.DeleteAllItems();

	LVITEM lvi;
	CString strText;

	int linecount=0;
	
	CMyOptions& rOptions = CMyOptions::GetMyOptions();
	
	for(int i=0; i<rOptions.m_aWinInfosOnInfoPane.GetCount();i++)
	{
		CWinInfo* wi = rOptions.m_aWinInfosOnInfoPane.GetAt(i);

		if(wi->m_bVisible)
			m_pDoc->GetWindowInfoTitle(i,strText);
		else
			continue;
       
		// Insert the first item
		lvi.mask =  /*LVIF_IMAGE |*/ LVIF_TEXT;
		lvi.iItem = linecount++;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strText);
		//lvi.iImage = i%8;		// There are 8 images in the image list
		theCtrl.InsertItem(&lvi);

		// Set subitem 1
		m_pDoc->GetWindowInfoData(i,strText);
		lvi.iSubItem =1;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strText);
		theCtrl.SetItem(&lvi);
        		
	}
	

	return 0;
}


void CMyListView::OnWininfoOptions()
{
	if(IDOK==ShowWinInfoOpDlg(this))
	{
		//UpdateWindowInfoView();
	}
}

void CMyListView::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	DoPopupMenu(IDR_POPUP_WININFO,this);
	*pResult = 0;
}
