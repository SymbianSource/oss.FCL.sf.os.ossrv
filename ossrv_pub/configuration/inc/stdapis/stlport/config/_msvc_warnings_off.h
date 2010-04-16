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
# if (_MSC_VER > 1000)
// #pragma warning ( disable : 4251 )	// ignore template classes being exported in .dll's
/* 
 * "this used in base member initializer list"
 * arrow operator warning
 * copy constr & assignment cannot be generated
 * "forcing value to bool 'true' or 'false'
 * typedef used instaead of full type
 * 4018 : signed/unsigned mismatch, 4146 - result still unsigned 
 * 4100: unreferenced formal parameter
 * 4663: C++ language change: to explicitly specialize class template 'identifier' use the following syntax
 */
#  pragma warning ( disable : 4355 4284  4231 4511 4512 4097 4786 4800 4018 4146 4244 4514 4127 4100 4663 4103 4786 4715)
#  pragma warning ( disable : 4245 4514 4660) // conversion from enum to unsigned int signed/unsigned mismatch
#  if (_MSC_VER > 1200)
// multiple copy constructors/assignment operators specified,
// with member templates are bogus...
#   pragma warning ( disable : 4521 4522)
#  endif  
# endif
