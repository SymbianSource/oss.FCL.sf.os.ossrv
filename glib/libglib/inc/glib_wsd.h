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



#ifndef __GLIB_WSD_H__
#define __GLIB_WSD_H__

#if (defined(__SYMBIAN32__) && (defined(__WINSCW__) || defined(__WINS__)))

#include <_ansi.h>
#include <sys/cdefs.h>
#include <glib.h>

/* --------------------- MACRO DEFINATIONS ------------------------*/
#ifndef EMULATOR
#define EMULATOR (defined(__SYMBIAN32__) && (defined(__WINSCW__) || defined(__WINS__)))
#endif /* EMULATOR */

#define VARIABLE_NAME_MACRO(name,filename) s_##filename##_g__ ## name ## _lock

#define FUNCTION_NAME_MACRO(name,filename) _s_##filename##_g__ ## name ## _lock

#define VARIABLE_NAME(var,filename) s_##filename##_##var

#define FUNCTION_NAME(var,filename) _s_##filename##_##var

#define VARIABLE_DECL_MACRO(name,filename,datatype) \
datatype VARIABLE_NAME_MACRO(name,filename);

#define VARIABLE_DECL(var,filename,datatype)\
datatype VARIABLE_NAME(var,filename);

#define VARIABLE_DECL_ARRAY(name,filename,datatype,size) \
datatype VARIABLE_NAME(name,filename)[size];

#define RETURN_VAL(var,filename) (Glib_ImpurePtr()->VARIABLE_NAME(var,filename))

#define RETURN_VAL_MACRO(var,filename) (Glib_ImpurePtr()->VARIABLE_NAME_MACRO(var,filename))

#define PLS(var,filename,type) \
type *FUNCTION_NAME(var,filename)() \
{ \
return &RETURN_VAL(var,filename);\
}

#define PLS_MACRO(var,filename,type) \
type *FUNCTION_NAME_MACRO(var,filename)() \
{ \
return &RETURN_VAL_MACRO(var,filename);\
}

#define PLS_ARRAY(var,filename,type) \
type *FUNCTION_NAME(var,filename)() \
{ \
return RETURN_VAL(var,filename);\
}
/* --------------------- END MACRO DEFINATIONS ------------------------*/

typedef struct _GDataset GDataset;
struct _GDataset
{
  gconstpointer location;
  GData        *datalist;
};

struct _GAllocator {
    gchar      *name;
    guint16     n_preallocs;
    guint       is_unused : 1;
    guint       type : 4;
    GAllocator *last;
    GMemChunk  *mem_chunk;
    gpointer    free_list;
  };

typedef struct _GLogDomain	GLogDomain;
typedef struct _GLogHandler	GLogHandler;

struct _GLogDomain
{
  gchar		*log_domain;
  GLogLevelFlags fatal_mask;
  GLogHandler	*handlers;
  GLogDomain	*next;
};

struct _GLogHandler
{
  guint		 id;
  GLogLevelFlags log_level;
  GLogFunc	 log_func;
  gpointer	 data;
  GLogHandler	*next;
};

typedef struct _GRealThread GRealThread;
struct  _GRealThread
{
  GThread thread;
  gpointer private_data;
  GRealThread *next;
  gpointer retval;
  GSystemThread system_thread;
};

typedef struct _ChunkLink      ChunkLink;
typedef struct _SlabInfo       SlabInfo;

struct _ChunkLink {
  ChunkLink *next;
  ChunkLink *data;
};
struct _SlabInfo {
  ChunkLink *chunks;
  guint n_allocated;
  SlabInfo *next, *prev;
};

