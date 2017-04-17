// EnumWinModules.h: interface for the CEnumWinModules class.
//
//////////////////////////////////////////////////////////////////////
// By Mike Ryan (mike@codexia.com)
// Copyright (c) 2000
// 4-30-2000
// Free usage granted in all applications including commercial.
// Do NOT distribute without permission from me.  I can be reached
// at mike@codexia.com, http://www.codexia.com
// Please feel free to email me about this class.
//
// Special thanks to Jeff Kay (jeff@codexia.com) for helping with the
// PSAPI functions.
//
// REVISIONS:
// 06.29.00: Added support for Windows9x and NTVDM 16-bit applications
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENUMWINMODULES_H__86C7CD44_E90B_4844_97DB_FE2043DC6CBF__INCLUDED_)
#define AFX_ENUMWINMODULES_H__86C7CD44_E90B_4844_97DB_FE2043DC6CBF__INCLUDED_

#include <afxtempl.h> // for carray
#include "psapi.h" // for the process handling, needs psapi.dll which is not distributed with windows.
					// note: psapi is a windows NT/2000 specific DLL (modified to work with win9x as well)
#include <tlhelp32.h> // for windows 98
#include <vdmdbg.h> // for ntvdm 16-bit


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_PROCESS_NUMBER 250	// should be a good number of processes.  Change if you are using on a server
								// that might be running more than 250 processes.

//// FILTERS ////				   // FOR ALL WINDOWS USE 0 (zero)
#define FILTER_VISIBLEONLY		1  // not compatible with NONVISIBLEONLY
#define FILTER_NONVISIBLEONLY	2  // not compatible with VISIBLEONLY
#define FILTER_PARENTONLY		4  // not compatible with CHILDONLY
#define FILTER_CHILDONLY		8  // not compatible with PARENTONLY
#define FILTER_APPS				16 // filter out programs by class name on the exclude list, use AddExclusion

typedef BOOL (CALLBACK *PROCENUMPROC)( DWORD, WORD, LPSTR, LPARAM);

typedef struct sWindowInfo
{
	CString strWindowTitle;
	CString strClassName;
	CString strModuleName;
	DWORD dwPID;
	HWND hWnd;
} sWindowInfo;

typedef struct sEnumInfoStruct
{
	DWORD dwPID;
	PROCENUMPROC lpProc;
	DWORD lParam;
	BOOL bEnd;
} sEnumInfoStruct;

class CEnumWinModules  
{
public:
	//// FUNCTIONS ////
	CEnumWinModules();
	virtual ~CEnumWinModules();
	void Clear(void);

	int Process(int nFilter); // main function, call this to enum all windows and set filtering info
	BOOL Filter(HWND hWnd); // for use by EnumWindowsProc
	void AddWindow(sWindowInfo *pWinInfo) { m_aWindows.Add(pWinInfo); } // add a sWindowInfo struct to m_aWindows
	void AddExclusion(CString strExclude);
	void ClearExclusions(void) { m_aExclusions.RemoveAll(); }

	// info retreval functions
	CString GetWindowTitle(int nIndex);
	CString GetWindowTitle(HWND hWnd);
	CString GetClassName(int nIndex);
	CString GetClassName(HWND hWnd);
	CString GetModuleName(int nIndex);
	CString GetModuleName(HWND hWnd);
	HWND GetHwnd(int nIndex);
	sWindowInfo *GetWindowInfo(int nIndex);
	sWindowInfo *GetWindowInfo(HWND hWnd);
	int GetWindowCount(void) { return (int)m_aWindows.GetSize(); }

protected:
	//// FUNCTIONS ////
	static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
	// following function used for NTVDM apps
	static BOOL WINAPI Enum16(DWORD dwThreadId, WORD hMod16, WORD hTask16, PSZ pszModName, PSZ pszFileName, LPARAM lpUserDefined);

	static void FillUpWindowInfo(HWND hWnd, CEnumWinModules* ew);

	//// VARIABLES ////
	CArray<sWindowInfo*, sWindowInfo*> m_aWindows;
	CArray<CString, CString> m_aExclusions;
	int m_nFilter;

public:
	CString	m_strFilter;
};

#endif // !defined(AFX_ENUMWINMODULES_H__86C7CD44_E90B_4844_97DB_FE2043DC6CBF__INCLUDED_)
