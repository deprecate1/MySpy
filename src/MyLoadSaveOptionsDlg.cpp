// MyLoadSaveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MySpy.h"
#include "MyLoadSaveOptionsDlg.h"
#include ".\myloadsaveoptionsdlg.h"


// CMyLoadSaveOptionsDlg dialog

IMPLEMENT_DYNAMIC(CMyLoadSaveOptionsDlg, CPropertyPage)
CMyLoadSaveOptionsDlg::CMyLoadSaveOptionsDlg()
	: CMyPropertyPage(CMyLoadSaveOptionsDlg::IDD)

{
}

CMyLoadSaveOptionsDlg::~CMyLoadSaveOptionsDlg()
{
}

void CMyLoadSaveOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SAVE_SETTINGS_ON_EXIT, m_buttonSaveSettingsOnExit);

}


BEGIN_MESSAGE_MAP(CMyLoadSaveOptionsDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_SAVE_SETTINGS_ON_EXIT, MySetModified)
	ON_BN_CLICKED(IDC_LOAD_DEFAULTS, OnBnClickedLoadDefaults)
	ON_MESSAGE(PSM_QUERYSIBLINGS, OnQuerySiblings)
END_MESSAGE_MAP()


// CMyLoadSaveOptionsDlg message handlers
void CMyLoadSaveOptionsDlg::OnBnClickedLoadDefaults()
{
	m_rOptions.LoadDefaults();
	QuerySiblings(PPM_UPDATE,NULL);
	if(QuerySiblings(PPM_IS_MODIFIED,NULL))
	{
		m_bModified = true;
		CPropertyPage::SetModified();
	}
}
void CMyLoadSaveOptionsDlg::MySetModified()
{
	SetModified();
}
void CMyLoadSaveOptionsDlg::Update()
{
	m_buttonSaveSettingsOnExit.SetCheck((BOOL)m_rOptions.m_bSaveSettingsOnExit);
}
void CMyLoadSaveOptionsDlg::Store()
{
	m_rOptions.m_bSaveSettingsOnExit = m_buttonSaveSettingsOnExit.GetCheck()?true:false;

}
BOOL CMyLoadSaveOptionsDlg::IsModified(void)
{
	if(m_rOptions.m_bSaveSettingsOnExit == (m_buttonSaveSettingsOnExit.GetCheck()?true:false))
		return FALSE;
	return TRUE;
}

BOOL CMyLoadSaveOptionsDlg::OnInitDialog()
{
	CMyPropertyPage::OnInitDialog();

	Update();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
