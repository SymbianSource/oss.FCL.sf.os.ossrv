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

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>

#include "fadapter.h"

#ifdef MAIN
#define genern1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif


static int cxxrand() { return rand();}

int genern1_test(int, char**)
{
   cout<<"Results of genern1_test:"<<endl;

#ifndef __STL_MEMBER_POINTER_PARAM_BUG		//*TY 07/18/98 - added conditional
											// since ptr_gen() is not defined under this condition
											// (see xfunction.h)
  vector <int> v1(10);

  generate_n(v1.begin(), v1.size(), ptr_gen(cxxrand));

  for(int i = 0; i < 10; i++)
    cout << v1[i] << ' ';
  cout << endl;
#endif	//	__STL_MEMBER_POINTER_PARAM_BUG	//*TY 07/18/98 - added

  return 0;
}
