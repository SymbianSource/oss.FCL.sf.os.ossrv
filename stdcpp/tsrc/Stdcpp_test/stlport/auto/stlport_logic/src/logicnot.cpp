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
#include <functional>
#include <algorithm>

#ifdef MAIN 
#define logicnot_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int logicnot_test(int, char**)
{
  cout<<"Results of logicnot_test:"<<endl;
bool input [7] = { 1, 0, 0, 1, 1, 1, 1 };

  int n = 0;
  count_if(input, input + 7, logical_not<bool>(), n);
  cout << "count = " << n << endl;
  if(n != 2)
  return 1;
  else
  return 0;
}
