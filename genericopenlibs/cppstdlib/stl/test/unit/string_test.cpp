// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// To make GLib C++ closer to STLport behavior we need this macro:
// Only mandatory when building unit tests without STLport, do not change
// anything when building with STLport
// 
//

#define _GLIBCXX_FULLY_DYNAMIC_STRING

//Has to be first for StackAllocator swap overload to be taken
//into account (at least using GCC 4.0.1)
#include "stack_allocator.h"

#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <sstream>
#endif

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
#  include <stdexcept>
#endif

#if !defined (STLPORT) || defined (_STLP_THREADS)
#  if defined (STLPORT) && defined (_STLP_PTHREADS) || \
      defined (__GNUC__) && !defined (__MINGW32__)
#    define USE_PTHREAD_API
#    include <pthread.h>
#  endif

#  if defined (STLPORT) && defined (_STLP_WIN32THREADS) || \
      defined (__GNUC__) && defined (__MINGW32__) || \
      defined (_MSC_VER)
#    define USE_WINDOWS_API
#    include <windows.h>
#  endif
#endif

#include "stack_allocator.h"
#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class StringTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(StringTest);
  CPPUNIT_TEST(constructor);
  CPPUNIT_TEST(reserve);
  CPPUNIT_TEST(assign);
  CPPUNIT_TEST(erase);
  CPPUNIT_TEST(data);
  CPPUNIT_TEST(c_str);
  CPPUNIT_TEST(null_char);
  CPPUNIT_TEST(insert);
  CPPUNIT_TEST(replace);
  CPPUNIT_TEST(resize);
  CPPUNIT_TEST(short_string);
  CPPUNIT_TEST(find);
  CPPUNIT_TEST(rfind);
  CPPUNIT_TEST(find_last_of);
  CPPUNIT_TEST(find_last_not_of);
  CPPUNIT_TEST(copy);
#if !defined (USE_PTHREAD_API) && !defined (USE_WINDOWS_API)
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(mt);
  CPPUNIT_STOP_IGNORE;
  CPPUNIT_TEST(short_string_optim_bug);
  CPPUNIT_TEST(compare);
#if defined (__DMC__)
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(template_expression);
#if defined (STLPORT) && defined (_STLP_MSVC) && (_STLP_MSVC < 1300)
#  define TE_TMP_TEST_IGNORED
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(te_tmp);
#if defined (TE_TMP_TEST_IGNORED)
  CPPUNIT_STOP_IGNORE;
#endif
#if defined (STLPORT) && defined (_STLP_NO_WCHAR_T)
  CPPUNIT_IGNORE;
#endif
#if defined (__CYGWIN__) && !defined (STLPORT)
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(template_wexpression);
  CPPUNIT_STOP_IGNORE;
#if defined (STLPORT) && defined (_STLP_USE_NO_IOSTREAMS)
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(io);
  CPPUNIT_STOP_IGNORE;
#if defined (STLPORT) && defined (_STLP_NO_CUSTOM_IO) 
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(allocator_with_state);
  CPPUNIT_STOP_IGNORE;
  CPPUNIT_TEST(capacity);
  CPPUNIT_TEST(str_cov1);
  CPPUNIT_TEST(str_cov2);
  CPPUNIT_TEST(str_cov3);
  CPPUNIT_TEST(str_cov4);
  CPPUNIT_TEST(str_cov5);
  CPPUNIT_TEST(str_cov6);
  CPPUNIT_TEST_SUITE_END();

protected:
  void constructor();
  void reserve();
  void erase();
  void data();
  void c_str();
  void null_char();
  void insert();
  void replace();
  void resize();
  void short_string();
  void find();
  void rfind();
  void find_last_of();
  void find_last_not_of();
  void copy();
  void assign();
  void mt();
  void short_string_optim_bug();
  void compare();
  void template_expression();
  void te_tmp();
  void template_wexpression();
  void io();
  void allocator_with_state();
  void capacity();
  void str_cov1();
  void str_cov2();
  void str_cov3();
  void str_cov4();
  void str_cov5();
  void str_cov6();
  static string func(const string& par) {
    string tmp( par );
    return tmp;
  }

#if defined (USE_PTHREAD_API) || defined (USE_WINDOWS_API)
#  if defined (USE_PTHREAD_API)
  static void* f(void*)
#  else
  static DWORD __stdcall f(void*)
#  endif
  {
    string s( "qyweyuewunfkHBUKGYUGL,wehbYGUW^(@T@H!BALWD:h^&@#*@(#:JKHWJ:CND" );

    for ( int i = 0; i < 2000000; ++i ) {
      string sx = func( s );
    }

    return 0;
  }
#endif

};

CPPUNIT_TEST_SUITE_REGISTRATION(StringTest);

//
// tests implementation
//
void StringTest::constructor()
{
#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    string s((size_t)-1, 'a');
    CPPUNIT_ASSERT( false );
  }
  catch (length_error const&) {
  }
  catch (...) {
    //Expected exception is length_error:
    CPPUNIT_ASSERT( false );
  }
#endif
}

void StringTest::reserve()
{
  string s;
#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    s.reserve(s.max_size() + 1);
    CPPUNIT_ASSERT( false );
  }
  catch (length_error const&) {
  }
  catch (...) {
    //Expected exception is length_error:
    CPPUNIT_ASSERT( false );
  }
#endif
}

void StringTest::mt()
{
#if defined (USE_PTHREAD_API) || defined (USE_WINDOWS_API)
  const int nth = 2;
#  if defined (USE_PTHREAD_API)
  pthread_t t[nth];

  for ( int i = 0; i < nth; ++i ) {
    pthread_create( &t[i], 0, f, 0 );
  }

  for ( int i = 0; i < nth; ++i ) {
    pthread_join( t[i], 0 );
  }
#  endif // PTHREAD

#  if defined (USE_WINDOWS_API)
  //DWORD start = GetTickCount();

  HANDLE t[nth];

  int i; // VC6 not support in-loop scope of cycle var
  for ( i = 0; i < nth; ++i ) {
    t[i] = CreateThread(NULL, 0, f, 0, 0, NULL);
  }

  if (WaitForMultipleObjects(nth, t, TRUE, INFINITE) == WAIT_FAILED) {
    // On some platforms (evc3/evc4) WaitForMultipleObjects() with fWaitAll == TRUE
    // is not supported. We then wait with a loop on each thread:
    for ( i = 0; i < nth; ++i ) {
      WaitForSingleObject(t[i], INFINITE);
    }
  }

  /*
  DWORD duration = GetTickCount() - start;
  ostringstream ostr;
  ostr << "Duration: " << duration << endl;
  CPPUNIT_MESSAGE(ostr.str().c_str());
  */
#  endif
#endif
}

