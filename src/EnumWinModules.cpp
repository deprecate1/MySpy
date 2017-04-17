// EnumWinModules.cpp: implementation of the CEnumWinModules class.
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

#include "stdafx.h"
#include "EnumWinModules.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEnumWinModules::CEnumWinModules() : m_nFilter(0)
{
}

CEnumWinModules::~CEnumWinModules()
{
    Clear();
}

void CEnumWinModules::Clear()
{
    for (int i=0;i<m_aWindows.GetSize();i++)
    {
        delete m_aWindows[i];
    }
    m_aWindows.RemoveAll();
}


// Function name    : EnumWindowsProc
// Description      : This function will enumerate all running windows and store the results in the
//                    class member variable m_aWindows.  The list will be filtered based on the params
//                    set by the Filter() function.
// Return type      : BOOL CALLBACK 
// Argument         : HWND hWnd
// Argument         : LPARAM lParam
//
// R E V I S I O N S:
// DATE       PROGRAMMER      CHANGES
//
BOOL CALLBACK CEnumWinModules::EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    CEnumWinModules *ew = (CEnumWinModules*)lParam;
    ASSERT(ew);

    if (!ew->Filter(hWnd))
    {
        FillUpWindowInfo(hWnd,ew);
    }

    return true; // continue enumeration (otherwise this would be false)
}


// Function name    : Filter
// Description      : tests whether or not we should filter this window
// Return type      : BOOL ; true on filter, false on not
// Argument         : HWND hWnd
//
// R E V I S I O N S:
// DATE       PROGRAMMER      CHANGES
//
BOOL CEnumWinModules::Filter(HWND hWnd)
{
    if (!m_nFilter) return false; // no reason to keep testing, they want all windows.

    // test visibility filters
    if (m_nFilter & FILTER_VISIBLEONLY)
    {
        // is this window invisible, if so filter it
        if (!IsWindowVisible(hWnd)) return true;
    }
    else if (m_nFilter & FILTER_NONVISIBLEONLY)
    {
        // is this window visible, if so filter it
        if (IsWindowVisible(hWnd)) return true;
    }

    // filter the parent/child windows
    if (m_nFilter & FILTER_PARENTONLY)
    {
        // is it a child? if yes, filter
        if (GetParent(hWnd)) return true;
    }
    else if (m_nFilter & FILTER_CHILDONLY)
    {
        // is it a parent? if yes, filter
        if (!GetParent(hWnd)) return true;
    }

    // filter apps by class name
    if (m_nFilter & FILTER_APPS)
    {
        CString temp;
        ::GetClassName(hWnd, temp.GetBuffer(_MAX_PATH), _MAX_PATH);
        temp.ReleaseBuffer();

        for (int i=0;i<m_aExclusions.GetSize();i++)
        {
            if (m_aExclusions.GetAt(i) == temp) return true;
        }
    }

    return false; // don't filter if we get to this point
}



