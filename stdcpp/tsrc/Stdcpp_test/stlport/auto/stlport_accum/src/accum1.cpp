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

#include <vector>
#include <numeric>
#include <iostream>


#ifdef MAIN
#define accum1_test main
#endif

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif


int accum1_test(int, char**)
{
    cout<<"Results of accum1_test:"<<endl;
  vector <int> v(5);
  for(int i = 0; i < v.size(); i++)
    v[i] = i + 1;
  int sum = accumulate(v.begin(), v.end(), 0);
  cout << "sum = " << sum << endl;

  if (sum == 15)
    return 0;
  else
  return 1;
}
