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
#define revcopy1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int revcopy1_test(int, char**)
{
  int failures=0;
  cout<<"Results of revcopy1_test:"<<endl;
  int numbers[6] = { 0, 1, 2, 3, 4, 5 };

  int result[6];
  reverse_copy((int*)numbers, (int*)numbers + 6, (int*)result);
  int i;
  for(i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;

  if(0!=numbers[0])
    failures++;
  else if(1!=numbers[1])
    failures++;
  else if(2!=numbers[2])
    failures++;
  else if(3!=numbers[3])
    failures++;
  else if(4!=numbers[4])
    failures++;
  else if(5!=numbers[5])
    failures++;
    

  for(i = 0; i < 6; i++)
    cout << result[i] << ' ';
  cout << endl;
  
  if(5!=result[0])
    failures++;
  else if(4!=result[1])
    failures++;
  else if(3!=result[2])
    failures++;
  else if(2!=result[3])
    failures++;
  else if(1!=result[4])
    failures++;
  else if(0!=result[5])
    failures++;
  
  if(failures)
    return 1;
  else
    return 0;
}

