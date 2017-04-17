#include "StdAfx.h"
#include ".\mywininfooptionsdlg.h"
#include "MainFrm.h"


// CMyWinInfoOptionsDlg dialog

IMPLEMENT_DYNAMIC(CMyWinInfoOptionsDlg, CPropertyPage)

CMyWinInfoOptionsDlg::CMyWinInfoOptionsDlg(CWnd* pParent /*=NULL*/)
: CMyPropertyPage(CMyWinInfoOptionsDlg::IDD)
{
}

CMyWinInfoOptionsDlg::~CMyWinInfoOptionsDlg()
{
}

void CMyWinInfoOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WIN_INFO_LIST, m_ctlOptionList);
	DDX_Control(pDX, IDC_TREE_OR_INFO_COMBO, m_comboWinInfoChoice);
}


BEGIN_MESSAGE_MAP(CMyWinInfoOptionsDlg, CPropertyPage)
ON_NOTIFY(NM_DBLCLK, IDC_WIN_INFO_LIST, OnNMDblclkWinInfoList)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_WIN_INFO_LIST, OnLvnItemchangedWinInfoList)
ON_BN_CLICKED(IDC_UP, OnBnClickedUp)
ON_BN_CLICKED(IDC_DOWN, OnBnClickedDown)
ON_MESSAGE(PSM_QUERYSIBLINGS, OnQuerySiblings)
ON_CBN_SELCHANGE(IDC_TREE_OR_INFO_COMBO, OnCbnSelchangeTreeOrInfoCombo)
END_MESSAGE_MAP()


// CMyWinInfoOptionsDlg message handlers



BOOL CMyWinInfoOptionsDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CRect rect;
	m_ctlOptionList.GetClientRect(&rect);
	m_ctlOptionList.InsertColumn(0, _T("Window Info"), LVCFMT_LEFT, rect.Width());

	m_ctlOptionList.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );

	ListView_SetExtendedListViewStyle(m_ctlOptionList.m_hWnd, 
		LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP 
		| LVS_EX_GRIDLINES );

	m_comboWinInfoChoice.AddString(_T("Window Tree"));
	m_comboWinInfoChoice.AddString(_T("Window Info Pane"));

	m_comboWinInfoChoice.SetCurSel(1);

	CloneWinInfoArray(m_rOptions.m_aWinInfosOnInfoPane,m_aWinInfosClone);

	Update();

	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMyWinInfoOptionsDlg::OnNMDblclkWinInfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctlOptionList.GetFirstSelectedItemPosition();
	int selectedItem = m_ctlOptionList.GetNextSelectedItem(pos);

	BOOL state = ListView_GetCheckState(pNMHDR->hwndFrom,selectedItem);
	ListView_SetCheckState(pNMHDR->hwndFrom,selectedItem,state?FALSE:TRUE);

	CWinInfo* wi = m_rOptions.m_aWinInfosOnInfoPane.GetAt(selectedItem);
	wi->m_bVisible = state?FALSE:TRUE;

	SetModified();
	*pResult = 0;
}



void CMyWinInfoOptionsDlg::OnLvnItemchangedWinInfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW  pNMListView = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	
    if (pNMListView->uOldState == 0 && pNMListView->uNewState == 0)
        return;    // No change

    // Old check box state
    BOOL bPrevState = (BOOL)(((pNMListView->uOldState & LVIS_STATEIMAGEMASK)>>12)-1);  
    if (bPrevState < 0)    // On startup there's no previous state 
        bPrevState = 0; // so assign as false (unchecked)

    // New check box state
    BOOL bChecked = (BOOL)(((pNMListView->uNewState & LVIS_STATEIMAGEMASK)>>12)-1);   
    if (bChecked < 0) // On non-checkbox notifications assume false
        bChecked = 0; 

    if (bPrevState == bChecked) // No change in check box
        return;

	// Now bChecked holds the new check box state

	m_ctlOptionList.SetItemState(pNMListView->iItem,LVIS_SELECTED,LVIS_SELECTED);

	CWinInfo* wi = m_aWinInfosClone.GetAt(pNMListView->iItem);
	wi->m_bVisible = bChecked;

	SetModified();

}