void StringTest::short_string()
{
  string const ref_short_str1("str1"), ref_short_str2("str2");
  string short_str1(ref_short_str1), short_str2(ref_short_str2);
  string const ref_long_str1("str                                                  1");
  string const ref_long_str2("str                                                  2");
  string long_str1(ref_long_str1), long_str2(ref_long_str2);

  CPPUNIT_ASSERT(short_str1 == ref_short_str1);
  CPPUNIT_ASSERT(long_str1 == ref_long_str1);

  {
    string str1(short_str1);
    str1 = long_str1;
    CPPUNIT_ASSERT(str1 == ref_long_str1);
  }

  {
    string str1(long_str1);
    str1 = short_str1;
    CPPUNIT_ASSERT(str1 == ref_short_str1);
  }

  {
    short_str1.swap(short_str2);
    CPPUNIT_ASSERT((short_str1 == ref_short_str2) && (short_str2 == ref_short_str1));
    short_str1.swap(short_str2);
  }

  {
    long_str1.swap(long_str2);
    CPPUNIT_ASSERT((long_str1 == ref_long_str2) && (long_str2 == ref_long_str1));
    long_str1.swap(long_str2);
  }

  {
    short_str1.swap(long_str1);
    CPPUNIT_ASSERT((short_str1 == ref_long_str1) && (long_str1 == ref_short_str1));
    short_str1.swap(long_str1);
  }

  {
    long_str1.swap(short_str1);
    CPPUNIT_ASSERT((short_str1 == ref_long_str1) && (long_str1 == ref_short_str1));
    long_str1.swap(short_str1);
  }

  {
    //This is to test move constructor
    vector<string> str_vect;
    str_vect.push_back(short_str1);
    str_vect.push_back(long_str1);
    str_vect.push_back(short_str2);
    str_vect.push_back(long_str2);
    CPPUNIT_ASSERT((str_vect[0] == ref_short_str1) &&
                   (str_vect[1] == ref_long_str1) &&
                   (str_vect[2] == ref_short_str2) &&
                   (str_vect[3] == ref_long_str2));
  }
}

void StringTest::erase()
{
  char const* c_str = "Hello, World!";
  string str(c_str);
  CPPUNIT_ASSERT( str == c_str );

  str.erase(str.begin() + 1, str.end() - 1); // Erase all but first and last.

  size_t i;
  for (i = 0; i < str.size(); ++i) {
    switch ( i ) {
      case 0:
        CPPUNIT_ASSERT( str[i] == 'H' );
        break;
      case 1:
        CPPUNIT_ASSERT( str[i] == '!' );
        break;
      default:
        CPPUNIT_ASSERT( false );
    }
  }

  str.insert(1, c_str);
  str.erase(str.begin()); // Erase first element.
  str.erase(str.end() - 1); // Erase last element.
  CPPUNIT_ASSERT( str == c_str );
  str.clear(); // Erase all.
  CPPUNIT_ASSERT( str.empty() );

  str = c_str;
  CPPUNIT_ASSERT( str == c_str );

  str.erase(1, str.size() - 1); // Erase all but first and last.
  for (i = 0; i < str.size(); i++) {
    switch ( i ) {
      case 0:
        CPPUNIT_ASSERT( str[i] == 'H' );
        break;
      case 1:
        CPPUNIT_ASSERT( str[i] == '!' );
        break;
      default:
        CPPUNIT_ASSERT( false );
    }
  }

  str.erase(1);
  CPPUNIT_ASSERT( str == "H" );
}

void StringTest::data()
{
  string xx;

  CPPUNIT_ASSERT( xx.data() != 0 );  // ISO-IEC-14882:1998(E), 21.3.6, paragraph 3
#if 0
  /* This test really not required: in ISO-IEC-14882:1998(E) paragraph 3 stated:
   * '... and can have zero added to it', again: 'CAN', but not 'MUST'.
   * That's why I am comment this test. But I don't remove it due to I had
   * unevident problem with misinterpretation of data() return (i.e. data()
   * and c_str() provide different functionality!) and expect that this is
   * more-or-less common pitfall.
   *    - ptr
   */
  string low( "2004-01-01" );
  // Blocks A and B should follow each other.
  // Block A:
  xx = "123456";
  xx += low;
  if ( strcmp( xx.data(), "1234562004-01-01" ) != 0 ) {
    return -1;
  }
  // End of block A

  // Block B:
  xx = "1234";
  xx += ";";

  if ( strcmp( xx.data(), "1234;" ) != 0 ) {
    return -1;
  }
  // End of block B
#endif
}

void StringTest::c_str()
{
  string low( "2004-01-01" );
  string xx;
  string yy;

  CPPUNIT_ASSERT( *(yy.c_str()) == '\0' ); // ISO-IEC-14882:1998(E), 21.3.6, paragraph 1

  // Blocks A and B should follow each other.
  // Block A:
  xx = "123456";
  xx += low;
  CPPUNIT_ASSERT( strcmp( xx.c_str(), "1234562004-01-01" ) == 0 );
  // End of block A

  // Block B:
  xx = "1234";
  xx += ";";
  CPPUNIT_ASSERT( strcmp( xx.c_str(), "1234;" ) == 0 );
  // End of block B
}

void StringTest::null_char()
{
  // ISO/IEC 14882:1998(E), ISO/IEC 14882:2003(E), 21.3.4 ('... the const version')
  const string s( "123456" );

  CPPUNIT_CHECK( s[s.size()] == '\0' );

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    //Check is only here to avoid warning about value of expression not used
    CPPUNIT_CHECK( s.at(s.size()) == '\0' );
    CPPUNIT_ASSERT( false );
  }
  catch (out_of_range const&) {
    CPPUNIT_ASSERT( true );
  }
  catch ( ... ) {
    CPPUNIT_ASSERT( false );
  }
