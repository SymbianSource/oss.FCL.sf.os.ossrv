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
//mwerks_debug_prefix.h
#define _STLP_NO_FORCE_INSTANTIATE 1// for debugging
#define EH_VECTOR_OPERATOR_NEW 1
#define _STLP_DEBUG 1 // enable the use of allocation debugging

#if __MWERKS__ >= 0x3000
#include <MSLCarbonPrefix.h>
#endif