#pragma once
#include "afxdlgs.h"
#include "MyOptions.h"

enum MyPropertyPageMsg
{
	PPM_UPDATE,
	PPM_STORE,
	PPM_IS_MODIFIED
};


class CMyPropertyPage :
	public CPropertyPage
{
public:
	CMyPropertyPage(UINT nId);
	virtual ~CMyPropertyPage(void){};
	void SetModified(void);
	virtual BOOL IsModified()=0;

	virtual void OnOK();
	virtual BOOL OnApply();
	virtual void OnCancel();

protected:
	CMyOptions& m_rOptions;
	BOOL m_bModified;

	virtual afx_msg LRESULT OnQuerySiblings(WPARAM wParam,LPARAM);
	virtual void Update()=0;
	virtual void Store()=0;
};
