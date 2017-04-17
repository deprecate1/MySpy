// MySpyView.cpp : implementation of the CMyTreeView class
//

#include "stdafx.h"
#include "MySpy.h"

#include "MySpyDoc.h"
#include "MyTreeView.h"
#include ".\mytreeview.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyTreeView
IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_COMMAND(ID_EDIT_FIND, OnMenuEditFind)
	ON_COMMAND(ID_EDIT_FILTER, OnMenuEditFilter)
//	ON_COMMAND(ID_VIEW_DISPLAY_IN_HEX, OnDisplayInHex)
//	ON_UPDATE_COMMAND_UI(ID_VIEW_DISPLAY_IN_HEX, OnUpdateDisplayInHex)
//	ON_COMMAND(IDB_VIEW_DISPLAY_IN_HEX, OnDisplayInHex)
//	ON_UPDATE_COMMAND_UI(IDB_VIEW_DISPLAY_IN_HEX, OnUpdateDisplayInHex)
	ON_UPDATE_COMMAND_UI(ID_VISIBILITY_ALL, OnUpdateVisibilityAll)
	ON_UPDATE_COMMAND_UI(ID_VISIBILITY_VISIBLEONLY, OnUpdateVisibilityVisibleonly)
	ON_UPDATE_COMMAND_UI(ID_VISIBILITY_NONVISIBLEONLY, OnUpdateVisibilityNonvisibleonly)
	//ON_UPDATE_COMMAND_UI(ID_PARENT_ALL, OnUpdateParentAll)
	ON_UPDATE_COMMAND_UI(ID_PARENT_PARENTSONLY, OnUpdateParentParentsonly)
	ON_UPDATE_COMMAND_UI(ID_PARENT_CHILDONLY, OnUpdateParentChildonly)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnTvnSelchanged)
	//ON_COMMAND_RANGE(ID_ACTION_SHOW,ID_ACTION_END, OnActionCommand)
	//ON_COMMAND_RANGE(ID_ACTION_END,ID_VIEW_END, OnViewCommand)
	ON_REGISTERED_MESSAGE(MYMSG_FINDNEXT_WAS_PRESSED,FindFindnext)
//	ON_NOTIFY_REFLECT(NM_KILLFOCUS, OnNMKillfocus)
	ON_WM_SETFOCUS()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRclick)
END_MESSAGE_MAP()
// CMyTreeView construction/destruction

CMyTreeView::CMyTreeView():CTreeView(),
m_pCtlTree(NULL),
m_pFindDlg(NULL),
m_rOptions(CMyOptions::GetMyOptions())
{

}

CMyTreeView::~CMyTreeView()
{
	if(m_pFindDlg) delete m_pFindDlg;
}

BOOL CMyTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

// CMyTreeView drawing

//void CMyTreeView::OnDraw(CDC* pDC)
//{
//	CMySpyDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//	
//	//CTreeView::OnDraw(pDC);
//}


// CMyTreeView diagnostics

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMySpyDoc* CMyTreeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySpyDoc)));
	return (CMySpyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyTreeView message handlers

void CMyTreeView::OnUpdateVisibilityAll(CCmdUI *pCmdUI)
{
	CMySpyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc || !pCmdUI->m_pMenu )
		return;

	if(m_rOptions.m_eVisibility == VISIBILITY_ALL)
		pCmdUI->m_pMenu->CheckMenuRadioItem(ID_VISIBILITY_ALL,ID_VISIBILITY_NONVISIBLEONLY,
		ID_VISIBILITY_ALL,MF_CHECKED);
	if(m_rOptions.m_eParent == PARENT_ALL)
		pCmdUI->m_pMenu->CheckMenuRadioItem(ID_PARENT_ALL,ID_PARENT_CHILDONLY,
		ID_PARENT_ALL,MF_CHECKED);
}

