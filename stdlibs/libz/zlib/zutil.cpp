/* zutil.cpp -- target dependent utility functions for the compression library
 * Copyright (C) 1995-2005 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* @(#) $Id: zutil.cpp,v 1.1.2.1 2008/08/14 15:26:58 e0222316 Exp $ */

#ifdef SYMBIAN_EZLIB_DEVICE
  #include <e32base.h>
#endif

#include "zutil.h"


#ifndef NO_DUMMY_DECL
struct internal_state      {int dummy;}; /* for buggy compilers */
#endif


const char * const z_errmsg[10] = {
"need dictionary",     /* Z_NEED_DICT       2  */
"stream end",          /* Z_STREAM_END      1  */
"",                    /* Z_OK              0  */
"file error",          /* Z_ERRNO         (-1) */
"stream error",        /* Z_STREAM_ERROR  (-2) */
"data error",          /* Z_DATA_ERROR    (-3) */
"insufficient memory", /* Z_MEM_ERROR     (-4) */
"buffer error",        /* Z_BUF_ERROR     (-5) */
"incompatible version",/* Z_VERSION_ERROR (-6) */
""};


#ifdef __SYMBIAN32__
EXPORT_C const char *  zlibVersion_r()
#else
const char * ZEXPORT zlibVersion()
#endif //__SYMBIAN32__
{
    return ZLIB_VERSION;
}


#ifdef __SYMBIAN32__
EXPORT_C uLong  zlibCompileFlags_r()
#else
uLong ZEXPORT zlibCompileFlags()
#endif //__SYMBIAN32__
{
    uLong flags;

    flags = 0;
    switch (sizeof(uInt)) {
    case 2:     break;
    case 4:     flags += 1;     break;
    case 8:     flags += 2;     break;
    default:    flags += 3;
    }
    switch (sizeof(uLong)) {
    case 2:     break;
    case 4:     flags += 1 << 2;        break;
    case 8:     flags += 2 << 2;        break;
    default:    flags += 3 << 2;
    }
    switch (sizeof(voidpf)) {
    case 2:     break;
    case 4:     flags += 1 << 4;        break;
    case 8:     flags += 2 << 4;        break;
    default:    flags += 3 << 4;
    }
    switch (sizeof(z_off_t)) {
    case 2:     break;
    case 4:     flags += 1 << 6;        break;
    case 8:     flags += 2 << 6;        break;
    default:    flags += 3 << 6;
    }
#ifdef DEBUG
    flags += 1 << 8;
#endif
#if defined(ASMV) || defined(ASMINF)
    flags += 1 << 9;
#endif
#ifdef ZLIB_WINAPI
    flags += 1 << 10;
#endif
#ifdef BUILDFIXED
    flags += 1 << 12;
#endif
#ifdef DYNAMIC_CRC_TABLE
    flags += 1 << 13;
#endif
#ifdef NO_GZCOMPRESS
    flags += 1L << 16;
#endif
#ifdef NO_GZIP
    flags += 1L << 17;
#endif
#ifdef PKZIP_BUG_WORKAROUND
    flags += 1L << 20;
#endif
#ifdef FASTEST
    flags += 1L << 21;
#endif
#ifdef STDC
#  ifdef NO_vsnprintf
        flags += 1L << 25;
#    ifdef HAS_vsprintf_void
        flags += 1L << 26;
#    endif
#  else
#    ifdef HAS_vsnprintf_void
        flags += 1L << 26;
#    endif
#  endif
#else
        flags += 1L << 24;
#  ifdef NO_snprintf
        flags += 1L << 25;
#    ifdef HAS_sprintf_void
        flags += 1L << 26;
#    endif
#  else
#    ifdef HAS_snprintf_void
        flags += 1L << 26;
#    endif
#  endif
#endif
    return flags;
}

#ifdef DEBUG

#  ifndef verbose
#    define verbose 0
#  endif
int z_verbose = verbose;

void z_error (m)
    char *m;
{
    fprintf(stderr, "%s\n", m);
    exit(1);
}
#endif


/* exported to allow conversion of error code to string for compress() and
 * uncompress()
 */
#ifdef __SYMBIAN32__
EXPORT_C const char *  zError_r(int err)
#else
const char * ZEXPORT zError(err)
    int err;
#endif //__SYMBIAN32__
{
    return ERR_MSG(err);
}


#if defined(_WIN32_WCE)
    /* The Microsoft C Run-Time Library for Windows CE doesn't have
     * errno.  We define it as a global variable to simplify porting.
     * Its value is always 0 and should not be used.
     */
    int errno = 0;
#endif

#ifndef HAVE_MEMCPY

#ifdef __SYMBIAN32__
void zmemcpy(    Bytef* dest,const Bytef*  source,uInt  len)
#else
void zmemcpy(dest, source, len)
    Bytef* dest;
    const Bytef* source;
    uInt  len;
#endif //__SYMBIAN32__	
{
    if (len == 0) return;
    do {
        *dest++ = *source++; /* ??? to be unrolled */
    } while (--len != 0);
}

#ifdef __SYMBIAN32__
int zmemcmp(    const Bytef* s1,    const Bytef*  s2,uInt  len)
#else	
int zmemcmp(s1, s2, len)
    const Bytef* s1;
    const Bytef* s2;
    uInt  len;
