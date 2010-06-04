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

#ifdef MAIN 
#define incl0_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int incl0_test(int, char**)
{
  cout<<"Results of incl0_test:"<<endl;
  int failures = 0;
int numbers1[5] = { 1, 2, 3, 4, 5 };
int numbers2[5] = { 1, 2, 4, 8, 16 };
int numbers3[2] = { 4, 8 };

  if(includes(numbers1, numbers1 + 5, numbers3, numbers3 + 2))
  {
  	failures++;
    cout << "numbers1 includes numbers3" << endl;
  }
  else
      cout << "numbers1 does not include numbers3" << endl;
  
  if(includes(numbers2, numbers2 + 5, numbers3, numbers3 + 2))
      cout << "numbers2 includes numbers3" << endl;
  else
  {
  	failures++;
    cout << "numbers2 does not include numbers3" << endl;
  }
  return 0;
}
