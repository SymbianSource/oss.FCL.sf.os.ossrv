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
#include <deque>
#include <algorithm>


#ifdef MAIN
#define alg5_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int alg5_test(int, char**)
{
 
  cout<<"Results of alg5_test:"<<endl;
  int failures = 0;
  //result array
  int res_arr[4] = { 1962, 1992, 2001, 1999};

  deque<int> years;
  years.push_back(1962);
  years.push_back(1992);
  years.push_back(2001);
  years.push_back(1999);
  deque<int>::iterator i;
  int j = 0;
  for(i = years.begin(); i != years.end(); i++, j++)
  {
  	cout << *i << endl;
  	if (*i != res_arr[j])
  		failures++;
  }

  if (!failures)
  	 return 0;
  else 
  return 1;
}
