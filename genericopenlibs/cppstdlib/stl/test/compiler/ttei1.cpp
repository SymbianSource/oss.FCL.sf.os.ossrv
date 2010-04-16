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
 *   MSVC 6
 *
 * It is known that this code compiled by following compilers:
 *   gcc 3.3.3
 *   gcc 3.4.1
 *   MSVC 8 Beta
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
    };
};

template <> template <typename T>
void A::B::C<true>::f( T& ) {}

