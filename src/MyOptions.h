#pragma once
#include "afx.h"
#include "singleton.hpp"
#include "threads.hpp"

using namespace std;
using namespace Dot;

typedef void (*MYCALLBACK)(HWND, CString&/*[out]OutputString*/);

enum Visibility
{
	VISIBILITY_ALL,
	VISIBILITY_VISIBLE_ONLY,
	VISIBILITY_NON_VISIBLE_ONLY
};
enum Parentcraft
{
	PARENT_ALL,
	PARENT_PARENTS_ONLY,
	PARENT_CHILDREN_ONLY
};

enum TitleId
{
	TID_TITLE,
	TID_HWND,
	TID_CLASS_NAME,
	TID_CLASS_STYLE,
	TID_MODULE_NAME,
	TID_RECT,
	TID_WINDOW_STYLE,
	TID_WINDOW_EXSTYLE,
	TID_PROCESS_ID,
	TID_THREAD_ID,
	TID_WINDOW_ID,
	TID_MAX
};

#ifndef __MY_OPTIONS_CPP__
 extern TCHAR* pstrTitleStrings[TID_MAX];
 extern MYCALLBACK pCallBackFns[TID_MAX];
#endif


class CWinInfo
{
public:
	explicit CWinInfo(TitleId nTitleId,BOOL bVisible=TRUE)
	{
		m_nTitleId = nTitleId;
		m_bVisible = bVisible;
	}
	~CWinInfo(){}
	
	CWinInfo& operator=(CWinInfo const& other) 
	{
		this->m_nTitleId = other.m_nTitleId;
		this->m_bVisible = other.m_bVisible;
		return *this; 
	}
	
	bool operator==(CWinInfo const& other)
	{
		if(m_nTitleId == other.m_nTitleId)
			if(m_bVisible==other.m_bVisible)
				return true;
		return false;
	}
	
	bool operator!=(CWinInfo const& other)
	{
		return !(operator==(other));
	}
	
	TitleId m_nTitleId;
	BOOL m_bVisible;
};


class CMyOptions  : public Singleton<CMyOptions
									,Dot::CreateUsingNew<CMyOptions>
									,Dot::DefaultLifetime
									,Dot::Threading::SingleThreaded/* don't need MultiThreaded*/>
					,public CObject
{
public:
	DECLARE_SERIAL(CMyOptions)
	CMyOptions(void);
	virtual ~CMyOptions(void);
	static CMyOptions& GetMyOptions(){return Instance();};

    inline CMyOptions& operator=(CMyOptions const&) { return *this; }
	void Serialize( CArchive& archive );
	BOOL LoadFromRegistry(void);
	BOOL WriteToRegistry(void);
	void LoadDefaults(void);
//members:
	static CString m_strRegKeyName;
//-------- Options
	bool		m_bActivateAfterAction;
	bool		m_bAlwaysOnTop;
	Parentcraft m_eParent; 
	Visibility	m_eVisibility; 
	bool        m_bDisplayInHex;
	bool		m_bResponseAboutCommandExecutionOnError;
	bool		m_bResponseAboutCommandExecutionOnSuccess;
	bool		m_bNoResponsePlease;
	bool		m_bSaveSettingsOnExit;
	UINT		m_nResponseTimeout;

	CArray<CWinInfo*> m_aWinInfosOnInfoPane;
	CArray<CWinInfo*> m_aWinInfosOnTree;
	
	CArray<CWinInfo*> m_aDefWinInfosOnInfoPane;
//--------

private:
	CFile* OpenTemporaryFile(CString& strFileName);
	void DeleteArrayItems(CArray<CWinInfo*> &ra);
	void GetWinInfoFromArchive(CArchive& ar, CArray<CWinInfo*>& ra);
	void PutWinInfoToArchive(CArchive& ar, CArray<CWinInfo*>& ra);
};

