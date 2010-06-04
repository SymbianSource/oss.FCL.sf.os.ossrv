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
#define equal1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int equal1_test(int, char**)
{
 
  cout<<"Results of equal1_test:"<<endl;
  vector <int> v1(10);
  for(int i = 0; i < v1.size(); i++)
    v1[i] = i;
  vector <int> v2(10);

  int failures = 0;
  if(equal(v1.begin(), v1.end(), v2.begin()))
  {
    cout << "v1 is equal to v2" << endl;
    failures++;
  }
  else
  {
    cout << "v1 is not equal to v2" << endl;
  }
  copy(v1.begin(), v1.end(), v2.begin());
  if(equal(v1.begin(), v1.end(), v2.begin()))
  {
    cout << "v1 is equal to v2" << endl;
  }
  else
  {
    cout << "v1 is not equal to v2" << endl;
    failures++;
  }

  if(!failures)
    return 0;
  else
    return 1;

}
