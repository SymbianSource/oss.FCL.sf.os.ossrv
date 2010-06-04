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

#include <algorithm>
#include <iostream>

#ifdef MAIN 
#define iterswp0_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int iterswp0_test(int, char**)
{
  cout<<"Results of iterswp0_test:"<<endl;
int numbers[6] = { 0, 1, 2, 3, 4, 5 };
int failures=0;
  iter_swap(numbers, numbers + 3);
  for(int i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  if(numbers[0] != 3)
  failures++;
   if(numbers[1] != 1)
  failures++;
   if(numbers[2] != 2)
  failures++;
   if(numbers[3] !=0 )
  failures++;
   if(numbers[4] != 4)
  failures++;
   if(numbers[5] != 5)
  failures++;
  return failures;
}
