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
class LexcmpTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(LexcmpTest);
  CPPUNIT_TEST(lexcmp1);
  CPPUNIT_TEST(lexcmp2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void lexcmp1();
  void lexcmp2();
};

CPPUNIT_TEST_SUITE_REGISTRATION(LexcmpTest);

//
// tests implementation
//
void LexcmpTest::lexcmp1()
{
  const unsigned size = 6;
  char n1[size] = "shoe";
  char n2[size] = "shine";

  bool before = lexicographical_compare(n1, n1 + size, n2, n2 + size);
  CPPUNIT_ASSERT(!before);
}
void LexcmpTest::lexcmp2()
{
  const unsigned size = 6;
  char n1[size] = "shoe";
  char n2[size] = "shine";

  bool before = lexicographical_compare(n1, n1 + size, n2, n2 + size, greater<char>());
  CPPUNIT_ASSERT(before);
}
