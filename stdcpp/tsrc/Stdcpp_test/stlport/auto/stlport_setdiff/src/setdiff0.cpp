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
#include <iostream>

#ifdef MAIN 
#define setdiff0_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int setdiff0_test(int, char**)
{
  int failures=0;
  cout<<"Results of setdiff0_test:"<<endl;
int v1[3] = { 13, 18, 23 };
int v2[4] = { 10, 13, 17, 23 };
int result[4] = { 0, 0, 0, 0 };

  set_difference((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);
  int i;
  for(i = 0; i < 4; i++)
    cout << result[i] << ' ';
  cout << endl;
  
  if(18!=result[0])
     failures++;
  else if(0!=result[1])
    failures++;   
  else if(0!=result[2])
    failures++;   
  else if(0!=result[3])
    failures++;   

  set_difference((int*)v2, (int*)v2 + 4, (int*)v1, (int*)v1 + 2, (int*)result);
  for(i = 0; i < 4; i++)
    cout << result[i] << ' ';
  cout << endl;
  
  if(10!=result[0])
     failures++;
  else if(17!=result[1])
    failures++;   
  else if(23!=result[2])
    failures++;   
  else if(0!=result[3])
    failures++;   

  if(failures)
    return 1;
  else
    return 0;
}



