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
#define iter2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
  const char* array[2];
  int j =0 ;
  int failures = 0;
static void print(const vector<const char*>& v_)
{
  std::vector<const char*>::const_iterator i;
  for(i = v_.begin(); i != v_.end(); i++)
  {
  	    cout << *i << endl;
       array[j++] = *i;        
  }
  if(array[0] != "zippy")
  failures++;
   if(array[1] != "motorboy")
  failures++;
}
int iter2_test(int, char**)
{
  cout<<"Results of iter2_test:"<<endl;
  vector<const char*> v;
  int failures = 0;
  v.push_back((char*) "zippy");
  v.push_back((char*) "motorboy");
  print(v);
  
   
  return failures;
}
