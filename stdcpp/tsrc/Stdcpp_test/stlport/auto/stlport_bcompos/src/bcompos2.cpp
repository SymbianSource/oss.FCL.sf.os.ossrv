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

#include "unary.h"

#ifdef MAIN
#define bcompos2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int bcompos2_test(int, char**)
{

	cout<<"Results of bcompos2_test:"<<endl;

	int array [6] = { -2, -1 , 0, 1, 2, 3 };

	int* p = find_if((int*)array, (int*)array + 6,
	compose2(logical_and<bool>(), odd(), positive()));
	if(p != array + 6)
	cout << *p << " is odd and positive" << endl;

	if (*p == 1)
	   return 0;
  else
  return 1;
}
