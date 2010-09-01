/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <glib.h>
#include <stdio.h>

#ifdef __SYMBIAN32__
#include <glib_global.h>
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/



void test_error_check_mutexes()
{
  
  GMutex* test_g_mutex_mutex = NULL;
  
  g_thread_init(NULL);	
  
  test_g_mutex_mutex = g_mutex_new ();

  g_assert (g_mutex_trylock (test_g_mutex_mutex));
//  g_assert (g_mutex_trylock (test_g_mutex_mutex) == FALSE);
  g_mutex_unlock (test_g_mutex_mutex);
  g_mutex_free (test_g_mutex_mutex);
}





int main (int   argc,
      char *argv[])
{
	#ifdef __SYMBIAN32__
	g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
	g_set_print_handler(mrtPrintHandler);
	#endif /*__SYMBIAN32__*/


	
	
	test_error_check_mutexes();
	
	#ifdef __SYMBIAN32__
  	testResultXml("error_check_mutexes");
  	#endif /* EMULATOR */
	
	return 0;
}