// Function name    : CEnumWinModules::Process
// Description      : The main function, call this to enum all the windows and set the class data members.
// Return type      : int ; see .h for description
// Argument         : int nFilter
//
// R E V I S I O N S:
// DATE       PROGRAMMER      CHANGES
//
int CEnumWinModules::Process(int nFilter)
{
    // test filter for validity
    // NOTE: these can be changed to return 0 instead of assert in a dynamic program
    ASSERT(!((nFilter & FILTER_VISIBLEONLY) && (nFilter & FILTER_NONVISIBLEONLY)));
    ASSERT(!((nFilter & FILTER_PARENTONLY) && (nFilter & FILTER_CHILDONLY)));

    // set filter
    m_nFilter = nFilter;
   // m_strFilter = L"";

    // clear all
    Clear();
    
    // process windows
    //::EnumWindows(EnumWindowsProc, (LPARAM)this);

    FillUpWindowInfo(::GetDesktopWindow(),this);

    ::EnumChildWindows(::GetDesktopWindow(),EnumWindowsProc, (LPARAM)this);

    OSVERSIONINFO osver;

    // get version
    osver.dwOSVersionInfoSize = sizeof(osver);
    if (!GetVersionEx(&osver)) return 0; // failed to obtain version information

    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT) // windows NT
    {
        // explicitly load the PSAPI dll so we don't get problems running under win9x
        HINSTANCE hLib = LoadLibrary(_T("PSAPI.DLL"));
        if (!hLib) return 0; // could not load psapi.dll

        HINSTANCE hVdmLib = LoadLibrary(_T("VDMDBG.DLL")); // for shell windows and anything running under the VDM
        if (!hVdmLib)
        {
            // unload psapi
            FreeLibrary(hLib);
            return 0;
        }

        // function defs for PSAPI
        BOOL (WINAPI *lpfEnumProcesses)( DWORD *, DWORD cb, DWORD * );
        BOOL (WINAPI *lpfEnumProcessModules)( HANDLE, HMODULE *, DWORD, LPDWORD );
#ifdef UNICODE
        DWORD (WINAPI *lpfGetModuleFileNameEx)( HANDLE, HMODULE, LPWSTR, DWORD );
#else
        DWORD (WINAPI *lpfGetModuleFileNameEx)( HANDLE, HMODULE, LPTSTR, DWORD );
#endif
        // function defs for NTVDM
        INT (WINAPI *lpfVDMEnumTaskWOWEx)( DWORD, TASKENUMPROCEX  fp, LPARAM );

        // get procedure handles
        lpfEnumProcesses = (BOOL(WINAPI *)(DWORD *,DWORD,DWORD*)) GetProcAddress( hLib, "EnumProcesses" ) ;
        lpfEnumProcessModules = (BOOL(WINAPI *)(HANDLE, HMODULE *, DWORD, LPDWORD)) GetProcAddress( hLib, "EnumProcessModules" ) ;
#ifdef UNICODE      
        lpfGetModuleFileNameEx =(DWORD (WINAPI *)(HANDLE, HMODULE, LPWSTR, DWORD )) GetProcAddress( hLib, "GetModuleFileNameExW" ) ;
#else
        lpfGetModuleFileNameEx =(DWORD (WINAPI *)(HANDLE, HMODULE, LPTSTR, DWORD )) GetProcAddress( hLib, "GetModuleFileNameExA" ) ;
#endif
        lpfVDMEnumTaskWOWEx =(INT(WINAPI *)( DWORD, TASKENUMPROCEX, LPARAM))GetProcAddress( hVdmLib, "VDMEnumTaskWOWEx" );
        if( lpfEnumProcesses == NULL || lpfEnumProcessModules == NULL || lpfGetModuleFileNameEx == NULL || lpfVDMEnumTaskWOWEx == NULL)
        {
            // some of the functions did not load properly... return out
            FreeLibrary(hLib);
            FreeLibrary(hVdmLib);
            return 0;
        }

        // enumerate processes
        DWORD *pdwProcessIDs = new DWORD[MAX_PROCESS_NUMBER]; // should be a good number of processes.  Change if you are using on a server
                // that might be running more than 250 processes.
                // change ti below in the EnumProcesses line as well. :)
        ASSERT(pdwProcessIDs);
        DWORD dwSize;

        if (!lpfEnumProcesses(pdwProcessIDs, MAX_PROCESS_NUMBER*sizeof(DWORD), &dwSize))
        {
            delete [] pdwProcessIDs;
            FreeLibrary(hLib);
            FreeLibrary(hVdmLib);
            return 0;
        }

        // get the exe names
        HANDLE hProcess;
        HMODULE hModule;
        DWORD dwSize2;
        TCHAR szFilename[_MAX_PATH];
        int nIndex = 0;
        dwSize = dwSize / sizeof(DWORD);
        for (int i=0;i<(int)dwSize;i++)
        {
            nIndex = -1;
            for (int j=0;j<m_aWindows.GetSize();j++)  // try to find a match of PID from a hWnd and PID from EnumProcesses
            {
                if (m_aWindows[j]->dwPID == pdwProcessIDs[i])
                {
                    nIndex = j;
                    break;
                }
            }

            if (nIndex > -1) // did we find a match
            {
                // open the process so we can get a handle
                hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, pdwProcessIDs[i]);
                if (hProcess)
                {
                    if (lpfEnumProcessModules(hProcess, &hModule, sizeof(hModule), &dwSize2))
                    {
                        // get path name
                        DWORD dw = lpfGetModuleFileNameEx(hProcess, hModule, szFilename, sizeof(szFilename));
                        if (dw==NULL)
                        {
                            GetLastError();
                            szFilename[0] = 0; // no name, so null it out
                        }

                        // did we get an NTVDM?
                        CString strTempFilename = szFilename;
                        strTempFilename.MakeUpper();
                        if (strTempFilename.Find(_T("NTVDM.EXE")) > -1)
                        {
                            sEnumInfoStruct sInfo;

                            // we found a 16-bit app... get it's name
                            sInfo.dwPID = pdwProcessIDs[i];
//                          sInfo.lpProc = lpProc;
//                          sInfo.lParam = LPARAM;
                            sInfo.bEnd = FALSE;
                            // Enum the 16-bit stuff.
                            //lpfVDMEnumTaskWOWEx(pdwProcessIDs[i], (TASKENUMPROCEX)Enum16, (LPARAM)&sInfo);

                            // Did our main enum func say quit?
                            if(sInfo.bEnd)
                                break ;                         
                        }

                        // add it to the list
                        m_aWindows[nIndex]->strModuleName = szFilename;
                    }               
                    CloseHandle(hProcess); // be nice. :)
                }
            }
        }

        delete [] pdwProcessIDs;
        FreeLibrary(hLib);
        FreeLibrary(hVdmLib);
    }
    else if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) // windows 9x
    {
        // load the kernel32 lib (explicitly)
        HINSTANCE hLib = LoadLibrary(_T("Kernel32.DLL"));
        if (!hLib) return 0;

        // ToolHelp Function Pointers.
        HANDLE (WINAPI *lpfCreateToolhelp32Snapshot)(DWORD,DWORD) ;
        BOOL (WINAPI *lpfProcess32First)(HANDLE,LPPROCESSENTRY32) ;
        BOOL (WINAPI *lpfProcess32Next)(HANDLE,LPPROCESSENTRY32) ;

        // get procedure pointers
        lpfCreateToolhelp32Snapshot = (HANDLE(WINAPI *)(DWORD,DWORD)) GetProcAddress( hLib, "CreateToolhelp32Snapshot");
        lpfProcess32First = (BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))GetProcAddress( hLib, "Process32First");
        lpfProcess32Next = (BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))GetProcAddress( hLib, "Process32Next");
        if( lpfProcess32Next == NULL || lpfProcess32First == NULL || lpfCreateToolhelp32Snapshot == NULL)
        {
            FreeLibrary(hLib);
            return 0;
        }

        // Get a handle to a Toolhelp snapshot of the systems
        // processes.
        HANDLE hSnapShot = lpfCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if(hSnapShot == INVALID_HANDLE_VALUE)
        {
            FreeLibrary(hLib);
            return 0;
        }

        // get the first process entry
        PROCESSENTRY32 procentry;
        procentry.dwSize = sizeof(PROCESSENTRY32);
        BOOL bFlag = lpfProcess32First( hSnapShot, &procentry );

        while (bFlag)
        {
            // check filtering
            for (int i=0;i<m_aWindows.GetSize();i++)
            {
                if (m_aWindows[i]->dwPID == procentry.th32ProcessID)
                {
                    // add entry to list
                    m_aWindows[i]->strModuleName = procentry.szExeFile;
                    break;
                }
            }

            // get next process entry
            procentry.dwSize = sizeof(PROCESSENTRY32);
            bFlag = lpfProcess32Next( hSnapShot, &procentry );
        }
    }
    else return 0;

    return 1;
}

