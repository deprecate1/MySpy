// MySpy.h : main header file for the MySpy application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

const TCHAR g_pszClassName[] = _T("MySpy_MainFrame");

// CMySpyApp:
// See MySpy.cpp for the implementation of this class
//

class CMySpyApp : public CWinApp
{
public:
	CMySpyApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

};

extern CMySpyApp theApp;