#include "StdAfx.h"
#include ".\mypropertypage.h"
#include "MainFrm.h"

CMyPropertyPage::CMyPropertyPage(UINT nId)
	:CPropertyPage(nId),
	m_bModified(FALSE),
	m_rOptions(CMyOptions::GetMyOptions())
{

}

void CMyPropertyPage::SetModified()
{
		m_bModified = IsModified();
		CPropertyPage::SetModified(m_bModified);
};


LRESULT CMyPropertyPage::OnQuerySiblings(WPARAM wParam,LPARAM)
{
	LRESULT lRet = 0;

	switch((MyPropertyPageMsg)wParam)
	{
		case PPM_UPDATE:
			Update();
			TRACE(_T("OnQuerySiblings PPM_UPDATE\n"));
			break;
		case PPM_STORE:
			Store();
			TRACE(_T("OnQuerySiblings PPM_STORE\n"));
			break;
		case PPM_IS_MODIFIED:
			lRet = (LRESULT)IsModified();
			TRACE(_T("OnQuerySiblings PPM_IS_MODIFIED ret=%d\n"),lRet);
			break;
	}

	return lRet;
}
BOOL CMyPropertyPage::OnApply()
{
	OnOK();

	return TRUE;
}

void CMyPropertyPage::OnCancel()
{
	if(m_bModified)
	{
		m_rOptions.LoadDefaults();
		Update();
		QuerySiblings(PPM_UPDATE,NULL);
		Store();
		QuerySiblings(PPM_STORE,NULL);
	}
	CPropertyPage::OnCancel();
}

void CMyPropertyPage::OnOK()
{
	Store();
	QuerySiblings(PPM_STORE,NULL);

	CMainFrame* mf = (CMainFrame*)GetParentFrame();

	mf->RefreshTreePane();
	mf->RefreshWinInfoPane();

	CPropertyPage::OnOK();
}