void CMyTreeView::OnUpdateVisibilityVisibleonly(CCmdUI *pCmdUI)
{
	if(m_rOptions.m_eVisibility == VISIBILITY_VISIBLE_ONLY)
		pCmdUI->m_pMenu->CheckMenuRadioItem(ID_VISIBILITY_ALL,ID_VISIBILITY_NONVISIBLEONLY,
		ID_VISIBILITY_VISIBLEONLY,MF_CHECKED);
}

void CMyTreeView::OnUpdateVisibilityNonvisibleonly(CCmdUI *pCmdUI)
{
	if(m_rOptions.m_eVisibility == VISIBILITY_NON_VISIBLE_ONLY)
		pCmdUI->m_pMenu->CheckMenuRadioItem(ID_VISIBILITY_ALL,ID_VISIBILITY_NONVISIBLEONLY,
		ID_VISIBILITY_NONVISIBLEONLY,MF_CHECKED);

}

//void CMyTreeView::OnUpdateParentAll(CCmdUI *pCmdUI)
//{
//	if(m_rOptions.m_eParent == PARENT_ALL)
//		pCmdUI->m_pMenu->CheckMenuRadioItem(ID_PARENT_ALL,ID_PARENT_CHILDONLY,
//		ID_PARENT_ALL,MF_CHECKED);
//}

void CMyTreeView::OnUpdateParentParentsonly(CCmdUI *pCmdUI)
{
	if(m_rOptions.m_eParent == PARENT_PARENTS_ONLY)
	{
		pCmdUI->m_pMenu->CheckMenuItem(ID_VISIBILITY_ALL,MF_UNCHECKED);
		pCmdUI->m_pMenu->CheckMenuRadioItem(ID_PARENT_ALL,ID_PARENT_CHILDONLY,
		ID_PARENT_PARENTSONLY,MF_CHECKED);
	}
}

void CMyTreeView::OnUpdateParentChildonly(CCmdUI *pCmdUI)
{
	if(m_rOptions.m_eParent == PARENT_CHILDREN_ONLY)
	{
		pCmdUI->m_pMenu->CheckMenuItem(ID_VISIBILITY_ALL,MF_UNCHECKED);
		pCmdUI->m_pMenu->CheckMenuRadioItem(ID_PARENT_ALL,ID_PARENT_CHILDONLY,
		ID_PARENT_CHILDONLY,MF_CHECKED);
	}
}


