// CMyFindDlg dialog
#include "stdafx.h"
#include "MySpy.h"

#include "MyFindDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CMyFindOptions::CMyFindOptions()
{
  	strToFind=NULL;
	hWndToFind=NULL;
	bMatchCase=FALSE;
	bDirectionUp=FALSE;
	bAlwaysFromBegin=FALSE;
	bResearch=FALSE;
	bFindByMouse=FALSE;
}

CMyFindOptions::~CMyFindOptions()
{
}

void CMyFindOptions::SetStrToFind(CString &s)
{
	 strToFind=(LPCTSTR)s;
	 hWndToFind=NULL;
}

void CMyFindOptions::SetHWndToFind(HWND hWnd)
{
	hWndToFind=hWnd;
	strToFind=NULL;
}

LPCTSTR CMyFindOptions::GetStrToFind()
{
	return strToFind;
}
HWND CMyFindOptions::GetHWndToFind()
{
	return hWndToFind;
}

static BOOL g_bClassRegistered = FALSE;

IMPLEMENT_DYNAMIC(CMyFindDlg, CDialog)
CMyFindDlg::CMyFindDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CMyFindDlg::IDD, pParent)
	, m_bHideMySpy(FALSE)
	, m_strToFind(_T(""))
{
	HINSTANCE hInst = AfxGetInstanceHandle();
	
	WNDCLASS wndcls;
	memset(&wndcls,0,sizeof(wndcls));
	
	::GetClassInfo(hInst,WC_DIALOG,&wndcls);

	//wndcls.style = CS_HREDRAW|CS_VREDRAW; // just the basics
	//wndcls.lpfnWndProc = ::DefWindowProc;
	//wndcls.hInstance = hInst;
	//wndcls.hIcon = ::LoadIcon(hInst,MAKEINTRESOURCE(IDR_MAINFRAME));
	//wndcls.hCursor = AfxGetApp()->LoadCursor(MAKEINTRESOURCE(IDC_ARROW));
	//wndcls.hbrBackground = ::CreateSolidBrush(RGB(255,255,0));  //bright yellow	bkgrnd
	wndcls.lpszClassName = g_pszFindDlgClassName;
	
	if(!AfxRegisterClass(&wndcls))
    {
		TRACE("Class Registration Failed\n");
		return;
    }

	g_bClassRegistered = TRUE;
	
    Create(IDD_FIND_DLG);

	m_bCapture=FALSE;
}

CMyFindDlg::~CMyFindDlg()
{
	if(g_bClassRegistered)
		::UnregisterClass(g_pszFindDlgClassName,AfxGetInstanceHandle());
}

void CMyFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FIND_DLG_EDIT_BOX, m_oComboBox);
	DDX_Check(pDX, IDC_FIND_RADIO_UP, m_FindOptions.bDirectionUp);
	DDX_Check(pDX, IDC_FIND_CHECK_MATCHCASE, m_FindOptions.bMatchCase);
	DDX_Control(pDX, IDC_TAB1, m_ctlFindMethod);
	DDX_Check(pDX, IDC_FINDBYMOUSE_HIDE_MYSPY, m_bHideMySpy);
}


BEGIN_MESSAGE_MAP(CMyFindDlg, CDialog)
    ON_CBN_EDITCHANGE(IDC_FIND_DLG_EDIT_BOX, OnCbnEditchangeFindDlgEditBox)
    ON_BN_CLICKED(IDC_FIND_FINDNEXT, OnBnClickedFindFindNext)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnTcnSelchangeTab1)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_FINDBYMOUSE_HIDE_MYSPY, OnBnClickedFindbymouseHideMyspy)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CMyFindDlg message handlers


void CMyFindDlg::OnCbnEditchangeFindDlgEditBox()
{
    CString s;
    m_oComboBox.GetWindowText(s);
    
    GetDlgItem(IDC_FIND_FINDNEXT)->EnableWindow((BOOL)!s.IsEmpty());
    
    m_FindOptions.bResearch = false;

}

BOOL CMyFindDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	TC_ITEM TabCtrlItem;
	TabCtrlItem.mask = TCIF_TEXT;
	TabCtrlItem.pszText = _T("By Text");
	m_ctlFindMethod.InsertItem( 0, &TabCtrlItem );
	TabCtrlItem.pszText = _T("By Mouse");
	m_ctlFindMethod.InsertItem( 1, &TabCtrlItem );

	ShowFindByMouse(SW_HIDE);
	ShowFindText(SW_SHOW);

    for(int i=0; i<m_aComboStringArray.GetSize(); i++)
        m_oComboBox.AddString(m_aComboStringArray.GetAt(i));
    
    m_FindOptions.bResearch = false;
    
    m_oComboBox.SetFocus();

    CheckRadioButton(IDC_RADIO_UP,IDC_RADIO_DOWN,IDC_RADIO_DOWN);

	m_hStatic=GetDlgItem(IDC_FINDBYMOUSE_CAPTURE)->m_hWnd;

	HINSTANCE hInst=AfxGetInstanceHandle();

	m_hBmpCross	= LoadBitmap (hInst, MAKEINTRESOURCE(IDB_CROSS));
	m_hBmpBlank	= LoadBitmap (hInst, MAKEINTRESOURCE(IDB_BLANK));
	m_hCurCross	= LoadCursor (hInst, MAKEINTRESOURCE(IDC_CROSS0));
	m_hCurHot   = LoadCursor (hInst, MAKEINTRESOURCE(IDC_CROSS1));
	m_hCurNormal= LoadCursor (NULL, IDC_ARROW);


    return FALSE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

