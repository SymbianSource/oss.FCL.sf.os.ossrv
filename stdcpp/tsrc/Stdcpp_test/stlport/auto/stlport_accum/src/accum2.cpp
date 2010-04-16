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
#define accum2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

static int mult(int initial_, int element_)
{
  return initial_ * element_;
}
int accum2_test(int, char**)
{
   cout<<"Results of accum2_test:"<<endl;

  vector <int> v(5);
  for(int i = 0; i < v.size(); i++)
    v[i] = i + 1;
  int prod = accumulate(v.begin(), v.end(), 1, mult);
  cout << "prod = " << prod << endl;
  
  if (prod == 120)
  	  return 0;
  else
  return 1;
}
