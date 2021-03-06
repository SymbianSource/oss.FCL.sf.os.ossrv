/*
* Copyright (c) 1997-2007 Nokia Corporation and/or its subsidiary(-ies).
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


#include <stdlib.h>	/* definition of exit() */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/ioctl.h>
#include "CTEST.H"




int port;

/**
@SYMTestCaseID          SYSLIB-STDLIB-CT-1105
@SYMTestCaseDesc	    Tests for serial port
@SYMTestPriority 	    High
@SYMTestActions  	    Tests for notification support
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/		
void Watcher(void)
	{
	int res;
	int notify[2] = {0,0};
	int supported = 0;


	res = ioctl(port, COMMIOCTL_NOTIFYSUPPORTED, &supported);
	printf("\nsupported notifies are %08lx\n",supported);
	while (-1 != res)
		{
		notify[0] = supported;
		res = ioctl(port, COMMIOCTL_NOTIFY, &notify[0]);
		printf("\n**Notify** res = %d params %d, %d, errno %d\n",res, notify[0], notify[1],errno);
		}

	}

/**
@SYMTestCaseID          SYSLIB-STDLIB-CT-1106
@SYMTestCaseDesc	    Tests for communication over the port
@SYMTestPriority 	    High
@SYMTestActions  	    Tests for reading and writing to a port back
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/		
void ping(void)
	{
	char buf1[50];
	char buf2[50];
	char* rptr =buf1;
	char* wptr = buf2;
	char * tptr;


	int err = 0;
	int timeout = 5000;	//5 seconds
	int threshold = -1;

	printf("port is %d\n",port);
	ioctl(port, COMMIOCTL_SETREADTHRESHOLD, &threshold);
	ioctl(port, COMMIOCTL_SETREADTIMEOUT, &timeout);

	strcpy(wptr, "ping");
	while (err >= 0)
		{
		err = read(port,rptr, 50);
		if (err >= 0)
			{
			rptr[err] = 0;
			err = write(port, wptr, strlen(wptr));
//			printf("read %s, written %s\n", rptr, wptr);
			tptr = wptr;
			wptr = rptr;
			rptr = tptr;

			}

		}
	}


int main(void)
	{
	void* t1;
	void* t2;
	
	start_posix_server();	/* calls SpawnPosixServer from C++ code */
	
	port = open("IRCOM1:", 0);
	
	t1 = create_thread(Watcher, "watcher");
	t2 = create_thread(ping, "ping");
	
	start_thread(t1);
	start_thread(t2);

	wait_for_thread(t2);
	
	close(port);

	wait_for_thread(t1);

	return 0;
	}

