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
 
// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <iostream>
#include <algorithm>
#include <functional>

#ifdef MAIN 
#define minus_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int minus_test(int, char**)
{
  cout<<"Results of minus_test:"<<endl;
int input1 [4] = { 1, 5, 7, 8 };
int input2 [4] = { 1, 4, 8, 3 };
int failures = 0;
  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, minus<int>());
  for(int i = 0; i < 4; i++)
    cout << output[i] << endl;
    if(output[0] != 0)
    failures++;
    if(output[1] != 1)
    failures++;
    if(output[2] != -1)
    failures++;
    if(output[3] != 5)
    failures++;
  return failures;
}
