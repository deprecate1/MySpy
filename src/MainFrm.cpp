// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MySpy.h"

#include "MainFrm.h"
#include ".\mainfrm.h"

#define MAINFRAME
#include "WindowsMsgIds.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

//HANDLE CMainFrame::m_hActionHandle=NULL;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_INFO_IN_STATUS_BAR, OnUpdateInfoInStatusBar)
	//toolbar update ui handlers
	ON_UPDATE_COMMAND_UI(IDB_SET_TOPMOST, OnUpdateSetTopMost)

	ON_UPDATE_COMMAND_UI(IDB_ACTION_SHOW, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_ACTION_HIDE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_ACTION_ENABLE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_ACTION_DISABLE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_ACTION_CLOSE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_ACTION_RESTORE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_ACTION_MINIMIZE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_ACTION_LBUTTONCLICK, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_ACTION_LBUTTON_DBLCLICK, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_ACTION_RBUTTONCLICK, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_ACTION_RBUTTON_DBLCLICK, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDB_POST_MESSAGE, OnUpdatePostMsgButton)
	ON_UPDATE_COMMAND_UI(IDB_SEND_MESSAGE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDC_STATIC_SETTEXT, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDC_EDIT_SETTEXT, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDC_CHECK_BROADCAST, OnUpdateToolBar)
	//	ON_UPDATE_COMMAND_UI(IDB_ACTION_HIGHLIGHT,					OnUpdateToolBar)

	ON_UPDATE_COMMAND_UI(IDC_CHECK_TRANSPARENT, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(IDC_SLIDER_TRANSPARENCY, OnUpdateSliderTransparency)
	ON_UPDATE_COMMAND_UI(IDC_STATIC_TRANSPARENCY, OnUpdateToolBar)

	//Menu update ui handlers
	ON_UPDATE_COMMAND_UI(ID_ACTION_SHOW, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_HIDE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_ENABLE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_DISABLE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_CLOSE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_RESTORE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_MINIMIZE, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_LBUTTONCLICK, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_LBUTTON_DBLCLICK, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_RBUTTONCLICK, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_RBUTTON_DBLCLICK, OnUpdateToolBar)

	ON_UPDATE_COMMAND_UI(ID_ACTION_SETINFOREGROUND, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SETNOTOPMOST, OnUpdateToolBar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SETTOPMOST, OnUpdateToolBar)

	ON_UPDATE_COMMAND_UI(IDB_VIEW_VISIBLE_ONLY, OnUpdateTBVisibleOnly)
	ON_UPDATE_COMMAND_UI(IDB_VIEW_ALL, OnUpdateTBViewAll)
	ON_UPDATE_COMMAND_UI(IDB_VIEW_NON_VISIBLE_ONLY, OnUpdateTBHiddenOnly)
	ON_UPDATE_COMMAND_UI(IDB_VIEW_PARENTS, OnUpdateTBParentsOnly)
	ON_UPDATE_COMMAND_UI(IDB_VIEW_CHILDREN_ONLY, OnUpdateTBChildrenOnly)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARS_MAINTOOLBAR, OnUpdateToolbarsMaintoolbar)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARS_POST_MSG_TB, OnUpdatePostMsgTb)
	ON_UPDATE_COMMAND_UI(ID_WINDOWINFOPANE_LISTVIEW, OnUpdateWindowinfopaneListview)
	ON_UPDATE_COMMAND_UI(ID_WINDOWINFOPANE_RICHEIDTVIEW, OnUpdateWindowinfopaneRicheidtview)
	ON_COMMAND(IDB_SET_TOPMOST, OnSetTopMost)
	ON_COMMAND(IDB_ACTION_HIGHLIGHT, OnHighlight)
	ON_COMMAND(IDM_STAYONTOP, OnStayontop)
	ON_COMMAND(IDB_POST_MESSAGE, OnPostMessage)
	ON_COMMAND(IDB_SEND_MESSAGE, OnSendMessage)
	ON_COMMAND(ID_TOOLBARS_MAINTOOLBAR, OnToolbarsMaintoolbar)
	ON_COMMAND(ID_TOOLBARS_POST_MSG_TB, OnPostMsgTb)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_EN_CHANGE(IDC_EDIT_SETTEXT, OnEnChangeEditSettext)
	ON_COMMAND(ID_WINDOWINFOPANE_LISTVIEW, OnWindowinfopaneListview)
	ON_COMMAND(ID_WINDOWINFOPANE_RICHEIDTVIEW, OnWindowinfopaneRicheidtview)

	ON_COMMAND_RANGE(ID_ACTION_END, ID_VIEW_END, OnViewCommand)
	ON_COMMAND_RANGE(ID_ACTION_SHOW, ID_ACTION_END, OnActionCommand)

	ON_COMMAND(ID_VIEW_DISPLAY_IN_HEX, OnDisplayInHex)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DISPLAY_IN_HEX, OnUpdateDisplayInHex)

	ON_COMMAND(IDB_VIEW_DISPLAY_IN_HEX, OnDisplayInHex)
	ON_UPDATE_COMMAND_UI(IDB_VIEW_DISPLAY_IN_HEX, OnUpdateDisplayInHex)

	ON_COMMAND(IDB_FIND, OnFind)
	ON_UPDATE_COMMAND_UI(IDB_FIND, OnUpdateFind)


	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)

	ON_WM_QUERYENDSESSION()
	ON_WM_ENDSESSION()
	//	ON_WM_MOUSEMOVE()
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_VIEW_AFTERACTIONACTIVATE, OnViewAfteractionactivate)
	ON_UPDATE_COMMAND_UI(ID_VIEW_AFTERACTIONACTIVATE, OnUpdateViewAfteractionactivate)
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TRANSPARENCY, OnNMReleasedcaptureSliderTransparency)
	ON_BN_CLICKED(IDC_CHECK_TRANSPARENT, OnBnClickedCheckTransparent)


	ON_EN_CHANGE(IDC_EDIT_AUTO_REFRESH, OnEnChangeEditAutoRefresh)
	ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INFO_IN_STATUS_BAR
};