CString CEnumWinModules::GetClassName(int nIndex)
{
    // test bounds
    ASSERT(nIndex > -1);
    ASSERT(nIndex < m_aWindows.GetSize());

    return m_aWindows.GetAt(nIndex)->strClassName;
}

CString CEnumWinModules::GetClassName(HWND hWnd)
{
    for (int i=0;i<m_aWindows.GetSize();i++)
    {
        if (m_aWindows[i]->hWnd == hWnd)
        {
            return GetClassName(i);
        }
    }
    ASSERT(0); // this is bad, of course we could return an empty string.
    return CString();
}

CString CEnumWinModules::GetWindowTitle(int nIndex)
{
    ASSERT(nIndex > -1);
    ASSERT(nIndex < m_aWindows.GetSize());

    CString strTitle;
    GetWindowText(m_aWindows[nIndex]->hWnd, strTitle.GetBuffer(_MAX_PATH), _MAX_PATH);
    strTitle.ReleaseBuffer();
    return strTitle;
}

CString CEnumWinModules::GetWindowTitle(HWND hWnd)
{
    for (int i=0;i<m_aWindows.GetSize();i++)
    {
        if (m_aWindows[i]->hWnd == hWnd)
        {
            return GetWindowTitle(i);
        }
    }
    ASSERT(0); // this is bad, of course we could return an empty string.
    return CString();
}

