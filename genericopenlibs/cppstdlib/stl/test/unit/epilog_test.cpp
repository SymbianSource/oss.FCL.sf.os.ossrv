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
#include <time.h>
#include <string>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)

struct some_struct {
    std::string s; // if std not properly redefined, error will be here
};

#endif
