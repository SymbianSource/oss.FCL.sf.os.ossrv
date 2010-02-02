/* Portion Copyright � 2008-09 Nokia Corporation and/or its subsidiary(-ies). All rights reserved. */
#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <time.h>
#include <stdlib.h>

#include <glib.h>
#include <glib/gthread.h>

#define DEBUG_MSG(args)
/* #define DEBUG_MSG(args) g_printerr args ; g_printerr ("\n");  */
#define PRINT_MSG(args)
/* #define PRINT_MSG(args) g_print args ; g_print ("\n"); */

#define MAX_THREADS            50
#define MAX_SORTS              5    /* only applies if
				       ASYC_QUEUE_DO_SORT is set to 1 */ 
#define MAX_TIME               20   /* seconds */
#define MIN_TIME               5    /* seconds */

#define SORT_QUEUE_AFTER       1
#define SORT_QUEUE_ON_PUSH     1    /* if this is done, the
				       SORT_QUEUE_AFTER is ignored */
#define QUIT_WHEN_DONE         1


#if SORT_QUEUE_ON_PUSH == 1
#  undef SORT_QUEUE_AFTER
#  define SORT_QUEUE_AFTER     0
#endif

#ifdef SYMBIAN
#include "mrt2_glib2_test.h"
#endif /*SYMBIAN*/


static GMainLoop   *main_loop = NULL;
static GThreadPool *thread_pool = NULL;
static GAsyncQueue *async_queue = NULL;


static gint
sort_compare (gconstpointer p1, gconstpointer p2, gpointer user_data)
{
  gint32 id1;
  gint32 id2;

  id1 = GPOINTER_TO_INT (p1);
  id2 = GPOINTER_TO_INT (p2);

  DEBUG_MSG (("comparing #1:%d and #2:%d, returning %d", 
	     id1, id2, (id1 > id2 ? +1 : id1 == id2 ? 0 : -1)));

  return (id1 > id2 ? +1 : id1 == id2 ? 0 : -1);
}

static gboolean
sort_queue (gpointer user_data)
{
  static gint     sorts = 0;
  static gpointer last_p = NULL;
  gpointer        p;
  gboolean        can_quit = FALSE;
  gint            sort_multiplier;
  gint            len;
  gint            i;

  sort_multiplier = GPOINTER_TO_INT (user_data);

  if (SORT_QUEUE_AFTER) {
    PRINT_MSG (("sorting async queue...")); 
    g_async_queue_sort (async_queue, sort_compare, NULL);

    sorts++;

    if (sorts >= sort_multiplier) {
      can_quit = TRUE;
    }
    
    g_async_queue_sort (async_queue, sort_compare, NULL);
    len = g_async_queue_length (async_queue);

    PRINT_MSG (("sorted queue (for %d/%d times, size:%d)...", sorts, MAX_SORTS, len)); 
  } else {
    can_quit = TRUE;
    len = g_async_queue_length (async_queue);
    DEBUG_MSG (("printing queue (size:%d)...", len)); 
  }

  for (i = 0, last_p = NULL; i < len; i++) {
    p = g_async_queue_pop (async_queue);
    DEBUG_MSG (("item %d ---> %d", i, GPOINTER_TO_INT (p))); 

    if (last_p) {
      g_assert (GPOINTER_TO_INT (last_p) <= GPOINTER_TO_INT (p));
    }

    last_p = p;
  }
  
  if (can_quit && QUIT_WHEN_DONE) {
    g_main_loop_quit (main_loop);
  }

  return !can_quit;
}

static void
enter_thread (gpointer data, gpointer user_data)
{
  gint   len;
  gint   id;
  gulong ms;

  id = GPOINTER_TO_INT (data);
  
  ms = g_random_int_range (MIN_TIME * 1000, MAX_TIME * 1000);
  DEBUG_MSG (("entered thread with id:%d, adding to queue in:%ld ms", id, ms));

  g_usleep (ms * 1000);

  if (SORT_QUEUE_ON_PUSH) {
    g_async_queue_push_sorted (async_queue, GINT_TO_POINTER (id), sort_compare, NULL);
  } else {
    g_async_queue_push (async_queue, GINT_TO_POINTER (id));
  }

  len = g_async_queue_length (async_queue);

  DEBUG_MSG (("thread id:%d added to async queue (size:%d)", 
	     id, len));
}

int 
main (int argc, char *argv[])
{

   gint   i;
  gint   max_threads = MAX_THREADS;
  gint   max_unused_threads = MAX_THREADS;
  gint   sort_multiplier = MAX_SORTS;
  gint   sort_interval;
  gchar *msg;
  
  #ifdef SYMBIAN
  g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
  #endif /*SYMBIAN*/
  g_thread_init (NULL);

  PRINT_MSG (("creating async queue..."));
  async_queue = g_async_queue_new ();
  g_assert(async_queue != NULL);

  g_return_val_if_fail (async_queue != NULL, EXIT_FAILURE);

  PRINT_MSG (("creating thread pool with max threads:%d, max unused threads:%d...",
	     max_threads, max_unused_threads));
  thread_pool = g_thread_pool_new (enter_thread,
				   async_queue,
				   max_threads,
				   FALSE,
				   NULL);

  g_return_val_if_fail (thread_pool != NULL, EXIT_FAILURE);

  g_thread_pool_set_max_unused_threads (max_unused_threads);

  PRINT_MSG (("creating threads..."));
  for (i = 1; i <= max_threads; i++) {
    GError *error = NULL;
  
    g_thread_pool_push (thread_pool, GINT_TO_POINTER (i), &error);
    
    g_assert (error == NULL);
  }

  if (!SORT_QUEUE_AFTER) {
    sort_multiplier = 1;
  }
  
  sort_interval = ((MAX_TIME / sort_multiplier) + 2)  * 1000;
  g_timeout_add (sort_interval, sort_queue, GINT_TO_POINTER (sort_multiplier));

  if (SORT_QUEUE_ON_PUSH) {
    msg = "sorting when pushing into the queue, checking queue is sorted";
  } else {
    msg = "sorting";
  }

  PRINT_MSG (("%s %d %s %d ms",
	      msg,
	      sort_multiplier, 
	      sort_multiplier == 1 ? "time in" : "times, once every",
	      sort_interval));

  DEBUG_MSG (("entering main event loop"));

  main_loop = g_main_loop_new (NULL, FALSE);
  g_main_loop_run (main_loop);
 
  
  #if SYMBIAN
  testResultXml("asyncqueue-test");
  #endif /* EMULATOR */
  
  return EXIT_SUCCESS;
}
