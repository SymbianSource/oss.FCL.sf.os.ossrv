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
#define less_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int less_test(int, char**)
{
  cout<<"Results of less_test:"<<endl;
int array [4] = { 3, 1, 4, 2 };
int failures=0;
  sort(array, array + 4, less<int>());
  for(int i = 0; i < 4; i++)
    cout << array[i] << endl;
    if (array[0]!= 1)
    failures++;
    if (array[1]!= 2)
    failures++;
    if (array[2]!= 3)
    failures++;
    if (array[3]!= 4)
    failures++;
  return failures;
}
