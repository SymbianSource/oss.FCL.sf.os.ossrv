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
#if defined (_STLP_MSVC) || defined (__ICL) || defined (__BORLANDC__)

# if defined (__BORLANDC__)
#  pragma option pop
#  pragma option -w-8062
# else
#  if !(defined (_STLP_MSVC) && (_STLP_MSVC < 1200))
//#   pragma warning (pop)
#  endif
#  pragma pack (pop)
# endif


#elif defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)

# pragma reset woff 1174
# pragma reset woff 1375
# pragma reset woff 1209
// from iterator_base.h
# pragma reset woff 1183

#elif defined(__DECCXX)

# ifdef __PRAGMA_ENVIRONMENT
#  pragma __environment __restore
# endif

#elif defined(__IBMCPP__)

#pragma info(restore)

#endif

