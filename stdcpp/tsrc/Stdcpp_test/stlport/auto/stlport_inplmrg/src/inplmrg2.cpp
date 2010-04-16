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
#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>

#ifdef MAIN 
#define inplmrg2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int inplmrg2_test(int, char**)
{
  cout<<"Results of inplmrg2_test:"<<endl;
  vector <int> v1(10);
  int failures = 0;
  for(int i = 0; i < v1.size(); i++)
    v1[i] =(v1.size() - i - 1) % 5;
  ostream_iterator <int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  inplace_merge(v1.begin(), v1.begin() + 5,
                 v1.end(),
                 greater<int>());
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  if(v1[0] != 4)
  failures++;
  if(v1[1] != 4)
  failures++;
  if(v1[2] != 3)
  failures++;
  if(v1[3] != 3)
  failures++;
  if(v1[4] != 2)
  failures++;
  if(v1[5] != 2)
  failures++;
  if(v1[6] != 1)
  failures++;
  if(v1[7] != 1)
  failures++;
  if(v1[8] != 0)
  failures++;
  if(v1[9] != 0)
  failures++;
  
  return failures;
}