#endif
}

void StringTest::insert()
{
  string strorg = "This is test string for string calls";
  string str;
  /*
   * In case of reallocation there is no auto reference problem
   * so we reserve a big enough string to be sure to test this
   * particular point.
   */
  str.reserve(100);
  str = strorg;

  //test self insertion:
  str.insert(10, str.c_str() + 5, 15);
  CPPUNIT_ASSERT( str == "This is teis test string st string for string calls" );

  str = strorg;
  str.insert(15, str.c_str() + 5, 25);
  CPPUNIT_ASSERT( str == "This is test stis test string for stringring for string calls" );

  str = strorg;
  str.insert(0, str.c_str() + str.size() - 4, 4);
  CPPUNIT_ASSERT( str == "allsThis is test string for string calls" );

  str = strorg;
  str.insert(0, str.c_str() + str.size() / 2 - 1, str.size() / 2 + 1);
  CPPUNIT_ASSERT( str == "ng for string callsThis is test string for string calls" );

  str = strorg;
  string::iterator b = str.begin();
  string::const_iterator s = str.begin() + str.size() / 2 - 1;
  string::const_iterator e = str.end();
  str.insert( b, s, e );
  CPPUNIT_ASSERT( str == "ng for string callsThis is test string for string calls" );

  str = strorg;
  str.insert(str.begin(), str.begin() + str.size() / 2 - 1, str.end());
  CPPUNIT_ASSERT( str == "ng for string callsThis is test string for string calls" );

#ifdef _STLP_MEMBER_TEMPLATES
  vector<int> int_vect;
  //Just a compile time test:
  str.insert(str.end(), int_vect.begin(), int_vect.end());
#endif

  string str0;
  str0.insert(str0.begin(), 5, '0');
  CPPUNIT_ASSERT( str0 == "00000" );

  string str1;
  {
    string::size_type pos = 0, nb = 2;
    str1.insert(pos, nb, '1');
  }
  CPPUNIT_ASSERT( str1 == "11" );

  str0.insert(0, str1);
  CPPUNIT_ASSERT( str0 == "1100000" );

  string str2("2345");
  str0.insert(str0.size(), str2, 1, 2);
  CPPUNIT_ASSERT( str0 == "110000034" );

  str1.insert(str1.begin() + 1, 2, '2');
  CPPUNIT_ASSERT( str1 == "1221" );

  str1.insert(2, "333333", 3);
  CPPUNIT_ASSERT( str1 == "1233321" );

  str1.insert(4, "4444");
  CPPUNIT_ASSERT( str1 == "12334444321" );

  str1.insert(str1.begin() + 6, '5');
  CPPUNIT_ASSERT( str1 == "123344544321" );
}

void StringTest::replace()
{
  /*
   * This test case is for the non template basic_string::replace method,
   * this is why we play with the const iterators and reference to guaranty
   * that the right method is called.
   */
  const string v( "78" );
  string s( "123456" );
  string const& cs = s;

  string::iterator i = s.begin() + 1;
  s.replace(i, i + 3, v.begin(), v.end());
  CPPUNIT_ASSERT( s == "17856" );

  s = "123456";
  i = s.begin() + 1;
  s.replace(i, i + 1, v.begin(), v.end());
  CPPUNIT_ASSERT( s == "1783456" );

  s = "123456";
  i = s.begin() + 1;
  string::const_iterator ci = s.begin() + 1;
  s.replace(i, i + 3, ci + 3, cs.end());
  CPPUNIT_ASSERT( s == "15656" );

  s = "123456";
  i = s.begin() + 1;
  ci = s.begin() + 1;
  s.replace(i, i + 3, ci, ci + 2);
  CPPUNIT_ASSERT( s == "12356" );

  s = "123456";
  i = s.begin() + 1;
  ci = s.begin() + 1;
  s.replace(i, i + 3, ci + 1, cs.end());
  CPPUNIT_ASSERT( s == "1345656" );

  s = "123456";
  s.replace(s.begin() + 4, s.end(), cs.begin(), cs.end());
  CPPUNIT_ASSERT( s == "1234123456" );

  /*
   * This is the test for the template replace method.
   */
  s = "123456";
  string::iterator b = s.begin() + 4;
  string::iterator e = s.end();
  string::const_iterator rb = s.begin();
  string::const_iterator re = s.end();
  s.replace(b, e, rb, re);
  CPPUNIT_ASSERT( s == "1234123456" );

  s = "123456";
  s.replace(s.begin() + 4, s.end(), s.begin(), s.end());
  CPPUNIT_ASSERT( s == "1234123456" );

  string strorg("This is test string for string calls");
  string str = strorg;
  str.replace(5, 15, str.c_str(), 10);
  CPPUNIT_ASSERT( str == "This This is tefor string calls" );

  str = strorg;
  str.replace(5, 5, str.c_str(), 10);
  CPPUNIT_ASSERT( str == "This This is test string for string calls" );

#if !defined (STLPORT) || defined (_STLP_MEMBER_TEMPLATES)
  deque<char> cdeque;
  cdeque.push_back('I');
  str.replace(str.begin(), str.begin() + 11, cdeque.begin(), cdeque.end());
  CPPUNIT_ASSERT( str == "Is test string for string calls" );
#endif
}

void StringTest::resize()
{
  string s;

  s.resize(0);

  CPPUNIT_ASSERT( *s.c_str() == 0 );

  s = "1234567";

  s.resize(0);
  CPPUNIT_ASSERT( *s.c_str() == 0 );

  s = "1234567";
  s.resize(1);
  CPPUNIT_ASSERT( s.size() == 1 );
  CPPUNIT_ASSERT( *s.c_str() == '1' );
  CPPUNIT_ASSERT( *(s.c_str() + 1) == 0 );

  s = "1234567";
  s.resize(10);
  CPPUNIT_ASSERT( s.size() == 10 );
  CPPUNIT_ASSERT( s[6] == '7' );
  CPPUNIT_ASSERT( s[7] == 0 );
  CPPUNIT_ASSERT( s[8] == 0 );
  CPPUNIT_ASSERT( s[9] == 0 );
}

