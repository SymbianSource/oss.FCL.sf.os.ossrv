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
#include <numeric>


#ifdef MAIN
#define divides_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int divides_test(int, char**)
{
	cout<<"Results of divides_test:"<<endl;
	int input [3] = { 2, 3, 4 };

	int result = accumulate(input, input + 3, 48, divides<int>());
	cout << "result = " << result << endl;

	if(result == 2)
    return 0;
  else
    return 1;

}
