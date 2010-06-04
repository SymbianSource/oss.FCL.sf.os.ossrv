/*
* Copyright (c) 2006-2008 Nokia Corporation and/or its subsidiary(-ies).
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


#include <sys/cdefs.h>
__FBSDID("$FreeBSD: src/lib/libc/gen/getprogname.c,v 1.4 2002/03/29 22:43:41 markm Exp $");


#include <stdlib.h>
#include "un-namespace.h"

#include "libc_private.h"

#ifndef __SYMBIAN32__
__weak_reference(_getprogname, getprogname);
#endif //__SYMBIAN32__

EXPORT_C const char * getprogname(void)
{
	return (__progname);
}
