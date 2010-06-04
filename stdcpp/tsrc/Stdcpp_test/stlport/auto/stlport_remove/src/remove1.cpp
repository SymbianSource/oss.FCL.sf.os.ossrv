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
#define remove1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int remove1_test(int, char**)
{
  int failures=0;
  cout<<"Results of remove1_test:"<<endl;
  int numbers[6] = { 1, 2, 3, 1, 2, 3 };

  remove((int*)numbers, (int*)numbers + 6, 1);
  for(int i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  
  if(2!=numbers[0])
     failures++;
  else if(3!=numbers[1])
     failures++;
   else if(2!=numbers[2])
     failures++;
  else if(3!=numbers[3])
     failures++;
   else if(2!=numbers[4])
     failures++;             
   else if(3!=numbers[5])
     failures++;  

  if(failures)
    return 1;
  else
    return 0;
}

