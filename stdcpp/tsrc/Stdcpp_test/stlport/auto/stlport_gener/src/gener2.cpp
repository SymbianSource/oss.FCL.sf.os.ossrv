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


#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iterator>

#include "fib.h"

#ifdef MAIN
#define gener2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int gener2_test(int, char**)
{
	cout<<"Results of gener2_test:"<<endl;
	int fib_res[10] = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };

	vector <int> v1(10);
	Fibonacci generator;
	int failures = 0;
	generate(v1.begin(), v1.end(), generator);
	ostream_iterator<int> iter(cout, " ");
	copy(v1.begin(), v1.end(), iter);
	cout << endl;

	for (int i = 0; i < 10; i++)
	{
		if(v1[i] != fib_res[i])
			failures++;
	}

	if (!failures)
	  	return 0;
	else
	return 1;
}
