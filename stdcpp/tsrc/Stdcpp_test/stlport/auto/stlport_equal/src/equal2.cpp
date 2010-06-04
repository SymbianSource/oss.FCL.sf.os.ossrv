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
#define equal2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
bool values_squared(int a_, int b_)
{
  return(a_ * a_ == b_);
}
int equal2_test(int, char**)
{
	cout<<"Results of equal2_test:"<<endl;

	vector <int> v1(10);
	vector <int> v2(10);
	for(int i = 0; i < v1.size(); i++)
	{
	v1[i] = i;
	v2[i] = i * i;
	}
	int failures = 0;
	if(equal(v1.begin(), v1.end(), v2.begin(), values_squared))
	{
		cout << "v2[i] == v1[i] * v1[i]" << endl;
	}
	else
	{
		cout << "v2[i] != v1[i] * v1[i]" << endl;
		failures++;
	}

	if(!failures)
    return 0;
  else
    return 1;

}
