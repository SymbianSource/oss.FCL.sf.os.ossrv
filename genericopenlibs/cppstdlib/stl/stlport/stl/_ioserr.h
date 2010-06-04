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
 * This file is included in every header that needs the STLport library to be
 * built; the header files mostly are the iostreams-headers. The file checks for
 * _STLP_USE_NO_IOSTREAMS or _STLP_NO_IOSTREAMS being not defined, so that the
 * iostreams part of STLport cannot be used when the symbols were defined
 * accidentally.
 */
#if defined (_STLP_NO_IOSTREAMS)
#  error STLport iostreams header cannot be used; you chose not to use iostreams in the STLport configuration file (stlport/stl/config/user_config.h).
#elif defined (_STLP_USE_NO_IOSTREAMS )
#  error STLport iostreams header cannot be used; your compiler do not support it.
#endif
