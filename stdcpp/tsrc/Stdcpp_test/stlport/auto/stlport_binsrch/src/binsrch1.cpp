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
#define binsrch1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int binsrch1_test(int, char**)
{
	cout<<"Results of binsrch1_test:"<<endl;
	int vector[100];
	for(int i = 0; i < 100; i++)
	vector[i] = i;

	if(binary_search(vector, vector + 100, 42))
	{
		cout << "found 42" << endl;
	 	return 0;
	}    
	else
	{
		cout << "did not find 42" << endl;
		return 1;
	}
}
