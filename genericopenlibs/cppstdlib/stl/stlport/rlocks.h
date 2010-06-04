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

#ifndef _STLP_misc_rlocks_h
# define _STLP_misc_rlocks_h
# if (__SUNPRO_CC >= 0x500 )
#  include <../CCios/rlocks.h>
# elif defined (__SUNPRO_CC)
#  include <../CC/rlocks.h>
# else
#  error "This file is for SUN CC only. Please remove it if it causes any harm for other compilers."
# endif
#endif

