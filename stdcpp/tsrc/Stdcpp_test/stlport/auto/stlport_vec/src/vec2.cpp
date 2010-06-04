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
#include <vector>
#include <algorithm>

#ifdef MAIN 
#define vec2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

static void print(vector<double>& vector_)
{
  for(int i = 0; i < vector_.size(); i++)
    cout << vector_[i] << " ";
  cout << endl;
}

int vec2_test(int, char**)
{
  int failures=0;
  cout<<"Results of vec2_test:"<<endl;

  vector<double> v1; // Empty vector of doubles.
  v1.push_back(32.1);
  v1.push_back(40.5);
  vector<double> v2; // Another empty vector of doubles.
  v2.push_back(3.56);
  cout << "v1 = ";
  print(v1);
  cout << "v2 = ";
  print(v2);
  
  if(32.1!=v1[0])
    failures++;
  else if(40.5 !=v1[1])
    failures++;
  else if(3.56 !=v2[0])
    failures++;     
    
  v1.swap(v2); // Swap the vector's contents.
  cout << "v1 = ";
  print(v1);
  cout << "v2 = ";
  print(v2);
  
  if(32.1!=v2[0])
    failures++;
  else if(40.5 !=v2[1])
    failures++;
  else if(3.56 !=v1[0])
    failures++; 
    
  v2 = v1; // Assign one vector to another.
  cout << "v2 = ";
  print(v2);
  
  if(3.56!=v2[0])
   failures++;
   
   if(failures)
     return 1;
   else   
    return 0;
}

/*Results of vec2_test:
v1 = 32.1 40.5
v2 = 3.56

v1 = 3.56
v2 = 32.1 40.5

v2 = 3.56
*/
