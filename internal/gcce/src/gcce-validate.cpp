/*
* ==============================================================================
*  Name        : gcce-validate.c
*  Part of     : internal/gcce
*  Description : This is a test program to test the cross linking of openc libraries with
*  programs compiled using the gcce compiler
Copyright © 2006 Nokia Corporation
All rights reserved.
Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this 
   list of conditions and the following disclaimer. 
 * Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution. 
 * Neither the name of the <ORGANIZATION> nor the names of its contributors 
   may be used to endorse or promote products derived from this software 
   without specific prior written permission. 
   
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ==============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#include <zlib.h>
#include <math.h>
#include <float.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>



#include <testharness.h>
#include "result_log.h"

int TestCond688()

{
	struct timespec abstime;
	struct timeval now;
	gettimeofday(&now,NULL);
	abstime.tv_sec = now.tv_sec + 5;
	abstime.tv_nsec = now.tv_usec * 1000;

	TRACE("+TestCond688\n");
	HarnessCommand lCommandArr[255] = 
	{
		{EThreadMain, EMutexInitStaticErrorCheck},
		{EThreadMain, ECondInit},

		{EThreadMain, EThreadCreate, (void*) EThread1},
		{EThreadMain, EThreadCreate, (void*) EThread2},
		{EThreadMain, EThreadCreate, (void*) EThread3},
		{EThreadMain, EThreadCreate, (void*) EThread4},
		
		{EThread1, EMutexLock},
		{EThread1, EPostSignal},
		{EThread1, ECondTimedWait,&abstime},

		{EThread2, EMutexLock},
		{EThread2, EPostSignal},
		{EThread2, ECondTimedWait,&abstime},

		{EThread3, EMutexLock},
		{EThread3, EPostSignal},
		{EThread3, ECondTimedWait,&abstime},

		{EThread4, EMutexLock},
		{EThread4, EPostSignal},
		{EThread4, ECondTimedWait,&abstime},

		{EThreadMain, EWaitForSignal},
		{EThreadMain, EWaitForSignal},
		{EThreadMain, EWaitForSignal},
		{EThreadMain, EWaitForSignal},

		{EThreadMain, EWaitTillSuspended, (void*) EThread1},
		{EThreadMain, EWaitTillSuspended, (void*) EThread2},
		{EThreadMain, EWaitTillSuspended, (void*) EThread3},
		{EThreadMain, EWaitTillSuspended, (void*) EThread4},

		{EThreadMain, EMutexLock},
		{EThreadMain, ECondBroadcast},
		{EThreadMain, EMutexUnlock},

		{EThread1, EVerifyResult, (void*) 0},
		{EThread2, EVerifyResult, (void*) 0},
		{EThread3, EVerifyResult, (void*) 0},
		{EThread4, EVerifyResult, (void*) 0},

		{EThread1, EMutexUnlock},
		{EThread2, EMutexUnlock},
		{EThread3, EMutexUnlock},
		{EThread4, EMutexUnlock},

		{EThread1, EStop},
		{EThread2, EStop},
		{EThread3, EStop},
		{EThread4, EStop},

		
		{EThreadMain, EThreadDestroy, (void*) EThread1},
		{EThreadMain, EThreadDestroy, (void*) EThread2},
		{EThreadMain, EThreadDestroy, (void*) EThread3},
		{EThreadMain, EThreadDestroy, (void*) EThread4},

		{EThreadMain, ECondDestroy},
		{EThreadMain, EMutexDestroy},

		{EThreadMain, EStop},
		{ENoThread, ELastCommand},
	};

	TRACE("-TestCond688\n");
	return LoadHarness(lCommandArr);
}


//sem_getvalue on a semaphore posted n times
int TestSem316()
{
	TRACE("+TestSem316\n");
	
	HarnessCommand lCommandArr[255] = 
	{
		{EThreadMain, ESemInit,  (void*) NULL},
		{EThreadMain, ESemPost},
		{EThreadMain, ESemPost},
		{EThreadMain, ESemPost},
		{EThreadMain, ESemPost},
		{EThreadMain, ESemWait},
		{EThreadMain, ESemWait},

		{EThreadMain, ESemGetValue},
		{EThreadMain, ECheckValue, (void*) 2},
		{EThreadMain, ESemDestroy},

		{EThreadMain, EStop},
		{ENoThread, ELastCommand},
	};

	TRACE("-TestSem316\n");
	return LoadHarness(lCommandArr);
}

//sem_trywait called on a non posted semaphore
int TestSem390()
{
	TRACE("+TestSem390\n");
	HarnessCommand lCommandArr[255] = 
	{
		{EThreadMain, ESemInit},
					
		{EThreadMain, EThreadCreate, (void*) EThread1},

		{EThread1, ESemTryWait},
		{EThread1, EVerifyErrno, (void*) EAGAIN},
		{EThread1, EPostSignal},
		{EThreadMain, EWaitForSignal},
		{EThread1, EStop},

		{EThreadMain, ESemDestroy},
		{EThreadMain, EThreadDestroy, (void*) EThread1},
		{EThreadMain, EStop},
		{ENoThread, ELastCommand},
	};

	TRACE("-TestSem390\n");
	return LoadHarness(lCommandArr);
}


#define FLOAT float
#define CHOOSE(Clongdouble,Cdouble,Cfloat,Cinlinelongdouble,Cinlinedouble,Cinlinefloat) Cfloat
#define IGNORE_ZERO_INF_SIGN		0x10





#define MANT_DIG CHOOSE ((LDBL_MANT_DIG-1), (DBL_MANT_DIG-1), (FLT_MANT_DIG-1),  \
                         (LDBL_MANT_DIG-1), (DBL_MANT_DIG-1), (FLT_MANT_DIG-1))
                         
#define KErrNone 0
#define KErrGeneral -1                         


int  check_float (FLOAT computed, FLOAT expected,FLOAT max_ulp, FLOAT &gen_ulp)
{
  int ok = 0;
  FLOAT diff = 0;
  FLOAT ulp = 0;

  
  
  if (isnan (computed) && isnan (expected))
  ok = 1;
  
  else if (isinf (computed) && isinf (expected))
    {
      /* Test for sign of infinities.  */
      if ((IGNORE_ZERO_INF_SIGN) == 0
	  && signbit (computed) != signbit (expected))
	  {
	  ok = 0;
	  }
      else
	  ok = 1;
    }
  /* Don't calc ulp for NaNs or infinities.  */
  else if (isinf (computed) || isnan (computed) || isinf (expected) || isnan (expected))
    ok = 0;
  else
    {
    diff = fabsf(computed - expected);
      /* ilogb (0) isn't allowed.  */
      if (expected == 0.0)
	  ulp = diff / ldexpf (1.0, - MANT_DIG);
      else
	  ulp = diff / ldexpf (1.0, ilogbf (expected) - MANT_DIG);
      
      if ((IGNORE_ZERO_INF_SIGN) == 0
	  && computed == 0.0 && expected == 0.0
	  && signbit(computed) != signbit (expected))
	  ok = 0;
      else if (ulp == 0.0 || (ulp <= max_ulp ))
	  ok = 1;
      else
	  {
	  ok = 0;
	  }

    }
  gen_ulp = ulp ;  
  
  return ok;
}


