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
#include <numeric>
#include <functional>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class DivideTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(DivideTest);
  CPPUNIT_TEST(div);
  CPPUNIT_TEST_SUITE_END();

protected:
  void div();
};

CPPUNIT_TEST_SUITE_REGISTRATION(DivideTest);

//
// tests implementation
//
void DivideTest::div()
{
  int input [3] = { 2, 3, 4 };
  int result = accumulate(input, input + 3, 48, divides<int>());
  CPPUNIT_ASSERT(result==2);
}
