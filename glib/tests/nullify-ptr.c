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
#include <glib/gprintf.h>
#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/

int main (int argc, char *argv[])
{
    char *ptr;
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
	
    g_print("Test nullify-ptr Start");
    g_nullify_pointer((gpointer)&ptr);
	
	if(ptr != NULL)
	    {
        g_print("ptr is not NULL");
	    assert_failed = 1;
	    }
	
	if(assert_failed)
          g_print("Test nullify-ptr Fail");
    else
          g_print("Test nullify-ptr Successful");
	
    #if __SYMBIAN32__
    testResultXml("nullify-ptr");
    #endif /* EMULATOR */

	return 0;
}
