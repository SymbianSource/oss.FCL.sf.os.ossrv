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
#define nextprm0_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int nextprm0_test(int, char**)
{
  cout<<"Results of nextprm0_test:"<<endl;
int v1[3] = { 0, 1, 2 };
int failures = 0;
  next_permutation(v1, v1 + 3);
  for(int i = 0; i < 3; i++)
    cout << v1[i] << ' ';
  cout << endl;
  if(v1[0] != 0)
  failures++;
  if(v1[1] != 2)
  failures++;
  if(v1[2] != 1)
  failures++;
  return failures;
}
