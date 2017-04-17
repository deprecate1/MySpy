#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
// CMyFindDlg dialog

class CMyFindOptions
{

public:
	CMyFindOptions();
	~CMyFindOptions();
	void SetStrToFind(CString &s);
	void SetHWndToFind(HWND hWnd);
	LPCTSTR GetStrToFind();
	HWND GetHWndToFind();

	BOOL bMatchCase;
	BOOL bDirectionUp;
	BOOL bAlwaysFromBegin;
	BOOL bResearch;

	BOOL bFindByMouse;

private:
	LPCTSTR strToFind;
	HWND hWndToFind;
};

const UINT MYMSG_FINDNEXT_WAS_PRESSED = RegisterWindowMessage(_T("MYMSG_FINDNEXT_WAS_PRESSED"));
const TCHAR g_pszFindDlgClassName[] = _T("MySpy_FindDialog");

class CMyFindDlg : public CDialog
{
    DECLARE_DYNAMIC(CMyFindDlg)

public:
    CMyFindDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CMyFindDlg();

// Dialog Data
    enum { IDD = IDD_FIND_DLG };

	CString GetFindString();
	HWND SmallestWindowFromPoint( const POINT point );
    BOOL IsResearch();
    void AddToCombo(CString str);
	void SetDisplayInHex(bool bSet){m_bDisplayInHex = bSet;};
	BOOL ShowFindByMouse(int nCmdShow);
	BOOL ShowFindText(int nCmdShow);

	DECLARE_MESSAGE_MAP()

    afx_msg void OnBnClickedOk();
    afx_msg void OnCbnEditchangeFindDlgEditBox();
    afx_msg void OnBnClickedFindFindNext();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedFindbymouseHideMyspy();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();    
private:
	CString m_strToFind;
	CComboBox m_oComboBox;
    CStringArray m_aComboStringArray;
	bool m_bDisplayInHex;
    bool m_bCapture;
	HWND m_hWndOld;
	HWND m_hStatic;
	HCURSOR 	m_hCurCross;
	HCURSOR 	m_hCurHot;
	HCURSOR 	m_hCurNormal;
	HBITMAP		m_hBmpCross;
	HBITMAP		m_hBmpBlank;
	BOOL m_bHideMySpy;
	CMyFindOptions m_FindOptions; 
	CTabCtrl m_ctlFindMethod;
};
