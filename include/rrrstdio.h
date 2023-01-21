#ifndef __RRRSTDIO_H__
#define __RRRSTDIO_H__

#ifdef __cplusplus
	extern "C"
	{
#endif // __cplusplus

#include <stdlib.h>

#define printf   __R_printf
#define fprintf  __R_fprintf
#define vfprintf __R_vfprintf

//typedef /* unspecified */ va_list;
typedef __builtin_va_list  va_list;

		/*
size_t fwrite(const void *ptr,
              size_t size, size_t nmemb,
              FILE *restrict stream);
		*/

int printf(const char *_fmt, ...);
int fprintf(FILE *_fp, const char *_fmt, ...);
int vfprintf(FILE *_fp, const char *_fmt, va_list ap);

		/*
#define stdin	((FILE *)0)
#define stdout	((FILE *)1)
#define stderr	((FILE *)2)
		*/

#ifdef __cplusplus
	}
#endif // __cplusplus

#endif // __RRRSTDIO_H__
