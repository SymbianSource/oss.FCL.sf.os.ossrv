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

#include <algorithm>
#include <vector>
#include <iostream>

#ifdef MAIN 
#define lwrbnd1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int lwrbnd1_test(int, char**)
{
  cout<<"Results of lwrbnd1_test:"<<endl;
  std::vector <int> v1(20);
  for(int i = 0; i < v1.size(); i++)
  {
    v1[i] = i/4;
    cout << v1[i] << ' ';
  }
  std::vector <int>::iterator location =  lower_bound(v1.begin(), v1.end(), 3);
  cout
    << "\n3 can be inserted at index: "
    <<(location - v1.begin())
    << endl;
    if ((location - v1.begin()) == 12)
  return 0;
    else
    return 1;
}