CString CMyFindDlg::GetFindString()
{
    return m_strToFind;
}

void CMyFindDlg::AddToCombo(CString str)
{
    bool bFound=false;
    for(int i=0; i<m_aComboStringArray.GetSize(); i++)
        if(0==m_aComboStringArray.GetAt(i).Compare(str))
        {
            bFound=true;
            break;
        }

    if(!bFound)
    {
        m_aComboStringArray.InsertAt(0,str);
        m_oComboBox.AddString(str);
        UpdateData(FALSE);
    }
}

BOOL CMyFindDlg::IsResearch()
{
    return m_FindOptions.bResearch;
}

void CMyFindDlg::OnBnClickedFindFindNext()
{
    UpdateData();


    m_oComboBox.GetWindowText(m_strToFind); 
	
	m_FindOptions.SetStrToFind(m_strToFind);
	m_FindOptions.bAlwaysFromBegin=FALSE;
    
	::SendMessage(GetParentFrame()->GetActiveView()->m_hWnd,
        MYMSG_FINDNEXT_WAS_PRESSED,(WPARAM)0,(LPARAM)&m_FindOptions);
    
	m_FindOptions.bResearch=true;
    
	//ActivateTopParent();
}

void CMyFindDlg::OnOK()
{
    OnBnClickedFindFindNext();

    CDialog::OnOK();
}


void CMyFindDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_ctlFindMethod.GetCurSel();

	switch(nTab)
	{
	case 0: //Text Find

		ShowFindByMouse(SW_HIDE);
		ShowFindText(SW_SHOW);
		m_FindOptions.bFindByMouse=FALSE;


		break;
	case 1:
		ShowFindText(SW_HIDE);
		ShowFindByMouse(SW_SHOW);
		m_FindOptions.bFindByMouse=TRUE;

		break;
	}

	// TODO: Add your control notification handler code here
	*pResult = 0;
}

BOOL CMyFindDlg::ShowFindByMouse(int nCmdShow)
{
	GetDlgItem(IDC_FINDBYMOUSE_CAPTURE)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_FINDBYMOUSE_STATIC)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_FINDBYMOUSE_HIDE_MYSPY)->ShowWindow(nCmdShow);
	CWnd* pCWnd = GetDlgItem(IDC_FINDBYMOUSE_SELECTED_HWND);
	pCWnd->ShowWindow(nCmdShow);
	if(nCmdShow==SW_SHOW)
		pCWnd->SetWindowText(_T("HWND:N/A"));

	return 0;
}
BOOL CMyFindDlg::ShowFindText(int nCmdShow)
{
	GetDlgItem(IDC_FIND_STATIC_FINDWHAT)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_FIND_DLG_EDIT_BOX)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_FIND_CHECK_MATCHCASE)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_FIND_RADIO_DOWN)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_FIND_RADIO_UP)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_FIND_STATIC_DIRECTION)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_FIND_FINDNEXT)->EnableWindow(nCmdShow==SW_HIDE?FALSE:TRUE);

	return 0;
}

void CMyFindDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	/*if (bCapture) {
			pt.x = MAKEPOINTS(lParam).x;
			pt.y = MAKEPOINTS(lParam).y;			
			::ClientToScreen (hDlg, &pt);
			OnMouseMove (hDlg, pt);
		}*/
	if(m_bCapture)
	{
		::ClientToScreen (m_hWnd, &point);
		HWND hWnd = SmallestWindowFromPoint (point);

		DWORD PID, TID;
		TID = ::GetWindowThreadProcessId (hWnd, &PID);

		if (GetCurrentProcessId () == PID)
			return;	
		 
		if (m_hWndOld == hWnd) return;	// prevent flickering
		
		if(m_hWndOld)
			CMainFrame::HighlightWindow(m_hWndOld);
		//	HighlightWindow(hWndOld,FALSE); 2. parameter has no eff
		
		CMainFrame::HighlightWindow(hWnd);
		//HighlightWindow(hWnd,TRUE);
		
		CString strText;
		if(m_bDisplayInHex)
			strText.Format(_T("0x%X"),hWnd);
		else
			strText.Format(_T("%lu"),hWnd);

		GetDlgItem(IDC_FINDBYMOUSE_SELECTED_HWND)->SetWindowText(_T("HWND:")+strText);

		m_FindOptions.bDirectionUp = FALSE;
		m_FindOptions.bAlwaysFromBegin=TRUE;
		m_FindOptions.SetHWndToFind(hWnd);

		::SendMessage(GetParentFrame()->GetActiveView()->m_hWnd,
			MYMSG_FINDNEXT_WAS_PRESSED,(WPARAM)0,(LPARAM)&m_FindOptions);


		m_hWndOld = hWnd;
	}

	CDialog::OnMouseMove(nFlags, point);
}

