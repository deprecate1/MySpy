#include "StdAfx.h"
#include ".\myoptions.h"

#define __MY_OPTIONS_CPP__
#include "MySpyDoc.h"

#define REG_BUFFER_SIZE 100
#define WIN_INF_TITLE_BUFFER_SIZE 20

IMPLEMENT_SERIAL( CMyOptions, CObject, 1)

CString     CMyOptions::m_strRegKeyName = _T("Software\\MySpy");
TCHAR* pstrTitleStrings[TID_MAX];
MYCALLBACK pCallBackFns[TID_MAX];

//private empty constructor!
CMyOptions::CMyOptions(void)
{
	int i=0;
	pCallBackFns[i++] = CMySpyDoc::GetTitleString;
	pCallBackFns[i++] = CMySpyDoc::GetHWNDString;
	pCallBackFns[i++] = CMySpyDoc::GetClassNameString;
	pCallBackFns[i++] = CMySpyDoc::GetClassStyleString;
	pCallBackFns[i++] = CMySpyDoc::GetModuleNameString;
	pCallBackFns[i++] = CMySpyDoc::GetRECTString;
	pCallBackFns[i++] = CMySpyDoc::GetStylesString;
	pCallBackFns[i++] = CMySpyDoc::GetExStylesString;
	pCallBackFns[i++] = CMySpyDoc::GetPIDString;
	pCallBackFns[i++] = CMySpyDoc::GetThreadIdString;
	pCallBackFns[i++] = CMySpyDoc::GetWindowIdentifierString;
	i=0;
	pstrTitleStrings[i++] = _T("Title");
	pstrTitleStrings[i++] = _T("HWND");
	pstrTitleStrings[i++] = _T("Class Name");
	pstrTitleStrings[i++] = _T("Class Style");
	pstrTitleStrings[i++] = _T("Module Name");
	pstrTitleStrings[i++] = _T("Rect");
	pstrTitleStrings[i++] = _T("Window Style");
	pstrTitleStrings[i++] = _T("Window ExStyle");
	pstrTitleStrings[i++] = _T("Process ID");
	pstrTitleStrings[i++] = _T("Thread ID");
	pstrTitleStrings[i++] = _T("Window ID");

	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_TITLE));
	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_HWND));
	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_CLASS_NAME));
	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_CLASS_STYLE));
	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_MODULE_NAME));
	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_RECT));
	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_WINDOW_STYLE));
	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_WINDOW_EXSTYLE));
	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_PROCESS_ID));
	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_THREAD_ID));
	m_aDefWinInfosOnInfoPane.Add(new CWinInfo(TID_WINDOW_ID));

	if(!LoadFromRegistry())
		LoadDefaults();
};

CMyOptions::~CMyOptions()
{
	if(m_bSaveSettingsOnExit)
		WriteToRegistry();

	DeleteArrayItems(m_aWinInfosOnInfoPane);
	DeleteArrayItems(m_aWinInfosOnTree);
	DeleteArrayItems(m_aDefWinInfosOnInfoPane);
	
}


void CMyOptions::LoadDefaults(void)
{

	m_bActivateAfterAction = true;
	m_bAlwaysOnTop	= false;
	m_eParent		= PARENT_ALL;
	m_eVisibility	= VISIBILITY_ALL;
	m_bDisplayInHex	= false;
	m_bResponseAboutCommandExecutionOnError = true;
	m_bResponseAboutCommandExecutionOnSuccess = false;
	m_bNoResponsePlease = false;
	m_bSaveSettingsOnExit = false;
	m_nResponseTimeout = 3000;

	DeleteArrayItems(m_aWinInfosOnInfoPane);

	for(int i=0; i<m_aDefWinInfosOnInfoPane.GetSize(); i++)
	{
		CWinInfo* pwi = m_aDefWinInfosOnInfoPane.GetAt(i);
		CWinInfo* pwi2 = new CWinInfo(pwi->m_nTitleId);
		m_aWinInfosOnInfoPane.Add(pwi2);
	}
	
	DeleteArrayItems(m_aWinInfosOnTree);

	for(int i=0; i<m_aDefWinInfosOnInfoPane.GetSize(); i++)
	{
		CWinInfo* pwi = m_aDefWinInfosOnInfoPane.GetAt(i);
		CWinInfo* pwi2;
		BOOL bVisibility=FALSE;
		TitleId tid = pwi->m_nTitleId;
		if( tid == TID_TITLE ||
			tid == TID_HWND  ||
			tid == TID_PROCESS_ID||
			tid == TID_MODULE_NAME )
		{
			bVisibility=TRUE;
		}
		pwi2 = new CWinInfo(tid,bVisibility);
		m_aWinInfosOnTree.Add(pwi2);
	}
}


