#if !defined(AFX_USEFULSPLITTERWND_H__61D2F7E7_7AAA_11D1_9F4C_008029E98A75__INCLUDED_)
#define AFX_USEFULSPLITTERWND_H__61D2F7E7_7AAA_11D1_9F4C_008029E98A75__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UsefulSplitterWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUsefulSplitterWnd window

class CUsefulSplitterWnd : public CSplitterWnd
{
// Construction
public:
	CUsefulSplitterWnd();

// Attributes
public:

private:
	BOOL m_bBarLocked;

// Operations
public:
	BOOL IsBarLocked(){return m_bBarLocked;}
	void LockBar(BOOL bState=TRUE){m_bBarLocked=bState;}
	BOOL ReplaceView(int row, int col,CRuntimeClass * pViewClass,SIZE size);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsefulSplitterWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUsefulSplitterWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUsefulSplitterWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEFULSPLITTERWND_H__61D2F7E7_7AAA_11D1_9F4C_008029E98A75__INCLUDED_)
