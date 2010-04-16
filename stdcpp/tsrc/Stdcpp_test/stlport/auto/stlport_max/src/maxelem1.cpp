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
#define maxelem1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int maxelem1_test(int, char**)
{
  cout<<"Results of maxelem1_test:"<<endl;
int numbers[6] = { 4, 10, 56, 11, -42, 19 };
int i = *max_element((int*)numbers, (int*)numbers + 6);
  cout << *max_element((int*)numbers, (int*)numbers + 6) << endl;
  if(i==56)
  return 0;
  else
  return 1;
}
