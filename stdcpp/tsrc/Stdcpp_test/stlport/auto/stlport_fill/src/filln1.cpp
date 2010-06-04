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

#ifdef MAIN
#define filln1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int filln1_test(int, char**)
{
	cout<<"Results of filln1_test:"<<endl;
	vector <int> v(10);
	fill_n(v.begin(), v.size(), 42);
	int failures = 0;
	for(int i = 0; i < 10; i++)
	{
		cout << v[i] << ' ';
		if(v[i] != 42)
			failures++;
	}
	cout << endl;

	if(!failures)
    return 0;
  else
    return 1;

}
