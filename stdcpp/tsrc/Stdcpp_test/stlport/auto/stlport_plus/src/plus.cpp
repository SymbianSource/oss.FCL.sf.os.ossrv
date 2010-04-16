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
#define plus_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int plus_test(int, char**)
{
  cout<<"Results of plus_test:"<<endl;
int input1 [4] = { 1, 6, 11, 8 };
int input2 [4] = { 1, 5, 2, 3 };

  int total = 
    inner_product(input1, input1 + 4, input2, 0, plus<int>(), multiplies <int>());
  cout << "total = " << total << endl;
  
  if(77==total)
     return 0;
  else
     return 1;   
}
