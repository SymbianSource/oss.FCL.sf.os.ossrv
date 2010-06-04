/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
*
*/

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>

#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/


int main (int argc, char **argv)
{
  FILE *infile;
  char buffer[1024];
  char **strings;
  char *srcdir = getenv ("srcdir");
  char *filename;
  const char *locale;
  const char *test;
  const char *expected;
  char *convert;
  char *current_locale = setlocale (LC_CTYPE, NULL);
  gint result = 0;
	#ifdef __SYMBIAN32__

  g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
  g_set_print_handler(mrtPrintHandler);
  #endif /*__SYMBIAN32__*/
  	
  
  if (!srcdir)
    srcdir = "c:";
  filename = g_strconcat (srcdir, G_DIR_SEPARATOR_S, "casemap.txt", NULL);
  
  infile = fopen (filename, "r");
  if (!infile)
    {
      fprintf (stderr, "Failed to open %s\n", filename );
      g_assert(FALSE && "unicode-caseconv failed");
      #ifdef __SYMBIAN32__
  	  testResultXml("unicode-caseconv");
  	  #endif /* EMULATOR */
      exit (1);
    }
  
  while (fgets (buffer, sizeof(buffer), infile))
    {
      if (buffer[0] == '#')
	continue;

      strings = g_strsplit (buffer, "\t", -1);

      locale = strings[0];

      if (!locale[0])
	locale = "C";
	
      if (strcmp (locale, current_locale) != 0)
	{
	  setlocale (LC_CTYPE, locale);
	  current_locale = setlocale (LC_CTYPE, NULL);

	  if (strncmp (current_locale, locale, 2) != 0)
	    {
	      fprintf (stderr, "Cannot set locale to %s, skipping\n", locale);
	      goto next;
	    }
	}
      
      test = strings[1];

      /* gen-casemap-txt.pl uses an empty string when a single character
       * doesn't have an equivalent in a particular case; since that behavior
       * is nonsense for multicharacter strings, it would make more sense
       * to put the expected result .. the original character unchanged. But 
       * for now, we just work around it here and take the empty string to mean
       * "same as original"
       */

      convert = g_utf8_strup (test, -1);
      expected = strings[4][0] ? strings[4] : test;
      if (strcmp (convert, expected) != 0)
	{
	  fprintf (stderr, "Failure: toupper(%s) == %s, should have been %s\n",
		   test, convert, expected);
	  result = 1;
	}
      g_free (convert);

      convert = g_utf8_strdown (test, -1);
      expected = strings[2][0] ? strings[2] : test;
      if (strcmp (convert, expected) != 0)
	{
	  fprintf (stderr, "Failure: tolower(%s) == %s, should have been %s\n",
		   test, convert, expected);
	  result = 1;
	}
      g_free (convert);

    next:
      g_strfreev (strings);
    }

  fclose (infile);

  g_free (filename);
  filename = g_strconcat (srcdir, G_DIR_SEPARATOR_S, "casefold.txt", NULL);
  
  infile = fopen (filename, "r");
  if (!infile)
    {
      fprintf (stderr, "Failed to open %s\n", filename );
	  g_assert(FALSE && "unicode-caseconv failed");
	  #ifdef __SYMBIAN32__
  	  testResultXml("unicode-caseconv");
      #endif /* EMULATOR */
      
      exit (1);
    }
  
  while (fgets (buffer, sizeof(buffer), infile))
    {
      if (buffer[0] == '#')
	continue;

      buffer[strlen(buffer) - 1] = '\0';
      strings = g_strsplit (buffer, "\t", -1);

      test = strings[0];

      convert = g_utf8_casefold (test, -1);
      if (strcmp (convert, strings[1]) != 0)
	{
	  fprintf (stderr, "Failure: casefold(%s) == '%s', should have been '%s'\n",
		   test, convert, strings[1]);
	  result = 1;
	}
      g_free (convert);

      g_strfreev (strings);
    }

  fclose (infile);
  g_free (filename);

	#ifdef __SYMBIAN32__
  			testResultXml("unicode-caseconv");
  	 #endif /* EMULATOR */
  
  return result;
}
