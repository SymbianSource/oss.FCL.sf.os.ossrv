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


#include <sys/stat.h>
#include<stdio.h>
#include <glib.h>
#include <glib/gprintf.h>
#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/
#define in_FILE "file.xbel"

int
main (int   argc,
      char *argv[])
    {
    GBookmarkFile* bookmark;
    gsize uris_len;
    gchar *bookmark_data = NULL;
    gboolean file_written,file_load;
    const gchar *rel_path;
    time_t time;
    const gchar *bookmark_filename = argv[1];
    GError        *error = NULL;
    gchar **bookmark_uri = NULL;
    
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
    
    g_print("Test bookmarkfile-test1 Start");
    bookmark = g_bookmark_file_new();
    file_load= g_bookmark_file_load_from_file(bookmark, bookmark_filename, &error);
    if(file_load != TRUE)
        {
        g_print("g_bookmark_file_load_from_file fails with err:%s",error->message);
        assert_failed = 1;
        }
    bookmark_data = g_bookmark_file_to_data(bookmark,&uris_len,&error);
    if(bookmark_data == NULL)
        {
        g_print("Bg_bookmark_file_to_data fails with err:%s",error->message);
        assert_failed = 1;
        }
    rel_path = in_FILE; // Code changed to Hardcode the data file in the c:\ private path. 
    file_written = g_bookmark_file_load_from_data_dirs(bookmark, rel_path,NULL, &error);
    if(file_written == FALSE)
           {
           g_print("g_bookmark_file_load_from_data_dirs fails with err:%s",error->message);
           assert_failed = 1;
           }
    
    bookmark_uri = g_bookmark_file_get_uris(bookmark, NULL);
    if(bookmark_uri == NULL)
            {
            g_print("g_bookmark_file_get_uris fails");
            assert_failed = 1;
            }
          
    bookmark_data = g_bookmark_file_get_mime_type(bookmark,*bookmark_uri,&error);
    if(bookmark_data == NULL)
        {
        g_print("URI cannot be found and the error code:%s",error->message);
        assert_failed = 1;
        }
    g_bookmark_file_set_is_private(bookmark,*bookmark_uri, TRUE);
    file_written = g_bookmark_file_get_is_private(bookmark,*bookmark_uri, &error);
    if(file_written == FALSE)
        {
        g_print("Private flag is not set in the URI and fails with :%s",error->message);
        assert_failed = 1;
        }
    
    g_bookmark_file_set_added(bookmark,*bookmark_uri,-1);//-1, To use the current time.
    time = g_bookmark_file_get_added(bookmark,*bookmark_uri,&error);
    if(time == -1)
        {
        g_print("URI cannot be found and fails with :%s",error->message);
        assert_failed = 1;
        } 
    g_strfreev(bookmark_uri);  
    g_bookmark_file_free(bookmark);
    
    if(assert_failed)
        g_print("Test bookmarkfile-test1 Fail");
    else
        g_print("Test bookmarkfile-test1 Successful");         
   
    #if __SYMBIAN32__
    testResultXml("bookmarkfile-test1");
    #endif /* EMULATOR */
    return 0;
    }