typedef struct {
  gboolean always_malloc;
  gboolean bypass_magazines;
  gsize    working_set_msecs;
  guint    color_increment;
} SliceConfig;
typedef struct {
  /* const after initialization */
  gsize         min_page_size, max_page_size;
  SliceConfig   config;
  gsize         max_slab_chunk_size_for_magazine_cache;
  /* magazine cache */
  GMutex       *magazine_mutex;
  ChunkLink   **magazines;                /* array of MAX_SLAB_INDEX (allocator) */
  guint        *contention_counters;      /* array of MAX_SLAB_INDEX (allocator) */
  gint          mutex_counter;
  guint         stamp_counter;
  guint         last_stamp;
  /* slab allocator */
  GMutex       *slab_mutex;
  SlabInfo    **slab_stack;                /* array of MAX_SLAB_INDEX (allocator) */
  guint        color_accu;
} Allocator;



struct global_struct
{
	
	//Global dsta of gatomic.c
	VARIABLE_DECL(g_atomic_mutex , gatomic,GMutex *)

	//Global variable of gbacktrace.c
	VARIABLE_DECL(glib_on_error_halt,gbacktrace,volatile gboolean)

	//Global data of gconvert.c
	VARIABLE_DECL(quark,g_convert_error_quark,GQuark)
	VARIABLE_DECL(cache_private,g_get_filename_charsets,GStaticPrivate)
	
	//Global data of gdataset.c
	VARIABLE_DECL_MACRO(g_dataset_global,gdataset,GStaticMutex)
	VARIABLE_DECL(g_dataset_location_ht,gdataset,GHashTable *)
	VARIABLE_DECL(g_dataset_cached,gdataset,GDataset *)
	VARIABLE_DECL_MACRO(g_quark_global,gdataset,GStaticMutex)
	VARIABLE_DECL(g_quark_ht,gdataset,GHashTable *)
	VARIABLE_DECL(g_quarks,gdataset,gchar **)
	VARIABLE_DECL(g_quark_seq_id,gdataset,GQuark)

	//Global data of gdate.c
	VARIABLE_DECL_MACRO(g_date_global,gdate,GStaticMutex)
	VARIABLE_DECL_ARRAY(long_month_names, gdate, gchar *,13)
	VARIABLE_DECL_ARRAY(short_month_names, gdate, gchar *,13)
	VARIABLE_DECL(current_locale,gdate, gchar *)
	VARIABLE_DECL_ARRAY(dmy_order, gdate, GDateDMY,3)
	VARIABLE_DECL(using_twodigit_years,gdate, gboolean)
	VARIABLE_DECL(locale_era_adjust,gdate, gint)

	//Global data of gfileutils.c
	VARIABLE_DECL(q,g_file_error_quark ,GQuark)
	VARIABLE_DECL(counter ,create_temp_file,int)

	//Global data of giochannel.c
	VARIABLE_DECL(q,g_io_channel_error_quark ,GQuark)

	//Global data of giounix.c
	VARIABLE_DECL(unix_channel_funcs,giounix,GIOFuncs )
	VARIABLE_DECL(g_io_watch_funcs,giounix,GSourceFuncs)

	//Global data of gkeyfile.c
	VARIABLE_DECL(error_quark ,g_key_file_error_quark,GQuark)

	//Global data of gmain.c
	VARIABLE_DECL_MACRO(main_loop,gmain,GStaticMutex)
	VARIABLE_DECL(default_main_context,gmain,GMainContext *)
	VARIABLE_DECL(main_contexts_without_pipe,gmain,GSList *)
	VARIABLE_DECL_MACRO(main_context_list,gmain,GStaticMutex)
	VARIABLE_DECL(main_context_list,gmain,GSList *)
	VARIABLE_DECL(depth_private,get_depth_pointer ,GStaticPrivate)
	VARIABLE_DECL(g_source_callback_funcs,gmain,GSourceCallbackFuncs)
	VARIABLE_DECL(g_timeout_funcs,gmain,GSourceFuncs)
	VARIABLE_DECL(g_child_watch_funcs ,gmain,GSourceFuncs)
	VARIABLE_DECL(g_idle_funcs,gmain,GSourceFuncs)

