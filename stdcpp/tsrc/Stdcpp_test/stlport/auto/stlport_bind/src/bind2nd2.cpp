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
#define bind2nd2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int bind2nd2_test(int, char**)
{

	cout<<"Results of bind2nd2_test:"<<endl;
	int array [3] = { 1, 2, 3 };

	replace_if(array, array + 3, bind2nd(greater<int>(), 2), 4);
	for(int i = 0; i < 3; i++)
	{
		cout << array[i] << endl;
	}
		
	if((array[0] == 1) && (array[1] == 2) && (array[2] == 4))
	   return 0;
  	else
  		return 1;
}
