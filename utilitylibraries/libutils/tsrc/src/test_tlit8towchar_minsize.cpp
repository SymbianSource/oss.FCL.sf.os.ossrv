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
#include "libutils.h"
#include"std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__
int main()
{
    __UHEAP_MARK;
    _LIT8(Kname,"min");
    wchar_t * des= new wchar_t [4]; 
    int retval =ESuccess;
    int size = 4;
    retval= Tlitc8ToWchar(Kname, des, size);

    if(retval ==ESuccess)
    {
    printf("Test_tlit8towchar_nullcheck passed\n");
    }
    else
    {
    assert_failed = true;
    printf("Test_tlit8towchar_nullcheck FAILURE\n");
    }
    delete[] des;
    des = NULL;	
    __UHEAP_MARKEND;
    testResultXml("test_tlit8towchar_minsize");
	return 0;
}
