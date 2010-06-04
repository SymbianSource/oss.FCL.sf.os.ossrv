/**
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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



#if (!defined __persist_mixed_STEP_H__)
#define __persist_mixed_STEP_H__
#include <test/testexecutestepbase.h>
#include "Te_floating_scheduleSuiteStepBase.h"

class Cpersist_mixedStep : public CTe_floating_scheduleSuiteStepBase
	{
public:
	Cpersist_mixedStep();
	~Cpersist_mixedStep();
	virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	virtual TVerdict doTestStepPostambleL();

// Please add/modify your class members here:
private:
	};

_LIT(Kpersist_mixedStep,"persist_mixedStep");

#endif
