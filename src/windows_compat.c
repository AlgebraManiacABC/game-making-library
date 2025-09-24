#ifdef _WIN32
#include "windows_compat.h"

int asprintf(char ** str, const char * fmt, ...)
{
	va_list args;
	va_start(args,fmt);
	int retval = vasprintf(str,fmt,args);
	va_end(args);
	return retval;
}

/* ---- MSVC vasprintf fallback ---- */
#if defined(_MSC_VER) && !defined(__clang__)
	#include <stdarg.h>
	#include <stdio.h>
	#include <stdlib.h>
	static int vasprintf(char **strp, const char *fmt, va_list ap) {
		va_list ap2; va_copy(ap2, ap);
		int needed = _vscprintf(fmt, ap2);
		va_end(ap2);
		if (needed < 0) { *strp = NULL; return -1; }
		char *buf = (char*)malloc((size_t)needed + 1);
		if (!buf) { *strp = NULL; return -1; }
		int written = vsnprintf(buf, (size_t)needed + 1, fmt, ap);
		if (written < 0) { free(buf); *strp = NULL; return -1; }
		*strp = buf;
		return written;
	}
#else
	int vasprintf(char ** str, const char * fmt, va_list args)
	{
		return __mingw_vasprintf(str,fmt,args);
	}
#endif

#endif