// MySpyView.h : interface of the CMyTreeView class
//


#pragma once

#include "afxcview.h"
#include "afxcmn.h"

#include "MyFindDlg.h"
#include "MyEditView.h"

enum TreeImageList
{
	TIMG_ROOT,
	TIMG_VISIBLE_CHILD,
	TIMG_VISIBLE_PARENT,
	TIMG_VISIBLE_CHILD_SELECTED,
	TIMG_VISIBLE_PARENT_SELECTED,
	TIMG_NONVISIBLE_CHILD,
	TIMG_NONVISIBLE_PARENT,
	TIMG_NONVISIBLE_CHILD_SELECTED,
	TIMG_NONVISIBLE_PARENT_SELECTED

};

class CMyTreeView : 
	public CTreeView,
	public CMyWindowInfoView
{
protected: // create from serialization only
	CMyTreeView();
	DECLARE_DYNCREATE(CMyTreeView)

// Attributes
public:
	CMySpyDoc* GetDocument() const;

// Operations
	void UpdateTree(void);
	BOOL SelectItem(HWND hWndSelected);
	HTREEITEM FindTreeItem(HTREEITEM startitem,CMyFindOptions* pFindOptions);
	//void DoPopupMenu(UINT nMenuID);
	void UpdateItem(HTREEITEM hItem);

// Implementation

	virtual ~CMyTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void UpdateItemRecursive(HTREEITEM hItem, sWindowInfo* sWinInf);
	CTreeCtrl*   m_pCtlTree;
	HTREEITEM    m_hLastItem;
	CImageList   m_ctlImage;
	CMyFindDlg*    m_pFindDlg;
	CMyOptions&  m_rOptions;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	HTREEITEM GetNextSiblingOfAncestor(HTREEITEM startitem);
	HTREEITEM GetJoungestDescendant(HTREEITEM startitem);
	HTREEITEM GetPrevItem(HTREEITEM startitem);
	HTREEITEM GetNextItem(HTREEITEM startitem);
public:
  BOOL FindDlgVisible();
	LRESULT UpdateWindowInfo(WPARAM,LPARAM){return 0;};
	afx_msg LRESULT FindFindnext(WPARAM,LPARAM);
// Overrides
//	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
// Generated message map functions
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnDisplayInHex();
//	afx_msg void OnUpdateDisplayInHex(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVisibilityAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVisibilityVisibleonly(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVisibilityNonvisibleonly(CCmdUI *pCmdUI);
	afx_msg void OnUpdateParentParentsonly(CCmdUI *pCmdUI);
	afx_msg void OnUpdateParentChildonly(CCmdUI *pCmdUI);
//	afx_msg void OnActionCommand(UINT nActionID);
//	afx_msg void OnViewCommand(UINT nActionID);
	afx_msg void OnMenuEditFind();
	afx_msg void OnMenuEditFilter();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);

	//CTreeCtrl* GetMySpyTreeCtrl(){return m_pCtlTree;}
};

#ifndef _DEBUG  // debug version in MySpyView.cpp
inline CMySpyDoc* CMyTreeView::GetDocument() const
   { return reinterpret_cast<CMySpyDoc*>(m_pDocument); }
#endif