void StringTest::find()
{
  string s("one two three one two three");
  CPPUNIT_ASSERT( s.find("one") == 0 );
  CPPUNIT_ASSERT( s.find('t') == 4 );
  CPPUNIT_ASSERT( s.find('t', 5) == 8 );
  //We are trying to get a const reference to the npos string static member to
  //force the compiler to allocate memory for this variable. It used to reveal
  //a bug of STLport which was simply declaring npos without instanciating it.
#if !defined (STLPORT) || !defined (_STLP_STATIC_CONST_INIT_BUG)
  string::size_type const& npos_local = string::npos;
#else
#  define npos_local string::npos
#endif
  CPPUNIT_ASSERT( s.find("four") == npos_local );
  CPPUNIT_ASSERT( s.find("one", string::npos) == npos_local );

  CPPUNIT_ASSERT( s.find_first_of("abcde") == 2 );

  CPPUNIT_ASSERT( s.find_first_not_of("enotw ") == 9 );
}

void StringTest::rfind()
{
  // 21.3.6.2
  string s("one two three one two three");

  CPPUNIT_ASSERT( s.rfind("two") == 18 );
  CPPUNIT_ASSERT( s.rfind("two", 0) == string::npos );
  CPPUNIT_ASSERT( s.rfind("two", 11) == 4 );
  CPPUNIT_ASSERT( s.rfind('w') == 19 );

  string test( "aba" );

  CPPUNIT_CHECK( test.rfind( "a", 2, 1 ) == 2 );
  CPPUNIT_CHECK( test.rfind( "a", 1, 1 ) == 0 );
  CPPUNIT_CHECK( test.rfind( "a", 0, 1 ) == 0 );

  CPPUNIT_CHECK( test.rfind( 'a', 2 ) == 2 );
  CPPUNIT_CHECK( test.rfind( 'a', 1 ) == 0 );
  CPPUNIT_CHECK( test.rfind( 'a', 0 ) == 0 );
}

void StringTest::find_last_of()
{
  // 21.3.6.4
  string s("one two three one two three");

  CPPUNIT_ASSERT( s.find_last_of("abcde") == 26 );

  string test( "aba" );

  CPPUNIT_CHECK( test.find_last_of( "a", 2, 1 ) == 2 );
  CPPUNIT_CHECK( test.find_last_of( "a", 1, 1 ) == 0 );
  CPPUNIT_CHECK( test.find_last_of( "a", 0, 1 ) == 0 );

  CPPUNIT_CHECK( test.find_last_of( 'a', 2 ) == 2 );
  CPPUNIT_CHECK( test.find_last_of( 'a', 1 ) == 0 );
  CPPUNIT_CHECK( test.find_last_of( 'a', 0 ) == 0 );
}

void StringTest::find_last_not_of()
{
  // 21.3.6.6
  string s("one two three one two three");

  CPPUNIT_ASSERT( s.find_last_not_of("ehortw ") == 15 );

  string test( "aba" );

  CPPUNIT_CHECK( test.find_last_not_of( "a", 2, 1 ) == 1 );
  CPPUNIT_CHECK( test.find_last_not_of( "b", 2, 1 ) == 2 );
  CPPUNIT_CHECK( test.find_last_not_of( "a", 1, 1 ) == 1 );
  CPPUNIT_CHECK( test.find_last_not_of( "b", 1, 1 ) == 0 );
  CPPUNIT_CHECK( test.find_last_not_of( "a", 0, 1 ) == string::npos );
  CPPUNIT_CHECK( test.find_last_not_of( "b", 0, 1 ) == 0 );

  CPPUNIT_CHECK( test.find_last_not_of( 'a', 2 ) == 1 );
  CPPUNIT_CHECK( test.find_last_not_of( 'b', 2 ) == 2 );
  CPPUNIT_CHECK( test.find_last_not_of( 'a', 1 ) == 1 );
  CPPUNIT_CHECK( test.find_last_not_of( 'b', 1 ) == 0 );
  CPPUNIT_CHECK( test.find_last_not_of( 'a', 0 ) == string::npos );
  CPPUNIT_CHECK( test.find_last_not_of( 'b', 0 ) == 0 );
}

void StringTest::copy()
{
  string s("foo");
  char dest[4];
  dest[0] = dest[1] = dest[2] = dest[3] = 1;
  s.copy(dest, 4);
  int pos = 0;
  CPPUNIT_ASSERT( dest[pos++] == 'f' );
  CPPUNIT_ASSERT( dest[pos++] == 'o' );
  CPPUNIT_ASSERT( dest[pos++] == 'o' );
  CPPUNIT_ASSERT( dest[pos++] == 1 );

  dest[0] = dest[1] = dest[2] = dest[3] = 1;
  s.copy(dest, 4, 2);
  pos = 0;
  CPPUNIT_ASSERT( dest[pos++] == 'o' );
  CPPUNIT_ASSERT( dest[pos++] == 1 );

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    s.copy(dest, 4, 5);
    CPPUNIT_ASSERT( false );
  }
  catch (out_of_range const&) {
    CPPUNIT_ASSERT( true );
  }
  catch ( ... ) {
    CPPUNIT_ASSERT( false );
  }
#endif
}

void StringTest::assign()
{
  string s;
  char const* cstr = "test string for assign";

  s.assign(cstr, cstr + 22);
  CPPUNIT_ASSERT( s == "test string for assign" );

  string s2("other test string");
  s.assign(s2);
  CPPUNIT_ASSERT( s == s2 );

  static string str1;
  static string str2;

  // short string optim:
  str1 = "123456";
  // longer than short string:
  str2 = "1234567890123456789012345678901234567890";

  CPPUNIT_ASSERT(str1[5] == '6');
  CPPUNIT_ASSERT(str2[29] == '0');
}

/* This test is to check if std::string properly supports the short string
 * optimization. It has been found out that eMbedded Visual C++ 3.0 and .NET
 * compilers for the ARM platform fail to pass structs and classes of certain
 * size per value. This seems to be a known compiler bug. For other processors
 * (e.g. x86) the error doesn't occur.
 * (The ARM compiler creates a temporary object from teststr on the stack, to
 * pass it to the helper function. It uses the copy constructor for this.
 * After this the temporary object is copied to another place on the stack.
 * The result is that the _M_finish pointer then points to the wrong buffer
 * end and the size of the short string is incorrectly calculated.)
 */
