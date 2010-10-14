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
#include <stdlib.h>
#include <glib.h>
#include <errno.h>
#include <glib/gprintf.h>
#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/

int main (int argc, char *argv[])
{
    gchar *uri = "http:\\\\www.no!ki@a.com";
    gchar *res_str = ":\\";
    char *p;
    char *q;
    char *escape_str;
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
    
    g_print("Test uri-funcs Start");
    p = g_uri_parse_scheme(uri);
    
    if(p)
        {
        if(strcmp(p, "http"))
            {
            g_print("g_uri_parse_scheme didnt work as expected");
            assert_failed = 1;
            }
        free(p);
        }
    else
        {
        g_print("g_uri_parse_scheme returnd NULL. errno = %d", errno);
        assert_failed = 1;
        }
    
    
    //escape the uri
    escape_str = g_uri_escape_string(uri, res_str, TRUE);
    
    if(escape_str)
        {
        g_print( "escape string %s", escape_str);
        
        //convert back only a segment
        q = g_uri_unescape_segment(escape_str, escape_str+16, NULL);
        if(q)
            {
            g_print( "unescape segment string %s", q);
            if(strcmp(q, "http:\\\\www.no!"))
                {
                g_print("g_uri_unescape_segment didnt work as expected");
                assert_failed = 1;
                }
            free(q);
            }
        else
            {
            g_print("g_uri_unescape_segment returned NULL. errno = %d", errno);
            assert_failed = 1;
            }
        
        //convert back the whole string
        p = g_uri_unescape_string(escape_str, NULL);
        if(p)
            {
            g_print( "unescape string %s", p);
            
            //converted string should be same as original uri string
            if(strcmp(p, uri))
                {
                g_print("g_uri_unescape_string returned NULL");
                assert_failed = 1;
                }
            
            free(p);
            }
        else
            {
            g_print("g_uri_unescape_string returned NULL. errno = %d", errno);
            assert_failed = 1;
            }
        
        free(escape_str);
        }
    else
        {
        g_print("g_uri_escape_string returned NULL. errno = %d", errno);
        assert_failed = 1;
        }
    
	if(assert_failed)
          g_print("Test uri-funcs Failed");
    else
          g_print("Test uri-funcs Successful");
	
    #if __SYMBIAN32__
    testResultXml("uri-funcs");
    #endif /* EMULATOR */

	return 0;
}
