// MySpyDoc.h : interface of the CMySpyDoc class
//


#pragma once
#include "afxrich.h"
#include "EnumWinModules.hpp"
#include "WindowsMsgIds.h"
#include "MyOptions.h"

const UINT MYMSG_SELECTION_CHANGED = RegisterWindowMessage(_T("MYMSG_SELECTION_CHANGED"));


class CMySpyDoc : public CRichEditDoc
{
protected: // create from serialization only
	CMySpyDoc();
	DECLARE_DYNCREATE(CMySpyDoc)
// Attributes
public:
	void SetCurrentlySelectedHwnd(HWND hWnd);
	void GetFullWindowInfoString(CString& strText);
	void GetWindowInfoTitle(int i, CString& strText);
	void GetWindowInfoData(int i, CString& strText);
	static LPCTSTR GetNumberFormat();

	CEnumWinModules m_oEnumWins;
	static sWindowInfo*	m_pWinInfo;
	HWND	m_hCurrentlySelectedHwnd;

	static const LPCTSTR m_pstrHexString;
	static const LPCTSTR m_pstrDecString;

// Operations
	static void GetHWNDString(HWND hWnd, CString& strOutput);
	static void GetRECTString(HWND hWnd,CString& strOutput);
	static void GetPIDString(HWND hWnd, CString& strOutput);
	static void GetWindowIdentifierString(HWND hWnd, CString& strOutput);
	static void GetStylesString(HWND hWnd, CString& );
	static void GetExStylesString(HWND hWnd, CString& strOutput);
	static void GetThreadIdString(HWND hWnd, CString& strOutput);
	static void GetTitleString(HWND hWnd, CString& strOutput);
	static void GetModuleNameString(HWND hWnd, CString& strOutput);
	static void GetClassNameString(HWND hWnd, CString& strOutput);
	static void GetClassStyleString(HWND hWnd, CString& strOutput);


// Overrides
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
	virtual ~CMySpyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
// Generated message map functions
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVisibilityAll();
	afx_msg void OnVisibilityVisibleonly();
	afx_msg void OnVisibilityNonvisibleonly();
	afx_msg void OnParentAll();
	afx_msg void OnParentParentsonly();
	afx_msg void OnParentChildonly();
	void Refresh(bool bRefreshView=true);
	BOOL SaveModified(void);
private:
static	CMyOptions& m_rOptions;
};