void StringTest::short_string_optim_bug()
{
   string teststr("shortest");

   bool short_string_optim_bug_helper(string teststr);

   CPPUNIT_ASSERT(true == short_string_optim_bug_helper(teststr));
}

bool short_string_optim_bug_helper(string teststr)
{
   size_t ss = teststr.size();
   return (ss == 8);
}

void StringTest::compare()
{
  string str1("abcdef");
  string str2;

  str2 = "abcdef";
  CPPUNIT_ASSERT( str1.compare(str2) == 0 );
  str2 = "abcde";
  CPPUNIT_ASSERT( str1.compare(str2) > 0 );
  str2 = "abcdefg";
  CPPUNIT_ASSERT( str1.compare(str2) < 0 );

  CPPUNIT_ASSERT( str1.compare("abcdef") == 0 );
  CPPUNIT_ASSERT( str1.compare("abcde") > 0 );
  CPPUNIT_ASSERT( str1.compare("abcdefg") < 0 );

  str2 = "cde";
  CPPUNIT_ASSERT( str1.compare(2, 3, str2) == 0 );
  str2 = "cd";
  CPPUNIT_ASSERT( str1.compare(2, 3, str2) > 0 );
  str2 = "cdef";
  CPPUNIT_ASSERT( str1.compare(2, 3, str2) < 0 );

  str2 = "abcdef";
  CPPUNIT_ASSERT( str1.compare(2, 3, str2, 2, 3) == 0 );
  CPPUNIT_ASSERT( str1.compare(2, 3, str2, 2, 2) > 0 );
  CPPUNIT_ASSERT( str1.compare(2, 3, str2, 2, 4) < 0 );

  CPPUNIT_ASSERT( str1.compare(2, 3, "cdefgh", 3) == 0 );
  CPPUNIT_ASSERT( str1.compare(2, 3, "cdefgh", 2) > 0 );
  CPPUNIT_ASSERT( str1.compare(2, 3, "cdefgh", 4) < 0 );
}

/*
class mystring : public string {
public:
  mystring() {}
  mystring(string const& s) : string(s) {}

  mystring& operator = (string const& s) {
    string::operator = (s);
    return *this;
  };
};
*/

void StringTest::template_expression()
{
  string one("one"), two("two"), three("three");
  string space(1, ' ');

  // check availability of [un]equality operators
  {
      // string-string
      one == two;
      one != two;
      // string-literal
      one == "two";
      one != "two";
      // literal-string
      "one" == two;
      "one" != two;
      // strsum-string
      (one + two) == three;
      (one + two) != three;
      // string-strsum
      one == (two + three);
      one != (two + three);
      // strsum-literal
      (one + two) == "three";
      (one + two) != "three";
      // literal-strsum
      "one" == (two + three);
      "one" != (two + three);
      // strsum-strsum
      (one + two) == (two + three);
      (one + two) != (two + three);
  }

  {
    string result(one + ' ' + two + ' ' + three);
    CPPUNIT_CHECK( result == "one two three" );
  }

  {
    string result(one + ' ' + two + ' ' + three, 4);
    CPPUNIT_CHECK( result == "two three" );
  }

  {
    string result(one + ' ' + two + ' ' + three, 4, 3);
    CPPUNIT_CHECK( result == "two" );
  }

  //2 members expressions:
  CPPUNIT_CHECK( (' ' + one) == " one" );
  CPPUNIT_CHECK( (one + ' ') == "one " );
  CPPUNIT_CHECK( (one + " two") == "one two" );
  CPPUNIT_CHECK( ("one " + two) == "one two" );
  CPPUNIT_CHECK( (one + space) == "one " );

  //3 members expressions:
  CPPUNIT_CHECK( ((one + space) + "two") == "one two" );
  CPPUNIT_CHECK( ("one" + (space + two)) == "one two" );
  CPPUNIT_CHECK( ((one + space) + two) == "one two" );
  CPPUNIT_CHECK( (one + (space + two)) == "one two" );
  CPPUNIT_CHECK( ((one + space) + 't') == "one t" );
  CPPUNIT_CHECK( ('o' + (space + two)) == "o two" );

  //4 members expressions:
  CPPUNIT_CHECK( ((one + space) + (two + space)) == "one two " );

  //special operators
  {
    string result;
    result = one + space + two;
    CPPUNIT_CHECK( result == "one two" );

    result += space + three;
    CPPUNIT_CHECK( result == "one two three" );
  }

  //special append method
  {
    string result;
    //Use reserve to avoid reallocation and really test auto-referencing problems:
    result.reserve(64);

    result.append(one + space + two);
    CPPUNIT_CHECK( result == "one two" );

    result.append(space + result + space + three);
    CPPUNIT_CHECK( result == "one two one two three" );

    result = "one two";
    result.append(space + three, 1, 2);
    CPPUNIT_ASSERT( result == "one twoth" );

    result.append(space + result);
    CPPUNIT_CHECK( result == "one twoth one twoth" );
  }

  //special assign method
  {
    string result;
    //Use reserve to avoid reallocation and really test auto-referencing problems:
    result.reserve(64);

    result.assign(one + space + two + space + three);
    CPPUNIT_CHECK( result == "one two three" );

    result.assign(one + space + two + space + three, 3, 5);
    CPPUNIT_CHECK( result == " two " );

    result.assign(one + result + three);
    CPPUNIT_CHECK( result == "one two three" );
  }

  {
    CPPUNIT_CHECK( !(one + ' ' + two).empty() );

    char result = (one + ' ' + two)[3];
    CPPUNIT_CHECK( result == ' ' );

    result = (one + ' ' + two).at(3);
    CPPUNIT_CHECK( result == ' ' );

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
    try {
      result = (one + ' ' + two).at(10);
      CPPUNIT_ASSERT(false);
    }
    catch (out_of_range const&) {
      CPPUNIT_ASSERT( result == ' ' );
    }
    catch (...) {
      CPPUNIT_ASSERT(false);
    }
#endif
  }

  /*
  mystring a("ing");
  //gcc failed to compile following expression when template expressions are activated.
  //MSVC sees no problem. gcc limitation or MSVC is too cool ??
  mystring b = "str" + a;
  */
}