	//Global data of gmarkup.c
	VARIABLE_DECL(error_quark ,g_markup_error_quark,GQuark)

	//Global data of gmem.c
	VARIABLE_DECL(glib_mem_vtable,gmem,GMemVTable)
	VARIABLE_DECL(vtable_set ,gmem,gboolean)
	VARIABLE_DECL(profile_data ,gmem,guint *)
	VARIABLE_DECL(profile_allocs  ,gmem,gulong)
	VARIABLE_DECL(profile_zinit ,gmem,gulong)
	VARIABLE_DECL(profile_frees  ,gmem,gulong)
	VARIABLE_DECL(gmem_profile_mutex  ,gmem,GMutex *) 
	VARIABLE_DECL(profiler_table,gmem,GMemVTable)
	VARIABLE_DECL(glib_mem_profiler_table,gmem,GMemVTable *)
	VARIABLE_DECL(g_mem_initialized ,gmem,gboolean)
	VARIABLE_DECL(g_mem_gc_friendly ,gmem,gboolean)
	VARIABLE_DECL(dummy ,g_allocator_new,struct _GAllocator)

	 //Global data of gmessages.c
  	VARIABLE_DECL(g_messages_lock,gmessages,GMutex *)
	VARIABLE_DECL(g_log_domains,gmessages,GLogDomain *)
	VARIABLE_DECL(g_log_always_fatal,gmessages,GLogLevelFlags)
	VARIABLE_DECL(glib_print_func,gmessages,GPrintFunc)
	VARIABLE_DECL(glib_printerr_func,gmessages,GPrintFunc)
	VARIABLE_DECL(g_log_depth,gmessages,GPrivate *)
	VARIABLE_DECL(g_log_msg_prefix,gmessages,GLogLevelFlags)
	VARIABLE_DECL(default_log_func,gmessages,GLogFunc)
	VARIABLE_DECL(default_log_data,gmessages,gpointer)
	VARIABLE_DECL(initialized ,g_messages_prefixed_init,gboolean)
	VARIABLE_DECL(handler_id,g_log_set_handler,guint)
	VARIABLE_DECL(warned,strdup_convert,gboolean)
	VARIABLE_DECL(_g_debug_initialized ,gmessages,gboolean)
	VARIABLE_DECL(_g_debug_flags,gmessages,guint)

	//Global data of goption.c
	VARIABLE_DECL(q,g_option_error_quark,GQuark)

	//Global data of grand.c
	VARIABLE_DECL_MACRO(global_random,grand,GStaticMutex)
	VARIABLE_DECL(global_random,grand,GRand *)
	VARIABLE_DECL(initialized ,get_random_version,gboolean)
	VARIABLE_DECL(random_version ,get_random_version,guint)
	VARIABLE_DECL(dev_urandom_exists,g_rand_new ,gboolean)

	//Global data of gscanner.c
	VARIABLE_DECL(g_scanner_config_template ,gscanner,GScannerConfig)

	//Global data of gshell.c
	VARIABLE_DECL(quark,g_shell_error_quark ,GQuark)

	//Global data of gspawn-symbian.c
	VARIABLE_DECL(debug,gspawn_symbian,int)
	VARIABLE_DECL(quark,g_spawn_error_quark ,GQuark)
	VARIABLE_DECL(warned_about_child_setup ,do_spawn_with_pipes,gboolean)

	//Global data of gthread.c
	VARIABLE_DECL(quark,g_thread_error_quark ,GQuark)
	VARIABLE_DECL(zero_thread,gthread,GSystemThread)
	VARIABLE_DECL(g_once_mutex,gthread,GMutex *)
	VARIABLE_DECL(g_once_cond,gthread,GCond *)
	VARIABLE_DECL(g_thread_specific_private ,gthread,GPrivate *)
	VARIABLE_DECL(g_thread_all_threads,gthread,GRealThread *)
	VARIABLE_DECL(g_thread_free_indeces,gthread,GSList *)
	VARIABLE_DECL_MACRO(g_thread,gthread,GStaticMutex)
	VARIABLE_DECL(next_index ,g_static_private_set,guint)
	VARIABLE_DECL(g_thread_use_default_impl,gthread,gboolean)
	VARIABLE_DECL(g_threads_got_initialized,gthread,gboolean)
	VARIABLE_DECL(g_thread_functions_for_glib_use,gthread,GThreadFunctions)

