// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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
//

#include <e32base.h>
#include <e32test.h>
#include <csch_cli.h>
#include <f32file.h>
#include "Thelpers.h"

#include "TestUtils.h"

// Globals
RTest					TheTest(_L("TC_TSCH_SCHEDULING1 - UTC"));
static RScheduler		TheScheduler;
static RFs				TheFsSession;

typedef CArrayFixFlat<TScheduleEntryInfo2>	CScheduleEntryInfoArray;
typedef CArrayFixFlat<TTaskInfo>			CTaskInfoArray;
typedef CArrayFixFlat<TSchedulerItemRef>    CSchItemRefArray;

_LIT(KMinimalTaskHandler, "MinimalTaskHandler");

_LIT(KTimeFormatString,						"%-B%:0%J%:1%T%:2%S%.%*C4%:3%+B");
_LIT(KCurrentDateTimeChanged,				"Date & Time changed to: [%S]\n");

//***********************************************************************************

// Sets time to before specified time by aTimeBeforeInSeconds
static void SetTimeBeforeL(RTest& aTest, TTsTime& aTime, TInt aTimeBeforeInSeconds)
	{
	TTimeIntervalSeconds secs(aTimeBeforeInSeconds);
	TTime time = aTime.GetLocalTime()-secs;
	SchSvrHelpers::SetHomeTimeL(time);
	TBuf<30> dateString;
	time.FormatL(dateString, KTimeFormatString);
	aTest.Printf(KCurrentDateTimeChanged, &dateString);
	}

// gets the due time for this schedule
static TTsTime GetDueTimeL(TInt aScheduleId)
	{
	TTsTime nextTimeScheduleIsDue;
	TScheduleState2 state;
	CScheduleEntryInfoArray* entries 
		= new (ELeave) CScheduleEntryInfoArray(3);
	CleanupStack::PushL(entries);
	CTaskInfoArray* tasks = new (ELeave) CTaskInfoArray(3);
	CleanupStack::PushL(tasks);

	TInt res = TheScheduler.GetScheduleL(aScheduleId, state, *entries, *tasks, nextTimeScheduleIsDue);
	TEST2(res, KErrNone);

	CleanupStack::PopAndDestroy(2); // entries, tasks
	
	return state.DueTime();
	}
	
// Forces the task to be exectued aCount times.
static void ForceTaskExecutionForSpecifiedIdL(TInt aId, TInt aCount)
	{
	TheTest.Printf(_L("Executing %d times\n"), aCount);
	TTsTime time;
	for (TInt i=0; i<aCount; ++i)
		{
		TheTest.Printf(_L("Execution %d\n"), i+1);
		time = GetDueTimeL(aId);		
		
		SetTimeBeforeL(TheTest, time, 5 /*seconds*/);		
		
		// Wait for notification that schedule has executed.
		TEST2(STaskSemaphore::WaitL(KDefaultTimeout), KErrNone);
		CleanupHelpers::KillProcess(KMinimalTaskHandler);
		}
	}

//creates a daily schedule with StartTime of aStartTime
static TInt CreateScheduleL(TSchedulerItemRef& aRef, 
							RScheduler& aScheduler, 
							const TTsTime& aStartTime)
	{
	CScheduleEntryInfoArray* entryList 
		= new (ELeave) CScheduleEntryInfoArray(1);
	CleanupStack::PushL(entryList);

	TScheduleEntryInfo2 entry1 (aStartTime, EDaily, 1, 30);
	entryList->AppendL(entry1);
	TInt res = aScheduler.CreatePersistentSchedule(aRef, *entryList);
	CleanupStack::PopAndDestroy(); // entryList
	return res;
	}

// counts the number of scheduled items based on the supplied filter.
static TInt CountScheduledItemsL(TScheduleFilter aFilter, 
								RScheduler& aScheduler)
	// Extract schedule references from the schedule server based on a filter. If
	{
	CSchItemRefArray* refs = new (ELeave) CSchItemRefArray(3);
	CleanupStack::PushL(refs);

	TInt res = aScheduler.GetScheduleRefsL(*refs, aFilter);
	TEST2(res, KErrNone);

	TInt count = refs->Count();
	CleanupStack::PopAndDestroy(); // refs
	return count;
	}	