#if !defined (TE_TMP_TEST_IGNORED)
class superstring
{
  public:
    superstring() :
      s("super")
    {}

    superstring( const string& str ) :
      s( str )
    {}

  superstring operator / (const string& str )
    { return superstring( s + "/" + str ); }

  superstring operator / (const char* str )
    { return superstring( s + "/" + str ); }

  private:
    string s;
};
#endif

void StringTest::te_tmp()
{
#if !defined (TE_TMP_TEST_IGNORED)
  superstring s;
  string more( "more" );
  string less( "less" );

  superstring r = s / (more + less);
#endif
}

void StringTest::template_wexpression()
{
#if !defined (STLPORT) || !defined (_STLP_NO_WCHAR_T)
#  if !defined (__CYGWIN__) || defined (STLPORT)
  wstring one(L"one"), two(L"two"), three(L"three");
  wstring space(1, L' ');

  {
    wstring result(one + L' ' + two + L' ' + three);
    CPPUNIT_CHECK( result == L"one two three" );
  }

  {
    wstring result(one + L' ' + two + L' ' + three, 4);
    CPPUNIT_CHECK( result == L"two three" );
  }

  {
    wstring result(one + L' ' + two + L' ' + three, 4, 3);
    CPPUNIT_CHECK( result == L"two" );
  }

  //2 members expressions:
  CPPUNIT_CHECK( (L' ' + one) == L" one" );
  CPPUNIT_CHECK( (one + L' ') == L"one " );
  CPPUNIT_CHECK( (one + L" two") == L"one two" );
  CPPUNIT_CHECK( (L"one " + two) == L"one two" );
  CPPUNIT_CHECK( (one + space) == L"one " );

  //3 members expressions:
  CPPUNIT_CHECK( ((one + space) + L"two") == L"one two" );
  CPPUNIT_CHECK( (L"one" + (space + two)) == L"one two" );
  CPPUNIT_CHECK( ((one + space) + two) == L"one two" );
  CPPUNIT_CHECK( (one + (space + two)) == L"one two" );
  CPPUNIT_CHECK( ((one + space) + L't') == L"one t" );
  CPPUNIT_CHECK( (L'o' + (space + two)) == L"o two" );

  //4 members expressions:
  CPPUNIT_CHECK( ((one + space) + (two + space)) == L"one two " );

  //special operators
  {
    wstring result;
    result = one + space + two;
    CPPUNIT_CHECK( result == L"one two" );

    result += space + three;
    CPPUNIT_CHECK( result == L"one two three" );
  }

  //special append method
  {
    wstring result;
    //Use reserve to avoid reallocation and really test auto-referencing problems:
    result.reserve(64);

    result.append(one + space + two);
    CPPUNIT_CHECK( result == L"one two" );

    result.append(space + result + space + three);
    CPPUNIT_CHECK( result == L"one two one two three" );

    result = L"one two";
    result.append(space + three, 1, 2);
    CPPUNIT_ASSERT( result == L"one twoth" );

    result.append(space + result);
    CPPUNIT_CHECK( result == L"one twoth one twoth" );
  }

  //special assign method
  {
    wstring result;
    //Use reserve to avoid reallocation and really test auto-referencing problems:
    result.reserve(64);

    result.assign(one + space + two + space + three);
    CPPUNIT_CHECK( result == L"one two three" );

    result.assign(one + space + two + space + three, 3, 5);
    CPPUNIT_CHECK( result == L" two " );

    result.assign(one + result + three);
    CPPUNIT_CHECK( result == L"one two three" );
  }

  {
    CPPUNIT_CHECK( !(one + L' ' + two).empty() );

    wchar_t result = (one + L' ' + two)[3];
    CPPUNIT_CHECK( result == L' ' );

    result = (one + L' ' + two).at(3);
    CPPUNIT_CHECK( result == L' ' );

#    if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
    try {
      result = (one + L' ' + two).at(10);
      CPPUNIT_ASSERT(false);
    }
    catch (out_of_range const&) {
      CPPUNIT_ASSERT( result == L' ' );
    }
    catch (...) {
      CPPUNIT_ASSERT(false);
    }
#    endif
  }
#  endif
#endif
}

void StringTest::io()
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
  string str("STLport");
  {
    ostringstream ostr;
    ostr << str;
    CPPUNIT_ASSERT( ostr.good() );
    CPPUNIT_ASSERT( ostr.str() == str );
  }
  {
    istringstream istr(str);
    string istr_content;
    istr >> istr_content;
    CPPUNIT_ASSERT( !istr.fail() && istr.eof() );
    CPPUNIT_ASSERT( istr_content == str );
  }
  {
    istringstream istr(str);
    istr.width(3);
    string istr_content;
    istr >> istr_content;
    CPPUNIT_ASSERT( !istr.fail() && !istr.eof() );
    CPPUNIT_ASSERT( istr_content == "STL" );
  }
#endif
}

