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

#include <sys/cdefs.h>
#ifndef __SYMBIAN32__ 
__FBSDID("$FreeBSD: src/lib/msun/src/s_lrintf.c,v 1.1 2005/01/11 23:12:55 das Exp $");
#endif //__SYMBIAN32__

#define type		float
#define	roundit		rintf
#define dtype		long
#define	fn		lrintf

#include "s_lrint.c"
