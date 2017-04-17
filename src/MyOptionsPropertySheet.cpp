// OptionsPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "MySpy.h"
#include "MyOptionsPropertySheet.h"
#include "MainFrm.h"
#include ".\myoptionspropertysheet.h"

// CMyOptionsPropertySheet

IMPLEMENT_DYNAMIC(CMyOptionsPropertySheet, CPropertySheet)
CMyOptionsPropertySheet::CMyOptionsPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_WinInfoOptionsDlg);
	AddPage(&m_ResponseOptionsDlg);
	AddPage(&m_LoadSaveOptionsDlg);

}

CMyOptionsPropertySheet::CMyOptionsPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_WinInfoOptionsDlg);
	AddPage(&m_ResponseOptionsDlg);
	AddPage(&m_LoadSaveOptionsDlg);
}

CMyOptionsPropertySheet::~CMyOptionsPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyOptionsPropertySheet, CPropertySheet)
END_MESSAGE_MAP()


// CMyOptionsPropertySheet message handlers

BOOL CMyOptionsPropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	return bResult;
}

