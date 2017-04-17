// MySpy.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MySpy.h"
#include "MainFrm.h"

#include "MySpyDoc.h"
#include "MyTreeView.h"
#include ".\myspy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMySpyApp

BEGIN_MESSAGE_MAP(CMySpyApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CMySpyApp construction

CMySpyApp::CMySpyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMySpyApp object

CMySpyApp theApp;
// Add a static BOOL that indicates whether the class was
// registered so that you can unregister it in ExitInstance
static BOOL bClassRegistered = FALSE;

// CMySpyApp initialization
int CMySpyApp::ExitInstance()
{
	if(bClassRegistered)
		::UnregisterClass(g_pszClassName,AfxGetInstanceHandle());
	return CWinApp::ExitInstance();
} 


BOOL CMySpyApp::InitInstance()
{
	
	// Register your unique class name that you wish to use
    WNDCLASS wndcls;

    memset(&wndcls, 0, sizeof(WNDCLASS));   // start with NULL
                                            // defaults

    wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wndcls.lpfnWndProc = ::DefWindowProc;
    wndcls.hInstance = AfxGetInstanceHandle();
    wndcls.hIcon = LoadIcon(IDR_MAINFRAME); // or load a different
                                            // icon
    wndcls.hCursor = LoadCursor( IDC_ARROW );
    wndcls.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wndcls.lpszMenuName = NULL;

    // Specify your own class name for using FindWindow later
    wndcls.lpszClassName = g_pszClassName;

    // Register the new class and exit if it fails
    if(!AfxRegisterClass(&wndcls))
    {
		TRACE("Class Registration Failed\n");
		return FALSE;
    }

    bClassRegistered = TRUE;

	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMySpyDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMyTreeView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// Parse command line for standard shell commands, DDE, file open

	CCommandLineInfo cmdInfo;

	ParseCommandLine(cmdInfo);
	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


	int nArgc = __argc;

	LPCTSTR *ppArgv = (LPCTSTR*) CommandLineToArgvW((TCHAR *)GetCommandLine(), &nArgc);

	CString strTmp; 

	switch (nArgc)
	{
	case 2:
		{
			strTmp=ppArgv[1];
			if(0==strTmp.CompareNoCase(_T("/top")))
			{
					CMainFrame* m = (CMainFrame*)m_pMainWnd;
					m->OnStayontop();
			}
		}
	}
 
	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

CAboutDlg* aboutDlg =NULL;

// App command to run the dialog
void CMySpyApp::OnAppAbout()
{
	
	
	//CAboutDlg aboutDlg;
	//aboutDlg.DoModal();
	
	//CString strTitle;
	//VERIFY(strTitle.LoadString(AFX_IDS_APP_TITLE));
	//ShellAbout(m_pMainWnd->GetSafeHwnd(), strTitle, _T(""), LoadIcon(IDR_MAINFRAME));
	if(!aboutDlg)
		aboutDlg = new CAboutDlg;
	aboutDlg->DoModal();
}


// CMySpyApp message handlers


void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	EndDialog(IDOK);
	//OnOK();
}