void CMyTreeView::UpdateTree(void)
 {
	CMySpyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	HWND hWndSelected = NULL;
	if(m_pCtlTree->GetCount()!=0)
	{
		HTREEITEM selectedItem=m_pCtlTree->GetSelectedItem();
		if(selectedItem)
		{
			hWndSelected = (HWND)m_pCtlTree->GetItemData(selectedItem);
		}
	}

	m_pCtlTree->DeleteAllItems();
	m_hLastItem=NULL;
	HTREEITEM hItem=NULL;

	m_pCtlTree->InsertItem(TVIF_PARAM|TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE,
		_T("Desktop (\"Title\"     \"Class\"     (PID)     [hWnd]     \"Module\")"),
		TIMG_ROOT,TIMG_ROOT,NULL,NULL,(LPARAM)GetDesktopWindow()->m_hWnd,NULL,
		TVI_ROOT);

	m_pCtlTree->SetItemState(m_pCtlTree->GetRootItem(), TVIS_BOLD, TVIS_BOLD);

	for (int i=0; i < pDoc->m_oEnumWins.GetWindowCount(); i++)
    {
		HTREEITEM hItem=NULL;
		sWindowInfo* sWinInf = pDoc->m_oEnumWins.GetWindowInfo(i);
		CString strTmp;
		// get parent
		HWND hWnd = sWinInf->hWnd;
		HWND hParentWnd=::GetParent(sWinInf->hWnd);

		// set item string
		if(m_rOptions.m_bDisplayInHex)
			strTmp.Format(_T("\"%s\" \"%s\" (0x%X) [0x%X] \"%s\""), 
			sWinInf->strWindowTitle, sWinInf->strClassName, sWinInf->dwPID, sWinInf->hWnd, sWinInf->strModuleName);
		else
			strTmp.Format(_T("\"%s\" \"%s\" (%d) [%d] \"%s\""), 
			sWinInf->strWindowTitle, sWinInf->strClassName, sWinInf->dwPID, sWinInf->hWnd, sWinInf->strModuleName);

		int nImageIndex;
		int nImageIndexSelected;

		hItem=m_hLastItem;

		while(hItem)
		{
			if((HWND)m_pCtlTree->GetItemData(hItem) == hParentWnd)
			{
				if(::IsWindowVisible(hParentWnd))
				{
					nImageIndex = TIMG_VISIBLE_PARENT;
					nImageIndexSelected = TIMG_VISIBLE_PARENT_SELECTED;
				}
				else
				{
					nImageIndex = TIMG_NONVISIBLE_PARENT;
					nImageIndexSelected = TIMG_NONVISIBLE_PARENT_SELECTED;
				}
				m_pCtlTree->SetItemImage(hItem,nImageIndex,nImageIndexSelected);
				break;
			}
			else
			{
				hItem=m_pCtlTree->GetParentItem(hItem);
			}
		}

		if(::IsWindowVisible(hWnd))
		{
			nImageIndex = TIMG_VISIBLE_CHILD;
			nImageIndexSelected = TIMG_VISIBLE_CHILD_SELECTED;
		}
		else
		{
			nImageIndex = TIMG_NONVISIBLE_CHILD;
			nImageIndexSelected = TIMG_NONVISIBLE_CHILD_SELECTED;
		}

		if(::IsWindow(hWnd))
		{
			m_hLastItem = m_pCtlTree->InsertItem(TVIF_PARAM|TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE, 
				strTmp, nImageIndex, nImageIndexSelected, NULL, NULL, 
				LPARAM(hWnd), (hItem)?hItem:m_pCtlTree->GetRootItem(), TVI_LAST);
		}
	}
	
	m_pCtlTree->SetItemImage(m_pCtlTree->GetRootItem(),TIMG_ROOT,TIMG_ROOT);
	m_pCtlTree->Expand(m_pCtlTree->GetRootItem(), TVE_EXPAND);

	if(::IsWindow(hWndSelected))
		if(!SelectItem(hWndSelected))
			SelectItem(NULL);//select root item
 }

 void CMyTreeView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
 {
	 UpdateTree();
 }

 void CMyTreeView::OnInitialUpdate()
 {
	 CTreeView::OnInitialUpdate();
 }

 int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
 {
	 lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS;
	 
	 if (CTreeView::OnCreate(lpCreateStruct) == -1)
          return -1;

 	CTreeCtrl& tctl= GetTreeCtrl();
	m_pCtlTree = &tctl;

	if(m_pCtlTree==NULL) return -1;

	// Create the Image List
	m_ctlImage.Create(IDB_IMAGELIST,16,0,RGB(255,0,255));
	m_ctlImage.SetBkColor(GetSysColor(COLOR_WINDOW));

	/// Attach image list to Tree
	m_pCtlTree->SetImageList(&m_ctlImage,TVSIL_NORMAL);
	//m_dropTarget.Register(this);
	 return 0;
 }


 void CMyTreeView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
 {
	 LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	 *pResult = 0;
	 
	 //m_pCtlTree->SetItemState(pNMTreeView->itemOld.hItem, 0, TVIS_BOLD);
	 //m_pCtlTree->SetItemState(pNMTreeView->itemNew.hItem, TVIS_BOLD, TVIS_BOLD);
	 m_pCtlTree->SetItemState(pNMTreeView->itemOld.hItem, 0, TVIS_DROPHILITED);
	 m_pCtlTree->SetItemState(pNMTreeView->itemNew.hItem, TVIS_DROPHILITED, TVIS_DROPHILITED);

	 CString strText; 
	 CMainFrame* mf = (CMainFrame*) GetParentFrame();

	 HTREEITEM selectedItem = pNMTreeView->itemNew.hItem;

	 HWND hWnd = (HWND) m_pCtlTree->GetItemData(selectedItem);

	 if(IsWindow(hWnd))
	 {

		 ::PostMessage(mf->m_wndSplitter.GetPane(1,0)->m_hWnd,MYMSG_SELECTION_CHANGED,
			(WPARAM)hWnd,NULL);
	 }
	 
	 if(selectedItem == m_pCtlTree->GetRootItem())
	 {
		 strText=_T("Ready");
		 mf->EnableActionToolbar(FALSE);

	 }
	 else
	 {
		strText = m_pCtlTree->GetItemText(m_pCtlTree->GetSelectedItem());
		mf->EnableActionToolbar(TRUE);
	 }
	
	 mf->m_wndStatusBar.SetPaneText(ID_SEPARATOR,strText);
 }

 void CMyTreeView::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
 {
	CPoint curPoint;
	GetCursorPos(&curPoint);
	ScreenToClient(&curPoint);
	
	m_pCtlTree->SelectItem(m_pCtlTree->HitTest(curPoint));
	DoPopupMenu(IDR_POPUP_ACTION,/*this*/(CMainFrame*) GetParentFrame());
	*pResult = 0;
 }

