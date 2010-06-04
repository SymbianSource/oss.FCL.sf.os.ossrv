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


#ifndef IOTA_H
#define IOTA_H

#include <numeric>

#ifdef __SYMBIAN32__
using std::iota;
#endif // __SYMBIAN32__

//iota definition used in unit test
template <typename _It, typename _Tp>
void __iota(_It __first, _It __last, _Tp __val) {
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  iota(__first, __last, __val);
#else
  while (__first != __last) {
    *__first++ = __val++;
  }
#endif
}

#endif
