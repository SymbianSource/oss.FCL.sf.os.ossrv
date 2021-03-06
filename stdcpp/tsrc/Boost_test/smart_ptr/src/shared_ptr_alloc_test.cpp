//
//  shared_ptr_alloc_test.cpp - use to evaluate the impact of count allocations
//
//  Copyright (c) 2002, 2003 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/*
 * � Portions copyright (c) 2006-2007 Nokia Corporation.  All rights reserved.
*/

#include <boost/shared_ptr.hpp>
#include <boost/config.hpp>
#include <boost/detail/quick_allocator.hpp>

#include <iostream>
#include <vector>
#include <ctime>
#include <cstddef>
#include <memory>

#ifdef __SYMBIAN32__
#include "std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__
#endif

#ifdef __SYMBIAN32__
int const n = 1024;
#else
int const n = 1024 * 1024;
#endif

template<class T> void test(T * = 0)
{
    std::clock_t t = std::clock();
    std::clock_t t2;

    {
        std::vector< boost::shared_ptr<T> > v;

        for(int i = 0; i < n; ++i)
        {
            boost::shared_ptr<T> pi(new T(i));
            v.push_back(pi);
        }

        t2 = std::clock();
    }

    std::clock_t t3 = std::clock();

    std::cout << "   " << static_cast<double>(t3 - t) / CLK_TCK << " seconds, " << static_cast<double>(t2 - t) / CLK_TCK << " + " << static_cast<double>(t3 - t2) / CLK_TCK << ".\n";
}

class X
{
public:

    explicit X(int n): n_(n)
    {
    }

    void * operator new(std::size_t)
    {
        return std::allocator<X>().allocate(1, static_cast<X*>(0));
    }

    void operator delete(void * p)
    {
        std::allocator<X>().deallocate(static_cast<X*>(p), 1);
    }

private:

    X(X const &);
    X & operator=(X const &);

    int n_;
};

class Y
{
public:

    explicit Y(int n): n_(n)
    {
    }

    void * operator new(std::size_t n)
    {
        return boost::detail::quick_allocator<Y>::alloc(n);
    }

    void operator delete(void * p, std::size_t n)
    {
        boost::detail::quick_allocator<Y>::dealloc(p, n);
    }

private:

    Y(Y const &);
    Y & operator=(Y const &);

    int n_;
};

class Z: public Y
{
public:

    explicit Z(int n): Y(n), m_(n + 1)
    {
    }

private:

    Z(Z const &);
    Z & operator=(Z const &);

    int m_;
};

int main()
{
	std_log(LOG_FILENAME_LINE,"[Test Case for shared_ptr_alloc_test]");
    std::cout << BOOST_COMPILER "\n";
    std::cout << BOOST_PLATFORM "\n";
    std::cout << BOOST_STDLIB "\n";

#if defined(BOOST_HAS_THREADS)
    std::cout << "BOOST_HAS_THREADS: (defined)\n";
#else
    std::cout << "BOOST_HAS_THREADS: (not defined)\n";
#endif

#if defined(BOOST_SP_USE_STD_ALLOCATOR)
    std::cout << "BOOST_SP_USE_STD_ALLOCATOR: (defined)\n";
#else
    std::cout << "BOOST_SP_USE_STD_ALLOCATOR: (not defined)\n";
#endif

#if defined(BOOST_SP_USE_QUICK_ALLOCATOR)
    std::cout << "BOOST_SP_USE_QUICK_ALLOCATOR: (defined)\n";
#else
    std::cout << "BOOST_SP_USE_QUICK_ALLOCATOR: (not defined)\n";
#endif

#if defined(BOOST_QA_PAGE_SIZE)
    std::cout << "BOOST_QA_PAGE_SIZE: " << BOOST_QA_PAGE_SIZE << "\n";
#else
    std::cout << "BOOST_QA_PAGE_SIZE: (not defined)\n";
#endif

    std::cout << n << " shared_ptr<int> allocations + deallocations:\n";

    test<int>();
    test<int>();
    test<int>();

    std::cout << n << " shared_ptr<X> allocations + deallocations:\n";

    test<X>();
    test<X>();
    test<X>();

    std::cout << n << " shared_ptr<Y> allocations + deallocations:\n";

    test<Y>();
    test<Y>();
    test<Y>();

    std::cout << n << " shared_ptr<Z> allocations + deallocations:\n";

    test<Z>();
    test<Z>();
    test<Z>();

#ifdef __SYMBIAN32__
	std_log(LOG_FILENAME_LINE,"Result : Passed");
	std_log(LOG_FILENAME_LINE,"[End Test Case ]");
#endif
	testResultXml("shared_ptr_alloc_test");
	close_log_file();
	return 0;
}
