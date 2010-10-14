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

static void
gstring_overwrite_int (GString *gstring,
                       guint    pos,
                       guint32  vuint)
{
  vuint = g_htonl (vuint);
  g_string_overwrite_len (gstring, pos, (const gchar*) &vuint, 4);
}

static void
gstring_append_int (GString *gstring,
                    guint32  vuint)
{
  vuint = g_htonl (vuint);
  g_string_append_len (gstring, (const gchar*) &vuint, 4);
}

static void
gstring_append_double (GString *gstring,
                       double   vdouble)
{
  union { double vdouble; guint64 vuint64; } u;
  u.vdouble = vdouble;
  u.vuint64 = GUINT64_TO_BE (u.vuint64);
  g_string_append_len (gstring, (const gchar*) &u.vuint64, 8);
}

static guint8*
g_test_log_dump (GTestLogMsg *msg,
                 guint       *len)
{
  GString *gstring = g_string_sized_new (1024);
  guint ui;
  gstring_append_int (gstring, 0);              /* message length */
  gstring_append_int (gstring, msg->log_type);
  gstring_append_int (gstring, msg->n_strings);
  gstring_append_int (gstring, msg->n_nums);
  gstring_append_int (gstring, 0);      /* reserved */
  for (ui = 0; ui < msg->n_strings; ui++)
    {
      guint l = strlen (msg->strings[ui]);
      gstring_append_int (gstring, l);
      g_string_append_len (gstring, msg->strings[ui], l);
    }
  for (ui = 0; ui < msg->n_nums; ui++)
    gstring_append_double (gstring, msg->nums[ui]);
  *len = gstring->len;
  gstring_overwrite_int (gstring, 0, *len);     /* message length */
  return (guint8*) g_string_free (gstring, FALSE);
}

void start_timer()
    {
    GTimer *timer;
    timer = g_timer_new ();
    g_timer_start(timer);
    g_timer_stop(timer);
    }

void test_g_test_trap()
    {
    if(g_test_trap_fork(0, G_TEST_TRAP_SILENCE_STDOUT))
        {
        exit(0);
        }
    
    if(!g_test_trap_has_passed())
        {
        g_print( "g_test_trap_has_passed didnt work as expected");
        assert_failed = 1;
        }
    }

void test_g_test_log_type_name()
    {
    const char *ret;
    ret = g_test_log_type_name(G_TEST_LOG_MESSAGE);
    
    if(strcmp(ret, "message"))
        {
        g_print( "g_test_log_type_name didnt work as expected");
        assert_failed = 1;
        }
    }

void test_g_test_timer()
    {
    double ret_time1, ret_time2;
    
    g_test_timer_start();
    ret_time1 = g_test_timer_elapsed();
    ret_time2 = g_test_timer_last();
    
    if(!(ret_time1 == ret_time2))
        {
        g_print( "g_test_timer* didnt work as expected");
        assert_failed = 1;
        }
    }

void test_g_log_buffer()
    {
    GTestLogBuffer* log_buffer;
    GTestLogMsg* log_msg;
	GTestLogMsg msg_ip;
    gchar *astrings[1] = {NULL};
    guint8 *dbuffer;
    guint dbufferlen;
    int i;

    msg_ip.log_type = G_TEST_LOG_MESSAGE;
    msg_ip.n_strings = 1;
    msg_ip.strings = astrings;
    astrings[0] = (gchar*) "test-log-some-dummy-log";
    msg_ip.n_nums = 0;
    msg_ip.nums = 0;
    dbuffer = (guint8*)g_test_log_dump(&msg_ip, &dbufferlen);
    
    log_buffer = g_test_log_buffer_new();
    
    if(log_buffer)
        {
        g_test_log_buffer_push(log_buffer, dbufferlen, (const guint8*)dbuffer);
            
        log_msg = g_test_log_buffer_pop(log_buffer);
        
        if(log_msg)
            {
            g_test_log_msg_free(log_msg);
            }
        else
            {
            g_print( "g_test_log_buffer_pop returned NULL");
            assert_failed = 1;
            }
        
        g_test_log_buffer_free(log_buffer);
        }
    else
        {
        g_print( "g_test_log_buffer_new returned NULL");
        assert_failed = 1;
        }

	g_free (dbuffer);
    }

int main (int argc, char *argv[])
{
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
    
    g_print("Test test-utils Start");
    g_test_init(&argc, &argv);
    
    test_g_test_trap();
    test_g_test_log_type_name();
    test_g_test_timer();
    test_g_log_buffer();
    
    if(assert_failed)
          g_print("Test test-utils Failed");
    else
          g_print("Test test-utils Successful");
	
    #if __SYMBIAN32__
    testResultXml("test-utils");
    #endif /* EMULATOR */

	return 0;
}
