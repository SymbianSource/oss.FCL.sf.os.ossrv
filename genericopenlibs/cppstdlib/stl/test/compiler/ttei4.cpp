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
 *   gcc 2.95.3
 *   gcc 3.3.3
 *   gcc 3.4.1
 *
 * It is known that this code compiled by following compilers:
 *
 *   MSVC 6
 *   MSVC 8 Beta
 */

/*
 * Indeed this code is wrong: 1. explicit template specialization
 * have to appear out-of-class; 2. specialized struct C have to
 * have function f.
 *
 */

struct A
{
  private:
    struct B
    {
        template <typename T>
        static void f( T& ) {}

        template <bool V>
        struct C
        {
            template <typename T>
            static void f( T& ) {}
        };

        template <>
        struct C<true>
        {
        };
    };
};