// CMainFrame construction/destruction
void LoadMsgIdList(CComboBox *box)
{
	if (!box)
		return;

	for (int i = 0; i<(sizeof(MSGMAP) / sizeof(sNamesAndValues)); i++)
		box->SetItemData(box->AddString(MSGMAP[i].strName), MSGMAP[i].uValue);

	box->LimitText(256);
}

TCHAR strParam[20]; //to hold string parameter value (eg. WM_SETTINGCHANGE)

CMainFrame::CMainFrame()
	: m_bOnTop(FALSE)
	, m_bEnableAction(false)
	, m_pDoc(NULL)
	, m_rOptions(CMyOptions::GetMyOptions())
	, m_pOptionsDlg(NULL)
	, m_nTransparencyChecked(FALSE)
	, m_bTimerAutoRefreshStart(FALSE)
{

}


CMainFrame::~CMainFrame()
{
	if (m_pOptionsDlg)
		delete m_pOptionsDlg;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndActionBar.CreateEx(this, TBSTYLE_FLAT, TBSTYLE_AUTOSIZE | WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndActionBar.LoadToolBar(IDR_MYSPY_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndViewToolBar.CreateEx(this, TBSTYLE_FLAT, TBSTYLE_AUTOSIZE | WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndViewToolBar.LoadToolBar(IDR_MYSPY_VIEW_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	// modify the style to include adjustable
	m_wndViewToolBar.ModifyStyle(0, CCS_ADJUSTABLE);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


	if (!m_wndPostMsgDlgBar.Create(this, IDD_SEND_MSG,
		CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create DlgBar\n");
		return -1;      // fail to create
	}

	CComboBox* pCBoxMsg = (CComboBox*)m_wndPostMsgDlgBar.GetDlgItem(IDC_COMBO_MSG);
	CComboBox* pCBoxLprm = (CComboBox*)m_wndPostMsgDlgBar.GetDlgItem(IDC_COMBO_LPARAM);
	CComboBox* pCBoxWprm = (CComboBox*)m_wndPostMsgDlgBar.GetDlgItem(IDC_COMBO_WPARAM);

	LoadMsgIdList(pCBoxMsg);
	LoadMsgIdList(pCBoxLprm);
	LoadMsgIdList(pCBoxWprm);

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	/*m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/

	EnableDocking(CBRS_ALIGN_ANY);

	m_wndActionBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndActionBar.SetWindowText(_T("Action Toolbar"));

	m_wndViewToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndViewToolBar.SetWindowText(_T("View Toolbar"));

	//Delete 'All' button from the toolbar!
	m_wndViewToolBar.PostMessage(TB_DELETEBUTTON, (WPARAM)4, (LPARAM)0);
	m_wndViewToolBar.RedrawWindow();

	m_wndPostMsgDlgBar.EnableDocking(CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);
	m_wndPostMsgDlgBar.SetWindowText(_T("PostMessage Toolbar"));

	DockControlBar(&m_wndViewToolBar);//,AFX_IDW_DOCKBAR_LEFT);
	DockControlBar(&m_wndActionBar, AFX_IDW_DOCKBAR_LEFT);
	DockControlBar(&m_wndPostMsgDlgBar, AFX_IDW_DOCKBAR_RIGHT);

	m_wndSplitter.SetActivePane(0, 0);
	m_pTreeViewPane = (CMyTreeView*)GetActiveView();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~(FWS_ADDTOTITLE);

	cs.lpszClass = g_pszClassName;

	return CFrameWnd::PreCreateWindow(cs);
}

// CMainFrame diagnostics
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers
void CMainFrame::OnDisplayInHex()
{
	if (!m_pDoc)
		m_pDoc = (CMySpyDoc*)GetActiveDocument();
	ASSERT_VALID(m_pDoc);
	if (!m_pDoc)
		return;

	m_rOptions.m_bDisplayInHex = !m_rOptions.m_bDisplayInHex;
	m_pDoc->Refresh();
}

void CMainFrame::OnUpdateDisplayInHex(CCmdUI *pCmdUI)
{
	if (!m_pDoc)
		m_pDoc = (CMySpyDoc*)GetActiveDocument();
	ASSERT_VALID(m_pDoc);
	if (!m_pDoc)
		return;

	pCmdUI->SetCheck((int)m_rOptions.m_bDisplayInHex);
}
void CMainFrame::OnFind()
{
	ASSERT_VALID(m_pTreeViewPane);
	if (!m_pTreeViewPane)
		return;
	m_pTreeViewPane->OnMenuEditFind();
}

void CMainFrame::OnUpdateFind(CCmdUI *pCmdUI)
{
	ASSERT_VALID(m_pTreeViewPane);
	if (!m_pTreeViewPane)
		return;

	pCmdUI->SetCheck((int)m_pTreeViewPane->FindDlgVisible() ? 1 : 0);
}
void CMainFrame::OnUpdateInfoInStatusBar(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
	CString strInfo;
	strInfo = L"Made by Mata";

	pCmdUI->SetText(strInfo);
}

void CMainFrame::OnSetTopMost()
{
	m_bOnTop = !m_bOnTop;
	if (m_bOnTop)
	{
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		CheckMenuItem(GetMenu()->m_hMenu, IDM_STAYONTOP, MF_CHECKED | MF_BYCOMMAND);
		//SetOptionDWORD( T("Stayontop"), 1 );
	} else
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		CheckMenuItem(GetMenu()->m_hMenu, IDM_STAYONTOP, MF_UNCHECKED | MF_BYCOMMAND);
		//SetOptionDWORD( T("Stayontop"), 0 );
	}

}
void CMainFrame::OnUpdateSetTopMost(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bOnTop);
}
void CMainFrame::OnStayontop()
{
	OnSetTopMost();
}

void CMainFrame::EnableActionToolbar(BOOL bEnable)
{
	m_bEnableAction = bEnable;
}

void CMainFrame::OnUpdateToolBar(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bEnableAction);
}
void CMainFrame::OnUpdatePostMsgButton(CCmdUI *pCmdUI)
{
	BOOL b = m_bEnableAction;
	CButton* checkBroadcast = (CButton*)m_wndPostMsgDlgBar.GetDlgItem(IDC_CHECK_BROADCAST);
	if (checkBroadcast)
	{
		b = m_bEnableAction ?
			(checkBroadcast->GetCheck() ? FALSE : TRUE) :
			FALSE;
	}
	pCmdUI->Enable(b);
}
void CMainFrame::OnUpdateSliderTransparency(CCmdUI *pCmdUI)
{
	BOOL b = m_bEnableAction;
	CButton* check = (CButton*)m_wndPostMsgDlgBar.GetDlgItem(IDC_CHECK_TRANSPARENT);
	if (check)
	{
		b = m_bEnableAction ?
			(check->GetCheck() ? TRUE : FALSE) :
			FALSE;
	}
	pCmdUI->Enable(b);

}

void CMainFrame::OnUpdateViewToolBar(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
void CMainFrame::OnUpdateTBVisibleOnly(CCmdUI *pCmdUI)
{
	if (m_rOptions.m_eVisibility == VISIBILITY_VISIBLE_ONLY)
		pCmdUI->SetRadio();
	else
		pCmdUI->SetRadio(FALSE);
}
void CMainFrame::OnUpdateTBViewAll(CCmdUI *pCmdUI)
{
	if (m_rOptions.m_eVisibility != VISIBILITY_ALL || m_rOptions.m_eParent != PARENT_ALL)
		pCmdUI->SetRadio(FALSE);
	else
		pCmdUI->SetRadio();
}
void CMainFrame::OnUpdateTBHiddenOnly(CCmdUI *pCmdUI)
{
	if (m_rOptions.m_eVisibility == VISIBILITY_NON_VISIBLE_ONLY)
		pCmdUI->SetRadio();
	else
		pCmdUI->SetRadio(FALSE);
}
void CMainFrame::OnUpdateTBParentsOnly(CCmdUI *pCmdUI)
{
	if (m_rOptions.m_eParent == PARENT_PARENTS_ONLY)
		pCmdUI->SetRadio();
	else
		pCmdUI->SetRadio(FALSE);
}
void CMainFrame::OnUpdateTBChildrenOnly(CCmdUI *pCmdUI)
{
	if (m_rOptions.m_eParent == PARENT_CHILDREN_ONLY)
		pCmdUI->SetRadio();
	else
		pCmdUI->SetRadio(FALSE);
}
void CMainFrame::OnSendMessage()
{
	SendOrPostMessage(TRUE);
}
void CMainFrame::OnPostMessage()
{
	SendOrPostMessage(FALSE);
}
void CMainFrame::SendOrPostMessage(BOOL bSend)
{

	CEditableComboBox* pCBoxMsg = (CEditableComboBox*)m_wndPostMsgDlgBar.GetDlgItem(IDC_COMBO_MSG);
	CEditableComboBox* pCBoxLParam = (CEditableComboBox*)m_wndPostMsgDlgBar.GetDlgItem(IDC_COMBO_LPARAM);
	CEditableComboBox* pCBoxWParam = (CEditableComboBox*)m_wndPostMsgDlgBar.GetDlgItem(IDC_COMBO_WPARAM);

	CTreeCtrl& tc = m_pTreeViewPane->GetTreeCtrl();

	HTREEITEM item = tc.GetSelectedItem();
	if (!item)
		return;

	int msg;
	WPARAM wParam;
	LPARAM lParam;
	try
	{
		msg = pCBoxMsg->GetBoxData();
		wParam = pCBoxWParam->GetBoxData();
		lParam = pCBoxLParam->GetBoxData();
	} catch (CEditableComboBox* ex)
	{
		MessageBox(_T("Wrong message id or number format!"), 0, MB_OK | MB_ICONERROR);
		::SetActiveWindow(ex->m_hWnd);
		ex->SetEditSel(0, -1);
		return;
	}

	CButton* pButton = (CButton*)m_wndPostMsgDlgBar.GetDlgItem(IDC_CHECK_BROADCAST);
	HWND hwnd;
	pButton->GetCheck() ? hwnd = HWND_BROADCAST : hwnd = (HWND)tc.GetItemData(item);

	if (bSend)
	{
		DWORD dwReturnValue;
		::SendMessageTimeout(hwnd, msg, wParam, lParam,
			SMTO_NOTIMEOUTIFNOTHUNG,
			5000, &dwReturnValue);
		if (0 == dwReturnValue)
		{
			DWORD dw = GetLastError();
			if (0 == dw)
				MessageBox(_T("The function timed out!"), 0, MB_OK | MB_ICONERROR);
			else
				ErrorMsgBox(dw);
		}
	} else
	{
		::PostMessage(hwnd, msg, wParam, lParam);
	}

	m_pTreeViewPane->SelectItem((HWND)tc.GetItemData(item));

}
int CEditableComboBox::FindInComboList(CString& str)
{
	str.Trim();
	for (int i = 0; i<GetCount(); i++)
	{
		CString strComboTxt;
		GetLBText(i, strComboTxt);
		if (0 == strComboTxt.Compare(str))
			return i;
	}
	return -1;
}

LONG CEditableComboBox::GetBoxData() //throw(CEditableComboBox*)
{
	CString str;
	GetWindowText(str);
	str.Trim();
	bool bIsStringParam = false;

	if (0 == str.Find(_T("\"")) && (str.GetLength() - 1 == str.ReverseFind(str.GetAt(0))))
	{
		str.Trim(_T("\""));
		bIsStringParam = true;
	} else
		str = str.MakeUpper();

	if (str.IsEmpty())
	{
		SetWindowText(_T("NULL"));
		return 0;
	} else if (0 == str.Compare(_T("NULL")))
	{
		SetWindowText(str);
		return 0;
	} else if (0 == str.Compare(_T("FALSE")))
	{
		SetWindowText(str);
		return 0;
	} else if (0 == str.Compare(_T("TRUE")))
	{
		SetWindowText(str);
		return 1;
	}

	LONGLONG value;

	int index = FindInComboList(str);

	if (-1 == index)
	{
		if (bIsStringParam)
		{
			_tcscpy(strParam, (LPCTSTR)str);
			value = /*reinterpret_cast<LONG>*/(LONG)(strParam);
		} else if (!StrToInt64Ex((LPCTSTR)str, STIF_SUPPORT_HEX, &value))
		{
			throw(this);
		}
	} else
	{
		value = GetItemData(index);
	}

	return (LONG)value;
}

void CMainFrame::OnToolbarsMaintoolbar()
{
	BOOL bVisible = ((m_wndViewToolBar.IsWindowVisible()) != 0);

	ShowControlBar(&m_wndViewToolBar, !bVisible, FALSE);
	RecalcLayout();
	// TODO: Add your command handler code here
}

void CMainFrame::OnUpdateToolbarsMaintoolbar(CCmdUI *pCmdUI)
{
	BOOL bVisible = ((m_wndViewToolBar.IsWindowVisible()) != 0);
	pCmdUI->SetCheck(bVisible);
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnPostMsgTb()
{
	BOOL bVisible = ((m_wndPostMsgDlgBar.IsWindowVisible()) != 0);

	ShowControlBar(&m_wndPostMsgDlgBar, !bVisible, FALSE);
	RecalcLayout();
	// TODO: Add your command handler code here
}

void CMainFrame::OnUpdatePostMsgTb(CCmdUI *pCmdUI)
{
	BOOL bVisible = ((m_wndPostMsgDlgBar.IsWindowVisible()) != 0);
	pCmdUI->SetCheck(bVisible);
	// TODO: Add your command update UI handler code here
}


void CMainFrame::OnEditCopy()
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnEnChangeEditSettext()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFrameWnd::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	//CMyTreeView* pView = (CMyTreeView*)GetActiveView();
	CTreeCtrl& tc = m_pTreeViewPane->GetTreeCtrl();

	HTREEITEM item = tc.GetSelectedItem();
	if (!item)
		return;

	HWND hWnd = (HWND)tc.GetItemData(item);

	if (!IsWindow(hWnd))
		return;

	CString title;
	m_wndPostMsgDlgBar.GetDlgItem(IDC_EDIT_SETTEXT)->GetWindowText(title);

	TRACE(_T("SetWindowText: %s \n"), title);

	//Set text on the selected window
	::SetWindowText(hWnd, title);
	::RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	//update informations on tree and on info pane
	m_pTreeViewPane->UpdateItem(item);
	RefreshWinInfoPane();
}

UINT CMainFrame::MultipleHighLight(LPVOID pParam)
{
#define MULTIPLE            10
#define TIME                200

	HWND hWnd = (HWND)pParam;

	if (hWnd == NULL || !IsWindow(hWnd))
		return 0;

	for (int i = 0; i<MULTIPLE; i++)
	{
		HighlightWindow(hWnd);
		Sleep(TIME);
	}
	return 0;
}

void CMainFrame::OnHighlight()
{
	ASSERT(m_pTreeViewPane);

	CTreeCtrl& tc = m_pTreeViewPane->GetTreeCtrl();

	HTREEITEM item = tc.GetSelectedItem();
	if (!item)
		return;

	HWND hWnd = (HWND)tc.GetItemData(item);

	AfxBeginThread((AFX_THREADPROC)CMainFrame::MultipleHighLight, (LPVOID)hWnd);
}
//-----------------------------------------------
// HighlightWindow
// Notice: from MSDN Spy Sample
//
void CMainFrame::HighlightWindow(HWND hWnd)
{

#define DINV                3
	HDC hdc;
	RECT rc;

	hdc = ::GetWindowDC(hWnd);
	::GetWindowRect(hWnd, &rc);

	int l = 0, t = 0;

	if (rc.left < 0) l = -rc.left;
	if (rc.top  < 0) t = -rc.top;

	::OffsetRect(&rc, -rc.left + l, -rc.top + t);


	int nWidthOftheScreen = GetSystemMetrics(SM_CXSCREEN);
	int nHeightOftheScreen = GetSystemMetrics(SM_CYSCREEN);

	if (rc.right > nWidthOftheScreen)rc.right = nWidthOftheScreen + DINV;
	if (rc.bottom>nHeightOftheScreen)rc.bottom = nHeightOftheScreen + DINV;

	if (!IsRectEmpty(&rc))
	{
		PatBlt(hdc, rc.left, rc.top, rc.right - rc.left,
			DINV, DSTINVERT);
		PatBlt(hdc, rc.left, rc.bottom - DINV, DINV,
			-(rc.bottom - rc.top - 2 * DINV), DSTINVERT);
		PatBlt(hdc, rc.right - DINV, rc.top + DINV, DINV,
			rc.bottom - rc.top - 2 * DINV, DSTINVERT);
		PatBlt(hdc, rc.right, rc.bottom - DINV, -(rc.right - rc.left),
			DINV, DSTINVERT);
	}
	::ReleaseDC(hWnd, hdc);
}


void CMainFrame::OnEndSession(BOOL bEnding)
{
	CFrameWnd::OnEndSession(bEnding);
}

BOOL CMainFrame::OnQueryEndSession()
{
	if (!CFrameWnd::OnQueryEndSession())
		return FALSE;

	CString strTitle;
	strTitle.LoadString(AFX_IDS_APP_TITLE);

	BOOL bRet = FALSE;
	if (IDYES == MessageBox(_T("Would you close ") + strTitle + _T("?"), strTitle, MB_YESNO | MB_ICONEXCLAMATION))
		bRet = TRUE;

	return bRet;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	BOOL bRetVal = m_wndSplitter.CreateStatic(this, 2, 1);

	CRect clientRect;
	GetClientRect(&clientRect);

	int nClientHeight = clientRect.Height();

	//TreeView
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMyTreeView), CSize(0, nClientHeight * 70 / 100 - 20), pContext);

	//WindowInfo Pane
	m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CMyEditView), CSize(0, 0), pContext);
	m_pWindowInfoPane = (CMyEditView*)m_wndSplitter.GetPane(1, 0);

	//m_wndSplitter.ReplaceView(1,0,RUNTIME_CLASS(CMyListView),CSize(0,0));

	return bRetVal;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnWindowinfopaneListview()
{

	if ((m_wndSplitter.GetPane(1, 0)->IsKindOf(RUNTIME_CLASS(CMyListView))) == TRUE)
		return;
	else
	{
		CRect rect;
		((CView *)m_wndSplitter.GetPane(1, 0))->GetWindowRect(&rect);

		m_wndSplitter.ReplaceView(1, 0, RUNTIME_CLASS(CMyListView), CSize(rect.Width(), rect.Height()));

		m_pWindowInfoPane2 = (CMyListView*)m_wndSplitter.GetPane(1, 0);
		m_pWindowInfoPane2->OnInitialUpdate();

		CMySpyDoc* pDoc = (CMySpyDoc*)GetActiveDocument();
		//ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		pDoc->UpdateAllViews(NULL, (LPARAM)pDoc->m_hCurrentlySelectedHwnd, (CObject*)pDoc->GetNumberFormat());

	}
}

