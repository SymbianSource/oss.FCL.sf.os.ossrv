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
#include <vector>
#include <algorithm>

#ifdef MAIN 
#define iter1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int iter1_test(int, char**)
{
  cout<<"Results of iter1_test:"<<endl;
   int failures = 0;
  vector<const char*> v; // Vector of character strings.
  const char* array[2];
  int j =0 ;
  v.push_back((char*) "zippy"); // First element.
  v.push_back((char*) "motorboy"); // Second element.
  typedef vector<const char*> vec;
  vec::iterator i = v.begin(); // Position at end.
  for(i = v.begin(); i != v.end(); i++)
  {
      cout << *i << endl; // Display item.
      array[j++] = *i;      
   }
  if(array[0] != "zippy")
  failures++;
   if(array[1] != "motorboy")
  failures++;
  
  return failures;
}
