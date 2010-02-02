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





#include <e32std.h>
#include <_ansi.h>
#include <glib.h>
#include "glib_wsd.h"
#include <stdlib.h>
#include <string.h>


#if EMULATOR
#include <pls.h> // For emulator WSD API 
const TUid KLibglibUid3 = {0x10281F2C};     // This is the UID of the library

G_BEGIN_DECLS
extern const GSourceFuncs temp_g_io_watch_funcs;
extern const GIOFuncs temp_unix_channel_funcs;
extern const GSourceFuncs temp_g_timeout_funcs;
extern const GSourceFuncs temp_g_child_watch_funcs;
extern const GSourceFuncs temp_g_idle_funcs;
extern const GSourceCallbackFuncs temp_g_source_callback_funcs;
extern const GMemVTable temp_glib_mem_vtable;
extern const GMemVTable temp_profiler_table;
extern const GThreadFunctions temp_g_thread_functions_for_glib_use;

void InitializeGlobalStaticMutexes(struct global_struct* g)
{
	GStaticMutex temp_init_mutex = { NULL, PTHREAD_MUTEX_INITIALIZER };

	GStaticRWLock temp_init_lock = {G_STATIC_MUTEX_INIT, NULL, NULL, 0, FALSE, 0, 0};
	
	//variable initialization for gdataset.c
	memcpy(&(g->VARIABLE_NAME_MACRO(g_dataset_global, gdataset)), &temp_init_mutex, sizeof(GStaticMutex));
	memcpy(&(g->VARIABLE_NAME_MACRO(g_quark_global, gdataset)), &temp_init_mutex, sizeof(GStaticMutex));
	
	//variable initialization for gdate.c
	memcpy(&(g->VARIABLE_NAME_MACRO(g_date_global, gdate)), &temp_init_mutex, sizeof(GStaticMutex));
	
	//variable initialization for gmain.c global data
	memcpy(&(g->VARIABLE_NAME_MACRO(main_loop, gmain)), &temp_init_mutex, sizeof(GStaticMutex));
	memcpy(&(g->VARIABLE_NAME_MACRO(main_context_list, gmain)), &temp_init_mutex, sizeof(GStaticMutex));
	
	//variable initialization for grand.c
	memcpy(&(g->VARIABLE_NAME_MACRO(global_random, grand)), &temp_init_mutex, sizeof(GStaticMutex));
	
	//variable initialization for gthread.c
	memcpy(&(g->VARIABLE_NAME_MACRO(g_thread, gthread)), &temp_init_mutex, sizeof(GStaticMutex));
	
	//variable initialization for gthreadpool.c
	memcpy(&(g->VARIABLE_NAME_MACRO(init, g_thread_pool_new)), &temp_init_mutex, sizeof(GStaticMutex));
	
	//variable initialization for gutf8.c
	memcpy(&(g->VARIABLE_NAME_MACRO(aliases, gutf8)), &temp_init_mutex, sizeof(GStaticMutex));
	
	//variable initialization for gutils.c
	memcpy(&(g->VARIABLE_NAME_MACRO(g_utils_global, gutils)), &temp_init_mutex, sizeof(GStaticMutex));
	memcpy(&(g->VARIABLE_NAME_MACRO(g_prgname, gutils)), &temp_init_mutex, sizeof(GStaticMutex));
	memcpy(&(g->VARIABLE_NAME_MACRO(g_application_name, gutils)), &temp_init_mutex, sizeof(GStaticMutex));
	
}


