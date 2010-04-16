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
 * It is known that this code not compiled by following compilers:
 *
 * It is known that this code compiled by following compilers:
 *
 *   MSVC 6
 *   MSVC 8 Beta
 */

/*
 * This code represent what STLport waits from a compiler which support
 * member template classes (!_STLP_NO_MEMBER_TEMPLATE_CLASSES)
 */

template <typename T1>
struct A
{
  template <typename T2>
  struct B
  {
    typedef T2 _Type;
  };
};


template <typename T1, typename T2>
struct C
{
  typedef typename A<T1>:: template B<T2>::_Type ABType;
};
