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
#define minelem1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int minelem1_test(int, char**)
{
  cout<<"Results of minelem1_test:"<<endl;
int numbers[6] = { -10, 15, -100, 36, -242, 42 };

  cout <<  *min_element((int*)numbers, (int*)numbers + 6) << endl;
  if(*min_element((int*)numbers, (int*)numbers + 6) == -242)
  return 0;
  else
  return 1;
}
