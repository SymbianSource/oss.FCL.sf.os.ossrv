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

#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#ifndef __SYMBIAN32__
#include <config.h>
#else
#include "config.h"
#endif //__SYMBIAN32__
#define DBUS_COMPILATION /* Cheat and use private stuff */
#include <dbus/dbus.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef __SYMBIAN32__
#include <dbus/dbus-mainloop.h>
#include <dbus/dbus-internals.h>
#else
#include "dbus-mainloop.h"
#include "dbus-internals.h"
#endif //__SYMBIAN32__
#undef DBUS_COMPILATION

dbus_bool_t test_connection_setup                 (DBusLoop       *loop,
                                                   DBusConnection *connection);
void        test_connection_shutdown              (DBusLoop       *loop,
                                                   DBusConnection *connection);
void        test_connection_dispatch_all_messages (DBusConnection *connection);
dbus_bool_t test_connection_dispatch_one_message  (DBusConnection *connection);


#endif
