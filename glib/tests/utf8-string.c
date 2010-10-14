// Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <sys/stat.h>
#include <glib.h>
#include <errno.h>
#include <glib/gprintf.h>
#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/

int main (int argc, char *argv[])
{
    gchar *src = "TestString";
    gchar dest[20];
    gchar *p;
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
    
    g_print("Test utf8-string Start");
    p = g_utf8_strncpy(dest, src, strlen(src));
    
    if(p == dest)
        {
        if(strcmp(dest, src))
            {
            g_print("g_utf8_strncpy didnt work as expected");
            assert_failed = 1;
            }
        }
    else
        {
        g_print("g_utf8_strncpy's return value is invalid");
        assert_failed = 1;
        }
    
    p = NULL;
    p = g_utf8_strrchr(src, strlen(src), 't');
    if(strcmp(p, "tring"))
        {
        g_print("g_utf8_strrchr didnt work as expected");
        assert_failed = 1;
        }
    
	if(assert_failed)
          g_print("Test utf8-string Failed");
    else
          g_print("Test utf8-string Successful");
	
    #if __SYMBIAN32__
    testResultXml("utf8-string");
    #endif /* EMULATOR */

	return 0;
}
