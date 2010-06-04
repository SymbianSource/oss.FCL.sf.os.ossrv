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
#include <functional>

#ifdef MAIN 
#define mset1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

typedef multiset<int, less<int> > mset;

int mset1_test(int, char**)
{
  cout<<"Results of mset1_test:"<<endl;
  mset s;
  int failures = 0;
  cout << "count(42) = " << s.count(42) << endl;
  s.insert(42);
  cout << "count(42) = " << s.count(42) << endl;
  s.insert(42);
  cout << "count(42) = " << s.count(42) << endl;
  mset::iterator i = s.find(40);
  if(i == s.end())
    cout << "40 Not found" << endl;
  else
  {
  	  failures++;
    cout << "Found " << *i << endl;
  }
  i = s.find(42);
  if(i == s.end())
  {
  	  failures++;
    cout << "Not found" << endl;
  }
  else
    cout << "Found " << *i << endl;
  int count = s.erase(42);
  cout << "Erased " << count << " instances" << endl;
  if(count != 2)
  failures++;
  return failures;
}