BOOL CMyTreeView::SelectItem(HWND hWndSelected)
{
	BOOL bRet = FALSE;

	if(hWndSelected)
	{
		HTREEITEM ret=NULL;

		CMyFindOptions sfo;
		sfo.bAlwaysFromBegin=TRUE;
		sfo.SetHWndToFind(hWndSelected);

		if((ret=FindTreeItem(m_pCtlTree->GetRootItem(),&sfo)))
		{
			m_pCtlTree->EnsureVisible(ret);
			bRet = m_pCtlTree->SelectItem(ret);
		}
	}
	else
	{
		bRet = m_pCtlTree->SelectItem(m_pCtlTree->GetRootItem());
	}

	return bRet;
}

void CMyTreeView::UpdateItem(HTREEITEM hItem)
{
	static int nRecursionsLevel = 0;
	static sWindowInfo* sWinInf = 0;
	static CMySpyDoc* pDoc = 0;

	if(0 == nRecursionsLevel++ || pDoc == 0)
	{
		pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		pDoc->Refresh(false);
	}

	HWND hWndSelected = (HWND)m_pCtlTree->GetItemData(hItem);
	
	if(::IsWindow(hWndSelected))
	{
        int nImageIndex;
		int nImageIndexSelected;
		
		if(::IsWindowVisible(hWndSelected))
		{
			nImageIndex = TIMG_VISIBLE_CHILD;
			nImageIndexSelected = TIMG_VISIBLE_CHILD_SELECTED;
		}
		else
		{
			nImageIndex = TIMG_NONVISIBLE_CHILD;
			nImageIndexSelected = TIMG_NONVISIBLE_CHILD_SELECTED;
		}
		
		if(m_pCtlTree->ItemHasChildren(hItem))
		{
			nImageIndex++; //Parent image id
			nImageIndexSelected++;

			HTREEITEM hNextItem;
			HTREEITEM hChildItem = m_pCtlTree->GetChildItem(hItem);
			
			while (hChildItem != NULL)
			{
				hNextItem = m_pCtlTree->GetNextItem(hChildItem, TVGN_NEXT);
				UpdateItem(hChildItem); //recursion
				hChildItem = hNextItem;
			}

		}

		m_pCtlTree->SetItemImage(hItem,nImageIndex,nImageIndexSelected);

		sWinInf = pDoc->m_oEnumWins.GetWindowInfo(hWndSelected);

		if(NULL!=sWinInf)
		{
			CString strTmp;

			if(m_rOptions.m_bDisplayInHex)
				strTmp.Format(_T("\"%s\" \"%s\" (0x%X) [0x%X] \"%s\""), 
				sWinInf->strWindowTitle, sWinInf->strClassName, sWinInf->dwPID, sWinInf->hWnd, sWinInf->strModuleName);
			else
				strTmp.Format(_T("\"%s\" \"%s\" (%d) [%d] \"%s\""), 
				sWinInf->strWindowTitle, sWinInf->strClassName, sWinInf->dwPID, sWinInf->hWnd, sWinInf->strModuleName);
			
			m_pCtlTree->SetItemText(hItem,strTmp);
		}
		else
		{
			m_pCtlTree->DeleteItem(hItem);
		}

	}
	else
	{
		m_pCtlTree->DeleteItem(hItem);
	}

	nRecursionsLevel--;
}
BOOL CMyTreeView::FindDlgVisible()
{
  BOOL bRet = false;
  if(m_pFindDlg)
  {
    bRet = m_pFindDlg->IsWindowVisible();
  }
  return bRet;

}
void CMyTreeView::OnMenuEditFind()
{
	HTREEITEM startitem=NULL, ret=NULL;

	if(!m_pFindDlg)
	{
		m_pFindDlg = new CMyFindDlg;
		//m_pFindDlg = new CFindReplaceDialog;
		//m_pFindDlg->Create(TRUE,_T(""),0,FR_DOWN,this);
	}

	if(m_pFindDlg)
	{

		CMySpyDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		m_pFindDlg->SetDisplayInHex(m_rOptions.m_bDisplayInHex);
		m_pFindDlg->CenterWindow();
		m_pFindDlg->ShowWindow(SW_SHOW);
	}
				
}

