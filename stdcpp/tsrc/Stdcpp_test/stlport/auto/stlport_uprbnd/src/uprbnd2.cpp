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
#define uprbnd2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

static bool char_str_less(const char* a_, const char* b_)
{
  return strcmp(a_, b_) < 0 ? 1 : 0;
}

int uprbnd2_test(int, char**)
{
  int x=0;
  cout<<"Results of uprbnd2_test:"<<endl;

  char* str [] = { "a", "a", "b", "b", "q", "w", "z" };

  const unsigned strCt = sizeof(str)/sizeof(str[0]);
  // DEC C++ generates incorrect template instatiation code 
  // for "d" so must cast 
  
  x=(upper_bound((char**)str,  (char**)str + strCt, (const char *)"d", char_str_less) - str);
  
  cout<< "d can be inserted at index: "<<x<<endl;
  
  
  if(4!=x)
    return 1;   
  else  
   return 0;
}