	//Global data of Gthreadpool.c
	VARIABLE_DECL(wakeup_thread_serial,gthreadpool,gint)
	VARIABLE_DECL(unused_thread_queue,gthreadpool,GAsyncQueue *)
	VARIABLE_DECL(unused_threads,gthreadpool,gint)
	VARIABLE_DECL(max_unused_threads,gthreadpool,gint)
	VARIABLE_DECL(kill_unused_threads,gthreadpool,gint)
	VARIABLE_DECL(max_idle_time,gthreadpool,guint)
	VARIABLE_DECL_MACRO(init,g_thread_pool_new,GStaticMutex)

	//Global data of gutf8.c
	VARIABLE_DECL_MACRO(aliases,gutf8,GStaticMutex)
	VARIABLE_DECL(alias_hash,get_alias_hash,GHashTable *)
	VARIABLE_DECL(cache_private,g_get_charset,GStaticPrivate)

	//Global data of gutils.c
	VARIABLE_DECL_MACRO(g_utils_global,gutils,GStaticMutex)
	VARIABLE_DECL(g_tmp_dir,gutils,gchar *)
	VARIABLE_DECL(g_user_name,gutils,gchar *)
	VARIABLE_DECL(g_real_name,gutils,gchar *)
	VARIABLE_DECL(g_home_dir,gutils,gchar *)
	VARIABLE_DECL(g_host_name,gutils,gchar *)
	VARIABLE_DECL(g_user_data_dir ,gutils,gchar *)
	VARIABLE_DECL(g_system_data_dirs,gutils,gchar **)
	VARIABLE_DECL(g_user_cache_dir,gutils,gchar *)
	VARIABLE_DECL(g_user_config_dir,gutils,gchar *)
	VARIABLE_DECL(g_system_config_dirs,gutils,gchar **)
	VARIABLE_DECL_MACRO(g_prgname,gutils,GStaticMutex)
	VARIABLE_DECL(g_prgname,gutils,gchar *)
	VARIABLE_DECL_MACRO(g_application_name ,gutils,GStaticMutex)
	VARIABLE_DECL(g_application_name ,gutils,gchar *)
	VARIABLE_DECL(alias_table ,gutils,GHashTable *)
	VARIABLE_DECL(said_before ,unalias_lang,gboolean)
	VARIABLE_DECL(cache_private ,g_get_language_names ,GStaticPrivate)
	VARIABLE_DECL(max_len,g_get_current_dir ,gulong)
	VARIABLE_DECL(_glib_gettext_initialized,_glib_gettext,gboolean)

	//Global data of localcharset.c
	VARIABLE_DECL(charset_aliases,localcharset,const char * volatile)

	//Global data of gstrfuncs.c
	VARIABLE_DECL(msg_private ,g_strerror,GStaticPrivate)
	VARIABLE_DECL(msg_private ,g_strsignal,GStaticPrivate)

	//Global data of gslice.c
	VARIABLE_DECL(private_thread_memory,gslice,GPrivate *)
	VARIABLE_DECL(sys_page_size,gslice,gsize)
	VARIABLE_DECL_ARRAY(allocator,gslice,Allocator,1)
	VARIABLE_DECL(slice_config,gslice,SliceConfig)
	VARIABLE_DECL(compat_valloc_trash,gslice,GTrashStack *)

};

__BEGIN_DECLS
struct global_struct *Glib_ImpurePtr();
__END_DECLS
#endif /* EMULATOR */

#endif /* __GLIB_WSD_H__ */