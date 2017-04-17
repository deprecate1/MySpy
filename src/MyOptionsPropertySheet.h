#pragma once

#include "MyResponseOptionsDlg.h"
#include "MyWinInfoOptionsDlg.h"
#include "MyLoadSaveOptionsDlg.h"

// CMyOptionsPropertySheet

class CMyOptionsPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyOptionsPropertySheet)

public:
	CMyOptionsPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyOptionsPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMyOptionsPropertySheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CMyWinInfoOptionsDlg m_WinInfoOptionsDlg;
	CMyResponseOptionsDlg m_ResponseOptionsDlg;
	CMyLoadSaveOptionsDlg m_LoadSaveOptionsDlg;
};


