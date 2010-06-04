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
#include <functional>

#ifdef MAIN
#define bnegate2_test main
#endif


#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int bnegate2_test(int, char**)
{

	cout<<"Results of bnegate2_test:"<<endl;
	int array [4] = { 4, 9, 7, 1 };
	int sorted_array[4] = {1, 4, 7, 9};
	int failures = 0;

	sort(array, array + 4, not2(greater<int>()));
	for(int i = 0; i < 4; i++)
	{
		cout << array[i] << endl;
		if (array[i] != sorted_array[i])
			failures++;
	}
	if(!failures)
 		return 0;
  	else
  	   return 1;
}
