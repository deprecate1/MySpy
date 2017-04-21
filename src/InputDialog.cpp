// InputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MySpy.h"
#include "InputDialog.h"
#include "afxdialogex.h"


// CInputDialog dialog

IMPLEMENT_DYNAMIC(CInputDialog, CDialogEx)

CInputDialog::CInputDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputDialog::IDD, pParent)
	, m_strInput(_T(""))
{

}

CInputDialog::~CInputDialog()
{
}

void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
}


BEGIN_MESSAGE_MAP(CInputDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_OK, &CInputDialog::OnBnClickedButtonInputOk)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_CANCEL, &CInputDialog::OnBnClickedButtonInputCancel)
END_MESSAGE_MAP()


// CInputDialog message handlers


BOOL CInputDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CInputDialog::OnBnClickedButtonInputOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	OnOK();
}


void CInputDialog::OnBnClickedButtonInputCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