//-----------------------------------------------
// SmallestWindowFromPoint
// Notice: from PasswordSpy by Brian Friesen
//
// Find the smallest window still containing the point
//
// WindowFromPoint returns the first window in the Z-order ->
// if the password control is sorounded by a Group Box or some other control,
// WindowFromPoint returns the handle to the sorounding control instead
// to the password control.
//
HWND CMyFindDlg::SmallestWindowFromPoint( const POINT point )
{	
	RECT rect, rcTemp;
	HWND hParent, hWnd, hTemp;

	hWnd = ::WindowFromPoint( point );
	if( hWnd != NULL )
	{
		::GetWindowRect( hWnd, &rect );
		hParent = ::GetParent( hWnd );

		// Has window a parent?
		if( hParent != NULL )
		{
			// Search down the Z-Order
			hTemp = hWnd;
			do{
				hTemp = ::GetWindow( hTemp, GW_HWNDNEXT );

				// Search window contains the point, hase the same parent, and is visible?
				::GetWindowRect( hTemp, &rcTemp );
				if(::PtInRect(&rcTemp, point) && ::GetParent(hTemp) == hParent && ::IsWindowVisible(hTemp))
				{
					// Is it smaller?
					if(((rcTemp.right - rcTemp.left) * (rcTemp.bottom - rcTemp.top)) < ((rect.right - rect.left) * (rect.bottom - rect.top)))
					{
						// Found new smaller window!
						hWnd = hTemp;
						::GetWindowRect(hWnd, &rect);
					}
				}
			}while( hTemp != NULL );
		}
	}

return hWnd;
}
void CMyFindDlg::OnLButtonDown(UINT nFlags, CPoint pt)
{
	RECT rc;

	::ClientToScreen (m_hWnd, &pt);
	
	::GetWindowRect(m_hStatic, &rc);

	if( ::PtInRect(&rc, pt) )
	{
		::SetCursor( m_hCurCross );
		::SendMessage (m_hStatic,(WPARAM)STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)m_hBmpBlank);
		::SetCapture( m_hWnd );
		m_bCapture = true;
	}

	CDialog::OnLButtonDown(nFlags, pt);
}


void CMyFindDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	if( m_bCapture )
	{
		if( m_hWndOld )
		{
			CMainFrame::HighlightWindow(m_hWndOld);
		}
		m_hWndOld = NULL;

		::SetCursor( m_hCurNormal );
		::SendMessage (m_hStatic,(WPARAM)STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)m_hBmpCross);
		::ReleaseCapture();
		if(m_bHideMySpy)
		{
			CheckDlgButton(IDC_FINDBYMOUSE_HIDE_MYSPY,MF_UNCHECKED);
			OnBnClickedFindbymouseHideMyspy();
		}
		m_bCapture = false;
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CMyFindDlg::OnKillFocus(CWnd* pNewWnd)
{   
	if( m_bCapture )
	{
		if( m_hWndOld )
			CMainFrame::HighlightWindow(m_hWndOld);
		m_hWndOld = NULL;

		::SetCursor( m_hCurNormal );
		::SendMessage (m_hStatic,(WPARAM)STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)m_hBmpCross);
		::ReleaseCapture();
		if(m_bHideMySpy)
		{
			CheckDlgButton(IDC_FINDBYMOUSE_HIDE_MYSPY,MF_UNCHECKED);
			OnBnClickedFindbymouseHideMyspy();
		}
		m_bCapture = false;
	}
	
	CDialog::OnKillFocus(pNewWnd);
}

void CMyFindDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	
	if(m_bCapture && (nState==WA_INACTIVE) && pWndOther!=(CWnd*)GetParentFrame())
	{
		if( m_hWndOld )
			CMainFrame::HighlightWindow(m_hWndOld);
		m_hWndOld = NULL;

		::SetCursor( m_hCurNormal );
		::SendMessage (m_hStatic,(WPARAM)STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)m_hBmpCross);
		::ReleaseCapture();
		if(m_bHideMySpy)
		{
			CheckDlgButton(IDC_FINDBYMOUSE_HIDE_MYSPY,MF_UNCHECKED);
			OnBnClickedFindbymouseHideMyspy();
		}
		m_bCapture = false;
	}
}

void CMyFindDlg::OnBnClickedFindbymouseHideMyspy()
{
	UpdateData();
	::ShowWindow(GetParentFrame()->m_hWnd,m_bHideMySpy?SW_HIDE:SW_SHOW);
}
