// SendMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MySpy.h"
#include "MySpyDoc.h"
#include "MainFrm.h"
#include "SendMsgDlg.h"
#include ".\sendmsgdlg.h"


// CSendMsgDlg dialog

IMPLEMENT_DYNCREATE(CSendMsgDlg, CDHtmlDialog)

CSendMsgDlg::CSendMsgDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CSendMsgDlg::IDD, CSendMsgDlg::IDH, pParent)
{
}

CSendMsgDlg::~CSendMsgDlg()
{
}

void CSendMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MSG, m_ctlComboMsg);
	DDX_Control(pDX, IDC_COMBO_LPARAM, m_ctlComboLParam);
	DDX_Control(pDX, IDC_COMBO_WPARAM, m_ctlComboWParam);
	DDX_Control(pDX, IDC_SLIDER_TRANSPARENCY, m_nSliderCtrl);
	DDX_Control(pDX, IDC_SPIN_AUTO_REFRESH, m_spinAutoRefresh);
}

BOOL CSendMsgDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	m_nSliderCtrl.SetRange(0,255);
	m_nSliderCtrl.SetPos(m_nSliderCtrl.GetRangeMax());
	m_spinAutoRefresh.SetRange(0, 99);
	m_spinAutoRefresh.SetBuddy((CWnd*)GetDlgItem(IDC_EDIT_AUTO_REFRESH));
	UpdateData();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_DHTML_EVENT_MAP(CSendMsgDlg)
//	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
//	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()
//
//
//
//// CSendMsgDlg message handlers
//
//HRESULT CSendMsgDlg::OnButtonOK(IHTMLElement* /*pElement*/)
//{
//	OnOK();
//	return S_OK;  // return TRUE  unless you set the focus to a control
//}
//
//HRESULT CSendMsgDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
//{
//	OnCancel();
//	return S_OK;  // return TRUE  unless you set the focus to a control
//}
//
BEGIN_MESSAGE_MAP(CSendMsgDlg, CDHtmlDialog)
//	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TRANSPARENCY, OnNMReleasedcaptureSliderTransparency)
//ON_BN_CLICKED(IDC_CHECK_TRANSPARENT, OnBnClickedCheckTransparent)
END_MESSAGE_MAP()
//
//
//void CSendMsgDlg::OnNMReleasedcaptureSliderTransparency(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	CMySpyDoc* pDoc = (CMySpyDoc*)((CMainFrame*)GetParentFrame())->GetActiveDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//
//	HWND hCurrWnd = pDoc->m_hCurrentlySelectedHwnd;
//	if (IsWindow(hCurrWnd))
//	{
//		::SetWindowLong(hCurrWnd, GWL_EXSTYLE, GetWindowLong(hCurrWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
//		::SetLayeredWindowAttributes(hCurrWnd, 0, (BYTE)m_nSliderCtrl.GetPos(), LWA_ALPHA);
//	}
//
//	*pResult = 0;
//}

//void CSendMsgDlg::OnBnClickedCheckTransparent()
//{
//	// TODO: Add your control notification handler code here
//}

