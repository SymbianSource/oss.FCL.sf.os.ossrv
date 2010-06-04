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
// This is an implementation file which
// is intended to be included multiple times with different _STLP_ASSOCIATIVE_CONTAINER
// setting

#if !defined (_STLP_EQUAL_OPERATOR_SPECIALIZED)
_STLP_TEMPLATE_HEADER
inline bool _STLP_CALL operator==(const _STLP_TEMPLATE_CONTAINER& __x,
                                  const _STLP_TEMPLATE_CONTAINER& __y) {
  return __x.size() == __y.size() &&
         equal(__x.begin(), __x.end(), __y.begin());
}
#endif /* _STLP_EQUAL_OPERATOR_SPECIALIZED */

_STLP_TEMPLATE_HEADER
inline bool _STLP_CALL operator<(const _STLP_TEMPLATE_CONTAINER& __x,
                                 const _STLP_TEMPLATE_CONTAINER& __y) {
  return lexicographical_compare(__x.begin(), __x.end(),
                                 __y.begin(), __y.end());
}

_STLP_RELOPS_OPERATORS( _STLP_TEMPLATE_HEADER , _STLP_TEMPLATE_CONTAINER )

#if defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER)
_STLP_TEMPLATE_HEADER
inline void _STLP_CALL swap(_STLP_TEMPLATE_CONTAINER& __x,
                            _STLP_TEMPLATE_CONTAINER& __y) {
  __x.swap(__y);
}
#endif /* _STLP_FUNCTION_TMPL_PARTIAL_ORDER */
