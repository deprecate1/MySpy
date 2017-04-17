#pragma once
#include "afxwin.h"
#include "MyPropertyPage.h"
// CMyResponseOptionsDlg dialog

class CMyResponseOptionsDlg : public CMyPropertyPage
{
	DECLARE_DYNAMIC(CMyResponseOptionsDlg)

public:
	CMyResponseOptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyResponseOptionsDlg();

// Dialog Data
	enum { IDD = IDD_COMMAND_OPTIONS_DLG };
	
	DECLARE_MESSAGE_MAP()
	
	afx_msg void OnBnClickedNoResponseAboutCommandExecution();
	afx_msg void MySetModified(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	BOOL IsModified();

	
private:
	CButton m_buttonActivateAfterAction;
	CButton m_buttonOnError;
	CButton m_buttonOnSuccess;
	CButton m_buttonNoResponse;
	CEdit m_editResponseTimeout;
	bool m_bApplied;
	void Store();
	void Update(void);
};
