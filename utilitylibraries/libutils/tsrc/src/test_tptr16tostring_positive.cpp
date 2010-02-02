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
void main()
{
    __UHEAP_MARK;
    {
    int retval =ESuccess;
    string str((const char*)"");
    _LIT(KTxt, "hellohello");
    HBufC* hbufc = KTxt().AllocLC();
    CleanupStack::PushL(hbufc);
    TPtr tptr1 = hbufc->Des();
    retval = Tptr16ToString(tptr1,str);

    if (retval ==ESuccess)
    {
    printf("tptr16tostring Passed");
    }
    else
    {
    assert_failed = true;
    printf("tptr16tostring failed");
    }      
    CleanupStack::PopAndDestroy(1);
    }
    __UHEAP_MARKEND;
    testResultXml("test_tptr16tostring_positive");
}
