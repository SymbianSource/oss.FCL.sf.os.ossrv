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
#include <iostream>


#ifdef MAIN
#define alg3_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int alg3_test(int, char**)
{
  
  cout<<"Results of alg3_test:"<<endl;
  int n=0;
  vector<int> i;
  i.push_back(1);
  i.push_back(4);
  i.push_back(2);
  i.push_back(8);
  i.push_back(2);
  i.push_back(2);
  count(i.begin(), i.end(), 2, n);
  cout << "Count of 2s = " << n << endl;

  if (n == 3)
  return 0;
  else 
  return 1;
}
