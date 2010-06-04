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
#define swap1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int swap1_test(int, char**)
{
  cout<<"Results of swap1_test:"<<endl;
  int a = 42;
  int b = 19;
  cout << "a = " << a << " b = " << b << endl;
  swap(a, b);
  cout << "a = " << a << " b = " << b << endl;
  
  if(a!=19 || b!=42)
     return 1;
  else
     return 0;
}

