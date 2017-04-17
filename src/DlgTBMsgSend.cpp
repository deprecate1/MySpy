// DlgTBMsgSend.cpp : implementation file
//

#include "stdafx.h"
#include "MySpy.h"
#include "DlgTBMsgSend.h"
#include ".\dlgtbmsgsend.h"
#include "WindowsMsgIds.h"

// CDlgTBMsgSend dialog

IMPLEMENT_DYNAMIC(CDlgTBMsgSend, CDialog)
CDlgTBMsgSend::CDlgTBMsgSend(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTBMsgSend::IDD, pParent)
{
}

CDlgTBMsgSend::~CDlgTBMsgSend()
{
}

void CDlgTBMsgSend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MSG, m_ctlMsgIdlList);
}


BEGIN_MESSAGE_MAP(CDlgTBMsgSend, CDialog)
END_MESSAGE_MAP()


// CDlgTBMsgSend message handlers

BOOL CDlgTBMsgSend::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadMsgIdList(m_ctlMsgIdlList);

	m_ctlMsgIdlList.AddString(_T("sfgsdfgdsg"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
