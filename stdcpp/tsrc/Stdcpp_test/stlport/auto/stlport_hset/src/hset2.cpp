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
#include <hash_set>

#ifdef MAIN 
#define hset2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

// __STL_TYPE_TRAITS_POD_SPECIALIZE(_Hashtable_node<int>*);

int hset2_test(int, char**)
{
  cout<<"Results of hset2_test:"<<endl;
  hash_set<int, hash<int>, equal_to<int> > s;
  int failures = 0;
  pair<std::hash_set<int, hash<int>, equal_to<int> >::const_iterator, bool> p = s.insert(42);
  if(p.second)
  {
  	   cout << "Inserted new element " << *(p.first) << endl;
  	   
  }
  else
  {
  	   cout << "Existing element = " << *(p.first) << endl;
  		failures++;
  }
  p = s.insert(42);
  if(p.second)
  {
    cout << "Inserted new element " << *(p.first) << endl;
  	   failures++;
  }
  else
  {
  	   cout << "Existing element = " << *(p.first) << endl;
  }
  return failures;
}
