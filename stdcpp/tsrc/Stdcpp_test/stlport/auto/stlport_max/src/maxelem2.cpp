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
#define maxelem2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

static bool str_compare(const char* a_, const char* b_)
{
  return strcmp(a_, b_) < 0 ? 1 : 0;
}

int maxelem2_test(int, char**)
{
  cout<<"Results of maxelem2_test:"<<endl;

char* names[] = { "Brett", "Graham", "Jack", "Mike", "Todd" };

  const unsigned namesCt = sizeof(names)/sizeof(names[0]);
  string max1 = *max_element((char**)names, (char**)names + namesCt, str_compare);
  cout << *max_element((char**)names, (char**)names + namesCt, str_compare) << endl;
  if(max1 == "Todd")
  return 0;
  else
  return 1;
}
