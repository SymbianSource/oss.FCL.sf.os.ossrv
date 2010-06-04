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
#define stblsrt2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

static bool string_less(const char* a_, const char* b_)
{
  return strcmp(a_, b_) < 0 ? 1 : 0;
}

int stblsrt2_test(int, char**)
{
  int failures=0;
  cout<<"Results of stblsrt2_test:"<<endl;

char* letters[6] = {"bb", "aa", "ll", "dd", "qq", "cc" };

  stable_sort(letters, letters + 6, string_less);
  for(int i = 0; i < 6; i++)
    cout << letters[i] << ' ';
  cout << endl;
  
  if(strcmp("aa",letters[0])!=0)
    failures++;
  else if(strcmp("bb",letters[1])!=0)
    failures++; 
  else if(strcmp("cc",letters[2])!=0)
    failures++;
  else if(strcmp("dd",letters[3])!=0)
    failures++; 
  else if(strcmp("ll",letters[4])!=0)
    failures++;
  else if(strcmp("qq",letters[5])!=0)
    failures++; 
      
  if(failures)
    return 1;
  else
    return 0;  
}

