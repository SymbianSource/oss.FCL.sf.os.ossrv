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
#include <list>

#ifdef MAIN 
#define list2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int list2_test(int, char**)
{
  cout<<"Results of list2_test:"<<endl;
int array1 [] = { 1, 16 };
int array2 [] = { 4, 9 };
int array3[4];
int failures = 0;int a=0;
  list<int> l1(array1, array1 + 2);
  list<int> l2(array2, array2 + 2);
  std::list<int>::iterator i = l1.begin();
  i++;
  l1.splice(i, l2, l2.begin(), l2.end());
  i = l1.begin();
  while(i != l1.end())
  {
  	array3[a++] = *i;
  	cout << *i++ << endl;
  }
    
  if(array3[0] != 1)
    failures++;
    if(array3[1] != 4)
    failures++;
    if(array3[2] != 9)
    failures++;
    if(array3[3] != 16)
    failures++;
  return failures;
}