void CMyTreeView::OnMenuEditFilter()
{
	XTRACE(L"menu filter click.\n");
}

LRESULT CMyTreeView::FindFindnext(WPARAM wParam, LPARAM lParam)
{
	CWaitCursor w;
	
	CMyFindOptions* pFindOptions = (CMyFindOptions*)lParam;

	HTREEITEM startitem=NULL; 
	HTREEITEM ret;

	if(pFindOptions->bAlwaysFromBegin)
		ret=m_pCtlTree->GetRootItem();
	else
		ret=m_pCtlTree->GetSelectedItem();

	if(pFindOptions->bResearch)
	{	
		ret=FindTreeItem(
			pFindOptions->bDirectionUp ? GetPrevItem(ret) : GetNextItem(ret), 
			pFindOptions); 
	}
	else
	{
		ret=FindTreeItem(ret?ret:m_pCtlTree->GetRootItem(),	
			pFindOptions);
	}

	if(ret)
	{	
		//we found it, select it!
		m_pCtlTree->EnsureVisible(ret);
		m_pCtlTree->SelectItem(ret);
		//m_pCtlTree->SetFocus();

		if(pFindOptions->GetStrToFind())
			m_pFindDlg->AddToCombo(pFindOptions->GetStrToFind());
	}
	else
	{
		if(pFindOptions->bFindByMouse)
		{
			int ret = MessageBox(_T("The window was not found on the tree. Would you refresh it?"),_T("Find Window"),MB_YESNO|MB_ICONQUESTION);
			if(ret==IDYES)
			{	
				CMySpyDoc* pDoc = GetDocument();
				ASSERT_VALID(pDoc);
				if (!pDoc)
					return 0;
				m_rOptions.m_eVisibility=VISIBILITY_ALL;
				m_rOptions.m_eParent=PARENT_ALL;
				pDoc->Refresh();

				SelectItem(pFindOptions->GetHWndToFind());
			}

		}
		else
			AfxMessageBox(IDS_TEXT_NOT_FOUND,/*_T("Find Window"),*/MB_OK|MB_ICONINFORMATION);
	}
	return 0;
}


