// MyResponseOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MySpy.h"
#include "MyResponseOptionsDlg.h"
#include "MainFrm.h"
#include ".\myresponseoptionsdlg.h"

// CMyResponseOptionsDlg dialog

IMPLEMENT_DYNAMIC(CMyResponseOptionsDlg, CPropertyPage)

CMyResponseOptionsDlg::CMyResponseOptionsDlg(CWnd* pParent /*=NULL*/)
: CMyPropertyPage(CMyResponseOptionsDlg::IDD)
, m_bApplied(false)
{

}

CMyResponseOptionsDlg::~CMyResponseOptionsDlg()
{
}

BOOL CMyResponseOptionsDlg::OnInitDialog()
{	
	CDialog::OnInitDialog();
	m_rOptions = CMyOptions::GetMyOptions();

	Update();
	
	return 0; //can return 0 only if it has explicitly set the input 
			  //focus to one of the controls in the dialog box
}

void CMyResponseOptionsDlg::Update(void)
{
	
	m_buttonOnError.SetCheck(m_rOptions.m_bResponseAboutCommandExecutionOnError);
	m_buttonOnSuccess.SetCheck(m_rOptions.m_bResponseAboutCommandExecutionOnSuccess);
	m_buttonNoResponse.SetCheck(m_rOptions.m_bNoResponsePlease);

	m_buttonOnError.EnableWindow(!m_rOptions.m_bNoResponsePlease);
	m_buttonOnSuccess.EnableWindow(!m_rOptions.m_bNoResponsePlease);

	CString strResponseTimeout;
	strResponseTimeout.Format(
		m_rOptions.m_bDisplayInHex?_T("0x%X"):_T("%lu"),
		m_rOptions.m_nResponseTimeout);
	m_editResponseTimeout.SetWindowText((LPCTSTR)strResponseTimeout.MakeUpper());
	m_editResponseTimeout.EnableWindow(!m_rOptions.m_bNoResponsePlease);

	m_buttonActivateAfterAction.SetCheck(m_rOptions.m_bActivateAfterAction);

}

void CMyResponseOptionsDlg::Store()
{
	m_rOptions.m_bResponseAboutCommandExecutionOnError = m_buttonOnError.GetCheck()?true:false;
	m_rOptions.m_bResponseAboutCommandExecutionOnSuccess =	m_buttonOnSuccess.GetCheck()?true:false;
	m_rOptions.m_bNoResponsePlease = m_buttonNoResponse.GetCheck()?true:false;

	CString strResponseTimeout;
	m_editResponseTimeout.GetWindowText(strResponseTimeout);
	m_rOptions.m_nResponseTimeout = _ttoi((LPCTSTR)strResponseTimeout);
	m_rOptions.m_bActivateAfterAction = m_buttonActivateAfterAction.GetCheck()?true:false;
}
void CMyResponseOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESPONSE_ON_ERROR, m_buttonOnError);
	DDX_Control(pDX, IDC_RESPONSE_ON_SUCCESS, m_buttonOnSuccess);
	DDX_Control(pDX, IDC_NO_RESPONSE_ABOUT_COMMAND_EXECUTION, m_buttonNoResponse);
	DDX_Control(pDX, IDC_EDIT_REPONSE_TIMEOUT, m_editResponseTimeout);
	DDX_Control(pDX, IDC_ACTIVATE_AFTER_ACTION, m_buttonActivateAfterAction);
}


BEGIN_MESSAGE_MAP(CMyResponseOptionsDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_RESPONSE_ON_ERROR, MySetModified)
	ON_BN_CLICKED(IDC_RESPONSE_ON_SUCCESS, MySetModified)
	ON_BN_CLICKED(IDC_NO_RESPONSE_ABOUT_COMMAND_EXECUTION, OnBnClickedNoResponseAboutCommandExecution)
	ON_EN_CHANGE(IDC_EDIT_REPONSE_TIMEOUT, MySetModified)
	ON_BN_CLICKED(IDC_ACTIVATE_AFTER_ACTION, MySetModified)
	ON_MESSAGE(PSM_QUERYSIBLINGS, OnQuerySiblings)
END_MESSAGE_MAP()


// CMyResponseOptionsDlg message handlers

void CMyResponseOptionsDlg::OnBnClickedNoResponseAboutCommandExecution()
{
	int status = !m_buttonNoResponse.GetCheck();
	m_buttonOnError.EnableWindow(status);
	m_buttonOnSuccess.EnableWindow(status);
	SetModified();
}

void CMyResponseOptionsDlg::MySetModified(void)
{
	SetModified();
}

BOOL CMyResponseOptionsDlg::IsModified()
{
	if(m_rOptions.m_bResponseAboutCommandExecutionOnError == (m_buttonOnError.GetCheck()?true:false))
		if(m_rOptions.m_bResponseAboutCommandExecutionOnSuccess ==	(m_buttonOnSuccess.GetCheck()?true:false))
			if(m_rOptions.m_bNoResponsePlease == (m_buttonNoResponse.GetCheck()?true:false))
			{
				CString strResponseTimeout;
				m_editResponseTimeout.GetWindowText(strResponseTimeout);
				if(m_rOptions.m_nResponseTimeout == _ttoi((LPCTSTR)strResponseTimeout))
					if(m_rOptions.m_bActivateAfterAction == (m_buttonActivateAfterAction.GetCheck()?true:false))
						return FALSE;
			}

	return TRUE;
}
