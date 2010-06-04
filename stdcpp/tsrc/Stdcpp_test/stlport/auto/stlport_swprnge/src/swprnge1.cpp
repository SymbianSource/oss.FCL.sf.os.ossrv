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
#define swprnge1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int swprnge1_test(int, char**)
{
  cout<<"Results of swprnge1_test:"<<endl;
  char word1[] = "World";
  char word2[] = "Hello";
  cout << word1 << " " << word2 << endl;
  swap_ranges((char*)word1, (char*)word1 + ::strlen(word1), (char*)word2);
  cout << word1 << " " << word2 << endl;
  
  if(strcmp(word1,"Hello") || strcmp(word2,"World"))
     return 1;
  else
     return 0;   
}

