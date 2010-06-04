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
#include <numeric>

#ifdef MAIN 
#define times_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int times_test(int, char**)
{
  cout<<"Results of times_test:"<<endl;
int input [4] = { 1, 5, 7, 2 };

  int total = accumulate(input, input + 4, 1, multiplies<int>());
  cout << "total = " << total << endl;
  if(70!=total)
    return 1;
  else  
    return 0;
}