void CMainFrame::OnUpdateWindowinfopaneListview(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio((m_wndSplitter.GetPane(1, 0)->IsKindOf(RUNTIME_CLASS(CMyListView))));
}

void CMainFrame::OnWindowinfopaneRicheidtview()
{
	if ((m_wndSplitter.GetPane(1, 0)->IsKindOf(RUNTIME_CLASS(CMyEditView))) == TRUE)
		return;
	else
	{
		CRect rect;
		((CView *)m_wndSplitter.GetPane(1, 0))->GetWindowRect(&rect);

		m_wndSplitter.ReplaceView(1, 0, RUNTIME_CLASS(CMyEditView), CSize(rect.Width(), rect.Height()));

		m_pWindowInfoPane = (CMyEditView*)m_wndSplitter.GetPane(1, 0);
		m_pWindowInfoPane->OnInitialUpdate();

		CMySpyDoc* pDoc = (CMySpyDoc*)GetActiveDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		pDoc->UpdateAllViews(NULL, (LPARAM)pDoc->m_hCurrentlySelectedHwnd, (CObject*)pDoc->GetNumberFormat());

	}
}

void CMainFrame::OnUpdateWindowinfopaneRicheidtview(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio((m_wndSplitter.GetPane(1, 0)->IsKindOf(RUNTIME_CLASS(CMyEditView))));
}

