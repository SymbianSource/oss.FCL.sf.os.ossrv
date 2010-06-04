/* crypto/md2/md2test.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */
 /*
 � Portions copyright (c) 2006 Nokia Corporation.  All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#ifndef SYMBIAN
#include "../e_os.h"
#else
#include "e_os.h"
#endif
#ifdef SYMBIAN
#ifdef stdin
#undef stdin
#endif
#ifdef stdout
#undef stdout
#endif
#ifdef stderr
#undef stderr
#endif

#define stdin fp_stdin
#define stdout fp_stdout
#define stderr fp_stderr

extern FILE *fp_stdout;
extern FILE *fp_stderr;
#endif

#ifdef OPENSSL_NO_MD2
int main(int argc, char *argv[])
{
    fprintf(stdout,"No MD2 support\n");
    return(0);
}
#else
#include <openssl/evp.h>
#include <openssl/md2.h>

#ifdef CHARSET_EBCDIC
#include <openssl/ebcdic.h>
#endif

static char *test[]={
	"",
	"a",
	"abc",
	"message digest",
	"abcdefghijklmnopqrstuvwxyz",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
	"12345678901234567890123456789012345678901234567890123456789012345678901234567890",
	NULL,
	};

static char *ret[]={
	"8350e5a3e24c153df2275c9f80692773",
	"32ec01ec4a6dac72c0ab96fb34c0b5d1",
	"da853b0d3f88d99b30283a69e6ded6bb",
	"ab4f496bfb2a530b219ff33031fe06b0",
	"4e8ddff3650292ab5a4108c3aa47940b",
	"da33def2a42df13975352846c30338cd",
	"d5976f79d83d3a0dc9806c3c66f3efd8",
	};

static char *pt(unsigned char *md);
#ifndef SYMBIAN
int main(int argc, char *argv[])
#else
int md2_main(int argc, char *argv[])
#endif
	{
	int i,err=0;
	char **P,**R;
	char *p;
	unsigned char md[MD2_DIGEST_LENGTH];

	P=test;
	R=ret;
	i=1;
	
	while (*P != NULL)
		{
		EVP_Digest((unsigned char *)*P,strlen(*P),md,NULL,EVP_md2(), NULL);
   if(errno==ENOMEM)
    {
	    return 1;
	  }  
		p=pt(md);
		if (strcmp(p,*R) != 0)
			{
		   if(errno==ENOMEM)
       {
	      return 1;
	     }  
	
			fprintf(stdout,"error calculating MD2 on '%s'\n",*P);
			fprintf(stdout,"got %s instead of %s\n",p,*R);
			err++;
			}
		else
			fprintf(stdout,"test %d ok\n",i);
		i++;
		R++;
		P++;
		}
#ifdef OPENSSL_SYS_NETWARE
    if (err) fprintf(stdout,"ERROR: %d\n", err);
#endif
    fprintf(stdout,"Test Case passed\n");
	//EXIT(err);
	return err;
	}

static char *pt(unsigned char *md)
	{
	int i;
	static char buf[80];

	for (i=0; i<MD2_DIGEST_LENGTH; i++)
		sprintf(&(buf[i*2]),"%02x",md[i]);
	return(buf);
	}
#endif
