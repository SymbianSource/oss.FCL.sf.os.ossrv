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
#include <deque>
#include <queue>

#ifdef MAIN 
#define pqueue1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int pqueue1_test(int, char**)
{
  int failures=0,i=0;
  int arr[3];
  cout<<"Results of pqueue1_test:"<<endl;
  priority_queue<int, deque<int>, less<int> > q;
  q.push(42);
  q.push(101);
  q.push(69);
  while(!q.empty())
  {
    arr[i]=q.top();
    cout << q.top() << endl;
    q.pop();
    i++;
  }
  
  if(101 !=arr[0])
    failures++;
  else if(69 !=arr[1])
    failures++;
  else if(42 !=arr[2])
    failures++;
    
    if(failures)
       return 1;
    else 
      return 0;
}