// Extract task references from the schedule server based on a ID
static void GetTaskInfoL(CTaskInfoArray& aTaskInfoArray,
						TInt aScheduleId)
	{
	aTaskInfoArray.Reset();
	TTsTime nextTimeScheduleIsDue;
	TScheduleState2 state;
	CScheduleEntryInfoArray* entries 
		= new (ELeave) CScheduleEntryInfoArray(3);
	CleanupStack::PushL(entries);
	TInt res = TheScheduler.GetScheduleL(aScheduleId, 
										state, 
										*entries, 
										aTaskInfoArray, 
										nextTimeScheduleIsDue);
	TEST2(res, KErrNone);
	CleanupStack::PopAndDestroy(entries);
	}

// schedules a transient task	
static TInt ScheduleTransientTaskL(TInt& aTaskId, 
								TSchedulerItemRef& aRef, 
								TInt aRepeat, 
								RScheduler& aScheduler)
	{
	CScheduleEntryInfoArray* entryList = new(ELeave) CScheduleEntryInfoArray(3);
	CleanupStack::PushL(entryList);

	aRef.iName = _L("transient one");

	// SCHEDULES
	TTime ttime1(SchSvrHelpers::UtcTimeBasedOnOffset(0, 1));
	TTsTime startTime1 (ttime1,ETrue); // 1 min in the future
	TScheduleEntryInfo2 entry1 (startTime1, EDaily, 1, 20);
	entryList->AppendL(entry1);
	TTime ttime2(SchSvrHelpers::UtcTimeBasedOnOffset(0, 2));
	TTsTime startTime2 (ttime2,ETrue); // 2 min in the future
	TScheduleEntryInfo2 entry2 (startTime2, EDaily, 1, 500);
	entryList->AppendL(entry2);

	TTime ttime3(SchSvrHelpers::UtcTimeBasedOnOffset(0, 3));
	TTsTime startTime3 (ttime3,ETrue); // 3 min in the future
	TScheduleEntryInfo2 entry3 (startTime3, EDaily, 1, 5);
	entryList->AppendL(entry3);

	// TASK
	TTaskInfo taskInfo;
	taskInfo.iName = _L("mail");
	taskInfo.iTaskId = aTaskId;
	taskInfo.iRepeat = aRepeat;
	taskInfo.iPriority = 2;
	HBufC* data = _L("the data, some strange new name ").AllocLC();

	// Schedule the item
	TInt res = aScheduler.ScheduleTask(taskInfo, *data, aRef, *entryList);
	CleanupStack::PopAndDestroy(2); // data, entryList

	aTaskId = taskInfo.iTaskId;
	return res;
	}


//***********************************************************************************