void CMainFrame::OnClose()
{
	//It must be replaced, so will RichEditDoc correctly destroyed
	//m_wndSplitter.ReplaceView(1,0,RUNTIME_CLASS(CMyEditView),CSize(/*rect.Width(),rect.Height()*/0,0));

	CFrameWnd::OnClose();
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
}

void CMainFrame::OnViewCommand(UINT nActionID)
{

	CMySpyDoc* pDoc = (CMySpyDoc*)GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CWaitCursor w;
	switch (nActionID)
	{
	case IDB_REFRESH:
		pDoc->Refresh();
		break;
	case IDB_VIEW_ALL:
		pDoc->OnVisibilityAll();
		pDoc->OnParentAll();
		break;
	case IDB_VIEW_VISIBLE_ONLY:
		if (m_rOptions.m_eVisibility == VISIBILITY_VISIBLE_ONLY)
			pDoc->OnVisibilityAll();
		else
			pDoc->OnVisibilityVisibleonly();
		break;
	case IDB_VIEW_NON_VISIBLE_ONLY:
		if (m_rOptions.m_eVisibility == VISIBILITY_NON_VISIBLE_ONLY)
			pDoc->OnVisibilityAll();
		else
			pDoc->OnVisibilityNonvisibleonly();
		break;
	case IDB_VIEW_PARENTS:
		if (m_rOptions.m_eParent == PARENT_PARENTS_ONLY)
			pDoc->OnParentAll();
		else
			pDoc->OnParentParentsonly();
		break;
	case IDB_VIEW_CHILDREN_ONLY:
		if (m_rOptions.m_eParent == PARENT_CHILDREN_ONLY)
			pDoc->OnParentAll();
		else
			pDoc->OnParentChildonly();
		break;
	}
}

