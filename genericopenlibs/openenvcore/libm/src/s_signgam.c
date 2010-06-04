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

#ifndef __SYMBIAN32__
#include <math.h>
#endif
#include "math_private.h"


#ifndef __SYMBIAN32__
int signgam = 0;
#else
#ifndef __WINSCW__
int _signgam = 0;
#endif//__WINSCW__
#endif //__SYMBIAN32__
