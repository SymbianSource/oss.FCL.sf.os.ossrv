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
#define equalto_test main
#endif


#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int equalto_test(int, char**)
{
	cout<<"Results of equalto_test:"<<endl;
	int input1 [4] = { 1, 7, 2, 2 };
	int input2 [4] = { 1, 6, 2, 3 };
	int res_arr[4] = { 1, 0, 1, 0 };
	int failures = 0;

	int output [4];
	transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, equal_to<int>());
	for(int i = 0; i < 4; i++)
	{
		cout << output[i] << endl;
		if (output[i] != res_arr[i])
			failures++;
	}

	if(!failures)
    return 0;
  else
    return 1;
}

