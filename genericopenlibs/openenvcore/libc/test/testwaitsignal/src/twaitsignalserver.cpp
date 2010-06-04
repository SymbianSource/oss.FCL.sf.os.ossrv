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
// Name        : twaitsignalserver.cpp
// 
//

#include <c32comm.h>

#if defined (__WINS__)
#define PDD_NAME		_L("ECDRV")
#else
#define PDD_NAME		_L("EUART1")
#define PDD2_NAME		_L("EUART2")
#define PDD3_NAME		_L("EUART3")
#define PDD4_NAME		_L("EUART4")
#endif

#define LDD_NAME		_L("ECOMM")

/**
 * @file
 *
 * Pipe test server implementation
 */
#include "twaitsignalserver.h"
#include "twaitsignal.h"


_LIT(KServerName, "twaitsignal");

CWaitsignalTestServer* CWaitsignalTestServer::NewL()
	{
	CWaitsignalTestServer *server = new(ELeave) CWaitsignalTestServer();
	CleanupStack::PushL(server);
	server->ConstructL(KServerName);
	CleanupStack::Pop(server);
	return server;
	}

static void InitCommsL()
    {
    TInt ret = User::LoadPhysicalDevice(PDD_NAME);
    User::LeaveIfError(ret == KErrAlreadyExists?KErrNone:ret);

#ifndef __WINS__
    ret = User::LoadPhysicalDevice(PDD2_NAME);
    ret = User::LoadPhysicalDevice(PDD3_NAME);
    ret = User::LoadPhysicalDevice(PDD4_NAME);
#endif

    ret = User::LoadLogicalDevice(LDD_NAME);
    User::LeaveIfError(ret == KErrAlreadyExists?KErrNone:ret);
    ret = StartC32();
    User::LeaveIfError(ret == KErrAlreadyExists?KErrNone:ret);
    }

LOCAL_C void MainL()
	{
	// Leave the hooks in for platform security
#if (defined __DATA_CAGING__)
	RProcess().DataCaging(RProcess::EDataCagingOn);
	RProcess().SecureApi(RProcess::ESecureApiOn);
#endif
	InitCommsL();
	
	CActiveScheduler* sched=NULL;
	sched=new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(sched);
	CWaitsignalTestServer* server = NULL;
	// Create the CTestServer derived server
	TRAPD(err, server = CWaitsignalTestServer::NewL());
	if(!err)
		{
		// Sync with the client and enter the active scheduler
		RProcess::Rendezvous(KErrNone);
		sched->Start();
		}
	delete server;
	delete sched;
	}

/**
 * Server entry point
 * @return Standard Epoc error code on exit
 */
TInt main()
	{
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	if(cleanup == NULL) 
		{
		return KErrNoMemory;  
		}
	TRAP_IGNORE(MainL());
	delete cleanup;
	__UHEAP_MARKEND;
	
	return KErrNone;
	}

CTestStep* CWaitsignalTestServer::CreateTestStep(const TDesC& aStepName)
	{
	CTestStep* testStep = NULL;

	if(aStepName == KTestpendingsignal1)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestpendingsignal2)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestpendingsignal3)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestpendingsignal4)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitsignal1)
		{
			testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitsignal2)
		{
			testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitsignal3)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitsignal4)
		{
			testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitsignal5)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitsignal6)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitsignal7)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitsignal8)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitsignal9)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitinfosignal1)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitinfosignal2)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitinfosignal3)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitinfosignal4)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitinfosignal5)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitinfosignal6)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitinfosignal7)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitinfosignal8)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTestwaitinfosignal9)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal1)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal2)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal3)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal4)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal5)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal6)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal7)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal8)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal9)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal10)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal11)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal12)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal13)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	if(aStepName == KTesttimedwaitsignal14)
		{
		testStep = new CTestWaitsignal(aStepName);
		}
	
	return testStep;
	 }