int atan2_testL()
{
 	// Create temporary variables in stack
  	//char Tname[]   = "atan2l_test_0_0_0_1";
  	FLOAT input1   = 0;
  	FLOAT input2   = 1;
  	FLOAT expected = 0;
  	FLOAT max_ulp  = 0; 
  	FLOAT gen_ulp;
  	
  	// Read parameters
  	
  	    
    // Do some testing
    FLOAT res = atan2f(input1, input2);
        
    if(check_float(res, expected, max_ulp, gen_ulp))
    {
    	return 0;
    }
    else
    {
    	return -1;
    }
   
}


#define TESTFILE "c:\\foo.gz"
int Gzprintf()
{
    int res = KErrNone ;
    gzFile file;
    const char * fname = TESTFILE ;
    file = gzopen(fname, "wb");
        if (file == NULL) 
    {
     res = KErrGeneral;
     return res;
    }   
    if (gzprintf(file, ", %s!", "hello") != 8) 
    {
       return KErrNone;
    }

    int err = gzclose(file);
    if(err == 0)
    {  	
     	res = KErrNone ;
    } 
    else
    {    	
        res =res= KErrGeneral;
    } 
    return res;
}
 
 
int getpwnam_negL( )
{
    //__UHEAP_MARK;
  	// Create temporary variables in stack
  	struct passwd* pwd;
  	char pw_nam[]="abc";
  	
    pwd=getpwnam(pw_nam);

    // Set test result
	if(pwd==NULL)       	
	{
		return 0;
	}
	else
	{
		return -1;
	}
       	
    //__UHEAP_MARKEND;
 }
 
int check (int thing, int number)
{
  if (!thing)
    {
	  return -1;
    }
  else 
	  return KErrNone;
}

/* Complain if first two args don't strcmp as equal.  */
int equal (const char *a, const char *b, int number)
{
  return check(a != NULL && b != NULL && (strcmp((a), (b)) == 0), number);
}


int memcpy2()
{
	char one[50];
	(void) strcpy(one, "abc");
	(void) memcpy(one, "xyz", 0);
	return equal(one, "abc", 4);			/* Zero-length copy. */
}

int strcmp1()
{

	int retval;
	//STEP 1
	retval = check (strcmp ("a", "a") == 0, 2);		/* Identity. */
	if (retval == KErrNone)
		retval = check (strcmp ("abc", "abc") == 0, 3);	/* Multicharacter. */

	return retval;
}

int strcat2()
{
	
	char one[50];
	int retval;

	//STEP 2
	(void) strcpy (one, "");
	(void) strcat (one, "");
	retval = equal (one, "", 7);			/* Boundary conditions. */
	if (retval == KErrNone)
		{
		(void) strcpy (one, "ab");
		(void) strcat (one, "");
		retval = equal (one, "ab", 8);
		if (retval == KErrNone)
			{
			(void) strcpy (one, "");
			(void) strcat (one, "cd");
			retval = equal (one, "cd", 9);	
			}
		}
	return retval;
}



static int 
do_test ()
{
	int nfns; 
	int retval =0;
	int i;
 int (*pfnArray[])() =
 {
	strcat2,
	strcmp1,
	memcpy2,
	getpwnam_negL,
	Gzprintf,
	atan2_testL,
	TestSem390,
	TestSem316,
	TestCond688,
 };

  nfns = (sizeof pfnArray)/(sizeof (int (*)()));
  for(i=0; i<nfns; i++)
  {
  	retval += pfnArray[i]();
  }
  return retval;
}

int
main (int argc, char *argv[])
{
  int retval = 0;
  retval = do_test();
  testResultXml("gcce-validate",retval);
}
