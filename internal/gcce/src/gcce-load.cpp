/*
* ==============================================================================
*  Name        : gcce-validate.c
*  Part of     : internal/gcce
*  Description : This is a test program to test the cross linking of openc libraries with
*  programs compiled using the gcce compiler
Copyright © 2006 Nokia Corporation
All rights reserved.
Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this 
   list of conditions and the following disclaimer. 
 * Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution. 
 * Neither the name of the <ORGANIZATION> nor the names of its contributors 
   may be used to endorse or promote products derived from this software 
   without specific prior written permission. 
   
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ==============================================================================
*/

#include <glib.h>
#include <stdio.h>

#include "result_log.h"

void mrtLogHandler(const gchar* log_domain, GLogLevelFlags log_level,
					const gchar* message, gpointer user_data)
{
	FILE *fp;
	fp = fopen("c:\\logtests.txt","a");
	
	if(fp)
	{
		fprintf(fp,message);
		fprintf(fp,"\n");
		fclose(fp);
	}
}

void mrtPrintHandler(const gchar *message)
{
	FILE *fp;
	fp = fopen("c:\\logtests.txt","a");
	
	if(fp)
	{
		fprintf(fp,message);
		fprintf(fp,"\n");
		fclose(fp);
	}
}



#define UNICODE_VALID(Char)                   \
    ((Char) < 0x110000 &&                     \
     (((Char) & 0xFFFFF800) != 0xD800) &&     \
     ((Char) < 0xFDD0 || (Char) > 0xFDEF) &&  \
     ((Char) & 0xFFFE) != 0xFFFE)




