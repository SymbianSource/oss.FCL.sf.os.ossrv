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
__FBSDID("$FreeBSD: src/lib/libc/gen/setprogname.c,v 1.8 2002/03/29 22:43:41 markm Exp $");

#include <stdlib.h>
#include <string.h>

#include "libc_private.h"

EXPORT_C void setprogname(const char *programname)
	{
	const char *p;
	p = strrchr(programname, '\\');
	if (p != NULL)
		__progname = p + 1;
	else
		__progname = programname;
	}
