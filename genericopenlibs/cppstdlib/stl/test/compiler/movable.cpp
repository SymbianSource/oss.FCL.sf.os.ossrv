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

#include <list>
#include <vector>
#include <string>

using namespace std;

struct S :
    public string
{
};

void test()
{
  list<S> l;
  l.push_back( S() );

  vector<S> v;
  v.push_back( S() );
}

