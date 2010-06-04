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
#define rndshuf0_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int rndshuf0_test(int, char**)
{
  cout<<"Results of rndshuf0_test:"<<endl;
int numbers[6] = { 1, 2, 3, 4, 5, 6 };
int failures =0;
  random_shuffle(numbers, numbers + 6);
  for(int i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  if (numbers[0] != 1 && numbers[1] != 4 && numbers[2] != 2 && numbers[3] != 5 && numbers[4] != 6 && numbers[5] != 3) 
  failures++;
  
  return failures;
}
