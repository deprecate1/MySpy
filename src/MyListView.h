#pragma once
#include "MyWindowInfoView.h"


// CMyListView view

class CMyListView : 
	public CListView,
	public CMyWindowInfoView
{
	DECLARE_DYNCREATE(CMyListView)

protected:
	CMyListView();           // protected constructor used by dynamic creation
	virtual ~CMyListView();

public:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	afx_msg void OnWininfoOptions();
	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnInitialUpdate();
	LRESULT UpdateWindowInfo(WPARAM wParam,LPARAM lParam);

protected:
	DECLARE_MESSAGE_MAP()
    afx_msg LRESULT OnMySelChanged(WPARAM,LPARAM);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


