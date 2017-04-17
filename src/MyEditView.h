#pragma once
#include "afxrich.h"
//#include "scewma0u.hpp"
#include "MySpyDoc.h"
#include "MyWindowInfoView.h"


class CMyEditView :
	public CRichEditView,
	public CMyWindowInfoView
{
public:
	CMyEditView(void);
	DECLARE_DYNCREATE(CMyEditView)
    ~CMyEditView(void);
    void OnInitialUpdate();
	LRESULT UpdateWindowInfo(WPARAM wParam,LPARAM lParam);
	afx_msg void OnEnSetfocus();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnWininfoOptions();
	afx_msg void OnDestroy();
	
	DECLARE_MESSAGE_MAP()
	CMySpyDoc* GetDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
    afx_msg LRESULT OnMySelChanged(WPARAM,LPARAM);
	void PrintInfoTitle(LPCTSTR strTitle);
	virtual HMENU GetContextMenu(WORD seltyp, LPOLEOBJECT lpoleobj, CHARRANGE* lpchrg);
	virtual void OnTextNotFound(LPCTSTR lpszFind);

private:
	CString m_strDisplayText;

};

#ifndef _DEBUG  // debug version in MyEditView.cpp
inline CMySpyDoc* CMyEditView::GetDocument()
   { return (CMySpyDoc*)m_pDocument; }
#endif