struct {
  const gchar *text;
  gint max_len;
  gint offset;
  gboolean valid;
} test[] = {  
  /* some tests to check max_len handling */
  /* length 1 */
  { "abcde", -1, 5, TRUE },
  { "abcde", 3, 3, TRUE },
  { "abcde", 5, 5, TRUE },
  { "abcde", 7, 5, FALSE },
  /* length 2 */
  { "\xc2\xa9\xc2\xa9\xc2\xa9", -1, 6, TRUE }, 
  { "\xc2\xa9\xc2\xa9\xc2\xa9",  1, 0, FALSE }, 
  { "\xc2\xa9\xc2\xa9\xc2\xa9",  2, 2, TRUE }, 
  { "\xc2\xa9\xc2\xa9\xc2\xa9",  3, 2, FALSE }, 
  { "\xc2\xa9\xc2\xa9\xc2\xa9",  4, 4, TRUE }, 
  { "\xc2\xa9\xc2\xa9\xc2\xa9",  5, 4, FALSE }, 
  { "\xc2\xa9\xc2\xa9\xc2\xa9",  6, 6, TRUE }, 
  { "\xc2\xa9\xc2\xa9\xc2\xa9",  7, 6, FALSE }, 
  /* length 3 */
  { "\xe2\x89\xa0\xe2\x89\xa0", -1, 6, TRUE },
  { "\xe2\x89\xa0\xe2\x89\xa0",  1, 0, FALSE },
  { "\xe2\x89\xa0\xe2\x89\xa0",  2, 0, FALSE },
  { "\xe2\x89\xa0\xe2\x89\xa0",  3, 3, TRUE },
  { "\xe2\x89\xa0\xe2\x89\xa0",  4, 3, FALSE },
  { "\xe2\x89\xa0\xe2\x89\xa0",  5, 3, FALSE },
  { "\xe2\x89\xa0\xe2\x89\xa0",  6, 6, TRUE },
  { "\xe2\x89\xa0\xe2\x89\xa0",  7, 6, FALSE },

  /* examples from http://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-test.txt */
  /* greek 'kosme' */
  { "\xce\xba\xe1\xbd\xb9\xcf\x83\xce\xbc\xce\xb5", -1, 11, TRUE },
  /* first sequence of each length */
  { "\x00", -1, 0, TRUE },
  { "\xc2\x80", -1, 2, TRUE },
  { "\xe0\xa0\x80", -1, 3, TRUE },
  { "\xf0\x90\x80\x80", -1, 4, TRUE },
  { "\xf8\x88\x80\x80\x80", -1, 0, FALSE },
  { "\xfc\x84\x80\x80\x80\x80", -1, 0, FALSE },
  /* last sequence of each length */
  { "\x7f", -1, 1, TRUE },
  { "\xdf\xbf", -1, 2, TRUE },
  { "\xef\xbf\xbf", -1, 0, FALSE },
  { "\xf7\xbf\xbf\xbf", -1, 0, FALSE },
  { "\xfb\xbf\xbf\xbf\xbf", -1, 0, FALSE },
  { "\xfd\xbf\xbf\xbf\xbf\xbf", -1, 0, FALSE },
  /* other boundary conditions */
  { "\xed\x9f\xbf", -1, 3, TRUE },
  { "\xee\x80\x80", -1, 3, TRUE },
  { "\xef\xbf\xbd", -1, 3, TRUE },
  { "\xf4\x8f\xbf\xbf", -1, 0, FALSE },
  { "\xf4\x90\x80\x80", -1, 0, FALSE },
  /* malformed sequences */
  /* continuation bytes */
  { "\x80", -1, 0, FALSE },
  { "\xbf", -1, 0, FALSE },
  { "\x80\xbf", -1, 0, FALSE },
  { "\x80\xbf\x80", -1, 0, FALSE },
  { "\x80\xbf\x80\xbf", -1, 0, FALSE },
  { "\x80\xbf\x80\xbf\x80", -1, 0, FALSE },
  { "\x80\xbf\x80\xbf\x80\xbf", -1, 0, FALSE },
  { "\x80\xbf\x80\xbf\x80\xbf\x80", -1, 0, FALSE },

  /* all possible continuation byte */
  { "\x80", -1, 0, FALSE },
  { "\x81", -1, 0, FALSE },
  { "\x82", -1, 0, FALSE },
  { "\x83", -1, 0, FALSE },
  { "\x84", -1, 0, FALSE },
  { "\x85", -1, 0, FALSE },
  { "\x86", -1, 0, FALSE },
  { "\x87", -1, 0, FALSE },
  { "\x88", -1, 0, FALSE },
  { "\x89", -1, 0, FALSE },
  { "\x8a", -1, 0, FALSE },
  { "\x8b", -1, 0, FALSE },
  { "\x8c", -1, 0, FALSE },
  { "\x8d", -1, 0, FALSE },
  { "\x8e", -1, 0, FALSE },
  { "\x8f", -1, 0, FALSE },
  { "\x90", -1, 0, FALSE },
  { "\x91", -1, 0, FALSE },
  { "\x92", -1, 0, FALSE },
  { "\x93", -1, 0, FALSE },
  { "\x94", -1, 0, FALSE },
  { "\x95", -1, 0, FALSE },
  { "\x96", -1, 0, FALSE },
  { "\x97", -1, 0, FALSE },
  { "\x98", -1, 0, FALSE },
  { "\x99", -1, 0, FALSE },
  { "\x9a", -1, 0, FALSE },
  { "\x9b", -1, 0, FALSE },
  { "\x9c", -1, 0, FALSE },
  { "\x9d", -1, 0, FALSE },
  { "\x9e", -1, 0, FALSE },
  { "\x9f", -1, 0, FALSE },
  { "\xa0", -1, 0, FALSE },
  { "\xa1", -1, 0, FALSE },
  { "\xa2", -1, 0, FALSE },
  { "\xa3", -1, 0, FALSE },
  { "\xa4", -1, 0, FALSE },
  { "\xa5", -1, 0, FALSE },
  { "\xa6", -1, 0, FALSE },
  { "\xa7", -1, 0, FALSE },
  { "\xa8", -1, 0, FALSE },
  { "\xa9", -1, 0, FALSE },
  { "\xaa", -1, 0, FALSE },
  { "\xab", -1, 0, FALSE },
  { "\xac", -1, 0, FALSE },
  { "\xad", -1, 0, FALSE },
  { "\xae", -1, 0, FALSE },
  { "\xaf", -1, 0, FALSE },
  { "\xb0", -1, 0, FALSE },
  { "\xb1", -1, 0, FALSE },
  { "\xb2", -1, 0, FALSE },
  { "\xb3", -1, 0, FALSE },
  { "\xb4", -1, 0, FALSE },
  { "\xb5", -1, 0, FALSE },
  { "\xb6", -1, 0, FALSE },
  { "\xb7", -1, 0, FALSE },
  { "\xb8", -1, 0, FALSE },
  { "\xb9", -1, 0, FALSE },
  { "\xba", -1, 0, FALSE },
  { "\xbb", -1, 0, FALSE },
  { "\xbc", -1, 0, FALSE },
  { "\xbd", -1, 0, FALSE },
  { "\xbe", -1, 0, FALSE },
  { "\xbf", -1, 0, FALSE },
  /* lone start characters */
  { "\xc0\x20", -1, 0, FALSE },
  { "\xc1\x20", -1, 0, FALSE },
  { "\xc2\x20", -1, 0, FALSE },
  { "\xc3\x20", -1, 0, FALSE },
  { "\xc4\x20", -1, 0, FALSE },
  { "\xc5\x20", -1, 0, FALSE },
  { "\xc6\x20", -1, 0, FALSE },
  { "\xc7\x20", -1, 0, FALSE },
  { "\xc8\x20", -1, 0, FALSE },
  { "\xc9\x20", -1, 0, FALSE },
  { "\xca\x20", -1, 0, FALSE },
  { "\xcb\x20", -1, 0, FALSE },
  { "\xcc\x20", -1, 0, FALSE },
  { "\xcd\x20", -1, 0, FALSE },
  { "\xce\x20", -1, 0, FALSE },
  { "\xcf\x20", -1, 0, FALSE },
  { "\xd0\x20", -1, 0, FALSE },
  { "\xd1\x20", -1, 0, FALSE },
  { "\xd2\x20", -1, 0, FALSE },
  { "\xd3\x20", -1, 0, FALSE },
  { "\xd4\x20", -1, 0, FALSE },
  { "\xd5\x20", -1, 0, FALSE },
  { "\xd6\x20", -1, 0, FALSE },
  { "\xd7\x20", -1, 0, FALSE },
  { "\xd8\x20", -1, 0, FALSE },
  { "\xd9\x20", -1, 0, FALSE },
  { "\xda\x20", -1, 0, FALSE },
  { "\xdb\x20", -1, 0, FALSE },
  { "\xdc\x20", -1, 0, FALSE },
  { "\xdd\x20", -1, 0, FALSE },
  { "\xde\x20", -1, 0, FALSE },
  { "\xdf\x20", -1, 0, FALSE },
  { "\xe0\x20", -1, 0, FALSE },
  { "\xe1\x20", -1, 0, FALSE },
  { "\xe2\x20", -1, 0, FALSE },
  { "\xe3\x20", -1, 0, FALSE },
  { "\xe4\x20", -1, 0, FALSE },
  { "\xe5\x20", -1, 0, FALSE },
  { "\xe6\x20", -1, 0, FALSE },
  { "\xe7\x20", -1, 0, FALSE },
  { "\xe8\x20", -1, 0, FALSE },
  { "\xe9\x20", -1, 0, FALSE },
  { "\xea\x20", -1, 0, FALSE },
  { "\xeb\x20", -1, 0, FALSE },
  { "\xec\x20", -1, 0, FALSE },
  { "\xed\x20", -1, 0, FALSE },
  { "\xee\x20", -1, 0, FALSE },
  { "\xef\x20", -1, 0, FALSE },
  { "\xf0\x20", -1, 0, FALSE },
  { "\xf1\x20", -1, 0, FALSE },
  { "\xf2\x20", -1, 0, FALSE },
  { "\xf3\x20", -1, 0, FALSE },
  { "\xf4\x20", -1, 0, FALSE },
  { "\xf5\x20", -1, 0, FALSE },
  { "\xf6\x20", -1, 0, FALSE },
  { "\xf7\x20", -1, 0, FALSE },
  { "\xf8\x20", -1, 0, FALSE },
  { "\xf9\x20", -1, 0, FALSE },
  { "\xfa\x20", -1, 0, FALSE },
  { "\xfb\x20", -1, 0, FALSE },
  { "\xfc\x20", -1, 0, FALSE },
  { "\xfd\x20", -1, 0, FALSE },
  /* missing continuation bytes */
  { "\x20\xc0", -1, 1, FALSE },
  { "\x20\xe0\x80", -1, 1, FALSE },
  { "\x20\xf0\x80\x80", -1, 1, FALSE },
  { "\x20\xf8\x80\x80\x80", -1, 1, FALSE },
  { "\x20\xfc\x80\x80\x80\x80", -1, 1, FALSE },
  { "\x20\xdf", -1, 1, FALSE },
  { "\x20\xef\xbf", -1, 1, FALSE },
  { "\x20\xf7\xbf\xbf", -1, 1, FALSE },
  { "\x20\xfb\xbf\xbf\xbf", -1, 1, FALSE },
  { "\x20\xfd\xbf\xbf\xbf\xbf", -1, 1, FALSE },
  /* impossible bytes */
  { "\x20\xfe\x20", -1, 1, FALSE },
  { "\x20\xff\x20", -1, 1, FALSE },
  /* overlong sequences */
  { "\x20\xc0\xaf\x20", -1, 1, FALSE },
  { "\x20\xe0\x80\xaf\x20", -1, 1, FALSE },
  { "\x20\xf0\x80\x80\xaf\x20", -1, 1, FALSE },
  { "\x20\xf8\x80\x80\x80\xaf\x20", -1, 1, FALSE },
  { "\x20\xfc\x80\x80\x80\x80\xaf\x20", -1, 1, FALSE },
  { "\x20\xc1\xbf\x20", -1, 1, FALSE },
  { "\x20\xe0\x9f\xbf\x20", -1, 1, FALSE },
  { "\x20\xf0\x8f\xbf\xbf\x20", -1, 1, FALSE },
  { "\x20\xf8\x87\xbf\xbf\xbf\x20", -1, 1, FALSE },
  { "\x20\xfc\x83\xbf\xbf\xbf\xbf\x20", -1, 1, FALSE },
  { "\x20\xc0\x80\x20", -1, 1, FALSE },
  { "\x20\xe0\x80\x80\x20", -1, 1, FALSE },
  { "\x20\xf0\x80\x80\x80\x20", -1, 1, FALSE },
  { "\x20\xf8\x80\x80\x80\x80\x20", -1, 1, FALSE },
  { "\x20\xfc\x80\x80\x80\x80\x80\x20", -1, 1, FALSE },
  /* illegal code positions */
  { "\x20\xed\xa0\x80\x20", -1, 1, FALSE },
  { "\x20\xed\xad\xbf\x20", -1, 1, FALSE },
  { "\x20\xed\xae\x80\x20", -1, 1, FALSE },
  { "\x20\xed\xaf\xbf\x20", -1, 1, FALSE },
  { "\x20\xed\xb0\x80\x20", -1, 1, FALSE },
  { "\x20\xed\xbe\x80\x20", -1, 1, FALSE },
  { "\x20\xed\xbf\xbf\x20", -1, 1, FALSE },
  { "\x20\xed\xa0\x80\xed\xb0\x80\x20", -1, 1, FALSE },
  { "\x20\xed\xa0\x80\xed\xbf\xbf\x20", -1, 1, FALSE },
  { "\x20\xed\xad\xbf\xed\xb0\x80\x20", -1, 1, FALSE },
  { "\x20\xed\xad\xbf\xed\xbf\xbf\x20", -1, 1, FALSE },
  { "\x20\xed\xae\x80\xed\xb0\x80\x20", -1, 1, FALSE },
  { "\x20\xed\xae\x80\xed\xbf\xbf\x20", -1, 1, FALSE },
  { "\x20\xed\xaf\xbf\xed\xb0\x80\x20", -1, 1, FALSE },
  { "\x20\xed\xaf\xbf\xed\xbf\xbf\x20", -1, 1, FALSE },
  { "\x20\xef\xbf\xbe\x20", -1, 1, FALSE },
  { "\x20\xef\xbf\xbf\x20", -1, 1, FALSE },

  { NULL, }
};

extern int do_test (gint         index, const gchar *text,  gint         max_len,	 gint         offset, gboolean     valid);

int
main (int argc, char *argv[])
{
  gint i;
 	  
  int any_failed = 0;
  int ret;
  for (i = 0; test[i].text; i++)
  {
  	ret = do_test (i, test[i].text, test[i].max_len, 
	     test[i].offset, test[i].valid);
	 any_failed += ret;
  
  }
    

  #ifdef SYMBIAN
  testResultXml("gcce-load",any_failed);
  #endif /* EMULATOR */
  
  return any_failed ? 1 : 0;
}
