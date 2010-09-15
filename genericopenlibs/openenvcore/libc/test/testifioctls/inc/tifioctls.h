/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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



#ifndef __TESTIFIOCTLS_H__
#define __TESTIFIOCTLS_H__

#include <test/testexecutestepbase.h>

_LIT(KExampleL, "ExampleL");
_LIT(KListInterfaces, "ListInterfaces");
_LIT(KCreateManyActiveInterfaces, "CreateManyActiveInterfaces");
_LIT(KChooseInterface, "ChooseInterface");
_LIT(KChooseActiveInterface, "ChooseActiveInterface");
_LIT(KTestIfNameIndex, "TestIfNameIndex");
_LIT(KTestIfIndexToName, "TestIfIndexToName");
_LIT(KTestIfNameToIndex, "TestIfNameToIndex");
_LIT(KTestSiocGIfIndex, "TestSiocGIfIndex");
_LIT(KConnectToIpUsingConnection, "ConnectToIpUsingConnection");
_LIT(KSendtoIpUsingConnection, "SendtoIpUsingConnection");
_LIT(KConnectToUrlUsingConnection, "ConnectToUrlUsingConnection");
_LIT(Kioctltest, "ioctltest");
_LIT(Kreadtest, "readtest");
_LIT(KTestAddDelRoute, "TestAddDelRoute");
_LIT(KTestAddDelRouteNegative1, "TestAddDelRouteNegative1");
_LIT(KTestAddDelRouteNegative2, "TestAddDelRouteNegative2");
_LIT(KTestMacAddress, "TestMacAddress");
_LIT(KTestMacAddressNegative1, "TestMacAddressNegative1");
_LIT(KTestioctlfile, "Testioctlfile");
_LIT(KTestioctl1, "Testioctl1");
_LIT(KTestioctlGetIfIpAddr, "TestGetIfIPAddr");
_LIT(KTestioctlGetIfAttributes, "TestGetIfAttributes");
_LIT(KTestioctlSetIfAttributes, "TestSetIfAttributes");
_LIT(KTestioctlSetIfDNSSuffix, "TestSetIfDNSSuffix");
_LIT(KTestioctlGetIfDNSSuffix, "TestGetIfDNSSuffix");
_LIT(KTestRouteIoctl, "TestRouteIoctl");
_LIT(KTestNumberOfRoutesIoctl, "TestNumberOfRoutesIoctl");
_LIT(KTestSetNameServers, "TestSetNameServers");
_LIT(KTestGetNameServers, "TestGetNameServers");


class CTestIfioctls : public CTestStep
	{
public:
	~CTestIfioctls(); 
	CTestIfioctls(const TDesC& aStepName);
	TVerdict doTestStepL();
	TVerdict doTestStepPreambleL();
	TVerdict doTestStepPostambleL();
private:
	TInt ExampleL();
	TInt ListInterfaces();
	TInt CreateManyActiveInterfaces();
	TInt ChooseInterface();
	TInt ChooseActiveInterface();
	TInt TestIfNameIndex();
	TInt TestIfIndexToName();
	TInt TestIfNameToIndex();
	TInt TestSiocGIfIndex();
	TInt ConnectToIpUsingConnection();
	TInt SendtoIpUsingConnection();
	TInt ConnectToUrlUsingConnection();
	TInt ioctltest();
	TInt readtest();
	TInt TestAddDelRoute();
	TInt TestAddDelRouteNegative1();
	TInt TestAddDelRouteNegative2();
	TInt TestMacAddress();
	TInt TestMacAddressNegative1();
	TInt Testioctlfile();
	TInt Testioctl1();
	TInt TestGetIfIPAddr();
	TInt GetIapName(char * aIapName,int len);
	TInt StartIap(const char *aIapName, int &fd);
	TInt TestGetIfAttributes();
	void printFlags(TInt flags);
	TInt TestSetIfAttributes();
	void FreeDnsSuffixes(char ** suffixes);
	TInt TestSetIfDNSSuffix();
	TInt TestGetIfDNSSuffix();	
	TInt TestRouteIoctl();
	TInt TestNumberOfRoutesIoctl();
	TInt TestSetNameServers();
	TInt TestGetNameServers();

	// util function
	void ReadStringParam(char* aString);
public:
	TInt iParamCount;
	
	};
#endif //