void StringTest::allocator_with_state()
{
#if !(defined (STLPORT) && defined (_STLP_NO_CUSTOM_IO)) 

  char buf1[1024];
  StackAllocator<char> stack1(buf1, buf1 + sizeof(buf1));

  char buf2[1024];
  StackAllocator<char> stack2(buf2, buf2 + sizeof(buf2));

  typedef basic_string<char, char_traits<char>, StackAllocator<char> > StackString;
  {
    StackString str1("string stack1", stack1);
    StackString str1Cpy(str1);

    StackString str2("string stack2", stack2);
    StackString str2Cpy(str2);

    str1.swap(str2);

    CPPUNIT_ASSERT( str1.get_allocator().swaped() );
    CPPUNIT_ASSERT( str2.get_allocator().swaped() );

    CPPUNIT_ASSERT( str1 == str2Cpy );
    CPPUNIT_ASSERT( str2 == str1Cpy );
    CPPUNIT_ASSERT( str1.get_allocator() == stack2 );
    CPPUNIT_ASSERT( str2.get_allocator() == stack1 );
  }
  CPPUNIT_ASSERT( stack1.ok() );
  CPPUNIT_ASSERT( stack2.ok() );
  stack1.reset(); stack2.reset();

  {
    StackString str1("longer string from stack1 allocator instance for dynamic allocation", stack1);
    StackString str1Cpy(str1);

    StackString str2("longer string from stack2 allocator instance for dynamic allocation", stack2);
    StackString str2Cpy(str2);

    str1.swap(str2);

    CPPUNIT_ASSERT( str1.get_allocator().swaped() );
    CPPUNIT_ASSERT( str2.get_allocator().swaped() );

    CPPUNIT_ASSERT( str1 == str2Cpy );
    CPPUNIT_ASSERT( str2 == str1Cpy );
    CPPUNIT_ASSERT( str1.get_allocator() == stack2 );
    CPPUNIT_ASSERT( str2.get_allocator() == stack1 );
  }
  CPPUNIT_ASSERT( stack1.ok() );
  CPPUNIT_ASSERT( stack2.ok() );
  stack1.reset(); stack2.reset();


  {
    StackString str1("string stack1", stack1);
    StackString str1Cpy(str1);

    StackString str2("longer string from stack2 allocator instance for dynamic allocation", stack2);
    StackString str2Cpy(str2);

    str1.swap(str2);

    CPPUNIT_ASSERT( str1.get_allocator().swaped() );
    CPPUNIT_ASSERT( str2.get_allocator().swaped() );

    CPPUNIT_ASSERT( str1 == str2Cpy );
    CPPUNIT_ASSERT( str2 == str1Cpy );
    CPPUNIT_ASSERT( str1.get_allocator() == stack2 );
    CPPUNIT_ASSERT( str2.get_allocator() == stack1 );
  }
  CPPUNIT_ASSERT( stack1.ok() );
  CPPUNIT_ASSERT( stack2.ok() );
  stack1.reset(); stack2.reset();


  {
    StackString str1("longer string from stack1 allocator instance for dynamic allocation", stack1);
    StackString str1Cpy(str1);

    StackString str2("string stack2", stack2);
    StackString str2Cpy(str2);

    str1.swap(str2);

    CPPUNIT_ASSERT( str1.get_allocator().swaped() );
    CPPUNIT_ASSERT( str2.get_allocator().swaped() );

    CPPUNIT_ASSERT( str1 == str2Cpy );
    CPPUNIT_ASSERT( str2 == str1Cpy );
    CPPUNIT_ASSERT( str1.get_allocator() == stack2 );
    CPPUNIT_ASSERT( str2.get_allocator() == stack1 );
  }
  CPPUNIT_ASSERT( stack1.ok() );
  CPPUNIT_ASSERT( stack2.ok() );
  stack1.reset(); stack2.reset();
#endif
}

void StringTest::capacity()
{
  string s;

  CPPUNIT_CHECK( s.capacity() > 0 );
  CPPUNIT_CHECK( s.capacity() < s.max_size() );
  CPPUNIT_CHECK( s.capacity() >= s.size() );

#ifndef _STLP_SHORT_STRING_SZ
#  define _STLP_SHORT_STRING_SZ 16 // see stlport/stl/_string_base.h
#endif

  for ( int i = 0; i < _STLP_SHORT_STRING_SZ + 2; ++i ) {
    s += ' ';
    CPPUNIT_CHECK( s.capacity() > 0 );
    CPPUNIT_CHECK( s.capacity() < s.max_size() );
    CPPUNIT_CHECK( s.capacity() >= s.size() );
  }
}
void StringTest::str_cov1()
	{
		{
		string example( "this is an example string" );
		string::iterator it = example.begin();   
		example.replace(it+4,example.end()-4,4,'o'); 
		CPPUNIT_CHECK(example == "thisooooring"  );
		}
		{
		string str4 ( "This perfectly unclear." );
		basic_string <char>::size_type indexCh4a;
		string str4a ( "clear" );
		indexCh4a = str4.rfind ( str4a , 15 );
		CPPUNIT_CHECK(indexCh4a == -1  );
		}
		{
		string str1f ( "Hello " ), str2f ( "Wide World " );
		swap(str1f,str2f);
		CPPUNIT_CHECK(str1f == "Wide World ");	
		CPPUNIT_CHECK(str2f == "Hello ");	
		}

	}
void StringTest::str_cov2()
	{
		{
		string result1a, result1b;
		string s1o ( "AAAAAAAA" );
		string s1p ( "BBB" );
		const char* cs1p = "CCC";
		result1a = s1o.replace ( 1 , 3 , s1p );
		CPPUNIT_CHECK(result1a == "ABBBAAAA");
		result1b = s1o.replace ( 5 , 3 , cs1p );
		CPPUNIT_CHECK(result1b == "ABBBACCC");
		string result2a, result2b;
		string s2o ( "AAAAAAAA" );
		string s2p ( "BBB" );
		result2a = s2o.replace ( 1 , 3 , s2p , 1 , 2 );
		CPPUNIT_CHECK(result2a == "ABBAAAA");
		string result3a;
		string s3o ( "AAAAAAAA" );
		char ch3p = 'C';
		result3a = s3o.replace ( 1 , 3 , 4 , ch3p );
		CPPUNIT_CHECK(result3a == "ACCCCAAAA");
		string s4o ( "AAAAAAAA" );
		string s4p ( "BBB" );
		const char* cs4p = "CCC";
		basic_string<char>::iterator IterF0, IterL0;
		IterF0 = s4o.begin ( );
		IterL0 = s4o.begin ( ) + 3;
		string result4a, result4b;
		result4a = s4o.replace ( IterF0 , IterL0 , s4p );
		CPPUNIT_CHECK(result4a == "BBBAAAAA");
		result4b = s4o.replace ( IterF0 , IterL0 , cs4p );
		CPPUNIT_CHECK(result4b == "CCCAAAAA");
		string s5o ( "AAAAAAAF" );
		const char* cs5p = "CCCBB";
		basic_string<char>::iterator IterF1, IterL1;
		IterF1 = s5o.begin ( );
		IterL1 = s5o.begin ( ) + 4;
		string result5a;
		result5a = s5o.replace ( IterF1 , IterL1 , cs5p , 4 );
		CPPUNIT_CHECK(result5a == "CCCBAAAF");
		string s6o ( "AAAAAAAG" );
		char ch6p = 'q';
		basic_string<char>::iterator IterF2, IterL2;
		IterF2 = s6o.begin ( );
		IterL2 = s6o.begin ( ) + 3;
		string result6a;
		result6a = s6o.replace ( IterF2 , IterL2 , 4 , ch6p );
		CPPUNIT_CHECK(result6a == "qqqqAAAAG");
		}
	}
