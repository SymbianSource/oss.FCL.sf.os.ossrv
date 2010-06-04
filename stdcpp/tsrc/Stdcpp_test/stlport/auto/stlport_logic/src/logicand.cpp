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

#include <functional>
#include <iostream>
#include <algorithm>

#ifdef MAIN 
#define logicand_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int logicand_test(int, char**)
{
  cout<<"Results of logicand_test:"<<endl;
int input1 [4] = { 1, 1, 0, 1 };
int input2 [4] = { 0, 1, 0, 0 };
int failures = 0;

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, logical_and<bool>());
  for(int i = 0; i < 4; i++)
    cout << output[i] << endl;
   if(output[0] != 0)
    failures++;
    if(output[1] != 1)
    failures++;
    if(output[2] !=0 )
    failures++;
	if(output[3] != 0)
    failures++;
  return failures;
}
