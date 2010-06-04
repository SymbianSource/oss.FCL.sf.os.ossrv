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

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>
#include <fstream>

#ifdef MAIN 
#define merge1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int merge1_test(int, char**)
{
  cout<<"Results of merge1_test:"<<endl;
  ofstream Outfile("c:\\merge1.txt");
  vector <int> v1(5);
  vector <int> v2(v1.size());
  iota(v1.begin(), v1.end(), 0);
  iota(v2.begin(), v2.end(), 3);
  vector <int> result(v1.size() + v2.size());
  merge(v1.begin(), v1.end(), v2.begin(), v2.end(), result.begin());
  ostream_iterator <int> iter(cout, " ");
  ostream_iterator <int> iterfile(Outfile, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  copy(v2.begin(), v2.end(), iter);
  cout << endl;
  copy(result.begin(), result.end(), iter);
  copy(result.begin(), result.end(), iterfile);
  cout << endl;
  return 0;
}
