#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <windows.h>

#pragma warning (disable : 4996)
#define USE_LARGE_BUFFER
// 如果需要监视的字符串大于512bytes 请使用 #define USE_LARGE_BUFFER
// 如果想使所有的XTRACE失效 请使用 #define NO_XTRACE

// ================================================================================
// 从这里开始就不要改了
// ================================================================================
// Usage:
// void XTRACE(COLORREF crText, LPCWSTR lpszFormat, ...);

#ifdef NO_XTRACE
	#define XTRACE

	#ifndef ASSERT
		#define ASSERT
	#endif
#else
	#define XTRACE		xTrace		// Trace to share memory viewer



#ifndef ASSERT
#define ASSERT assert
#include <assert.h>
#endif

// 默认输出黑色
#ifndef XTRACE_TEXT_COLOR
	#define XTRACE_TEXT_COLOR RGB(0, 0, 0)
#endif
inline void xTrace(LPCWSTR lpszFormat, ...);

class DllLoad
{
public:
	DllLoad(LPCWSTR lpszName)
	{
		m_hModule = NULL;
		TCHAR szTemp[MAX_PATH] = _T("");
		if(::GetTempPath(MAX_PATH - 1, szTemp))
		{
			wcscat_s(szTemp, lpszName);
			m_hModule = ::LoadLibrary(szTemp);
		}
	}
	~DllLoad()
	{	::FreeLibrary(m_hModule);	 m_hModule = NULL;
	}
	operator  HMODULE() { return m_hModule;}
protected:
	HMODULE m_hModule;
};

typedef void (WINAPIV * MAGIC_TRACE_PROC)(int nMsg, WPARAM wParam, LPARAM lParam, WPARAM wParam2, LPARAM lParam2);

inline MAGIC_TRACE_PROC GetMagicTraceProc()
{
	static DllLoad xdl(_T("xTRACE.dll"));
	static MAGIC_TRACE_PROC fnMagicTraceProc = (MAGIC_TRACE_PROC)::GetProcAddress(HMODULE(xdl), "MagicTraceProc"); 
	return fnMagicTraceProc;
}

#ifndef USE_LARGE_BUFFER
inline void xTrace(LPCWSTR lpszFormat, ...)
{
	MAGIC_TRACE_PROC pMTrace = GetMagicTraceProc();
	if (pMTrace)
	{
		va_list args;
		va_start(args, lpszFormat);
		int nBuf;
		TCHAR szBuffer[512];
		nBuf = wvsprintf(szBuffer, lpszFormat, args);
		va_end(args);

#if 0
		OutputDebugString(W2T(szBuffer));
#else
		if (nBuf)
			pMTrace(0, XTRACE_TEXT_COLOR, (LPARAM)szBuffer, 0, 0);
#endif
	}
}

inline void xTrace(COLORREF textCr, LPCWSTR lpszFormat, ...)
{
	MAGIC_TRACE_PROC pMTrace = GetMagicTraceProc();
	if (pMTrace)
	{
		va_list args;
		va_start(args, lpszFormat);
		int nBuf;
		TCHAR szBuffer[512];
		nBuf = wvsprintf(szBuffer, lpszFormat, args);
		va_end(args);

#if 0
		OutputDebugString(W2T(szBuffer));
#else
		if (nBuf)
			pMTrace(0, textCr, (LPARAM)szBuffer, 0, 0);
#endif
	}

}

#else

inline void ____xTrace_unicode(COLORREF textCr, LPCWSTR lpszFormat, va_list args)
{
	MAGIC_TRACE_PROC pMTrace = GetMagicTraceProc();
	if (!pMTrace)
		return;

	// 显示时间
	{
		SYSTEMTIME sys;
		GetLocalTime(&sys);

		TCHAR szBuf[512] = _T("");
		wsprintf(szBuf
			, L"%d-%02d-%02d %02d:%02d:%02d.%04d "
			, sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds
		);
		pMTrace(0, textCr, (LPARAM)szBuf, 0, 0);
	}

	// 显示消息内容
	{
		int nBuf;
		TCHAR * pszBuffer = new TCHAR[4096];
		nBuf = wvsprintf(pszBuffer, lpszFormat, args);
		if (nBuf) 
		{
			int len = wcslen(pszBuffer);
			int rest = len;
			TCHAR * pTemp = pszBuffer;
			while (rest)
			{
				int l = rest;
				if (l > 508)
				{
					l = 508;
					const TCHAR * p2 = CharPrevW(pTemp, pTemp+l);
					l = p2 - pTemp;
				}
				TCHAR szBuf[512] = _T("");
				wcsncpy(szBuf, pTemp , l);
				pMTrace(0, textCr, (LPARAM)szBuf, 0, 0);
				pTemp += l;
				rest -= l;
			}
		}
		delete [] pszBuffer;
	}

}

// unicode封装1
inline void xTrace(COLORREF textCr, LPCWSTR lpszFormat, ...)
{
	va_list ap;
	va_start(ap, lpszFormat);
	____xTrace_unicode(textCr, lpszFormat, ap);
	va_end(ap);
}

// unicode封装2
inline void xTrace(LPCWSTR lpszFormat, ...)
{
	va_list ap;
	va_start(ap, lpszFormat);
	____xTrace_unicode(XTRACE_TEXT_COLOR, lpszFormat, ap);
	va_end(ap);
}

// ANSI封装2
inline void xTrace(COLORREF textCr, LPCSTR lpszFormat, ...)
{
	va_list ap;
	va_start(ap, lpszFormat);
	char * pszBuffer = new char[4096];
	vsprintf(pszBuffer, lpszFormat, ap);
	va_end(ap);

	// 转换成unicode输出
	USES_CONVERSION;
	xTrace(textCr, L"%s", A2W(pszBuffer));
	delete[] pszBuffer;
}

// ANSI封装2
inline void xTrace(LPCSTR lpszFormat, ...)
{
	va_list ap;
	va_start(ap, lpszFormat);
	char * pszBuffer = new char[4096];
	vsprintf(pszBuffer, lpszFormat, ap);
	va_end(ap);

	// 转换成unicode输出
	USES_CONVERSION;
	xTrace(XTRACE_TEXT_COLOR, L"%s", A2W(pszBuffer));
	delete[] pszBuffer;
}

#endif
#endif
