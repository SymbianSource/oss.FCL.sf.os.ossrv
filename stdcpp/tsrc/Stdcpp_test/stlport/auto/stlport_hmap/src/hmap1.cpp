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
#include <hash_map>
#include <rope>

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
#ifdef MAIN
#define hmap1_test main
#endif

int hmap1_test(int, char**)
{
	cout<<"Results of hmap1_test:"<<endl;
	typedef hash_map<char, crope, hash<char>, equal_to<char> > maptype;
	maptype m;

	int failures = 0;
	// Store mappings between roman numerals and decimals.
	m['l'] = "50";
	m['x'] = "20"; // Deliberate mistake.
	m['v'] = "5";
	m['i'] = "1";
	cout << "m['x'] = " << m['x'] << endl;
	
	m['x'] = "10"; // Correct mistake.
	cout << "m['x'] = " << m['x'] << endl;

	cout << "m['z'] = " << m['z'] << endl; // Note default value is added.
	cout << "m.count('z') = " << m.count('z') << endl;
	
	pair<maptype::iterator, bool> p =
	m.insert(pair<const char, crope>('c', crope("100")));
	if(p.second)
	{
		cout << "First insertion successful" << endl;
	}
	else
	{
		failures++;
	}
	p = m.insert(pair<const char, crope>('c', crope("100")));
	if(p.second)
	{
		cout << "Second insertion successful" << endl;
		failures++;
	}
	else
	{
		cout << "Existing pair " <<(*(p.first)).first
		<< " -> " <<(*(p.first)).second << endl;		
	}

	if (!failures)
	return 0;
	else
	return 1;
}