void CMainFrame::OnActionCommand(UINT nActionID)
{
	CWaitCursor w;


	CTreeCtrl& tc = m_pTreeViewPane->GetTreeCtrl();

	HTREEITEM item = tc.GetSelectedItem();
	if (!item)
		return;

	m_sActionParam.hWnd = (HWND)tc.GetItemData(item);
	m_sActionParam.nActionID = nActionID;
	m_sActionParam.uRet = NOT_SET;

	if (0 == m_sActionParam.hActionReady)
	{
		m_sActionParam.hActionReady = CreateEvent(
			NULL,         // no security attributes
			TRUE,         // manual-reset event
			FALSE,        // initial state is signaled
			_T("MyActionEvent")  // object name
			);

		if (m_sActionParam.hActionReady == 0)
		{
			TRACE(_T("Action handle not created!"));
		}
	}

	switch (nActionID)
	{
	case ID_ACTION_HIGHLIGHT:
		OnHighlight();
		break;
	default:
		::AfxBeginThread(ThreadForActionOnSelectedWindow, &m_sActionParam);
	}

	if (m_sActionParam.hActionReady)
	{
		DWORD dwTimeout = 0;

		if (false == m_rOptions.m_bNoResponsePlease)
			dwTimeout = m_rOptions.m_nResponseTimeout;

		if (0 == dwTimeout){
			SetEvent(m_sActionParam.hActionReady);
			dwTimeout = INFINITE;
		} else
			ResetEvent(m_sActionParam.hActionReady);

		DWORD dwWaitResult = WaitForSingleObject(m_sActionParam.hActionReady, dwTimeout);

		switch (m_sActionParam.uRet)
		{
		case REFRESH_DOC:
			OnViewRefresh();
			break;
		case UPDATE_ITEM:
			m_pTreeViewPane->UpdateItem(item);
			break;
		case NOT_SET:
			TRACE(_T("m_sActionParam.uRet NOT_SET!\n"));
			break;
		}

		if (0 == m_rOptions.m_bNoResponsePlease)
		{
			CString strTitle;
			strTitle.LoadString(AFX_IDS_APP_TITLE);
			switch (dwWaitResult)
			{
			case WAIT_OBJECT_0:
				if (m_rOptions.m_bResponseAboutCommandExecutionOnSuccess)
					MessageBox(_T("Command executed on selected window successfully!"), strTitle, MB_OK | MB_ICONINFORMATION);
				break;
				// time-out occured
			default:
				if (m_rOptions.m_bResponseAboutCommandExecutionOnError)
					MessageBox(_T("Selected window not responding!"), strTitle, MB_OK | MB_ICONEXCLAMATION);
			}
		}
	}

	if (m_rOptions.m_bActivateAfterAction)
		SetFocus();
}

