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

#include <string>
#include <iostream>

#ifdef MAIN 
#define string1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int string1_test(int, char**)
{
  int failures=0;
  cout<<"Results of string1_test:"<<endl;
  char* array = "Hello, World!";
  std::string v(array);
  int i;
  cout << v << endl;
  
  if(v.compare("Hello, World!"))
     failures++;
     
  v.erase(v.begin() + 1, v.end() - 1); // Erase all but first and last.
  for(i = 0; i < v.size(); i++)
    cout << "v[" << i << "] = " << v[i] << endl;
  cout << endl;
  
   if('H'!=v[0])
     failures++;
   else if('!'!=v[1])
     failures++;
      
  
  v.insert(1, (char*)array);
  v.erase(v.begin()); // Erase first element.
  v.erase(v.end() - 1); // Erase last element.
  cout << v << endl;
  if(v.compare("Hello, World!"))
    failures++;
  v.clear(); // Erase all.
  
  if(failures)
    return 1;
  else
    return 0;  
}


