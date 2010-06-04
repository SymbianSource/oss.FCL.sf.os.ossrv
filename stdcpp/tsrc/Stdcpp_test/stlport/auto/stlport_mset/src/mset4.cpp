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
#include <set>

#ifdef MAIN 
#define mset4_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int mset4_test(int, char**)
{
  cout<<"Results of mset4_test:"<<endl;
int array [] = { 3, 6, 1, 2, 3, 2, 6, 7, 9 };
int failures = 0;
  typedef multiset<int, less<int> > mset;
  mset s(array, array + 9);
  pair<mset::const_iterator, mset::const_iterator> p = s.equal_range(3);
  cout << "lower bound = " << *(p.first) << endl;
   if (*(p.first) != 3)
  failures++;
  cout << "upper bound = " << *(p.second) << endl;
   if (*(p.second) != 6)
  failures++;
  return failures;
}
