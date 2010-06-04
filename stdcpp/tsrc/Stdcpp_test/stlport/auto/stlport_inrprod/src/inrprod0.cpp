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

#include <numeric>
#include <iostream>

#ifdef MAIN 
#define inrprod0_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int inrprod0_test(int, char**)
{
  cout<<"Results of inrprod0_test:"<<endl;
 
int vector1[5] = { 1, 2, 3, 4, 5 };
int vector2[5] = { 1, 2, 3, 4, 5 };

  int result;
  result = inner_product(vector1, vector1 + 5, vector2, 0);
  cout << "Inner product = " << result << endl;
  if (result == 55)
  return 0;
  else 
  return 1;
}

