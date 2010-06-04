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
#define lexcmp1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int lexcmp1_test(int, char**)
{
  cout<<"Results of lexcmp1_test:"<<endl;
const unsigned size = 6;
char n1[size] = "shoe";
char n2[size] = "shine";
int failures=0;

  bool before = lexicographical_compare(n1, n1 + size, n2, n2 + size);
  if(before)
  {
  	    cout << n1 << " is before " << n2 << endl;
  	    failures++;
  }
  else
    cout << n2 << " is before " << n1 << endl;
  return failures;
}
