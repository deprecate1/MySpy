// cntritem.h : interface of the CMyCntrItem class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
class CMySpyDoc;
class CMyEditView;

class CMyCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CMyCntrItem)

// Constructors
public:
	CMyCntrItem(REOBJECT *preo=NULL, CMySpyDoc* pContainer=NULL);
	//CMyCntrItem(REOBJECT* preo = NULL, CWordPadDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.
// Implementation
	CMySpyDoc* GetDocument()
		{ return (CMySpyDoc*)COleClientItem::GetDocument(); }
	CMyEditView* GetActiveView()
		{ return (CMyEditView*)COleClientItem::GetActiveView(); }


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
