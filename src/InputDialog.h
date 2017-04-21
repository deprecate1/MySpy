#pragma once


// CInputDialog dialog

class CInputDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDialog)

public:
	CInputDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInputDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_INPUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strInput;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonInputOk();
	afx_msg void OnBnClickedButtonInputCancel();
};
