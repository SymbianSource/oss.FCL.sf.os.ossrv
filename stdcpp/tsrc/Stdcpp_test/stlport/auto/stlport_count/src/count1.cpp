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
#include <vector>
#include <iostream>

#ifdef MAIN
#define count1_test main
#endif


#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int count1_test(int, char**)
{

	cout<<"Results of count1_test:"<<endl;
	vector <int> numbers(100);
	for(int i = 0; i < 100; i++)
	numbers[i] = i % 3;
	int elements = 0;
	count(numbers.begin(), numbers.end(), 2, elements);
	cout << "Found " << elements << " 2's." << endl;

	if(elements == 33)
	    return 0;
  	else
    return 1;

}