/**
@file
@SYMTestCaseID				SYSLIB-SCHSVR-CT-0254
@SYMTestCaseDesc 			Replicated test for for defect (EDNEMHE-4Q69BG) - UTC
@SYMTestPriority 			High
@SYMTestActions  			Create time based schedules and then jump to a time after the due time but within the validity period and check it schedule still fires
@SYMTestExpectedResults		The test must not fail.
@SYMPREQ					PREQ234
*/
static void Test1L()
	{
	_LIT(KTaskData1, "This is some really exciting task data (number 1)");
	_LIT(KTaskData2, "This is some really exciting task data (number 2)");
	_LIT(KTestName,	"SmsTest");

	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-SCHSVR-CT-0254 TheTest3: SMS:Sending to multiple recipients "));
	
	TheTest.Next(_L("Connect to Scheduler"));
	TInt res = TheScheduler.Connect();
	TEST2(res, KErrNone);

	TheTest.Next(_L("Registering Client"));
	TEST2(SchSvrHelpers::RegisterClientL(TheScheduler), KErrNone);

	// Set the time to a known value, since this makes testing much easier (and more
	// repeatable).	
	SchSvrHelpers::SetHomeTimeL(TTime(TDateTime(2000, EJanuary, 1, 9, 55, 0, 0))); // 9:55 am

	// This is the time when we want the schedule to fire
	TDateTime datetime(2000, EJanuary, 1, 10, 0, 0, 0);
	TTsTime startTimeForSchedule(datetime, ETrue); // 10:00 am


	// Prepare a schedule describing when we want the tasks to run (10:00 am)
	TSchedulerItemRef ref;
	User::LeaveIfError(CreateScheduleL(ref, TheScheduler, startTimeForSchedule));

	// Disable the schedule whilst we set it up
	User::LeaveIfError(TheScheduler.DisableSchedule(ref.iHandle));

	// Associate a task with the schedule
	TTaskInfo taskInfo1;
	taskInfo1.iRepeat = 0;
	taskInfo1.iName = KTestName;
	taskInfo1.iPriority = 2;

	// Create some data associated with this task
	HBufC* taskData1 = KTaskData1().AllocLC();
	User::LeaveIfError(TheScheduler.ScheduleTask(taskInfo1, *taskData1, ref.iHandle));
	CleanupStack::PopAndDestroy(); // taskData1

	// Associate a task (2) with the schedule
	TTaskInfo taskInfo2;
	taskInfo2.iRepeat = 0;
	taskInfo2.iName = KTestName;
	taskInfo2.iPriority = 2;

	// Create some data associated with this task
	HBufC* taskData2 = KTaskData2().AllocLC();
	User::LeaveIfError(TheScheduler.ScheduleTask(taskInfo2, *taskData2, ref.iHandle));
	CleanupStack::PopAndDestroy(); // taskData2

	// We should now have two tasks scheduled at exactly the same time...
	User::LeaveIfError(TheScheduler.EnableSchedule(ref.iHandle));

	// Set the time to 5 minutes *AFTER* the schedule was due to run (10:05am). In this instance,
	// based on the new fixed Schedule Server, the schedule should still execute since 
	// it falls within the validity period (30 mins), however, in the old scheme of things,
	// the schedule would not be valid again until tomorrow (2/1/2000) at 10:00am and hence
	// would not execute until then.	
	SchSvrHelpers::SetHomeTimeL(TTime(TDateTime(2000, EJanuary, 1, 10, 5, 0, 0))); // 10:05 am

	// Now wait for something to happen...
	TEST2(STaskSemaphore::WaitL(KDefaultTimeout), KErrNone);
	CleanupHelpers::KillProcess(KMinimalTaskHandler);
	}

//***********************************************************************************

/**
@file
@SYMTestCaseID				SYSLIB-SCHSVR-CT-0255
@SYMTestCaseDesc 			Replicated test for for defect (EDNEMHE-4Q69BG) - UTC
@SYMTestPriority 			High
@SYMTestActions  			Create time based schedules and then jump to a time after the due time but within the validity period and check it schedule still fires
@SYMTestExpectedResults		The test must not fail.
@SYMPREQ					PREQ234
*/
static void Test2L()
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-SCHSVR-CT-0255 Testing creation of transient schedule with task repeating 5 times "));	
	TInt tTask = 0;
	TSchedulerItemRef ref;
	// schedule has 3 entries - +1min, +2min and +3min
	TInt res = ScheduleTransientTaskL(tTask, ref, 5, TheScheduler);//5 repeats
	TEST2(res, KErrNone);
	
	TheTest.Printf(_L("Get Task count and repeat count\n"));

	CTaskInfoArray* tasks = new (ELeave) CTaskInfoArray(3);
	CleanupStack::PushL(tasks);
	GetTaskInfoL(*tasks, ref.iHandle);
	TEST(tasks->Count() == 1);
	TTaskInfo info = tasks->At(0);
	TEST(info.iRepeat == 5);
	ForceTaskExecutionForSpecifiedIdL(ref.iHandle, 3);
	GetTaskInfoL(*tasks, ref.iHandle);
	TEST(tasks->Count() == 1);
	info = tasks->At(0);
	TEST(info.iRepeat == 2); // still 2 repeats to go.
	ForceTaskExecutionForSpecifiedIdL(ref.iHandle, 2);

	CleanupStack::PopAndDestroy(tasks);
	
	TInt scheduleCount = CountScheduledItemsL(EPendingSchedules, TheScheduler);
	// There should be no schedules as its a transient one and last schedule
	// should have deleted itself.
	TEST(scheduleCount == 0); 
	SchSvrHelpers::Pause(TheTest);
	}

