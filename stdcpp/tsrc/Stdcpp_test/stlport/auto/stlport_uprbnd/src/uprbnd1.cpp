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
#define uprbnd1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int uprbnd1_test(int, char**)
{
  int x=0;
  
  cout<<"Results of uprbnd1_test:"<<endl;
  int array[20];
  for(int i = 0; i < 20; i++)
  {
    array[i] = i/4;
    cout << array[i] << ' ';
  }
  
  x=(upper_bound((int*)array, (int*)array + 20, 3) - array);
 
  cout<< "\n3 can be inserted at index: "<<x << endl;
  
  if(16!=x)
    return 1;  
  else 
   return 0;
}

/*sults of uprbnd1_test:
0 0 0 0 1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4
3 can be inserted at index: 16*/
