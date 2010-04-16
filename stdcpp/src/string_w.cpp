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

#include "stlport_prefix.h"
#include <stl/_string.h>

_STLP_BEGIN_NAMESPACE
# ifndef _STLP_NO_FORCE_INSTANTIATE
#  ifndef _STLP_NO_WCHAR_T
template class _STLP_CLASS_DECLSPEC allocator<wchar_t>;
template class _STLP_CLASS_DECLSPEC _String_base<wchar_t, allocator<wchar_t> >;
# ifdef _STLP_DEBUG
template class _STLP_CLASS_DECLSPEC _Nondebug_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
# endif
template class _STLP_CLASS_DECLSPEC basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
#  endif
# endif
_STLP_END_NAMESPACE

