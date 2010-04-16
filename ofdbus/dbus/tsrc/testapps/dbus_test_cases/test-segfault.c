/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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

/* This is simply a process that segfaults */
#include <stdlib.h>
#ifndef TODO
#include <signal.h>
#endif
#include <sys/time.h>
#include <sys/resource.h>

int
main ()
{
  char *p;  

  struct rlimit r = { 0, };
  #ifndef TODO
  getrlimit (RLIMIT_CORE, &r);
  r.rlim_cur = 0;
  setrlimit (RLIMIT_CORE, &r);
  
   raise (SIGSEGV);
  #endif
  p = NULL;
  *p = 'a';
  
  return 0;
}
