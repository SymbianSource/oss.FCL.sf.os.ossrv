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

 
#include <algorithm>
#include <cstring> 
#include <string>
#include <deque>
#include <iterator>
#include <iostream>
#include <functional>

typedef std::string Str;
typedef std::deque<Str> Dq;
#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int insert1_test(int, char**)
{
  Str array1 [] = { "laurie", "jennifer", "leisa" };
  Dq nam(array1, array1 + 3);
  Dq::iterator i = nam.begin() + 2;
  Str a;
  
   a=*i;
   cout<<*i;
   
  if(a.compare("leisa")!=0)  
   return 1;
  else   
  return 0;
}