#endif //__SYMBIAN32__		
{
    uInt j;

    for (j = 0; j < len; j++) {
        if (s1[j] != s2[j]) return 2*(s1[j] > s2[j])-1;
    }
    return 0;
}

#ifdef __SYMBIAN32__
void zmemzero( Bytef* dest,uInt  len)
#else	
void zmemzero(dest, len)
    Bytef* dest;
    uInt  len;
#endif //__SYMBIAN32__		
{
    if (len == 0) return;
    do {
        *dest++ = 0;  /* ??? to be unrolled */
    } while (--len != 0);
}
#endif


#ifdef SYS16BIT

#ifdef __TURBOC__
/* Turbo C in 16-bit mode */

#  define MY_ZCALLOC

/* Turbo C malloc() does not allow dynamic allocation of 64K bytes
 * and farmalloc(64K) returns a pointer with an offset of 8, so we
 * must fix the pointer. Warning: the pointer must be put back to its
 * original form in order to free it, use zcfree().
 */

#define MAX_PTR 10
/* 10*64K = 640K */

local int next_ptr = 0;

typedef struct ptr_table_s {
    voidpf org_ptr;
    voidpf new_ptr;
} ptr_table;

local ptr_table table[MAX_PTR];
/* This table is used to remember the original form of pointers
 * to large buffers (64K). Such pointers are normalized with a zero offset.
 * Since MSDOS is not a preemptive multitasking OS, this table is not
 * protected from concurrent access. This hack doesn't work anyway on
 * a protected system like OS/2. Use Microsoft C instead.
 */

voidpf zcalloc (voidpf opaque, unsigned items, unsigned size)
{
    voidpf buf = opaque; /* just to make some compilers happy */
    ulg bsize = (ulg)items*size;

    /* If we allocate less than 65520 bytes, we assume that farmalloc
     * will return a usable pointer which doesn't have to be normalized.
     */
    if (bsize < 65520L) {
        buf = farmalloc(bsize);
        if (*(ush*)&buf != 0) return buf;
    } else {
        buf = farmalloc(bsize + 16L);
    }
    if (buf == NULL || next_ptr >= MAX_PTR) return NULL;
    table[next_ptr].org_ptr = buf;

    /* Normalize the pointer to seg:0 */
    *((ush*)&buf+1) += ((ush)((uch*)buf-0) + 15) >> 4;
    *(ush*)&buf = 0;
    table[next_ptr++].new_ptr = buf;
    return buf;
}

void  zcfree (voidpf opaque, voidpf ptr)
{
    int n;
    if (*(ush*)&ptr != 0) { /* object < 64K */
        farfree(ptr);
        return;
    }
    /* Find the original pointer */
    for (n = 0; n < next_ptr; n++) {
        if (ptr != table[n].new_ptr) continue;

        farfree(table[n].org_ptr);
        while (++n < next_ptr) {
            table[n-1] = table[n];
        }
        next_ptr--;
        return;
    }
    ptr = opaque; /* just to make some compilers happy */
    Assert(0, "zcfree: ptr not found");
}

#endif /* __TURBOC__ */


#ifdef M_I86
/* Microsoft C in 16-bit mode */

#  define MY_ZCALLOC

#if (!defined(_MSC_VER) || (_MSC_VER <= 600))
#  define _halloc  halloc
#  define _hfree   hfree
#endif

voidpf zcalloc (voidpf opaque, unsigned items, unsigned size)
{
    if (opaque) opaque = 0; /* to make compiler happy */
    return _halloc((long)items, size);
}

void  zcfree (voidpf opaque, voidpf ptr)
{
    if (opaque) opaque = 0; /* to make compiler happy */
    _hfree(ptr);
}

#endif /* M_I86 */

#endif /* SYS16BIT */



#ifndef MY_ZCALLOC /* Any system without a special alloc function */

#ifndef STDC
extern voidp  malloc OF((uInt size));
extern voidp  calloc OF((uInt items, uInt size));
extern void   free   OF((voidpf ptr));
#endif

#ifdef __SYMBIAN32__
voidpf zcalloc (voidpf opaque,unsigned  items, unsigned size)
#else 	
voidpf zcalloc (opaque, items, size)
    voidpf opaque;
    unsigned items;
    unsigned size;
#endif //__SYMBIAN32__	
{
    if (opaque) items += size - size; /* make compiler happy */
#ifndef SYMBIAN_EZLIB_DEVICE
  return sizeof(uInt) > 2 ? (voidpf)malloc(items * size) : (voidpf)calloc(items, size);
#else
	TInt bytes = items*size;
	TAny *ptr = User::AllocZ(bytes); // Symbian Native memory allocation API
	return (voidpf) ptr;
#endif //SYMBIAN_EZLIB_DEVICE
}

#ifdef __SYMBIAN32__
void  zcfree (voidpf opaque,voidpf  ptr)
#else 	
void  zcfree (opaque, ptr)
    voidpf opaque;
    voidpf ptr;
#endif //__SYMBIAN32__	
{
#ifndef SYMBIAN_EZLIB_DEVICE
  free(ptr);
#else
	User::Free(ptr); // Symbian Native memory deallocation API
#endif //SYMBIAN_EZLIB_DEVICE
    if (opaque) return; /* make compiler happy */
}

#endif /* MY_ZCALLOC */