void CMainFrame::OnViewAfteractionactivate()
{
	m_rOptions.m_bActivateAfterAction = !m_rOptions.m_bActivateAfterAction;
}

void CMainFrame::OnUpdateViewAfteractionactivate(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_rOptions.m_bActivateAfterAction);
}

UINT CMainFrame::ThreadForActionOnSelectedWindow(LPVOID pParam)
{
	struct ActionParam* pActionParam = static_cast<struct ActionParam*>(pParam);

	ThreadReturnValues uRet = NOT_SET;

	switch (pActionParam->nActionID)
	{
	case ID_ACTION_SHOW: case IDB_ACTION_SHOW:
		::ShowWindow(pActionParam->hWnd, SW_SHOW);
		uRet = UPDATE_ITEM;
		break;
	case ID_ACTION_HIDE: case IDB_ACTION_HIDE:
		::ShowWindow(pActionParam->hWnd, SW_HIDE);
		uRet = UPDATE_ITEM;
		break;
	case ID_ACTION_DISABLE:	case IDB_ACTION_DISABLE:
		::EnableWindow(pActionParam->hWnd, FALSE);
		uRet = UPDATE_ITEM;
		break;
	case ID_ACTION_ENABLE: case IDB_ACTION_ENABLE:
		::EnableWindow(pActionParam->hWnd, TRUE);
		uRet = UPDATE_ITEM;
		break;
	case ID_ACTION_CLOSE: case IDB_ACTION_CLOSE:
		::PostMessage(pActionParam->hWnd, WM_CLOSE, 0, 0);
		uRet = REFRESH_DOC;
		break;
	case ID_ACTION_SETINFOREGROUND:	case IDB_ACTION_SETINFOREGROUND:
		::SetForegroundWindow(pActionParam->hWnd);
		uRet = UPDATE_ITEM;
		break;
	case ID_ACTION_SETTOPMOST:	//case IDB_ACTION_SETTOPMOST:
		::SetWindowPos(pActionParam->hWnd,
			HWND_TOPMOST, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE);
		uRet = UPDATE_ITEM;
		break;
	case ID_ACTION_SETNOTOPMOST: //case IDB_ACTION_SETNOTOPMOST:
		::SetWindowPos(pActionParam->hWnd,
			HWND_NOTOPMOST, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE);
		uRet = UPDATE_ITEM;
		break;
	case ID_ACTION_LBUTTONCLICK: case IDB_ACTION_LBUTTONCLICK:
		::PostMessage(pActionParam->hWnd, WM_LBUTTONDOWN, 0, 0);
		Sleep(100);
		::PostMessage(pActionParam->hWnd, WM_LBUTTONUP, 0, 0);
		uRet = REFRESH_DOC;
		break;
	case ID_ACTION_RBUTTONCLICK: case IDB_ACTION_RBUTTONCLICK:
		::PostMessage(pActionParam->hWnd, WM_RBUTTONDOWN, 0, 0);
		Sleep(100);
		::PostMessage(pActionParam->hWnd, WM_RBUTTONUP, 0, 0);
		uRet = REFRESH_DOC;
		break;
	case ID_ACTION_LBUTTON_DBLCLICK: case IDB_ACTION_LBUTTON_DBLCLICK:
		::PostMessage(pActionParam->hWnd, WM_LBUTTONDBLCLK, 0, 0);
		uRet = REFRESH_DOC;
		break;
	case ID_ACTION_RBUTTON_DBLCLICK: case IDB_ACTION_RBUTTON_DBLCLICK:
		::PostMessage(pActionParam->hWnd, WM_RBUTTONDBLCLK, 0, 0);
		uRet = REFRESH_DOC;
		break;
	case IDB_ACTION_RESTORE: case ID_ACTION_RESTORE:
		::ShowWindow(pActionParam->hWnd, SW_RESTORE);
		break;
	case IDB_ACTION_MINIMIZE: case ID_ACTION_MINIMIZE:
		::ShowWindow(pActionParam->hWnd, SW_SHOWMINIMIZED);
		break;
	}

	pActionParam->uRet = uRet;

	SetEvent(pActionParam->hActionReady);

	return uRet;
}

