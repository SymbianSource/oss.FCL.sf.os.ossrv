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

#ifdef MAIN
#define findif0_test main
#endif
static bool odd(int a_)
{
  return a_ % 2;
}

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int findif0_test(int, char**)
{
	cout<<"Results of findif0_test:"<<endl;

	int numbers[6] = { 2, 4, 8, 15, 32, 64 };

	int* location = find_if((int*)numbers, (int*)numbers + 6, odd);
	if(location != numbers + 6)
	cout
	  << "Value "
	  << *location
	  << " at offset "
	  <<(location - numbers)
	  << " is odd"
	  << endl;

	if((*location == 15) && ((location - numbers) == 3))
    return 0;
  else
    return 1;

}