void CMyOptions::Serialize( CArchive& ar)
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( ar );

    // now do the stuff for our specific class
    if( ar.IsStoring() )
	{
        ar << m_bActivateAfterAction;
		ar << m_bAlwaysOnTop;
		ar << m_eParent; 
		ar << m_eVisibility; 
		ar << m_bDisplayInHex;
		ar << m_bResponseAboutCommandExecutionOnError;
		ar << m_bResponseAboutCommandExecutionOnSuccess;
		ar << m_bNoResponsePlease;
		ar << m_bSaveSettingsOnExit;
		ar << m_nResponseTimeout;

		PutWinInfoToArchive(ar,m_aWinInfosOnInfoPane);
		PutWinInfoToArchive(ar,m_aWinInfosOnTree);

	}
    else
	{
        ar >> m_bActivateAfterAction;
        ar >> m_bAlwaysOnTop;

		int tmp;
		ar >> tmp;
		m_eParent = (Parentcraft)tmp; 
		ar >> tmp;
		m_eVisibility = (Visibility)tmp; 
		
		ar >> m_bDisplayInHex;
		ar >> m_bResponseAboutCommandExecutionOnError;
		ar >> m_bResponseAboutCommandExecutionOnSuccess;
		ar >> m_bNoResponsePlease;
		ar >> m_bSaveSettingsOnExit;
		ar >> m_nResponseTimeout;

		m_aWinInfosOnInfoPane.RemoveAll();
		
		try{

			GetWinInfoFromArchive(ar,m_aWinInfosOnInfoPane);
			GetWinInfoFromArchive(ar,m_aWinInfosOnTree);
	    }
		catch(CArchiveException* aex)
		{
			if(aex->m_cause != CArchiveException::endOfFile)
				throw aex;
			else
			{
				TRACE(_T("End of file reached!\n"));
				aex->Delete();
			}
		}
	}
       
}

BOOL CMyOptions::LoadFromRegistry(void)
{
	CRegKey key;
	key.Create(HKEY_CURRENT_USER,m_strRegKeyName);
	ULONG nLong = REG_BUFFER_SIZE;
	BYTE* lpBuffer = (BYTE*)calloc(REG_BUFFER_SIZE,sizeof(BYTE));
	LONG lRet;

	int i = 1;
	do{
		nLong*=i++;
		lpBuffer = (BYTE*)realloc(lpBuffer,nLong*sizeof(BYTE));
		lRet=key.QueryBinaryValue(_T("Options"),lpBuffer,&nLong);
	}
	while(!(ERROR_SUCCESS==lRet || ERROR_FILE_NOT_FOUND==lRet || i > 10));
	
	if(ERROR_SUCCESS!=lRet)
	{
		TRACE(_T("QueryBinaryValue Options Failed!\n"));
		return 0;
	}
	CString strFileName;
	CFile* f = OpenTemporaryFile(strFileName);
	f->Write(lpBuffer,nLong);
	f->Close();
	delete f;

	f = OpenTemporaryFile(strFileName);
	CArchive ar_load(f,CArchive::load);
	Serialize(ar_load);

	ar_load.Close();

	delete f;

	delete lpBuffer;
	DeleteFile(strFileName);
	return 1;
}
BOOL CMyOptions::WriteToRegistry(void)
{
	BOOL nRetVal = TRUE;
	CString strFileName;
	CFile* f = OpenTemporaryFile(strFileName);

	CArchive ar_store(f,CArchive::store);
	Serialize(ar_store);
	ar_store.Flush();
	ULONGLONG length = f->GetLength();
	ar_store.Close();
	delete f;
	
	BYTE* lpBuff = new BYTE[(UINT)length];

	f = OpenTemporaryFile(strFileName);

	UINT nReadedBytes = f->Read( lpBuff, (UINT)length );

	if(nReadedBytes == length)
	{
		CRegKey key;
		key.Create(HKEY_CURRENT_USER,m_strRegKeyName);
		key.SetBinaryValue(_T("Options"),lpBuff, (ULONG)length);
	}
	else
	{
		TRACE(_T("WriteToRegistry failed!\n"));
		nRetVal = FALSE;
	}


	delete f;

	DeleteFile(strFileName);

	return nRetVal;
}

//If strFileName is empty than opens a MySpyxxxxxxxx.dat file
CFile* CMyOptions::OpenTemporaryFile(CString& strFileName)
{
	CFile* f = new CFile();

	UINT nOpenFlags = CFile::modeReadWrite;

	if(strFileName.IsEmpty())
	{
		nOpenFlags |= CFile::modeCreate;
		CTime t = CTime::GetCurrentTime();
		LONG n = (LONG)t.GetTime();
		_itot((int)n,strFileName.GetBuffer(10),10);
		
		strFileName.ReleaseBuffer();
		strFileName = _T("MySpy")+strFileName+_T(".dat");
	}
	CFileException e;
	if( !f->Open(strFileName,nOpenFlags, &e))
	{
		TRACE("Couldn't open file: %s\n",strFileName);
		return NULL;
	}

	return f;
}

void CMyOptions::DeleteArrayItems(CArray<CWinInfo*> &ra)
{
	while(ra.GetCount())
	{
		delete ra.GetAt(0);
		ra.RemoveAt(0);
	}
}

void CMyOptions::GetWinInfoFromArchive(CArchive& ar, CArray<CWinInfo*>& ra)
{
	int nId = 0;
	int bVisibility = 0;
	while(nId >= 0)
	{
		ar >> nId;
		ar >> bVisibility;

		if(nId >= 0)
			ra.Add(new CWinInfo((TitleId)nId,bVisibility));
	}
}

void CMyOptions::PutWinInfoToArchive(CArchive& ar, CArray<CWinInfo*>& ra)
{
		for(int i=0; i < ra.GetSize(); i++)
		{
			CWinInfo* pwi = (CWinInfo*)ra.GetAt(i);
			ar << (UINT)pwi->m_nTitleId;
			ar << (BOOL)pwi->m_bVisible;
		}

		//Put 2x -1 to signal the end of the array
		ar << -1;
		ar << -1;


}
