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
#define parsrtc0_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int parsrtc0_test(int, char**)
{
  int failures=0;
  
  cout<<"Results of parsrtc0_test:"<<endl;
  int numbers[6] = { 5, 2, 4, 3, 1, 6 };

  int result[3];
  partial_sort_copy((int*)numbers, (int*)numbers + 6, (int*)result, (int*)result + 3);
  for(int i = 0; i < 3; i++)
    cout << result[i] << ' ';
  cout << endl;
  
  if(1!=result[0])
     failures++;  
  else if(2!=result[1])
     failures++;
  else if(3!=result[2])
     failures++;      
  
  
  if(failures)
    return 1;
  else  
     return 0;
}
