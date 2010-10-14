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
#include <string.h>
#include <glib/gprintf.h>
#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/

#define MAX_FILENAME_LENGTH	256
#define MAX_PATH_LENGTH		256

int main (int argc, char *argv[])
{
	char folder_name[] = "c:\\example\\test\\";
	char file_name[]   = "test.txt";
	const gchar *ret_file_name;

	gchar input_file[MAX_PATH_LENGTH];
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
	
    g_print("Test base-name Start");
    sprintf(input_file, "%s%s", folder_name, file_name);

	ret_file_name = g_basename(input_file);
	
	if(ret_file_name != NULL)
	    {
        if(g_strcmp0(ret_file_name, file_name) !=0 )
            {
            g_print( "g_basename returned wrong file name");
            assert_failed = 1;
            }
	    }
	else
	    {
        g_print( "g_basename returned NULL. errno  = %d", errno);
        assert_failed = 1;
	    }

	
	if(assert_failed)
          g_print("Test base-name Failed");
    else
          g_print("Test base-name Successful");
	
    #if __SYMBIAN32__
    testResultXml("base-name");
    #endif /* EMULATOR */

	return 0;
}
