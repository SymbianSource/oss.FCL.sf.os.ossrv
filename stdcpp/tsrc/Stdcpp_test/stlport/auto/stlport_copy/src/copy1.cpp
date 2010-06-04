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
#include <iostream>
#include <cstring>


#ifdef MAIN
#define copy1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int copy1_test(int, char**)
{
	cout<<"Results of copy1_test:"<<endl;
	char string[23] = "A string to be copied.";

	char result[23];
	copy(string, string + 23, result);
	cout << " Src: " << string << "\nDest: " << result << endl;

	if (!strcmp(string, result))
 		return 0;
  	else
  	   return 1;
}
