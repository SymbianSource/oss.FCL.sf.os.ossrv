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
void main()
{
    __UHEAP_MARK;
    TBufC<20> buf _L("praveen");
    TPtr16 src = buf.Des();
    wchar_t * des= new wchar_t [20]; 
    int size=5;
    int retval =ESuccess;
    retval= Tptr16ToWcharp(src,des,size);

    if(retval == EInvalidSize)
    {
    printf(" Test_tptr16towcharp_invalidsize PASSED\n");
    }
    else
    {
    assert_failed = true;
    printf(" Test_tptr16towcharp_invalidsize FAILURE\n");
    }
    delete[] des;
    des = NULL;	
    __UHEAP_MARKEND;
}
