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

#include "glib.h"
#include <stdio.h>

#include "result_log.h"

#define UNICODE_VALID(Char)                   \
    ((Char) < 0x110000 &&                     \
     (((Char) & 0xFFFFF800) != 0xD800) &&     \
     ((Char) < 0xFDD0 || (Char) > 0xFDEF) &&  \
     ((Char) & 0xFFFE) != 0xFFFE)



EXPORT_C int do_test (gint         index,
	 const gchar *text, 
	 gint         max_len,
	 gint         offset,
	 gboolean     valid)
{
  const gchar *end;
  gboolean result;
  int failed =0;
  
  result = g_utf8_validate (text, max_len, &end);

  if (result != valid || end - text != offset)
    {
      GString *str;
      const gchar *p;

      failed++;
      
      str = g_string_new (0);
      for (p = text; *p; p++)
	g_string_append_printf (str, "\\x%02hhx", *p);
      g_print ("%d: g_utf8_validate (\"%s\", %d) failed, "
	       "expected %s %d, got %s %d\n",
	       index,
	       str->str, max_len, 
	       valid ? "TRUE" : "FALSE", offset,
	       result ? "TRUE" : "FALSE", (gint) (end - text));
      g_string_free (str, FALSE);
    }
    return failed;
}

