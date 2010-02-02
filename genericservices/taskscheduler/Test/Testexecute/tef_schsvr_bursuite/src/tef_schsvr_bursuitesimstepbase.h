/**
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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



/**
 @file
*/

#if (!defined __TEF_SCHSVR_BURSUITESIMSTEPBASE__)
#define __TEF_SCHSVR_BURSUITESIMSTEPBASE__

#include "tef_schsvr_bursuitestepbase.h"
#include <babackup.h>

/////////////////////////////////////////

class CTefSchsvrBURSuiteSimStepBase : public CTefSchsvrBURSuiteStepBase
	{
public:
	virtual ~CTefSchsvrBURSuiteSimStepBase();
	CTefSchsvrBURSuiteSimStepBase();

protected:
	void Simulate_StartBackupL();
	void Simulate_EndBackupL();
	void Simulate_StartRestoreL();
	void Simulate_EndRestoreL(TBool aSuccess);

	virtual TVerdict doTestStepPreambleL(); 	

private:
	CBaBackupSessionWrapper* iBackupClient;
	CActiveScheduler* iSched;	
	};

#endif