void CMyWinInfoOptionsDlg::OnBnClickedUp()
{

	POSITION pos = m_ctlOptionList.GetFirstSelectedItemPosition();
	int selectedItem = m_ctlOptionList.GetNextSelectedItem(pos);
	if(selectedItem > 0)
	{
		ChangeItems(selectedItem,selectedItem-1);
	}
	m_ctlOptionList.SetFocus();
	SetModified();

	
}

void CMyWinInfoOptionsDlg::OnBnClickedDown()
{	
	POSITION pos = m_ctlOptionList.GetFirstSelectedItemPosition();
	int selectedItem = m_ctlOptionList.GetNextSelectedItem(pos);
	if(selectedItem < m_ctlOptionList.GetItemCount() -1 )
	{
		ChangeItems(selectedItem,selectedItem+1);
	}
	m_ctlOptionList.SetFocus();
	SetModified();
}

void CMyWinInfoOptionsDlg::ChangeItems(int item1, int item2)
{
	BOOL bState = m_ctlOptionList.GetCheck(item1);
//delete all items from list control
	m_ctlOptionList.DeleteAllItems();

	INT_PTR nInfoCount = m_aWinInfosClone.GetCount();
	//int beforeSelectedItem = item1-1;

//change items	
	CWinInfo* pwi2 = m_aWinInfosClone.GetAt((INT_PTR)item2);
	CWinInfo* pwi1 = m_aWinInfosClone.GetAt((INT_PTR)item1);

	m_aWinInfosClone.SetAt(item2,m_aWinInfosClone.GetAt((INT_PTR)item1));
	m_aWinInfosClone.SetAt(item1,pwi2);



//put items to the control
	for(int i=0; i<nInfoCount; i++)
	{
		CWinInfo* pwi = m_aWinInfosClone.GetAt(i);
		m_ctlOptionList.InsertItem(i,pstrTitleStrings[pwi->m_nTitleId]);
		// Use macro to set check state
		if(i==item2)
		{
			ListView_SetCheckState(m_ctlOptionList.m_hWnd,i,bState);
		}
		else
		{
			ListView_SetCheckState(m_ctlOptionList.m_hWnd,i,pwi->m_bVisible);
		}
	}
	
	m_ctlOptionList.SetItemState(item2, LVIS_SELECTED, LVIS_SELECTED);
}

void CMyWinInfoOptionsDlg::Store()
{
	CloneWinInfoArray(m_aWinInfosClone,m_rOptions.m_aWinInfosOnInfoPane);
}

void CMyWinInfoOptionsDlg::Update(void)
{	

	m_ctlOptionList.DeleteAllItems();

	for(int i=0; i<m_rOptions.m_aWinInfosOnInfoPane.GetCount(); i++)
	{
		CWinInfo* wi = m_rOptions.m_aWinInfosOnInfoPane.GetAt(i);
		m_ctlOptionList.InsertItem(i,pstrTitleStrings[wi->m_nTitleId]);
		// Use macro to set check state
		ListView_SetCheckState(m_ctlOptionList.m_hWnd,i,wi->m_bVisible);
	}

}

void CMyWinInfoOptionsDlg::CloneWinInfoArray(CArray<CWinInfo*> &src,CArray<CWinInfo*> &dest)
{
		
	int i=0;
	
	while(dest.GetCount())
	{
		CWinInfo* destWinInf = dest.GetAt(0);
		dest.RemoveAt(0);
		delete destWinInf;
	}

	for(i=0; i < src.GetCount(); i++)
	{
		CWinInfo* srcWinInf = src.GetAt(i);
		dest.Add(new CWinInfo(srcWinInf->m_nTitleId,srcWinInf->m_bVisible));

	}
}
BOOL CMyWinInfoOptionsDlg::IsModified(void)
{
	if(0 == m_aWinInfosClone.GetSize() - m_rOptions.m_aWinInfosOnInfoPane.GetSize())
	{
		for(int i=0; i<m_aWinInfosClone.GetSize(); i++)
			if(*(m_aWinInfosClone.GetAt(i)) != *(m_rOptions.m_aWinInfosOnInfoPane.GetAt(i)))
				return TRUE;
	}
	else
		TRACE(_T("The size of clone and source are not equal!!\n"));
	return FALSE;
}

void CMyWinInfoOptionsDlg::OnCbnSelchangeTreeOrInfoCombo()
{
	//m_comboWinInfoChoice.G
}
