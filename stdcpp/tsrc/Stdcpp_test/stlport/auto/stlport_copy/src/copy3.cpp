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
#include <iterator>

#ifdef MAIN
#define copy3_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int copy3_test(int, char**)
{

	cout<<"Results of copy3_test:"<<endl;
	int failures = 0;
	vector <int> v1(10);
	for(int i = 0; i < v1.size(); i++)
		v1[i] = i;
	vector <int> v2(10);
	copy(v1.begin(), v1.end(), v2.begin());

	for (int i = 0; i < v1.size(); i++)
	{
		if(v2[i] != i)
			failures++;
	}

	ostream_iterator<int> iter(cout, " ");
	copy(v2.begin(), v2.end(), iter);
	cout << endl;

	if(!failures)
    return 0;
  else
    return 1;

}
