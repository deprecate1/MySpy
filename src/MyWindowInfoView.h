#pragma once
#include "afxwin.h"
#include "resource.h"
#include "MySpyDoc.h"

class CMyWindowInfoView
{
public:
	 CMyWindowInfoView(void);
	~CMyWindowInfoView(void);
     
	virtual LRESULT UpdateWindowInfo(WPARAM,LPARAM){return 0;};
     
	 LRESULT UpdateWindowInfoView();
protected:
 	 void DoPopupMenu(UINT nMenuID,CWnd* pWnd);
	 int FindMenuItem(CMenu* Menu, LPCTSTR MenuString);
	 int ShowWinInfoOpDlg(CWnd* pParent);
	 CMySpyDoc* m_pDoc;

};
