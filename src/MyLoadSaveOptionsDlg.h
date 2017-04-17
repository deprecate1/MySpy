#pragma once
#include "MyPropertyPage.h"
// CMyLoadSaveOptionsDlg dialog

class CMyLoadSaveOptionsDlg : public CMyPropertyPage
{
	DECLARE_DYNAMIC(CMyLoadSaveOptionsDlg)

public:
	CMyLoadSaveOptionsDlg();
	virtual ~CMyLoadSaveOptionsDlg();

// Dialog Data
	enum { IDD = IDD_LOAD_SAVE_PROPERTYPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
private:
	CButton m_buttonSaveSettingsOnExit;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void MySetModified();
	afx_msg void OnBnClickedLoadDefaults();
	//afx_msg LRESULT OnQuerySiblings(WPARAM wParam,LPARAM);

	void Update();
	void Store();
	BOOL IsModified(void);
	virtual BOOL OnInitDialog();
};
