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
#include <iterator>

#include <algorithm>
#include <vector>
#include <iterator>
// #include <functional>
#include <numeric>
#include <iostream>

#ifdef MAIN 
#define prevprm2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int prevprm2_test(int, char**)
{
  int failures=0;
  cout<<"Results of prevprm2_test:"<<endl;
  vector <int> v1(3);
  iota(v1.begin(), v1.end(), 0);
  ostream_iterator<int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  
  if(0!=v1[0])
     failures++;
   else if(1 !=v1[1])
     failures++;
   else if(2!=v1[2])
     failures++;
     
  for(int i = 0; i < 9; i++)
  {
    prev_permutation(v1.begin(), v1.end(), greater<int>());
    copy(v1.begin(), v1.end(), iter);
    
    switch(i)
     {
       case 0: if(0 !=v1[0])
                 failures++;
               else if(2 !=v1[1])
                 failures++;
               else if(1 !=v1[2])
                 failures++;
                break;        
       
       case 1: if(1 !=v1[0])
                 failures++;
               else if(0 !=v1[1])
                 failures++;
               else if(2 !=v1[2])
                 failures++;
                 break;        
      case 2: if(1 !=v1[0])
                 failures++;
               else if(2 !=v1[1])
                 failures++;
               else if(0 !=v1[2])
                   failures++;    
                   break;        
     case 3: if(2 !=v1[0])
                 failures++;
               else if(0 !=v1[1])
                 failures++;
               else if(1 !=v1[2])
                 failures++;  
                  break;        
   case 4: if(2 !=v1[0])
                 failures++;
               else if(1 !=v1[1])
                 failures++;
               else if(0 !=v1[2])
                 failures++;  
                 break;        
                 
     case 5: if(0 !=v1[0])
                 failures++;
               else if(1 !=v1[1])
                 failures++;
               else if(2 !=v1[2])
                 failures++;  
                break;        
    case 6: if(0 !=v1[0])
                 failures++;
               else if(2 !=v1[1])
                 failures++;
               else if(1 !=v1[2])
                 failures++;  
                   break;         
    case 7: if(1 !=v1[0])
                 failures++;
               else if(0 !=v1[1])
                 failures++;
               else if(2 !=v1[2])
                 failures++;               
                 break;             
     case 8: if(1 !=v1[0])
                 failures++;
               else if(2 !=v1[1])
                 failures++;
               else if(0 !=v1[2])
                 failures++;  
                  break;        
   }
    
    cout << endl;
  }
  if(failures)
    return 1;
  else  
    return 0;
}
