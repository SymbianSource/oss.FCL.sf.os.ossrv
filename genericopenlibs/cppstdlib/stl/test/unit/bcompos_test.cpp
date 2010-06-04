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
#include "unary.h"

#include "cppunit/cppunit_proxy.h"

#if defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class BcomposTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(BcomposTest);
#if !defined (STLPORT) || defined (_STLP_NO_EXTENSIONS)
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(bcompos1);
  CPPUNIT_TEST(bcompos2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void bcompos1();
  void bcompos2();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BcomposTest);

//
// tests implementation
//
void BcomposTest::bcompos1()
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  int array [6] = { -2, -1, 0, 1, 2, 3 };

  binary_compose<logical_and<bool>, odd, positive>
  b = binary_compose<logical_and<bool>, odd, positive>(logical_and<bool>(), odd(), positive());

  int* p = find_if((int*)array, (int*)array + 6, b);
  CPPUNIT_ASSERT(p != array + 6);
#endif
}

void BcomposTest::bcompos2()
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  int array [6] = { -2, -1 , 0, 1, 2, 3 };

  int* p = find_if((int*)array, (int*)array + 6,
  compose2(logical_and<bool>(), odd(), positive()));
  CPPUNIT_ASSERT(p != array + 6);
#endif
}