//***********************************************************************************

/**
@file
@SYMTestCaseID				SYSLIB-SCHSVR-CT-0256
@SYMTestCaseDesc 			Replicated test for for defect (DEF055586L) - UTC
@SYMTestPriority 			High
@SYMTestActions  			Create a time-based schedule check that there are 0 entries in the scehule after it fires
@SYMTestExpectedResults		The test must not fail.
@SYMPREQ					PREQ234
*/
static void DEF055586L()
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-SCHSVR-CT-0256 DEF055586 - Last element in array missed by loop "));
	TheTest.Next(_L("Connect to Scheduler"));
	TInt res = TheScheduler.Connect();
	TEST2(res, KErrNone);

	TheTest.Next(_L("Registering Client"));
	TEST2(SchSvrHelpers::RegisterClientL(TheScheduler), KErrNone);

	// Set the time to a known value, since this makes testing much easier (and more
	// repeatable).	
	SchSvrHelpers::SetHomeTimeL(TTime(TDateTime(2000, EJanuary, 1, 9, 55, 0, 0))); // 9:55 am

	// This is the time when we want the schedule to fire
	TDateTime datetime(2000, EJanuary, 1, 10, 0, 0, 0);
	TTsTime startTimeForSchedule(datetime, ETrue); // 10:00 am

	// Prepare a schedule describing when we want the tasks to run (10:00 am)
	TSchedulerItemRef ref;

	CScheduleEntryInfoArray* entryList = new (ELeave) CScheduleEntryInfoArray(1);
	CleanupStack::PushL(entryList);

	TScheduleEntryInfo2 entry1 (startTimeForSchedule, EDaily, 0, 30); // TTimeIntervalDays: set to 0 to induce an error
	entryList->AppendL(entry1);
	TInt err = TheScheduler.CreatePersistentSchedule(ref, *entryList);

	TEST2(err, KErrArgument);

	TheTest.Next(_L("DEF055586 - Now checking 0 entries in schedule"));
	entryList->Reset();
	
	err = TheScheduler.CreatePersistentSchedule(ref, *entryList);
	
	TEST2(err, KErrArgument);
	
	CleanupStack::PopAndDestroy(); // entryList
	}
	
