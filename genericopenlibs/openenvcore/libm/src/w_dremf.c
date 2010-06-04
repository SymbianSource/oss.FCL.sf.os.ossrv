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
 * dremf() wrapper for remainderf().
 *
 * Written by J.T. Conklin, <jtc@wimsey.com>
 * Placed into the Public Domain, 1994.
 */
/* $FreeBSD: src/lib/msun/src/w_dremf.c,v 1.3 2004/07/28 05:53:18 kan Exp $ */

#include <math.h>
#include "math_private.h"
#ifdef __SYMBIAN_COMPILE_UNUSED__
float
dremf(float x, float y)
{
	return remainderf(x, y);
}
#endif
