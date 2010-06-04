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
#include <map>

#ifdef MAIN 
#define map1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

#include "map1.hpp"
ostream& operator<<(ostream& s, Int x)
  { return s << x.val; }

int map1_test(int, char**)
{
  cout<<"Results of map1_test:"<<endl;
  typedef map<char, Int, less<char> > maptype;
  maptype m;
  int failures = 0;
  // Store mappings between roman numerals and decimals.
  char ch = 'l';
  m[ch] = 50;
  m['x'] = 20; // Deliberate mistake.
  m['v'] = 5;
  m['i'] = 1;
  cout << "m['x'] = " << m['x'] << endl;
  m['x'] = 10; // Correct mistake.
  cout << "m['x'] = " << m['x'] << endl;
  cout << "m['z'] = " << m['z'] << endl; // Note default value is added.
  cout << "m.count('z') = " << m.count('z') << endl;

  pair<maptype::iterator, bool> p =
      m.insert(pair<const char, Int>('c', 100));
  if(p.second)
    cout << "First insertion successful" << endl;
  p = m.insert(pair<const char, Int>('c', 100));
  if(p.second)
  {
  	
    cout << "Second insertion successful" << endl;
    failures++;
  }
  else
    cout << "Existing pair " <<(*(p.first)).first
         << " -> " <<(*(p.first)).second << endl;
        Int a = 100;
        if(((*(p.first)).first) != 'c')
        	 failures++;
        if ((*(p.first)).second != a)
  		     failures++;
         return failures;
}
