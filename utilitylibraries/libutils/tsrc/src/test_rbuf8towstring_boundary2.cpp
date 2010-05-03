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
#include<e32base.h>
#include "libutils.h"
#include"std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__
int main()
{
    int retval =ESuccess;
    wstring des;
    __UHEAP_MARK;	
    RBuf8  buf;
    buf.Create(10);
    buf.Copy((TUint8 *)"Hello", 5);
    buf.CleanupClosePushL();
    //int size =15;
    retval = Rbuf8ToWstring(buf, des  );

    int rbuf_len = buf.Length();
    int string_len = des.length();
    if (retval ==ESuccess && rbuf_len == string_len && rbuf_len == 5 && string_len == 5)
    {
    printf("test rbuf8towstring boundary2 Passed\n");
    }
    else
    {
    assert_failed = true;
    printf("test rbuf8towstring boundary2 Failed\n");
    }
    CleanupStack::PopAndDestroy(1);
    __UHEAP_MARKEND;
    testResultXml("test_rbuf8towstring_boundary2");
	return 0;
}
