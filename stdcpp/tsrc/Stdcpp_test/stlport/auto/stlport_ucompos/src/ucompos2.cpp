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
#include "unary.h"

#ifdef MAIN 
#define ucompos2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int ucompos2_test(int, char**)
{
  int failures=0;
  cout<<"Results of ucompos2_test:"<<endl;

  int input [3] = { -1, -4, -16 };

  int output [3];
  transform((int*)input, (int*)input + 3, (int*)output, 
    compose1(square_root(), negate<int>()));
  for(int i = 0; i < 3; i++)
   cout << output[i] << endl;
  
   if(1!=output[0])
    failures++;
  else if(2!=output[1])
    failures++;
  else if(4!=output[2])
    failures++;
  
  if(failures)
    return 1;
  else         
    return 0;
}
