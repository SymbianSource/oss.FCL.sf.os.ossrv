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
#include <vector>
#include <algorithm>
#include <functional>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class GreaterTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(GreaterTest);
  CPPUNIT_TEST(greatert);
  CPPUNIT_TEST(greatereq);
  CPPUNIT_TEST_SUITE_END();

protected:
  void greatert();
  void greatereq();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GreaterTest);

//
// tests implementation
//
void GreaterTest::greatert()
{
  int array[4] = { 3, 1, 4, 2 };
  sort(array, array + 4, greater<int>() );

  CPPUNIT_ASSERT(array[0]==4);
  CPPUNIT_ASSERT(array[1]==3);
  CPPUNIT_ASSERT(array[2]==2);
  CPPUNIT_ASSERT(array[3]==1);
}
void GreaterTest::greatereq()
{
  int array [4] = { 3, 1, 4, 2 };
  sort(array, array + 4, greater_equal<int>());
  CPPUNIT_ASSERT(array[0]==4);
  CPPUNIT_ASSERT(array[1]==3);
  CPPUNIT_ASSERT(array[2]==2);
  CPPUNIT_ASSERT(array[3]==1);
}