HTREEITEM CMyTreeView::FindTreeItem(HTREEITEM startitem, CMyFindOptions* pFindOptions )
{
	if(startitem==NULL) return NULL;

	while(startitem)
	{
		if(pFindOptions->bAlwaysFromBegin)//it means that we search the HWND
		{
			HWND hWnd =	(HWND)m_pCtlTree->GetItemData(startitem);
			if(hWnd==pFindOptions->GetHWndToFind())
				break; //founded!!!
		}
		else
		{
			CString buff = m_pCtlTree->GetItemText(startitem);
			CString label = pFindOptions->GetStrToFind();

			if(!pFindOptions->bMatchCase)
			{
				label.MakeLower();
				buff.MakeLower();
			}

			if(buff.Find(label)!=-1)
				break; //founded!!!
		}
		if(pFindOptions->bDirectionUp)
			startitem = GetPrevItem(startitem);
		else
			startitem = GetNextItem(startitem);
	}
	return startitem;
}

HTREEITEM CMyTreeView::GetNextSiblingOfAncestor(HTREEITEM startitem)
{
	HTREEITEM ret = m_pCtlTree->GetNextSiblingItem(startitem);

	if(ret) 
		return ret;

	ret = m_pCtlTree->GetParentItem(startitem);

	if(ret == m_pCtlTree->GetRootItem())
		return NULL;
	
	return GetNextSiblingOfAncestor(ret);
}

HTREEITEM CMyTreeView::GetJoungestDescendant(HTREEITEM startitem)
{
	
	HTREEITEM ret = m_pCtlTree->GetChildItem(startitem);

	if(!ret)//No child
		return startitem;

	HTREEITEM tmp;

	while(ret)
	{
		tmp = ret;
		ret = m_pCtlTree->GetNextSiblingItem(ret);
	}

	return GetJoungestDescendant(tmp);
}

HTREEITEM CMyTreeView::GetPrevItem(HTREEITEM startitem)
{
	HTREEITEM ret = m_pCtlTree->GetPrevSiblingItem(startitem);
	if(ret)
	{
		if(m_pCtlTree->ItemHasChildren(ret))
			return GetJoungestDescendant(ret);
		else
            return ret;
	}
	
	ret = m_pCtlTree->GetParentItem(startitem);

	//if(ret==m_pCtlTree->GetRootItem())
	//	return NULL;
	return ret;
}

HTREEITEM CMyTreeView::GetNextItem(HTREEITEM startitem)
{

	if(m_pCtlTree->ItemHasChildren(startitem))
			return m_pCtlTree->GetChildItem(startitem);

	return GetNextSiblingOfAncestor(startitem);
}

void CMyTreeView::OnSetFocus(CWnd* pOldWnd)
{
	__super::OnSetFocus(pOldWnd);

	if(pOldWnd->m_hWnd==this->m_hWnd || pOldWnd->m_hWnd==NULL)
		return;

	CString strText; 
	CMainFrame* mf = (CMainFrame*) GetParentFrame();

	HTREEITEM selectedItem = m_pCtlTree->GetSelectedItem();

	HWND hWnd = (HWND) m_pCtlTree->GetItemData(selectedItem);

	if(IsWindow(hWnd))
	{
		::PostMessage(mf->m_wndSplitter.GetPane(1,0)->m_hWnd,MYMSG_SELECTION_CHANGED,
		(WPARAM)hWnd,NULL);
	}
	
    if(selectedItem == m_pCtlTree->GetRootItem())
	{
		strText=_T("Ready");
		mf->EnableActionToolbar(FALSE);

	}
	else
	{
	strText = m_pCtlTree->GetItemText(m_pCtlTree->GetSelectedItem());
	mf->EnableActionToolbar(TRUE);
	}

	mf->m_wndStatusBar.SetPaneText(ID_SEPARATOR,strText);
}

