#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSendMsgDlg dialog

class CSendMsgDlg : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CSendMsgDlg)

public:
	CSendMsgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSendMsgDlg();
// Overrides
//	HRESULT OnButtonOK(IHTMLElement *pElement);
//	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Dialog Data
	enum { IDD = IDD_SEND_MSG, IDH = IDR_HTML_SENDMSGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_DHTML_EVENT_MAP()
public:
	CComboBox m_ctlComboMsg;
	CComboBox m_ctlComboLParam;
	CComboBox m_ctlComboWParam;
	CSliderCtrl m_nSliderCtrl;
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnNMReleasedcaptureSliderTransparency(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnBnClickedCheckTransparent();
	CSpinButtonCtrl m_spinAutoRefresh;
};
