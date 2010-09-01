/* GObject - GLib Type, Object, Parameter and Signal Library
 * Copyright (C) 2000 Red Hat, Inc.
 * Portions copyright (c) 2006 Nokia Corporation.  All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#include	"gtypeplugin.h"
#include	"gobjectalias.h"

#ifdef __SYMBIAN32__
#include <gobject_wsd.h>
#endif /* __SYMBIAN32__ */


/* --- functions --- */
#if EMULATOR

PLS(type_plugin_type ,g_type_plugin_get_type,GType)
#define type_plugin_type  (*FUNCTION_NAME(type_plugin_type ,g_type_plugin_get_type)())

#endif /* EMULATOR */

GType
g_type_plugin_get_type (void)
{
  #if !(EMULATOR)
  static GType type_plugin_type = 0;
  #endif /* EMULATOR*/
  
  if (!type_plugin_type)
    {
      static const GTypeInfo type_plugin_info = {
	sizeof (GTypePluginClass),
	NULL,           /* base_init */
	NULL,           /* base_finalize */
      };
      
      type_plugin_type = g_type_register_static (G_TYPE_INTERFACE, g_intern_static_string ("GTypePlugin"), &type_plugin_info, 0);
    }
  
  return type_plugin_type;
}

#if EMULATOR
#undef type_plugin_type 
#endif /* EMULATOR */

EXPORT_C void
g_type_plugin_use (GTypePlugin *plugin)
{
  GTypePluginClass *iface;
  
  g_return_if_fail (G_IS_TYPE_PLUGIN (plugin));
  
  iface = G_TYPE_PLUGIN_GET_CLASS (plugin);
  iface->use_plugin (plugin);
}

EXPORT_C void
g_type_plugin_unuse (GTypePlugin *plugin)
{
  GTypePluginClass *iface;
  
  g_return_if_fail (G_IS_TYPE_PLUGIN (plugin));
  
  iface = G_TYPE_PLUGIN_GET_CLASS (plugin);
  iface->unuse_plugin (plugin);
}

EXPORT_C void
g_type_plugin_complete_type_info (GTypePlugin     *plugin,
				  GType            g_type,
				  GTypeInfo       *info,
				  GTypeValueTable *value_table)
{
  GTypePluginClass *iface;
  
  g_return_if_fail (G_IS_TYPE_PLUGIN (plugin));
  g_return_if_fail (info != NULL);
  g_return_if_fail (value_table != NULL);
  
  iface = G_TYPE_PLUGIN_GET_CLASS (plugin);
  iface->complete_type_info (plugin,
			     g_type,
			     info,
			     value_table);
}

EXPORT_C void
g_type_plugin_complete_interface_info (GTypePlugin    *plugin,
				       GType           instance_type,
				       GType           interface_type,
				       GInterfaceInfo *info)
{
  GTypePluginClass *iface;
  
  g_return_if_fail (G_IS_TYPE_PLUGIN (plugin));
  g_return_if_fail (info != NULL);
  
  iface = G_TYPE_PLUGIN_GET_CLASS (plugin);
  iface->complete_interface_info (plugin,
				  instance_type,
				  interface_type,
				  info);
}

#define __G_TYPE_PLUGIN_C__
#include "gobjectaliasdef.c"
