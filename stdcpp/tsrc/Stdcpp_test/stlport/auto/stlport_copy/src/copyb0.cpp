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
#define copyb0_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int copyb0_test(int, char**)
{

cout<<"Results of copyb0_test:"<<endl;
int numbers[5] = { 1, 2, 3, 4, 5 };

int failures = 0;
int result[5];
copy_backward(numbers, numbers + 5, (int*)result + 5);
int i;
for(i = 0; i < 5; i++)
	cout << numbers[i] << ' ';
cout << endl;
for(i = 0; i < 5; i++)
	cout << result[i] << ' ';
cout << endl;

for(int i = 0; i < 5; i++)
{
	if (result[i] != numbers[i])
		failures++;
}

if(!failures)
    return 0;
  else
    return 1;

}
