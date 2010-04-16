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
#define vec5_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int vec5_test(int, char**)
{
  int failures=0;
  cout<<"Results of vec5_test:"<<endl;
  int array [] = { 1, 4, 9, 16 };

  vector<int> v(array, array + 4);
  for(int i = 0; i < v.size(); i++)
    cout << "v[" << i << "] = " << v[i] << endl;
  
  if(1!=v[0])
    failures++;
  else if(4!=v[1])
    failures++;
  else if(9!=v[2])
    failures++;
  else if(16!=v[3])
    failures++;
  
  if(failures)
    return 1;        
  else
    return 0;
}
/*Results of vec5_test:
v[0] = 1
v[1] = 4
v[2] = 9
v[3] = 16
*/
