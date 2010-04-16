/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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




#ifndef BUS_SELINUX_H
#define BUS_SELINUX_H

#ifndef __SYMBIAN32__
#include <dbus/dbus-hash.h>
#else
#include "dbus-hash.h"
#endif //__SYMBIAN32__
#include <dbus/dbus-connection.h>
#include "services.h"

dbus_bool_t bus_selinux_pre_init (void);
dbus_bool_t bus_selinux_full_init(void);
void        bus_selinux_shutdown (void);

dbus_bool_t bus_selinux_enabled  (void);

void bus_selinux_id_ref    (BusSELinuxID *sid);
void bus_selinux_id_unref  (BusSELinuxID *sid);

DBusHashTable* bus_selinux_id_table_new    (void);
BusSELinuxID*  bus_selinux_id_table_lookup (DBusHashTable    *service_table,
                                            const DBusString *service_name);
dbus_bool_t    bus_selinux_id_table_insert (DBusHashTable    *service_table,
                                            const char       *service_name,
                                            const char       *service_context);
void           bus_selinux_id_table_print  (DBusHashTable    *service_table);
const char*    bus_selinux_get_policy_root (void);

dbus_bool_t    bus_selinux_append_context      (DBusMessage    *message,
						BusSELinuxID   *context,
						DBusError      *error);

dbus_bool_t bus_selinux_allows_acquire_service (DBusConnection *connection,
                                                BusSELinuxID   *service_sid,
						const char     *service_name,
						DBusError      *error);

dbus_bool_t bus_selinux_allows_send            (DBusConnection *sender,
                                                DBusConnection *proposed_recipient,
						const char     *msgtype, /* Supplementary audit data */
						const char     *interface,
						const char     *member,
						const char     *error_name,
						const char     *destination,
						DBusError      *error);

BusSELinuxID* bus_selinux_init_connection_id (DBusConnection *connection,
                                              DBusError      *error);



#endif /* BUS_SELINUX_H */