CString CEnumWinModules::GetModuleName(int nIndex)
{
    ASSERT(nIndex > -1);
    ASSERT(nIndex < m_aWindows.GetSize());

    return m_aWindows[nIndex]->strModuleName;
}

CString CEnumWinModules::GetModuleName(HWND hWnd)
{
    for (int i=0;i<m_aWindows.GetSize();i++)
    {
        if (m_aWindows[i]->hWnd == hWnd)
        {
            return GetModuleName(i);
        }
    }
    ASSERT(0); // this is bad, of course we could return an empty string.
    return CString();
}

HWND CEnumWinModules::GetHwnd(int nIndex)
{
    ASSERT(nIndex > -1);
    ASSERT(nIndex < m_aWindows.GetSize());

    return m_aWindows.GetAt(nIndex)->hWnd;
}

sWindowInfo *CEnumWinModules::GetWindowInfo(int nIndex)
{
    ASSERT(nIndex > -1);
    ASSERT(nIndex < m_aWindows.GetSize());

    return m_aWindows.GetAt(nIndex);
}

sWindowInfo *CEnumWinModules::GetWindowInfo(HWND hWnd)
{
    if(!IsWindow(hWnd))
        return NULL;

    bool bFound = false;
  int i=0;
    for(i=0; i<m_aWindows.GetSize(); i++)
    {
        if(m_aWindows.GetAt(i)->hWnd == hWnd)
        {
            bFound = true;
            break;
        }
    }

    if(bFound)
        return m_aWindows.GetAt(i);
    else
        return NULL;
}


// Function name    : CEnumWinModules::AddExclusion
// Description      : Exclude a window from the list based on class name
// Return type      : void 
// Argument         : CString strExlude
//
// R E V I S I O N S:
// DATE       PROGRAMMER      CHANGES
//
void CEnumWinModules::AddExclusion(CString strExlude)
{
    m_aExclusions.Add(strExlude);
}

void CEnumWinModules::FillUpWindowInfo(HWND hWnd, CEnumWinModules* ew)
{
    sWindowInfo *pWindowInfo = new sWindowInfo;
    ASSERT(pWindowInfo);

    // get window class name
    CString strClass;
    ::GetClassName(hWnd, strClass.GetBuffer(_MAX_PATH), _MAX_PATH);
    strClass.ReleaseBuffer();
    pWindowInfo->strClassName = strClass;
    
    // get window title
    TCHAR pStrWindowText[_MAX_PATH]={0};
    ::GetWindowText(hWnd, pStrWindowText , _MAX_PATH-1);
    pWindowInfo->strWindowTitle = pStrWindowText;

    // get pid
    DWORD dwPID;
    GetWindowThreadProcessId(hWnd, &dwPID);
    pWindowInfo->dwPID = dwPID;

    // get hwnd
    pWindowInfo->hWnd = hWnd;

    // add it
    ew->AddWindow(pWindowInfo);
}