#pragma once
#include "afxwin.h"
#include "resource.h"
#include "MyPropertyPage.h"
// CMyWinInfoOptionsDlg dialog

class CMyWinInfoOptionsDlg : public CMyPropertyPage
{
	DECLARE_DYNAMIC(CMyWinInfoOptionsDlg)

public:
	CMyWinInfoOptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyWinInfoOptionsDlg();

// Dialog Data
	enum { IDD = IDD_WINDOW_INFO_VIEW_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CListCtrl m_ctlOptionList;

	DECLARE_MESSAGE_MAP()
public:
	HWND GetOptionListCtrlHwnd(){return m_ctlOptionList.m_hWnd;}
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkWinInfoList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingWinInfoList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedWinInfoList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();

	void CloneWinInfoArray(CArray<CWinInfo*>& src,CArray<CWinInfo*>& dest);
private:
	void ChangeItems(int item1, int item2);
	CArray<CWinInfo*> m_aWinInfosClone;
public:
	void Update(void);
	void Store();
	BOOL IsModified(void);
	afx_msg void OnCbnSelchangeTreeOrInfoCombo();
	CComboBox m_comboWinInfoChoice;
};

