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
#include <set>

#ifdef MAIN 
#define set2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int set2_test(int, char**)
{
  int failures=0;
  cout<<"Results of set2_test:"<<endl;
  set<int, less<int> > s;
  pair<std::set<int, less<int> >::const_iterator, bool> p = s.insert(42);
  if(p.second)
   {
     cout << "Inserted new element " << *(p.first) << endl;
       if(42 !=*(p.first))
         failures++;
     } 
  else
    cout << "Existing element = " << *(p.first) << endl;
  
  if(!p.second)
    failures++;
       
  p = s.insert(42);

  if(p.second)
      cout << "Inserted new element " << *(p.first) << endl;
   else
    {
      cout << "Existing element = " << *(p.first) << endl;
        if(42 !=*(p.first))
            failures++; 
     }
  
  if(p.second)
    failures++;  
     
  if(failures)
    return 1;
  else
    return 0;  
}
