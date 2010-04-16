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
#include <numeric>
#include <functional>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class TimesTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(TimesTest);
  CPPUNIT_TEST(times);
  CPPUNIT_TEST_SUITE_END();

protected:
  void times();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TimesTest);

//
// tests implementation
//
void TimesTest::times()
{
  int input [4] = { 1, 5, 7, 2 };
  int total = accumulate(input, input + 4, 1, multiplies<int>());
  CPPUNIT_ASSERT(total==70);
}