//DEF061595  Schedule timers incorrectly expire when system time is changed 	
//The test will create and submit one schedule which execution time is one year later.
//Then the test will change the system time to be current time + 1 day.
//Although the schedule time is set to be current time + 1 year, the schedule task(s) will
//be executed immediately because the schedule timer expires when the system time changes.
void DEF061595L()
	{
	TheTest.Next(_L("DEF061595  Schedule timers incorrectly expire when system time is changed"));
	//Get current time in currTime variable
	TTime currTime;		
	currTime.HomeTime();
	//Prepare the task time (in taskTime variable) to be currTime + 1 year.
	TTime taskTime(currTime + TTimeIntervalYears(1));		
	TInt taskYear = taskTime.DateTime().Year();
	//Connect to the Task Scheduler Server	
	RScheduler	scheduler;
	CleanupClosePushL(scheduler);
	TInt res = scheduler.Connect();
	TEST2(res, KErrNone);
	TEST2(SchSvrHelpers::RegisterClientL(scheduler), KErrNone);
	//Create new schedule. The new schedule task will run 1 year later.
	TTsTime taskTsTime(taskTime, EFalse);
	TSchedulerItemRef ref;
	TEST2(::CreateScheduleL(ref, scheduler, taskTsTime), KErrNone);
	// Disable the schedule whilst we set it up
	TEST2(scheduler.DisableSchedule(ref.iHandle), KErrNone);
	// Associate a task with the schedule
	_LIT(KTaskInfo, "DEF061595");
	TTaskInfo taskInfo;
	taskInfo.iRepeat = 0;
	taskInfo.iName = KTaskInfo;
	taskInfo.iPriority = 2;
	const TInt KTaskDataLen = 1;
	HBufC* taskData = HBufC::NewLC(KTaskDataLen);
	TEST2(scheduler.ScheduleTask(taskInfo, *taskData, ref.iHandle), KErrNone);
	//We should now have one tasks scheduled to be executed after 1 year.
	//Enable schedule.
	TEST2(scheduler.EnableSchedule(ref.iHandle), KErrNone);
	//Get the scheduled task info. The task year should be the same as it was set in the schedule.
	TTime nextTime;	
	TPtr pTaskData = taskData->Des();
	TEST2(scheduler.GetTaskInfoL(taskInfo.iTaskId, taskInfo, pTaskData, ref, nextTime), KErrNone);
	TInt nextTaskYear = nextTime.DateTime().Year();	
	TEST(nextTaskYear == taskYear);
	//Change the system time to be current time + 1 day	
	TEST2(SchSvrHelpers::SetUTCTimeL(currTime + TTimeIntervalDays(1)), KErrNone);
	//Get the scheduled task info again. If the defect is not fixed, the call will fail
	//with KErrNotFound (because SchSvrHelpers::SetUTCTimeL() call will make the schedule timer to expire)
	TInt err = scheduler.GetTaskInfoL(taskInfo.iTaskId, taskInfo, pTaskData, ref, nextTime);
//TODO	TEST2(err, KErrNone);
//TODO	nextTaskYear = nextTime.DateTime().Year();
//TODO	TEST(nextTaskYear == taskYear);
	
	CleanupStack::PopAndDestroy(taskData);
	CleanupStack::PopAndDestroy(&scheduler);
	CleanupHelpers::KillProcess(KMinimalTaskHandler);
	}

/**
@SYMTestCaseID          SYSLIB-SCHSVR-CT-1655
@SYMTestCaseDesc	    Tests for defect number DEF079983
@SYMTestPriority 	    High
@SYMTestActions  	    Check to ensure all task files have been cleaned up
						after scheduled tasks completed
@SYMTestExpectedResults Test must not fail
@SYMDEF 				DEF079983
*/		
static void DEF079983L()
	{
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-SCHSVR-CT-1655 DEF079983: Private directory of schsvr flooded with files "));
	// A dummy scheduled task:
	// Create some transient schedule task and repeat 5 times
	TheTest.Printf(_L("DEF079983: Create a dummy scheduled task"));
	TInt tTask = 0;
	TSchedulerItemRef ref;
	// 5 repeats
	TInt res = ScheduleTransientTaskL(tTask, ref, 5, TheScheduler);
	TEST2(res, KErrNone);
	ForceTaskExecutionForSpecifiedIdL(ref.iHandle, 5);
	
	// Check for left task files after scheduled tasks completed
	// To access private data cage, uses SchSvrHelplers::CheckTaskFilesL()
	TheTest.Next(_L("DEF079983: Now checking no files left when tasks completed"));
	TInt err = SchSvrHelpers::CheckTaskFilesL();
	// If there's any task files left, test fails with error code KErrGeneral
	TEST(err == KErrNone);
	}		

