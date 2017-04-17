#ifndef __PRINT_BIN_2015_H
#define __PRINT_BIN_2015_H
#include "xtrace.h"

#define DEBUG_PRINT_BIN

#define PRINT_BYTE_PER_LINE		16
#ifdef DEBUG_PRINT_BIN

static inline void __printline(COLORREF textCr, int addr, void *buffer, int len)
{
	TCHAR outstr[256] = L"";
	TCHAR temp[8] = L"";
	wsprintf(outstr, L",0X%04X: ", addr);
	for (int i = 0; i < len; i++) {
		wsprintf(temp, L"%02X ", ((unsigned char *)buffer)[i]);
		wcscat(outstr, temp);
	}
	wcscat(outstr, L"\n");
	XTRACE(textCr, outstr);
}

static inline void printbin(COLORREF textCr, void *buffer, int len)
{
	//XTRACE(textCr, _T("\n"));
	int i;
	for (i = 0; i < len; i += PRINT_BYTE_PER_LINE) {
		int leave = len - i;
		if (leave >= PRINT_BYTE_PER_LINE)
			__printline(textCr, i, (char *)buffer + i, PRINT_BYTE_PER_LINE);
		else
			__printline(textCr, i, (char *)buffer + i, leave);
	}
	//XTRACE(textCr, _T("\n"));
}

static inline void printbin(void *buffer, int len)
{
	printbin(RGB(0, 0, 0), buffer, len);
}
#else
#define printbin(buffer, len)
#endif

#endif
