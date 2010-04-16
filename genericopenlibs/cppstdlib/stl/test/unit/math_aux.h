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
#ifndef __MATH_AUX_H
#define __MATH_AUX_H

#include <limits>

/*
 * This function is not only used to compare floating point values with a tolerance,
 * it also leads to ambiguity problems if the called functions do not have the
 * right prototype.
 */
template <class _Tp>
bool are_equals(_Tp val, _Tp ref) {
  if (val < ref) {
    return (ref - val) <= std::numeric_limits<_Tp>::epsilon();
  }
  else {
    return (val - ref) <= std::numeric_limits<_Tp>::epsilon();
  }
}

#endif // __MATH_AUX_H
