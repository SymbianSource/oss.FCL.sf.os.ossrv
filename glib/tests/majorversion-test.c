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
#include <stdio.h>
#include "glib.h"
#include <glib/gprintf.h>
#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/

int
main (int   argc,
      char *argv[])
    {
    const guint *major_version = NULL;
    const guint *minor_version = NULL;
    const guint *micro_version = NULL;
    const guint *interface_age = NULL;
    const guint *binary_age = NULL;
    const gchar *check_version = NULL;
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
    
    g_print("Test majorversion-test Start");
    major_version = _glib_major_version();
    minor_version = _glib_minor_version(); 
    micro_version = _glib_micro_version();
    interface_age = _glib_interface_age();
    binary_age    = _glib_binary_age();  
    g_print("Binary age :%d\n Interface age:%d",*binary_age,*interface_age);
    check_version = glib_check_version((*major_version),(*minor_version),(*micro_version));
    if(check_version != NULL)
        {
        g_print("GLib library in use is not compatible with the given verison");
        assert_failed = 1;
        }
    if(assert_failed)
        {
        g_print("%s",check_version);
        g_print("Test majorversion-test Fail");
        }
    else
        g_print("Test majorversion-test Successful");          
    
    #if __SYMBIAN32__
    testResultXml("majorversion-test");
    #endif /* EMULATOR */
    return 0;
    }
    