void StringTest::str_cov3()
	{
		{
		string str1 ("This is the sample test string"), str2;
		basic_string <char>::reverse_iterator str_rIter, str1_rIter, str2_rIter;
		basic_string <char>::const_reverse_iterator str1_rcIter;
		str1_rIter = str1.rend ( );
		str1_rIter--;
		CPPUNIT_CHECK(*str1_rIter == 'T');
		str_rIter = str1.rbegin( ); 
		CPPUNIT_CHECK(*str_rIter == 'g');
		str1_rcIter = str1.rbegin( );
		CPPUNIT_CHECK(*str1_rcIter == 'g');
		str1_rcIter = str1.rend ( );
		str1_rcIter--;
		CPPUNIT_CHECK(*str1_rcIter == 'T');
		}
		{
		string str1a ( "Hello " );
		str1a = "0";
		CPPUNIT_CHECK(str1a == "0");
		}
		{
		string str1 ("Hello world");
		CPPUNIT_CHECK(str1.length ( ) == 11);
		}
		{
		int comp5a;
		string s5o ( "AACAB" );
		const char* cs5p = "CAB";
		comp5a = s5o.compare (  2 , 3 , cs5p );
		CPPUNIT_CHECK(comp5a == 0);		
		}

	}
void StringTest::str_cov4()
	{
		{
		string str4 ( "12-ab-12-ab" );
		basic_string <char>::size_type indexCh4a;
		string str4a ( "ba3" );
		indexCh4a = str4.find_last_of  ( str4a , 8 );
		CPPUNIT_CHECK(indexCh4a == 4);
		}
		{
		string str4 ( "12-ab-12-ab" );
		basic_string <char>::size_type indexCh4a;
		string str4a ( "b-a" );
		indexCh4a = str4.find_last_not_of  ( str4a , 5 );
		CPPUNIT_CHECK(indexCh4a == 1);
		}
		{
		string str1 ( "abcd-1234-abcd-1234" );
		basic_string <char>::size_type indexCh1a;

		indexCh1a = str1.find_first_of ( "d" , 5 );
		CPPUNIT_CHECK(indexCh1a == 13);
		string str2 ( "12-ab-12-ab" );
		basic_string <char>::size_type indexCh2a;

		string str2a ( "ba3" );
		indexCh2a = str2.find_first_of ( str2a , 5 );
		CPPUNIT_CHECK( indexCh2a == 9 );
		}
		{
		string str4 ( "12-ab-12-ab" );
 	    basic_string <char>::size_type indexCh4a;

		string str4a ( "ba3" );
		indexCh4a = str4.find_first_not_of ( str4a , 5 );
		CPPUNIT_CHECK(indexCh4a == 5 );
		}
	}
void StringTest::str_cov5()
	{
		{
		string str4 ( "clearly this perfectly unclear." );
		basic_string <char>::size_type indexCh4a;

		string str4a ( "clear" );
		indexCh4a = str4.find ( str4a , 5 );
		CPPUNIT_CHECK( indexCh4a != string::npos );
		}
		{
		const char *cstr1a = "Hello Out There.";
		basic_string <char> str1a ( cstr1a , 5);
		CPPUNIT_CHECK( str1a == "Hello" );	
		}
		{
		string str1a,str1b;
		const char *cstr1a = "Out There";
		str1a.assign ( cstr1a );
		CPPUNIT_CHECK(str1a == "Out There");	
		
		str1b.assign ( cstr1a , 3 );
		CPPUNIT_CHECK(str1b == "Out");	
		
		string str1f ( "Hello " ), str2f ( "Wide World " );
		str1f.assign ( str2f.begin ( ) + 5 , str2f.end ( ) - 1 );
		CPPUNIT_CHECK(str1f == "World");	
		}
		{
		string str1f ( "Hello " ), str2f ( "Wide World " );
		str1f.append ( str2f.begin ( ) + 5 , str2f.end ( ) - 1 );
		CPPUNIT_CHECK(str1f == "Hello World");	
		
		string str1b ( "Hello " );
		const char *cstr1b = "Out There ";
		str1b.append ( cstr1b , 3 );
		CPPUNIT_CHECK(str1b == "Hello Out");	
		}
	}
void StringTest::str_cov6()
	{
		{
		string s1 ( "AACAB" );
		string s2 ( "BACAB" );
		const char* s3 = "CAB";
		
		bool flag;
		
		flag = s2 >= s1;
		CPPUNIT_CHECK(flag == true);		
		
		flag = s3 >= s1;
		CPPUNIT_CHECK(flag == true);		
		
		flag = s1 >= s3;
		CPPUNIT_CHECK(flag == false);
		
		flag = s2 > s1;
		CPPUNIT_CHECK(flag == true);		
		
		flag = s3 > s1;
		CPPUNIT_CHECK(flag == true);		
		
		flag = s1 > s3;
		CPPUNIT_CHECK(flag == false);
		
		flag = s2 <= s1;
		CPPUNIT_CHECK(flag == false);		
		
		flag = s3 <= s1;
		CPPUNIT_CHECK(flag == false);		
		
		flag = s1 <= s3;
		CPPUNIT_CHECK(flag == true);
		
		flag = s3 < s1;
		CPPUNIT_CHECK(flag == false);		
		
		flag = s1 < s3;
		CPPUNIT_CHECK(flag == true);
		}
		{
		string str1 ( "xddd-1234-abcd" );
		basic_string <char>::size_type indexCh1a;

		indexCh1a = str1.find_first_not_of ( "d" , 2 );
		CPPUNIT_CHECK(indexCh1a == 4);	
		}
	}

