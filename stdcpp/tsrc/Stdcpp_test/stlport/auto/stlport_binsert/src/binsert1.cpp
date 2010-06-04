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
#include <vector>
#include <algorithm>


#ifdef MAIN 
#define binsert1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int binsert1_test(int, char**)
{
	cout<<"Results of binsert1_test:"<<endl;
	char* array [] = { "laurie", "jennifer", "leisa" };

	vector<char*> names;
	copy(array, array + 3, back_insert_iterator<vector <char*> >(names));
	std::vector<char*>::iterator i;
	int j;
	int failures = 0;
	for(i = names.begin(), j=0; i != names.end(); i++, j++)
	{
		cout << *i << endl;
		if(*i != array[j])
			failures++;
	}
	
	if(!failures)
 		return 0;
  	else
  	   return 1;
}
