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
#ifndef ALIGNED_BUFFER_H
#define ALIGNED_BUFFER_H

_STLP_BEGIN_NAMESPACE
// this is for fake initialization
template<class T>
union _Stl_aligned_buffer {
  char buf[sizeof(T)];
  struct { double a; double b; } padding;

  T* operator&() {
    return __REINTERPRET_CAST(T*, this);
  }

  T const* operator&() const {
    return __REINTERPRET_CAST(T const*, this);
  }
};
_STLP_END_NAMESPACE

#endif
