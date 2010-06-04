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
#define adjfind1_test main
#endif


#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int adjfind1_test(int, char**)
{

	cout<<"Results of adjfind1_test:"<<endl;
	int failures = 0;
	typedef vector<int> IntVector;
	IntVector v(10);
	for(int i = 0; i < v.size(); i++)
	v[i] = i;
	IntVector::iterator location;
	location = adjacent_find(v.begin(), v.end());
	if(location != v.end())
	{
		cout << "Found adjacent pair of: " << *location << endl;
		failures++;
	}
	else
	{
		cout << "No adjacent pairs" << endl;
	}
	v[6] = 7;
	location = adjacent_find(v.begin(), v.end());
	if(location != v.end())
	{
		cout << "Found adjacent pair of: " << *location << endl;
		if (*location != 7)
			failures++;
	}
	else
	{
		cout << "No adjacent pairs" << endl;
		failures++;
	}

	if (!failures)
		return 0;
	else
	return 1;
}
