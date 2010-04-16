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

 
#include <pthread.h>
#include "libc_wsd_defs.h"

#ifdef __SYMBIAN32__
#ifndef EMULATOR
pthread_mutex_t __gdtoa_locks[] = {
         PTHREAD_MUTEX_INITIALIZER,
         PTHREAD_MUTEX_INITIALIZER
 };
#else
GET_GLOBAL_ARRAY_FROM_TLS(__gdtoa_locks, pthread_mutex_t)
#define __gdtoa_locks (GET_WSD_VAR_NAME(__gdtoa_locks, g)())
#endif
#endif


