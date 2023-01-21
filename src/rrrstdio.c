#include <stdarg.h>
#include <stdlib.h>
#include "rrrstdio.h"


int printf(const char *_fmt, ...)
{
	va_list ap;
	int     ret;

	va_start(ap, _fmt);
	ret = vfprintf(stdout, _fmt, ap);
	va_end(ap);

	return ret;
}

int fprintf(FILE *_fp, const char *_fmt, ...)
{
	va_list ap;
	int     ret;

	va_start(ap, _fmt);
	ret = vfprintf(_fp, _fmt, ap);
	va_end(ap);

	return ret;
}

static inline
int positive(int *x)
{
	if ( x == 0)	return -1;
	if (*x >= 0)	return  0;

	*x = 0 - *x;

	return 1;
}

static inline
size_t len_dtoa(int *_x, int *_neg)
{
	size_t l;
	int    x;
	int    neg;

	if (_x == 0)
		return -1;

	neg = positive(_x);
	l = 1 + neg;

	if (_neg != NULL)
		*_neg = neg;

	x = *_x;
	while (x != 0)
	{
		x /= 10;
		l ++;
	}

	return l;
}

static inline
size_t len_xtoa(unsigned *_x)
{
	size_t   l;
	unsigned x;

	if (_x == 0)
		return -1;

	l = 2;

	x = *_x;
	while (x != 0)
	{
		x >>= 8;
		l  += 2;
	}

	return l;
}

static inline
char *dtoa(int x, size_t *_len)
{
	char  *c;
	char  *str;
	size_t len;
	int    neg;

	len = len_dtoa(&x, &neg);
	str = malloc(len);
	c   = str + (len - 1);

	if (_len != 0)
		*_len = len;

	*(c--) = '\0';
	do
	{
		*(c--) = '0' + (x % 10);
		x /= 10;
	}
	while (x != 0);

	if (neg)
		*(c--) = '-';

	return str;
}

static inline
char *xtoa(unsigned x, size_t *_len)
{
	char  *c;
	char  *str;
	size_t len;

	len = len_xtoa(&x);
	str = malloc(len);
	c   = str + (len - 2);

	if (_len != 0)
		*_len = len;

	*(short *)(c--) = 0;
	do
	{
		*(c--) = "0123456789abcdef" [x & 15];
		x >>= 4;
	}
	while (x != 0);

	return str;
}

static inline
int pvpercentf(FILE *_fp, const char op, va_list *ap)
{
	char  *str;
	size_t len;

	switch (op)
	{
	case ('d'):
		str = dtoa(va_arg(*ap, int), &len);
		return fwrite(str, len, 1, _fp);

	case ('x'):
		str = xtoa(va_arg(*ap, unsigned), &len);
		return fwrite(str, len, 1, _fp);

	case ('c'):
		return fputc(va_arg(*ap, int), _fp);

	default:
		fputc('%', _fp);
		return fputc(op, _fp);
	}

}

int vfprintf(FILE *_fp, const char *_fmt, va_list ap)
{
	char  *c;

	for ( c = (char *)_fmt; *c != 0; c++ )
		if ( *c == '%' )
			pvpercentf(_fp, *(++c), &ap);
		else
			fputc(*c, _fp);

	return c - _fmt;
}
