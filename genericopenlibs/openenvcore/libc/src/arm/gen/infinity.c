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

/*
 * infinity.c
 */

#include <sys/cdefs.h>
#ifndef __SYMBIAN32__
__FBSDID("$FreeBSD: src/lib/libc/arm/gen/infinity.c,v 1.1 2004/05/14 12:04:30 cognet Exp $");
#endif //__SYMBIAN32__

#include <math.h>
#ifndef __SYMBIAN32__

/* bytes for +Infinity on a 387 */
const union __infinity_un __infinity = { 
#if BYTE_ORDER == BIG_ENDIAN
	{ 0x7f, 0xf0, 0, 0, 0, 0, 0, 0 }
#else
	{ 0, 0, 0, 0, 0, 0, 0xf0, 0x7f }
#endif
};

/* bytes for NaN */
const union __nan_un __nan = {
#if BYTE_ORDER == BIG_ENDIAN
	{0xff, 0xc0, 0, 0}
#else
	{ 0, 0, 0xc0, 0xff }
#endif
};
#endif //__SYMBIAN32__
