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
/*
 * Note: Strstreams are really broken in STLport. But strstreams are 
 * obsolete, and even if ones was mentioned in D7.1--D7.4 of 
 * Standard, we have no wish to spent time with repair ones.
 */
#include <strstream>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

class StrstreamBufferReadTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(StrstreamBufferReadTest);
  CPPUNIT_TEST(readFromBuffer);
  CPPUNIT_TEST_SUITE_END();

protected:
  void readFromBuffer();
};

CPPUNIT_TEST_SUITE_REGISTRATION(StrstreamBufferReadTest);

void StrstreamBufferReadTest::readFromBuffer()
{
  char hello[] = "Hello";
  strstream stream(hello, sizeof(hello), ios_base::in);
  char cur;
  stream >> cur;
  CPPUNIT_ASSERT(cur == 'H'); 
}