void CMainFrame::OnViewRefresh()
{
	CMySpyDoc* pDoc = (CMySpyDoc*)GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->Refresh();
}

CString CMainFrame::GetFilterString()
{
	CMySpyDoc* pDoc = (CMySpyDoc*)GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return L"";

	return pDoc->GetFilterString();
}

void CMainFrame::SetFilterString(CString filter)
{
	CMySpyDoc* pDoc = (CMySpyDoc*)GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetFilterString(filter);
}

void CMainFrame::RefreshTreePane()
{
	m_pTreeViewPane->UpdateWindow();
}
void CMainFrame::RefreshWinInfoPane()
{
	((CMyEditView*)m_wndSplitter.GetPane(1, 0))->UpdateWindowInfoView();
	//if(m_wndSplitter.GetPane(1,0)->IsKindOf(RUNTIME_CLASS(CMyEditView)))
	//	m_pWindowInfoPane->UpdateWindowInfoView();
	//else if (m_wndSplitter.GetPane(1,0)->IsKindOf(RUNTIME_CLASS(CMyListView)))
	//	m_pWindowInfoPane2->UpdateWindowInfoView();
}

int CMainFrame::ShowWinInfoOpDlg(CWnd* pParent)
{
	if (!m_pOptionsDlg)
	{
		m_pOptionsDlg = new CMyOptionsPropertySheet(_T("Options"), pParent);
	}

	if (m_pOptionsDlg)
		return (int)m_pOptionsDlg->DoModal();
	else
		return FALSE;
}
void CMainFrame::OnViewOptions()
{
	if (IDOK == ShowWinInfoOpDlg(this))
	{
		//UpdateWindowInfoView();
	}
}
void CMainFrame::ErrorMsgBox(DWORD dw)
{
	TCHAR szBuf[80];
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	wsprintf(szBuf,
		_T("Function failed with error %d:\r\n %s"),
		dw, lpMsgBuf);

	MessageBox(szBuf, 0, MB_OK | MB_ICONERROR);

	LocalFree(lpMsgBuf);

}
void CMainFrame::OnNMReleasedcaptureSliderTransparency(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMySpyDoc* pDoc = (CMySpyDoc*)GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CSliderCtrl* pCtrlPos = (CSliderCtrl*)m_wndPostMsgDlgBar.GetDlgItem(IDC_SLIDER_TRANSPARENCY);

	BYTE pos = 50;

	if (pCtrlPos)
		pos = pCtrlPos->GetPos();

	HWND hCurrWnd = pDoc->m_hCurrentlySelectedHwnd;
	if (IsWindow(hCurrWnd))
	{
		::SetWindowLong(hCurrWnd, GWL_EXSTYLE, GetWindowLong(hCurrWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		::SetLayeredWindowAttributes(hCurrWnd, 0, pos * 255 / 100, LWA_ALPHA);
	}

	if (pResult)
		*pResult = 0;
}
void CMainFrame::OnBnClickedCheckTransparent()
{
	m_nTransparencyChecked = m_nTransparencyChecked ? FALSE : TRUE;

	CMySpyDoc* pDoc = (CMySpyDoc*)GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (FALSE == m_nTransparencyChecked)
	{
		HWND hCurrWnd = pDoc->m_hCurrentlySelectedHwnd;
		if (IsWindow(hCurrWnd))
		{
			::SetWindowLong(hCurrWnd, GWL_EXSTYLE, GetWindowLong(hCurrWnd, GWL_EXSTYLE)	& ~WS_EX_LAYERED);
		}
	} else
	{
		OnNMReleasedcaptureSliderTransparency(NULL, NULL);
	}
}

#define TIMER_ID_AUTO_REFRESH		9527

void CMainFrame::OnEnChangeEditAutoRefresh()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDHtmlDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strAutoRefresh;
	m_wndPostMsgDlgBar.GetDlgItem(IDC_EDIT_AUTO_REFRESH)->GetWindowText(strAutoRefresh);
	//XTRACE(L"value1: %s\n", strAutoRefresh);

	int nAutoRefresh = _ttoi(strAutoRefresh);
	if (m_bTimerAutoRefreshStart) {
		m_bTimerAutoRefreshStart = FALSE;
		KillTimer(TIMER_ID_AUTO_REFRESH);
	}

	if (nAutoRefresh > 0) {
		SetTimer(TIMER_ID_AUTO_REFRESH, 1000 * nAutoRefresh, NULL);
		m_bTimerAutoRefreshStart = TRUE;
	}
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (TIMER_ID_AUTO_REFRESH == nIDEvent) {
		// XTRACE(L"timer 11111\n");
		OnViewRefresh();
	}

	CFrameWnd::OnTimer(nIDEvent);
}
