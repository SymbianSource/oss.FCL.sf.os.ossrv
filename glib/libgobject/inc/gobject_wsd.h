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


#ifndef __GOBJECT_WSD_H__
#define __GOBJECT_WSD_H__

#if (defined(__SYMBIAN32__) && (defined(__WINSCW__) || defined(__WINS__)))

#include <_ansi.h>
#include <sys/cdefs.h>
#include <gobject.h>
#include <gbsearcharray.h>

/* --------------------------- MACRO DEFINATIONS --------------------------*/

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

#define RETURN_VAL(var,filename) (Gobject_ImpurePtr()->VARIABLE_NAME(var,filename))

#define RETURN_VAL_MACRO(var,filename) (Gobject_ImpurePtr()->VARIABLE_NAME_MACRO(var,filename))

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
/* ------------------------ END MACRO DEFINATIONS --------------------------*/


typedef struct _GObjectNotifyContext          GObjectNotifyContext;
typedef void (*GObjectNotifyQueueDispatcher) (GObject     *object,
					      guint        n_pspecs,
					      GParamSpec **pspecs);

struct _GObjectNotifyContext
{
  GQuark                       quark_notify_queue;
  GObjectNotifyQueueDispatcher dispatcher;
  GTrashStack                 *_nqueue_trash; /* unused */
};

typedef guint (*function_type) (GObject*, gint);
#ifdef __cplusplus
extern "C"
#endif /* extern "C" */
guint object_floating_flag_handler (GObject *object,gint job);

typedef struct _Emission     Emission;
typedef enum
{
  EMISSION_STOP,
  EMISSION_RUN,
  EMISSION_HOOK,
  EMISSION_RESTART
} EmissionState;
typedef struct _SignalNode   SignalNode;
typedef struct
{
  GSignalAccumulator func;
  gpointer           data;
} SignalAccumulator;

struct _Emission
{
  Emission             *next;
  gpointer              instance;
  GSignalInvocationHint ihint;
  EmissionState         state;
  GType			chain_type;
};

struct _SignalNode
{
  /* permanent portion */
  guint              signal_id;
  GType              itype;
  const gchar             *name;
  guint              destroyed : 1;
  
  /* reinitializable portion */
  guint		     test_class_offset : 12;
  guint              flags : 8;
  guint              n_params : 8;
  GType		    *param_types; /* mangled with G_SIGNAL_TYPE_STATIC_SCOPE flag */
  GType		     return_type; /* mangled with G_SIGNAL_TYPE_STATIC_SCOPE flag */
  GBSearchArray     *class_closure_bsa;
  SignalAccumulator *accumulator;
  GSignalCMarshaller c_marshaller;
  GHookList         *emission_hooks;
};

#define class class1

typedef struct _TypeNode        TypeNode;
typedef struct _CommonData      CommonData;
typedef struct _IFaceData       IFaceData;
typedef struct _ClassData       ClassData;
typedef struct _InstanceData    InstanceData;
typedef union  _TypeData        TypeData;
typedef struct _IFaceEntry      IFaceEntry;

typedef enum
{
  UNINITIALIZED,
  BASE_CLASS_INIT,
  BASE_IFACE_INIT,
  CLASS_INIT,
  IFACE_INIT,
  INITIALIZED
} InitState;

struct _TypeNode
{
  GTypePlugin *plugin;
  guint        n_children : 12;
  guint        n_supers : 8;
  guint        _prot_n_ifaces_prerequisites : 9;
  guint        is_classed : 1;
  guint        is_instantiatable : 1;
  guint        mutatable_check_cache : 1;	/* combines some common path checks */
  GType       *children;
  TypeData * volatile data;
  GQuark       qname;
  GData       *global_gdata;
  union {
    IFaceEntry  *iface_entries;		/* for !iface types */
    GType       *prerequisistes;
  } _prot;
  GType        supers[1]; /* flexible array */
};

