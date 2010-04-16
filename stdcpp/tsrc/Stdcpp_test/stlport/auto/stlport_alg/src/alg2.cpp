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
#define alg2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int alg2_test(int, char**)
{
 
  cout<<"Results of alg2_test:"<<endl;
  int n = 0;
  int i [] = { 1, 4, 2, 8, 2, 2 };

  count(i, i + 6, 2, n);
  cout << "Count of 2s = " << n << endl;

  if (n == 3)
  return 0;
  else 
  return 1;
}
