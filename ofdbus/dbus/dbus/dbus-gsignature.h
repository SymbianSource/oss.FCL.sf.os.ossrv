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

#ifndef DBUS_GOBJECT_SIGNATURE_H
#define DBUS_GOBJECT_SIGNATURE_H

#include <dbus/dbus.h>
#ifndef __SYMBIAN32__
#include <dbus/dbus-signature.h>
#else
#include "dbus/dbus-signature.h"
#endif
#include <glib.h>

GType          _dbus_gtype_from_basic_typecode (int typecode);

GType          _dbus_gtype_from_signature      (const char              *signature,
					       gboolean                 is_client);

GType          _dbus_gtype_from_signature_iter (DBusSignatureIter       *sigiter,
					       gboolean                 is_client);

GArray *       _dbus_gtypes_from_arg_signature (const char              *signature,
						gboolean                 is_client);

#endif