struct _IFaceEntry
{
  GType           iface_type;
  GTypeInterface *vtable;
  InitState       init_state;
};
struct _CommonData
{
  guint             ref_count;
  GTypeValueTable  *value_table;
};
struct _IFaceData
{
  CommonData         common;
  guint16            vtable_size;
  GBaseInitFunc      vtable_init_base;
  GBaseFinalizeFunc  vtable_finalize_base;
  GClassInitFunc     dflt_init;
  GClassFinalizeFunc dflt_finalize;
  gconstpointer      dflt_data;
  gpointer           dflt_vtable;
};
struct _ClassData
{
  CommonData         common;
  guint16            class_size;
  guint              init_state : 4;
  GBaseInitFunc      class_init_base;
  GBaseFinalizeFunc  class_finalize_base;
  GClassInitFunc     class_init;
  GClassFinalizeFunc class_finalize;
  gconstpointer      class_data;
  gpointer           class;
};
struct _InstanceData
{
  CommonData         common;
  guint16            class_size;
  guint              init_state : 4;
  GBaseInitFunc      class_init_base;
  GBaseFinalizeFunc  class_finalize_base;
  GClassInitFunc     class_init;
  GClassFinalizeFunc class_finalize;
  gconstpointer      class_data;
  gpointer           class;
  guint16            instance_size;
  guint16            private_size;
  guint16            n_preallocs;
  GInstanceInitFunc  instance_init;
  GMemChunk        *mem_chunk;
};
union _TypeData
{
  CommonData         common;
  IFaceData          iface;
  ClassData          class;
  InstanceData       instance;
};
typedef struct {
  gpointer            cache_data;
  GTypeClassCacheFunc cache_func;
} ClassCacheFunc;
typedef struct {
  gpointer                check_data;
  GTypeInterfaceCheckFunc check_func;
} IFaceCheckFunc;

struct global_struct
{
	//Global data of gboxed.c
	VARIABLE_DECL(boxed_bsa,gboxed,GBSearchArray *)
	VARIABLE_DECL(type_id,g_closure_get_type ,GType)
	VARIABLE_DECL(type_id,g_value_get_type ,GType)
	VARIABLE_DECL(type_id,g_value_array_get_type ,GType)
	VARIABLE_DECL(type_id,g_date_get_type ,GType)
	VARIABLE_DECL(type_id,g_strv_get_type ,GType)
	VARIABLE_DECL(type_id,g_gstring_get_type ,GType)
	VARIABLE_DECL(type_id,g_hash_table_get_type ,GType)

	//Global data of genums.c
	VARIABLE_DECL(initialized ,g_enum_types_init,gboolean)
	VARIABLE_DECL(info,g_enum_types_init,GTypeInfo)

	//Global data of gobject.c
	VARIABLE_DECL(quark_closure_array,gobject,GQuark)
	VARIABLE_DECL(quark_weak_refs,gobject,GQuark)
	VARIABLE_DECL(quark_toggle_refs,gobject,GQuark)
	VARIABLE_DECL(pspec_pool,gobject,GParamSpecPool *)
	VARIABLE_DECL(property_notify_context,gobject,GObjectNotifyContext)
	VARIABLE_DECL_ARRAY(gobject_signals,gobject,gulong,1)
	VARIABLE_DECL_MACRO(construct_objects_lock,gobject,GStaticMutex)
	VARIABLE_DECL(construct_objects,gobject,GSList *)
	#ifdef	G_ENABLE_DEBUG
	VARIABLE_DECL_MACRO(debug_objects,gobject,GStaticMutex)
	VARIABLE_DECL(g_trap_object_ref,gobject,volatile GObject *)
	VARIABLE_DECL(debug_objects_count,gobject,guint)
	VARIABLE_DECL(debug_objects_ht,gobject,GHashTable	*)
	#endif /* G_ENABLE_DEBUG */
	VARIABLE_DECL(initialized ,g_object_type_init,gboolean)
	VARIABLE_DECL(info,g_object_type_init,GTypeInfo)
	VARIABLE_DECL(floating_flag_handler,gobject,function_type)
	VARIABLE_DECL(g_initially_unowned_parent_class,gobject,gpointer)
	VARIABLE_DECL(g_define_type_id,g_initially_unowned_get_type,GType)

	//GLobal data of gparam.c
	VARIABLE_DECL(quark_floating ,gparam,GQuark)
	VARIABLE_DECL(init_smutex,g_param_spec_pool_new ,GStaticMutex)

	//Global data of gparamspec.c
	VARIABLE_DECL(pspec_info,g_param_spec_types_init,GParamSpecTypeInfo)
	VARIABLE_DECL(g_param_spec_types ,gparamspecs,GType *)

