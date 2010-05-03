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

#include <stdio.h>
#include<e32std.h>
#include <e32base.h>
#include "libutils.h"
#include"std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__
int main()
{
    wstring str(L"Hello World");
    __UHEAP_MARK;
    RBuf16 buf;
    buf.CleanupClosePushL();
    int retval =ESuccess;
    retval = WstringToRbuf16(str, buf);

    if (retval ==ESuccess)
    {
    printf("wstringtorbuf16 Passed");
    }
    else
    {
    assert_failed = true;
    printf("wstringtorbuf16 Failed");
    }	
    CleanupStack::PopAndDestroy(1);
    __UHEAP_MARKEND;
    testResultXml("test_wstringtorbuf16_positive");
	return 0;
}
