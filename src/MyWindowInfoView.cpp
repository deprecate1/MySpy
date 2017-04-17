#include "StdAfx.h"
#include ".\mywindowinfoview.h"
#include "MainFrm.h"

CMyWindowInfoView::CMyWindowInfoView(void)
{
	m_pDoc = NULL;
}

CMyWindowInfoView::~CMyWindowInfoView(void)
{
}

void CMyWindowInfoView::DoPopupMenu(UINT nMenuID,CWnd* pWnd)
{
	CMenu popMenu;

	popMenu.LoadMenu(nMenuID);

	//int count = popMenu.GetMenuItemCount();

	CMenu* pSubMenu=popMenu.GetSubMenu(0);

	int pos = FindMenuItem(pSubMenu, _T("Dummy Item"));

	if(pos>-1)
          pSubMenu->RemoveMenu(pos,MF_BYPOSITION);

	CPoint posMouse;
	GetCursorPos(&posMouse);

	popMenu.GetSubMenu(0)->TrackPopupMenu(0,posMouse.x,posMouse.y,pWnd);
}

int CMyWindowInfoView::FindMenuItem(CMenu* Menu, LPCTSTR MenuString)
{
   ASSERT(Menu);
   ASSERT(::IsMenu(Menu->GetSafeHmenu()));

   int count = Menu->GetMenuItemCount();
   for (int i = 0; i < count; i++)
   {
      CString str;
      if (Menu->GetMenuString(i, str, MF_BYPOSITION) &&
         (str.Compare(MenuString) == 0))
         return i;
   }

   return -1;
}

int CMyWindowInfoView::ShowWinInfoOpDlg(CWnd* pParent)
{
	CMainFrame* mf = (CMainFrame*)AfxGetMainWnd();
	return mf->ShowWinInfoOpDlg(pParent);
}

LRESULT CMyWindowInfoView::UpdateWindowInfoView()
{
	HWND selected=NULL;
	LPCTSTR numformat=NULL;

	if (m_pDoc)
	{
		selected = m_pDoc->m_hCurrentlySelectedHwnd;
		numformat= m_pDoc->GetNumberFormat();
	}

	return UpdateWindowInfo((WPARAM)selected,(LPARAM)numformat);
}