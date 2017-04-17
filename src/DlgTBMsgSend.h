#pragma once
#include "afxwin.h"


// CDlgTBMsgSend dialog

class CDlgTBMsgSend : public CDialog
{
	DECLARE_DYNAMIC(CDlgTBMsgSend)

public:
	CDlgTBMsgSend(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTBMsgSend();

// Dialog Data
	enum { IDD = IDD_SEND_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// Contains the Id-s of windows messages
	CListBox m_ctlMsgIdlList;
	virtual BOOL OnInitDialog();
};