int InitializeWsd(struct global_struct* g)
{
	memset(g,0,sizeof(struct global_struct));

	//variable initialization for gbacktrace.c global data
	g->VARIABLE_NAME(glib_on_error_halt,gbacktrace) = TRUE ;
	
	//variable initialization for gdate.c global data
	g->VARIABLE_NAME(long_month_names,gdate)[0] = "Error";
	g->VARIABLE_NAME(short_month_names,gdate)[0] = "Error";
	g->VARIABLE_NAME(dmy_order,gdate)[0] = G_DATE_DAY;
	g->VARIABLE_NAME(dmy_order,gdate)[1] = G_DATE_MONTH;
	g->VARIABLE_NAME(dmy_order,gdate)[2] = G_DATE_YEAR;
	
	//variable initialization for giounix.c global data
	memcpy(&(g->VARIABLE_NAME(unix_channel_funcs,giounix)),&temp_unix_channel_funcs,sizeof(GIOFuncs));
	memcpy(&(g->VARIABLE_NAME(g_io_watch_funcs,giounix)),&temp_g_io_watch_funcs,sizeof(GSourceFuncs));
	
	//variable initialization for gmain.c global data
	memcpy(&(g->VARIABLE_NAME(g_source_callback_funcs,gmain)),&temp_g_source_callback_funcs,sizeof(GSourceCallbackFuncs));
	memcpy(&(g->VARIABLE_NAME(g_timeout_funcs,gmain)),&temp_g_timeout_funcs,sizeof(GSourceFuncs));
	memcpy(&(g->VARIABLE_NAME(g_child_watch_funcs,gmain)),&temp_g_child_watch_funcs,sizeof(GSourceFuncs));
	memcpy(&(g->VARIABLE_NAME(g_idle_funcs,gmain)),&temp_g_idle_funcs,sizeof(GSourceFuncs));
	
	//variable initialization for gmem.c global data
	memcpy(&(g->VARIABLE_NAME(glib_mem_vtable,gmem)),&temp_glib_mem_vtable,sizeof(GMemVTable));
	memcpy(&(g->VARIABLE_NAME(profiler_table,gmem)),&temp_profiler_table,sizeof(GMemVTable));

	#ifdef G_DISABLE_CHECKS
	g->VARIABLE_NAME(glib_mem_profiler_table,gmem)= &(g->VARIABLE_NAME(glib_mem_vtable,gmem));
	#else
	g->VARIABLE_NAME(glib_mem_profiler_table,gmem) = &(g->VARIABLE_NAME(profiler_table,gmem));
	#endif /* G_DISABLE_CHECKS */
	
	#ifdef ENABLE_GC_FRIENDLY_DEFAULT
	g->VARIABLE_NAME(g_mem_gc_friendly,gmem)= TRUE;
	#else
	g->VARIABLE_NAME(g_mem_gc_friendly,gmem)= FALSE;
	#endif /* ENABLE_GC_FRIENDLY_DEFAULT */
	
	(g->VARIABLE_NAME(dummy,g_allocator_new)).name = "GAllocator is deprecated";
	(g->VARIABLE_NAME(dummy,g_allocator_new)).n_preallocs = 1;
	(g->VARIABLE_NAME(dummy,g_allocator_new)).is_unused = TRUE;
	
	//variable initialization for gmessages.c global data
	g->VARIABLE_NAME(g_log_always_fatal,gmessages) = (GLogLevelFlags)G_LOG_FATAL_MASK;
	g->VARIABLE_NAME(g_log_msg_prefix,gmessages) = (GLogLevelFlags)(G_LOG_LEVEL_ERROR | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_DEBUG);
	g->VARIABLE_NAME(default_log_func,gmessages) = g_log_default_handler;
	
	//variable initialization for gscanner.c global data
	GScannerConfig temp_g_scanner_config_template =
	{
	  (
	   " \t\r\n"
	   )			/* cset_skip_characters */,
	  (
	   G_CSET_a_2_z
	   "_"
	   G_CSET_A_2_Z
	   )			/* cset_identifier_first */,
	  (
	   G_CSET_a_2_z
	   "_"
	   G_CSET_A_2_Z
	   G_CSET_DIGITS
	   G_CSET_LATINS
	   G_CSET_LATINC
	   )			/* cset_identifier_nth */,
	  ( "#\n" )		/* cpair_comment_single */,
	  
	  FALSE			/* case_sensitive */,
	  
	  TRUE			/* skip_comment_multi */,
	  TRUE			/* skip_comment_single */,
	  TRUE			/* scan_comment_multi */,
	  TRUE			/* scan_identifier */,
	  FALSE			/* scan_identifier_1char */,
	  FALSE			/* scan_identifier_NULL */,
	  TRUE			/* scan_symbols */,
	  FALSE			/* scan_binary */,
	  TRUE			/* scan_octal */,
	  TRUE			/* scan_float */,
	  TRUE			/* scan_hex */,
	  FALSE			/* scan_hex_dollar */,
	  TRUE			/* scan_string_sq */,
	  TRUE			/* scan_string_dq */,
	  TRUE			/* numbers_2_int */,
	  FALSE			/* int_2_float */,
	  FALSE			/* identifier_2_string */,
	  TRUE			/* char_2_token */,
	  FALSE			/* symbol_2_token */,
	  FALSE			/* scope_0_fallback */,
	  FALSE			/* store_int64 */,
	};

	memcpy(&(g->VARIABLE_NAME(g_scanner_config_template,gscanner)),&temp_g_scanner_config_template,sizeof(GScannerConfig));
	
	//variable initialization for gspawn-symbian.c global data
	#ifdef G_SPAWN_SYMBIAN_DEBUG
	g->VARIABLE_NAME(debug,gspawn_symbian) = 1;
	#else
	g->VARIABLE_NAME(debug,gspawn_symbian) = -1;
	#endif // G_SPAWN_SYMBIAN_DEBUG 
	
	//variable initialization for gthread.c global data
	g->VARIABLE_NAME(g_thread_use_default_impl,gthread) = TRUE ;
	memcpy(&(g->VARIABLE_NAME(g_thread_functions_for_glib_use,gthread)),&temp_g_thread_functions_for_glib_use,sizeof(GThreadFunctions));
	
	//variable initialization for gslice.c global data
	(g->VARIABLE_NAME(slice_config,gslice)).working_set_msecs = 15 * 1000 ;
	(g->VARIABLE_NAME(slice_config,gslice)).color_increment	 = 1 ;
	
	InitializeGlobalStaticMutexes(g);
	
	return KErrNone;
}

struct global_struct *Glib_ImpurePtr()
{
#if defined(__WINSCW__) || defined(__WINS__)

	// Access the PLS of this process
	struct global_struct* p  = Pls<struct global_struct>(KLibglibUid3, &InitializeWsd);
    return p;

#else

	return NULL;	

#endif

}

G_END_DECLS
#endif /* EMULATOR */ 

