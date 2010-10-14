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

#include <glib.h>
#include <errno.h>
#include <sys/stat.h>
#include <glib/gprintf.h>
#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/

int main (int argc, char *argv[])
{
    char appName[] = "TestApp";
    const char *retAppName;
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
    
    g_print("Test app-name Start");
    g_set_application_name(appName);
    
    retAppName = g_get_application_name();
	
	if(retAppName != NULL)
	    {
        if(g_strcmp0(appName, retAppName) !=0 )
            {
            g_print( "g_get_application_name returned wrong name");
            assert_failed = 1;
            }
	    }
	else
	    {
        g_print( "g_get_application_name returned NULL. errno  = %d", errno);
        assert_failed = 1;
	    }
	
	g_free((void *)retAppName);
	
	if(assert_failed)
          g_print("Test app-name Failed");
    else
          g_print("Test app-name Successful");
	
    #if __SYMBIAN32__
	testResultXml("app-name");
    #endif /* EMULATOR */

	return 0;
}
