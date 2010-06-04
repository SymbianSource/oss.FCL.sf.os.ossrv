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
#define sort1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int sort1_test(int, char**)
{
  
  int failures=0;
  cout<<"Results of sort1_test:"<<endl;
int array[6] = { 1, 50, -10, 11, 42, 19 };

  sort(array, array + 6);
  for(int i = 0; i < 6; i++)
    cout << array[i] << ' ';
  cout << endl;
  
  if(-10!=array[0])
    failures++;
  else if(1 !=array[1])
    failures++;
  else if(11!=array[2])
    failures++;
  else if(19!=array[3])
    failures++;
  else if(42!=array[4])
    failures++;
  else if(50!=array[5])
    failures++;
    
    if(failures)
      return 1;
    else 
      return 0;          
     
  }

