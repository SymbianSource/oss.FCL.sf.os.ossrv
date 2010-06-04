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
#define negate_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int negate_test(int, char**)
{
  cout<<"Results of negate_test:"<<endl;
int input [3] = { 1, 2, 3 };
int failures = 0;
  int output[3];
  transform((int*)input, (int*)input + 3, (int*)output, negate<int>());
  for(int i = 0; i < 3; i++)
    cout << output[i] << endl;
    
    if(output[0] != -1)
    failures++;
    if(output[1] != -2)
    failures++;
    if(output[2] != -3)
    failures++;
    
  return failures;
}
