// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "afxwin.h"
#include "MySpyDoc.h"
#include "MyTreeView.h"
#include "SendMsgDlg.h"
#include "MyFindDlg.h"
#include "MyEditView.h"
#include "MyListView.h"
#include "UsefulSplitterWnd.h"
#include "MyOptionsPropertySheet.h"
#include "afxext.h"

class CMyToolBar : public CToolBar
{
};
class CMyDialogBar : public CDialogBar
{
};


class CEditableComboBox : public CComboBox
{
protected:
	int FindInComboList(CString& str);
public:
	LONG GetBoxData();
};

enum ThreadReturnValues
{
	NOT_SET,
	REFRESH_DOC,
	UPDATE_ITEM
};

class CMainFrame : public CFrameWnd
{

	// create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CUsefulSplitterWnd m_wndSplitter;
	CStatusBar  m_wndStatusBar;
	static void HighlightWindow(HWND hWnd);
	static UINT MultipleHighLight(LPVOID pParam);
	void EnableActionToolbar(BOOL bEnable);

	afx_msg void OnDisplayInHex();
	afx_msg void OnUpdateDisplayInHex(CCmdUI *pCmdUI);

	afx_msg void OnFind();
	afx_msg void OnUpdateFind(CCmdUI *pCmdUI);

	afx_msg void OnStayontop();
	afx_msg void OnHighlight();
	afx_msg void OnToolbarsMaintoolbar();
	afx_msg void OnUpdateToolbarsMaintoolbar(CCmdUI *pCmdUI);
	afx_msg void OnPostMsgTb();
	afx_msg void OnUpdatePostMsgTb(CCmdUI *pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnEnChangeEditSettext();
	afx_msg void OnEndSession(BOOL bEnding);
	afx_msg BOOL OnQueryEndSession();
	afx_msg void OnWindowinfopaneListview();
	afx_msg void OnUpdateWindowinfopaneListview(CCmdUI *pCmdUI);
	afx_msg void OnWindowinfopaneRicheidtview();
	afx_msg void OnUpdateWindowinfopaneRicheidtview(CCmdUI *pCmdUI);
	//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnViewAfteractionactivate();
	afx_msg void OnUpdateViewAfteractionactivate(CCmdUI *pCmdUI);
	afx_msg void OnViewRefresh();
	void RefreshTreePane();
	void RefreshWinInfoPane();
	int ShowWinInfoOpDlg(CWnd* pParent);

	CMyTreeView* m_pTreeViewPane;
	CMyEditView* m_pWindowInfoPane;
	CMyListView* m_pWindowInfoPane2;

protected:  // control bar embedded members
	//CToolBar    m_wndToolBar; 
	CMyToolBar    m_wndActionBar;//Default toolbar
	CMyToolBar    m_wndViewToolBar;
	CMyDialogBar  m_wndPostMsgDlgBar;
	CDHtmlDialog* m_pHtmlDg;

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateInfoInStatusBar(CCmdUI *pCmdUI);
	afx_msg void OnSetTopMost();
	afx_msg void OnUpdateSetTopMost(CCmdUI *pCmdUI);
	afx_msg void OnUpdateToolBar(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePostMsgButton(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSliderTransparency(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewToolBar(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTBVisibleOnly(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTBViewAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTBHiddenOnly(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTBParentsOnly(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTBChildrenOnly(CCmdUI *pCmdUI);
	afx_msg void OnPostMessage();
	afx_msg	void OnSendMessage();
	afx_msg void OnNMReleasedcaptureSliderTransparency(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckTransparent();

	void SendOrPostMessage(BOOL bSend);

	afx_msg void OnViewCommand(UINT nActionID);
	afx_msg void OnActionCommand(UINT nActionID);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);


	afx_msg void OnEnChangeEditAutoRefresh();		// change spin value: auto refresh
public:
	CString GetFilterString();
	void SetFilterString(CString filter);

private:
	void ErrorMsgBox(DWORD dw);

	struct ActionParam {
		HWND hWnd;
		int nActionID;
		ThreadReturnValues uRet;
		// handle for WaitForSingleObject
		HANDLE hActionReady;
		ActionParam() : hWnd(0), nActionID(0), uRet(NOT_SET), hActionReady(0){};
	} m_sActionParam;
	static UINT ThreadForActionOnSelectedWindow(LPVOID);
	//static HANDLE m_hActionHandle;
	CMySpyDoc* m_pDoc;
	BOOL m_bOnTop;
	BOOL m_bEnableAction;
	CMyOptions& m_rOptions;
	CMyOptionsPropertySheet* m_pOptionsDlg;

	BOOL m_bTimerAutoRefreshStart;
public:
	afx_msg void OnViewOptions();
private:
	BOOL m_nTransparencyChecked;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};


