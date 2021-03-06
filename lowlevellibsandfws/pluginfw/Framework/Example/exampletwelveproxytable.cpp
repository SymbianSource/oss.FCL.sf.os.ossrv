// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// The proxy table of PlugIn EComExample12Downgraded 
// 
//

/**
 @file
 @internalComponent
*/

#include "ImplementationProxy.h"
#include "exampletwelve.h"	

// __________________________________________________________________________
// Exported proxy for instantiation method resolution
// Define the interface UIDs

const TImplementationProxy KImplementationTable[] =
	{
	IMPLEMENTATION_PROXY_ENTRY(0x10009E3C,CImplementationClassTwelveBasic::NewL)
	};

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount = sizeof(KImplementationTable) / sizeof(TImplementationProxy);
	return KImplementationTable;
	}
