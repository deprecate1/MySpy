// cntritem.cpp : implementation of the CMyCntrItem class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "MySpy.h"

#include "MySpyDoc.h"
#include "MyEditView.h"

#include "MyCntrItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCntrItem implementation

IMPLEMENT_SERIAL(CMyCntrItem, CRichEditCntrItem, 0)

CMyCntrItem::CMyCntrItem(REOBJECT *preo, CMySpyDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
}

/////////////////////////////////////////////////////////////////////////////
// CMyCntrItem diagnostics

#ifdef _DEBUG
void CMyCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CMyCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