/**
@SYMTestCaseID          SYSLIB-SCHSVR-CT-3362
@SYMTestCaseDesc	    Replicated test for for defect (INC098909) - UTC   
@SYMTestPriority 	    High
@SYMTestActions  	    Mark heap of Scheduler then create a schedule & task wait for its 
						execution then check heap again for memory leaks
@SYMTestExpectedResults Test must not fail (i.e. No memory leaks)
@SYMDEF                INC098909: Process !TaskScheluder leaks memory in mail polls.
*/
static void INC098909()
	{
	const TInt KTimeToWait = 10*1000*1000; 
	SchSvrHelpers::DeleteScheduleFilesL();
	
	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-SCHSVR-CT-3362 INC098909: Process !TaskScheluder leaks memory in mail polls "));
	TheTest.Next(_L("Connect to Scheduler"));
	TEST2(TheScheduler.Connect(),KErrNone);

	TheTest.Next(_L("Registering Client"));
	TEST2(SchSvrHelpers::RegisterClientL(TheScheduler), KErrNone);
	
	User::LeaveIfError(TheScheduler.__DbgMarkHeap());

	//Create Schedule
	CArrayFixFlat<TScheduleEntryInfo2>* entryList = new(ELeave) CArrayFixFlat<TScheduleEntryInfo2>(1);
	CleanupStack::PushL(entryList);
	TSchedulerItemRef ref;
	
	TTsTime startTime1(SchSvrHelpers::UtcTimeBasedOnOffset(0, 0), ETrue); // 0m:0s from "now"

	TScheduleEntryInfo2 entry1 (startTime1, EDaily, 1, 20);
	entryList->AppendL(entry1);
	
	// Create the schedule for the task...
	TEST2(TheScheduler.CreatePersistentSchedule(ref, *entryList),KErrNone);
	
	//Create Task
	TTaskInfo task;
	task.iRepeat	= 1; // repeat once
	task.iName		= _L("Test ");
	task.iPriority	= 100;
	
	HBufC* taskData = HBufC::NewLC(1);
	TEST2(TheScheduler.ScheduleTask(task, *taskData,ref.iHandle), KErrNone);
	
	CleanupStack::PopAndDestroy(taskData);
	CleanupStack::PopAndDestroy(entryList);	
	
	//Wait schedule to complete
	User::After(KTimeToWait);

	User::LeaveIfError(TheScheduler.__DbgMarkEnd(0));
	
	TheScheduler.Close();
	// really clean out the scheduler (get rid of all the files and process)
	SchSvrHelpers::DeleteScheduleFilesL();
	CleanupHelpers::KillProcess(KMinimalTaskHandler);
	// Now wait for something to happen...
	TEST2(STaskSemaphore::WaitL(KDefaultTimeout), KErrNone);	
	}

GLDEF_C TInt DoTheTestsL()
	{
	//Delete old files.
	SchSvrHelpers::DeleteScheduleFilesL();
	
	STaskSemaphore sem;
	sem.CreateL();

	TheTest.Next(_L("Start tests"));
	// Add tests here:-
	Test1L();
	Test2L();
	INC098909();
	DEF055586L();
	DEF061595L();
	DEF079983L();	// task file check test
	
	sem.Close();
	
	//Tidying up so next test will be clear.
	TheTest.Next(_L("Delete all schedules"));
	SchSvrHelpers::DeleteAllSchedulesL(TheScheduler);
	SchSvrHelpers::Pause(TheTest, 2);
	TheTest.Next(_L("Delete old files\n"));
	SchSvrHelpers::DeleteScheduleFilesL();

	TheScheduler.Close();

	return KErrNone;
	}

//***********************************************************************************
GLDEF_C TInt E32Main()
    {
	__UHEAP_MARK;
	TheTest.Title();
	TheTest.Start(_L("TC_TSCH_SCHEDULING1 - UTC"));

	TInt error = KErrNone;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	if	(!cleanup)
		return KErrNoMemory;
	//If the previous test fails, SCHSVR.exe may stay in memory.
	TRAP(error,CleanupHelpers::TestCleanupL());
	TEST2(error, KErrNone);

	TTime now;
	now.HomeTime();
	// Used to Set the system UTC time and UTC offset
	// so that correct UTC Time values are returned while using time based APIs.
	SchSvrHelpers::SetHomeTimeL(now);

	TEST2(TheFsSession.Connect(), KErrNone);
	TheTest.Next(_L("Do the tests"));
	TRAP(error, DoTheTestsL());
	TEST2(error,KErrNone);
	TheFsSession.Close();
	TRAP(error,CleanupHelpers::TestCleanupL());
	TEST2(error, KErrNone);
	delete cleanup;	

	TheTest.End();
	TheTest.Close();
	__UHEAP_MARKEND;
	return KErrNone;
	}
