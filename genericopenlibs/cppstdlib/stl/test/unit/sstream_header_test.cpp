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
/* This test purpose is simply to check Standard header independancy that
 * is to say that the header can be included alone without any previous
 * include.
 * Additionnaly, for C Standard headers that STLport expose, it can also be
 * used to check that files included by those headers are compatible with
 * pure C compilers.
 */

//Including this fle makes the test STLport specific but this is the only way to check
//compiler config:
#include <stl/config/features.h>

#if !defined (_STLP_USE_NO_IOSTREAMS)
#  include <sstream>
#endif
