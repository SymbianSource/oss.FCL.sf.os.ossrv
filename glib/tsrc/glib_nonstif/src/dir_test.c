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

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "glib.h"

#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/


int main (int   argc,char *argv[])
{
	GDir *dir;
	GError *error;	
	int ret;
	ret = mkdir("c:\\temp", 0666);
	g_print("mkdir for temp returns %d and error is %d", ret, errno);
	ret = mkdir("c:\\temp\\tmp", 0666);
	g_print("mkdir for temp returns %d and error is %d", ret, errno);
	#ifdef __SYMBIAN32__
	g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
	g_set_print_handler(mrtPrintHandler);	
	#endif /*SYMBIAN*/
	
	dir = g_dir_open("c:\\temp",0,&error);
	
	g_assert(dir != NULL);
	
	g_assert(!strcmp(g_dir_read_name(dir),"tmp"));
	
	g_dir_close(dir);
	
	#if __SYMBIAN32__
  	testResultXml("dir_test");
  	#endif /* EMULATOR */

	rmdir("c:\\temp\\tmp");
	rmdir("c:\\temp");
	return 0;
}