	//Global data of gsignal.c
	#ifdef	G_ENABLE_DEBUG
	VARIABLE_DECL(g_trace_instance_signals,gsignal,volatile gpointer )
	VARIABLE_DECL(g_trap_instance_signals,gsignal,volatile gpointer )
	#endif /* G_ENABLE_DEBUG */

 	VARIABLE_DECL(g_signal_key_bsa,gsignal,GBSearchArray *)
	VARIABLE_DECL(g_signal_hlbsa_bconfig,gsignal,GBSearchConfig)
	VARIABLE_DECL(g_class_closure_bconfig,gsignal,GBSearchConfig)
	VARIABLE_DECL(g_handler_list_bsa_ht,gsignal,GHashTable    *)
	VARIABLE_DECL(g_recursive_emissions,gsignal,Emission *)
	VARIABLE_DECL(g_restart_emissions ,gsignal,Emission *)
	VARIABLE_DECL(g_handler_sequential_number ,gsignal,gulong)
	VARIABLE_DECL_MACRO(g_signal_mutex,gsignal,GStaticMutex)
	VARIABLE_DECL(g_n_signal_nodes,gsignal,guint)
	VARIABLE_DECL(g_signal_nodes ,gsignal,SignalNode   **)
	VARIABLE_DECL(seq_hook_id ,g_signal_add_emission_hook ,gulong)

	//Global data of gsourceclosure.c
	VARIABLE_DECL(our_type ,g_io_channel_get_type ,GType)
	VARIABLE_DECL(etype ,g_io_condition_get_type,GType)
	VARIABLE_DECL(closure_callback_funcs,gsourceclosure,GSourceCallbackFuncs)

	//Global data of gtype.c
	VARIABLE_DECL(type_rw_lock,gtype,GStaticRWLock)
	VARIABLE_DECL(static_n_class_cache_funcs,gtype,guint)
	VARIABLE_DECL(static_class_cache_funcs ,gtype,ClassCacheFunc *)
	VARIABLE_DECL(static_n_iface_check_funcs,gtype,guint)
	VARIABLE_DECL(static_iface_check_funcs,gtype,IFaceCheckFunc *)
	VARIABLE_DECL(static_quark_type_flags,gtype,GQuark)
	VARIABLE_DECL(static_quark_iface_holder,gtype,GQuark)
	VARIABLE_DECL(static_quark_dependants_array,gtype,GQuark)
	VARIABLE_DECL(_g_type_debug_flags,gtype,GTypeDebugFlags)
	VARIABLE_DECL(static_type_nodes_ht,gtype,GHashTable *)
	VARIABLE_DECL_ARRAY(static_fundamental_type_nodes,gtype,TypeNode *,(G_TYPE_FUNDAMENTAL_MAX >> G_TYPE_FUNDAMENTAL_SHIFT) + 1)
	VARIABLE_DECL(static_fundamental_next,gtype,GType)
	VARIABLE_DECL_MACRO(instance_real_class,gtype,GStaticMutex)
	VARIABLE_DECL(instance_real_class_bsa,gtype,GBSearchArray *)
	VARIABLE_DECL(instance_real_class_bconfig,gtype,GBSearchConfig)
	VARIABLE_DECL_ARRAY(debug_keys,g_type_init_with_debug_flags ,GDebugKey,2)
	VARIABLE_DECL_MACRO(type_init_lock,g_type_init_with_debug_flags,GStaticMutex)

	//Global data of gtypemodule.c
	VARIABLE_DECL(parent_class ,gtypemodule,gpointer)
	VARIABLE_DECL(type_module_type,g_type_module_get_type ,GType)

	//Global data of gtypeplugin.c
	VARIABLE_DECL(type_plugin_type ,g_type_plugin_get_type,GType)

	//Global data of gvalue.c
	VARIABLE_DECL(transform_array,gvalue,GBSearchArray *)
	VARIABLE_DECL(transform_bconfig,gvalue,GBSearchConfig)

	// Global data of gvaluetypes.c
	VARIABLE_DECL(type ,g_gtype_get_type ,GType)

};

#undef class

__BEGIN_DECLS
struct global_struct *Gobject_ImpurePtr();
__END_DECLS
#endif 

#endif /* __GOBJECT_WSD_H__ */
