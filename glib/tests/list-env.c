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
    const gchar *variable1 = "TEST_VAR1";
    gchar *value1 = "testvalue1";
    const gchar *variable2 = "TEST_VAR2";
    gchar *value2 = "testvalue2";
    gchar **env_list;
    gint i, found = 0;
    guint no_of_variables =0;
    gboolean found_var1 = 0,  found_var2 = 0;
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
    
    g_print("Test list-env Start");
    if(g_setenv (variable1, value1, TRUE) && g_setenv (variable2, value2, TRUE))
        {
        env_list = g_listenv();
        
        if(env_list)
            {
            no_of_variables = g_strv_length(env_list);
            
            if(no_of_variables)
                {
                for(i = 0; i<no_of_variables; i++)
                    {
                    gchar *data = env_list[i];
                    
                    if(g_strcmp0(data, variable1) == 0)
                        found_var1 = 1;
                    else if(g_strcmp0(data, variable2) == 0)
                        found_var2 = 1;
                    }
                
                if(!(found_var1 && found_var2))
                    {
                    g_print( "g_listenv failed");
                    assert_failed = 1;
                    }
                }
            else
                {
                g_print( "g_listenv returned list is of length 0");
                assert_failed = 1;
                }
            
            g_strfreev(env_list);
            }
        else
            {
            g_print( "g_listenv returned NULL");
            assert_failed = 1;
            }
        }
    else
        {
        g_print( "setting env variable failed. errno = %d", errno);
        }
    
    if(assert_failed)
          g_print("Test list-env Failed");
    else
          g_print("Test list-env Successful");
	
    #if __SYMBIAN32__
    testResultXml("list-env");
    #endif /* EMULATOR */

	return 0;
}
