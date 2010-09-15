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


// INCLUDE FILES
#include <e32svr.h>
#include "tifioctls.h"

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <stdapis/arpa/inet.h>
#include <cdblen.h>
#include <stdapis/net/if.h>
#include <sys/ioctl.h>
#include <stdapis/netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdapis/net/route.h>
#include <in_sock.h>
#include <in_iface.h>
#include <es_sock.h>
#include <in_sock.h>
#include <in_iface.h>
#include <nifman.h>
 

// EXTERNAL FUNCTION PROTOTYPES
TInt PrintInterfaceList(void *aIfc);
TInt PrintAndSelectInterface(void *aIfc, ifreq &aIfr);
//void GetParameters(char aParamets[10][256]);
void StripStar(char *aString);

// CONSTANTS
const TInt KErrSocket = -1002;
const TInt KErrIoctl = -1003;
//const TInt KErrGetHostByName = -1004;
const TInt KErrBind = -1005;
const TInt KErrConnect = -1006;
const TInt KErrSendto = -1007;

const TUint KTestPort = 5000;



// MODULE DATA STRUCTURES
enum InterfaceType
	{
	EACCESS_POINT,
	EACTIVE_CONNECTION
	};
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestIfioctls::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTestIfioctls::ExampleL(  )
    {

    // Print to UI
    _LIT( Ktifioctls, "tifioctls: In Example" );
    INFO_PRINTF1(Ktifioctls);
    
    TPtrC string;
    _LIT( KParam, "Param: %S" );
    _LIT( Kstring, "string" );
     
    TBool res = GetStringFromConfig(ConfigSection(), Kstring, string);
    if (res)
    {
        INFO_PRINTF2( KParam, &string );
       
    }
    return KErrNone;

    }
TInt CTestIfioctls::ListInterfaces(  )
	{
	ifconf ifc;
	TInt sockfd;
	TInt ret = KErrNone;
	TBool res = EFalse;
	TInt Iface;
	_LIT( KIface, "Iface" );
	TInt operation ; 
	sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);	
    if (sockfd < 0)
        {
        ret = KErrSocket;
        goto close;
        }
   	
   	TInt IfconfLen;
   	_LIT( KIfconfLen, "IfconfLen" );
	res = GetIntFromConfig(ConfigSection(), KIfconfLen, IfconfLen);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read ifconfig length") ;
		close(sockfd);
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}
   
	ifc.ifc_len = sizeof(ifreq) * IfconfLen;	
	if (ifc.ifc_len == 0)
		{
		ifc.ifc_buf = NULL;
		}
	else
		{
		ifc.ifc_buf = (caddr_t)malloc( ifc.ifc_len );
		}	
	// 1 = Interfaces, 2 = Active interfaces
	
	res = GetIntFromConfig(ConfigSection(), KIface, Iface);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read interface type") ;
	 	INFO_PRINTF1(Kerr) ;
		close(sockfd);
	 	return KErrGeneral ;
		}

	operation = Iface; 
	if (operation == 2)
		{
		ret = ioctl(sockfd,SIOCGIFACTIVECONF, &ifc);
		}
	else if (operation == 1)
		{
		ret = ioctl(sockfd,SIOCGIFCONF, &ifc);
		}
		
	close:
		close(sockfd);
		free(ifc.ifc_buf);
		return ret;
	}
	
	
TInt CTestIfioctls::CreateManyActiveInterfaces(  )
	{
	ifreq ifr;
	TInt sockfdArry[100];
	TInt sockfdCnt;
	TInt ret = KErrNone;
	TInt index;	
	ifconf ifc;	
	TInt sockfd;
	
	// Name of the interface
	TPtrC String;
	_LIT( KString, "String" );
    TBool res = GetStringFromConfig(ConfigSection(), KString, String );
	if(!res)  
		{
     	_LIT(Kerr , "Failed to read interface name") ;
     	INFO_PRINTF1(Kerr) ;
     	return KErrGeneral ;
		}
    TBuf8<256> asciiBuffer;
	asciiBuffer.Copy(String);
	TInt len = asciiBuffer.Length();
	
	Mem::Copy(ifr.ifr_name, asciiBuffer.Ptr(), len);
	ifr.ifr_name[len] = 0;

	StripStar(ifr.ifr_name);

	// Number of interafces
	TInt No;
	_LIT( KNo, "No" );
	res = GetIntFromConfig(ConfigSection(), KNo, No);

	sockfdCnt = No;	
	
	for (index = 0; index < sockfdCnt; index++)
		{
		sockfdArry[index] = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);	
    	if (sockfdArry[index] < 0)
        	{
        	ret = KErrSocket;
        	goto close;
        	}
		ret = ioctl(sockfdArry[index],SIOCSIFNAME, &ifr);
		if (ret != KErrNone)
			{
			ret = KErrIoctl;
			goto close;
			}
		ret = ioctl(sockfdArry[index], SIOCIFSTART , &ifr);
		if (ret != KErrNone)
			{
			goto close;
			}
		}
	ifc.ifc_buf = NULL;
	sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);	
    if (sockfd < 0)
       	{
       	ret = KErrSocket;
       	goto close;
       	}
	ret = ioctl(sockfd,SIOCGIFACTIVECONF, &ifc);

close:
	for (index = 0; index < sockfdCnt; index++)
		{
		ioctl(sockfdArry[index], SIOCIFSTOP, &ifr);
		close(sockfdArry[index]);
		}
	return ret;
	}
	
	
TInt CTestIfioctls::ChooseInterface()
	{
	ifreq ifr;
	TInt sockfd;
	TInt ret = KErrNone;	
	// Name of the interface
	TPtrC String;
	_LIT( KString, "String" );
    TBool res = GetStringFromConfig(ConfigSection(), KString, String );
	if(!res)  
		{
     	_LIT(Kerr , "Failed to read interface name") ;
     	INFO_PRINTF1(Kerr) ;
     	return KErrGeneral ;
		}
    TBuf8<256> asciiBuffer;
	asciiBuffer.Copy(String);

	TInt len = asciiBuffer.Length();
	Mem::Copy(ifr.ifr_name, asciiBuffer.Ptr(), len);
	ifr.ifr_name[len] = 0;
	StripStar(ifr.ifr_name);
	
	sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);	
    if (sockfd < 0)
        {
        ret = KErrSocket;
        close(sockfd);
		return ret;
        }
	ret = ioctl(sockfd,SIOCSIFNAME, &ifr);
	if (ret != KErrNone)
		{
		ret = KErrIoctl;
		close(sockfd);
		return ret;
		}
	ret = ioctl(sockfd, SIOCIFSTART , &ifr);
	if (ret != KErrNone)
		{
		close(sockfd);
		return ret;
		}
	
	ret = ioctl(sockfd, SIOCIFSTOP, &ifr);
	return ret;		
	}
		
	
TInt CTestIfioctls::ChooseActiveInterface(  )
	{
	ifreq ifr;
	TInt sockfd1=0, sockfd2=0;
	TInt ret = KErrNone;
	// Name of the interface
	TPtrC String;
	_LIT( KString, "String" );
    TBool res = GetStringFromConfig(ConfigSection(), KString, String );
	if(!res)  
    	{
     	_LIT(Kerr , "Failed to read interface name") ;
     	INFO_PRINTF1(Kerr) ;
     	return KErrGeneral ;
    	}
	TBuf8<256> asciiBuffer;
	asciiBuffer.Copy(String);

	TInt len = asciiBuffer.Length();
	Mem::Copy(ifr.ifr_name, asciiBuffer.Ptr(), len);
	ifr.ifr_name[len] = 0;
	StripStar(ifr.ifr_name);
	
	sockfd1 = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if (sockfd1 < 0)
        {
        ret = KErrSocket;
        ioctl(sockfd1, SIOCIFSTOP, &ifr);
		close(sockfd1);
		return ret;
        }
	ret = ioctl(sockfd1,SIOCSIFNAME, &ifr);
	if (ret != KErrNone)
		{
		ret = KErrIoctl;
		ioctl(sockfd1, SIOCIFSTOP, &ifr);
		close(sockfd1);
		return ret;
		}
	ret = ioctl(sockfd1, SIOCIFSTART , &ifr);
	if (ret != KErrNone)
		{
		ioctl(sockfd1, SIOCIFSTOP, &ifr);
		close(sockfd1);
		return ret;
		}
		
	sockfd2 = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if (sockfd2 < 0)
        {
        ret = KErrSocket;
        ioctl(sockfd2, SIOCIFSTOP, &ifr);
		ioctl(sockfd1, SIOCIFSTOP, &ifr);
		close(sockfd1);
		return ret;
        }
	ret = ioctl(sockfd2,SIOCSIFNAME, &ifr);
	if (ret != KErrNone)
		{
		ret = KErrIoctl;
		ioctl(sockfd2, SIOCIFSTOP, &ifr);
		ioctl(sockfd1, SIOCIFSTOP, &ifr);
		close(sockfd1);
		return ret;
		}
	ret = ioctl(sockfd2, SIOCIFACTIVESTART , &ifr);
	if (ret != KErrNone)
		{
		ioctl(sockfd2, SIOCIFSTOP, &ifr);
		ioctl(sockfd1, SIOCIFSTOP, &ifr);
		close(sockfd1);
		return ret;
		}
	return ret;
	}
	
TInt CTestIfioctls::TestIfNameIndex()
	{
	TInt ret = KErrNone;
	struct if_nameindex *ifname;
	ifname = if_nameindex();
	if_freenameindex(ifname);
	return ret;
	}	
	
TInt CTestIfioctls::TestIfIndexToName(  )
	{
	TInt ret = KErrNone;
	char ifName[255];	
	
	TInt IfIndex;
	_LIT( KIfIndex, "IfIndex" );
	TBool res = GetIntFromConfig(ConfigSection(), KIfIndex, IfIndex);
	if(!res)
		{
	 	_LIT(Kerr , "Failed to read interface index from ini file.") ;
	 	INFO_PRINTF1(Kerr) ;
	 	return KErrGeneral ;
		}

	if_indextoname(IfIndex, ifName);
	
	return ret;
	}	

TInt CTestIfioctls::TestIfNameToIndex(  )
	{
	TInt ret = KErrNone;
	char IfName[30];
	TPtrC String;
	_LIT( KString, "String" );
    TBool res = GetStringFromConfig(ConfigSection(), KString, String );
    if(!res)  
		{
     	_LIT(Kerr , "Failed to read interface name from ini file.") ;
     	INFO_PRINTF1(Kerr) ;
     	return KErrGeneral ;
		}
	TBuf8<256> asciiBuffer;
	asciiBuffer.Copy(String);

	TInt len = asciiBuffer.Length();
	Mem::Copy(IfName, asciiBuffer.Ptr(), len);
	IfName[len] = 0;	
	StripStar(IfName);
	if_nametoindex(IfName);
	
	return ret;
	}
	

TInt CTestIfioctls::TestSiocGIfIndex(  )
	{
	TInt ret = KErrNone;
	
	struct ifreq ifr;
	int sockfd;
	
	TPtrC String;
	_LIT( KString, "String" );
    TBool res = GetStringFromConfig(ConfigSection(), KString, String );
    if(!res)  
		{
     	_LIT(Kerr , "Failed to read interface name from ini file.") ;
     	INFO_PRINTF1(Kerr) ;
     	return KErrGeneral ;
		}
	TBuf8<256> asciiBuffer;
	 asciiBuffer.Copy(String);

	TInt len = asciiBuffer.Length();
	Mem::Copy(ifr.ifr_name, asciiBuffer.Ptr(), len);
	ifr.ifr_name[len] = 0;
	StripStar(ifr.ifr_name);
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);	
	*(ifr.ifr_name + sizeof(ifr.ifr_name) - 1 ) = '\0';
	if (ioctl(sockfd, SIOCGIFINDEX, &ifr) != -1)
		{
		ret = KErrIoctl;
		}
		
	close(sockfd);
	return ret;
	}


TInt CTestIfioctls::ConnectToIpUsingConnection(  )
	{
	ifreq ifr;
	TInt sockfd;
	TInt ret = KErrNone;
	struct sockaddr_in destAddr, selfAddr;	
	TPtrC String = NULL ;
	
	// Name of the interface
	TPtrC IfaceName;
	_LIT( KIfaceName, "IfaceName" );
    TBool res = GetStringFromConfig(ConfigSection(), KIfaceName, IfaceName);
    if(!res)  
		{
     	_LIT(Kerr , "Failed to read interface name from ini file.") ;
     	INFO_PRINTF1(Kerr) ;
     	return KErrGeneral ;
		}
	TBuf8<256> asciiBuffer;
	 asciiBuffer.Copy(IfaceName);

	TInt len = asciiBuffer.Length();
	Mem::Copy(ifr.ifr_name, asciiBuffer.Ptr(), len);
	ifr.ifr_name[len] = 0;
	StripStar(ifr.ifr_name);
	
	sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);	
    if (sockfd < 0)
        {
        ret = KErrSocket;
        goto close;
        }
	ret = ioctl(sockfd,SIOCSIFNAME, &ifr);
	if (ret != KErrNone)
		{
		ret = KErrIoctl;
		goto close;
		}
	ret = ioctl(sockfd, SIOCIFSTART , &ifr);
	if (ret != KErrNone)
		{
		goto close;
		}
	
	selfAddr.sin_family = AF_INET;
	selfAddr.sin_addr.s_addr = INADDR_ANY;
	selfAddr.sin_port = htons(KTestPort);	/* echo */
	
	ret = bind(sockfd,(struct sockaddr*)&selfAddr, sizeof(selfAddr));
	if (ret != KErrNone)
		{
		ret = KErrBind;
		goto close;
		}
	
	destAddr.sin_family = AF_INET;
	
	char ipaddr[20];
	
	_LIT( KString, "String" );
    res = GetStringFromConfig(ConfigSection(), KString, String );
    if(!res)  
		{
     	_LIT(Kerr , "Failed to read interface name from ini file.") ;
     	INFO_PRINTF1(Kerr) ;
     	return KErrGeneral ;
		}
	asciiBuffer.Copy(String);

	len = asciiBuffer.Length();
	Mem::Copy(ipaddr, asciiBuffer.Ptr(), len);
	ipaddr[len] = 0;
	
	destAddr.sin_addr.s_addr = inet_addr(ipaddr);
	destAddr.sin_port = htons(KTestPort);	/* http */
	ret = connect(sockfd, (struct sockaddr*)&destAddr, sizeof(destAddr));
	if (ret != KErrNone)
		{
		ret = KErrConnect;
		goto close;
		}

	close:
	ioctl(sockfd, SIOCIFSTOP, &ifr);
	close(sockfd);
	return ret;
	}
	

TInt CTestIfioctls::SendtoIpUsingConnection(  )
	{
	ifreq ifr;
	TInt sockfd;
	TInt ret = KErrNone;
	struct sockaddr_in destAddr, selfAddr;		
	
	char message[] = "Hello How Are You";
	TInt length;
	TInt size;
	TPtrC String = NULL;
	
	// Name of the interface
	TPtrC IfaceName;
	_LIT( KIfaceName, "IfaceName" );
    TBool res = GetStringFromConfig(ConfigSection(), KIfaceName, IfaceName);
    if(!res)  
		{
     	_LIT(Kerr , "Failed to read interface name from ini file.") ;
     	INFO_PRINTF1(Kerr) ;
     	return KErrGeneral ;
		}
	TBuf8<256> asciiBuffer;
	asciiBuffer.Copy(IfaceName);

	TInt len = asciiBuffer.Length();
	Mem::Copy(ifr.ifr_name, asciiBuffer.Ptr(), len);
	ifr.ifr_name[len] = 0;
	StripStar(ifr.ifr_name);
	
	sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);	
    if (sockfd < 0)
        {
        ret = KErrSocket;
        goto close;
        }
	ret = ioctl(sockfd,SIOCSIFNAME, &ifr);
	if (ret != KErrNone)
		{
		ret = KErrIoctl;
		goto close;
		}
	ret = ioctl(sockfd, SIOCIFSTART , &ifr);
	if (ret != KErrNone)
		{
		goto close;
		}
	selfAddr.sin_family = AF_INET;
	selfAddr.sin_addr.s_addr = INADDR_ANY;
	selfAddr.sin_port = htons(KTestPort);	/* echo */
	
	ret = bind(sockfd,(struct sockaddr*)&selfAddr, sizeof(selfAddr));
	if (ret != KErrNone)
		{
		ret = KErrBind;
		goto close;
		}
	
	length = strlen(message);
	destAddr.sin_family = AF_INET;
	
	char ipaddr[20];
	
	_LIT( KString, "String" );
    res = GetStringFromConfig(ConfigSection(), KString, String );
    if(!res)  
		{
     	_LIT(Kerr , "Failed to read interface name from ini file.") ;
     	INFO_PRINTF1(Kerr) ;
		close(sockfd);
     	return KErrGeneral ;
		}
	asciiBuffer.Copy(String);

	len = asciiBuffer.Length();
	Mem::Copy(ipaddr,asciiBuffer.Ptr(), len);
	ipaddr[len] = 0;
	
	destAddr.sin_addr.s_addr = inet_addr(ipaddr);
	destAddr.sin_port = htons(KTestPort);	/* http */
	size = sizeof(destAddr);
	ret = sendto(sockfd, message, length, 0, (struct sockaddr*)&destAddr, size);
	if (ret == -1)
		{
		ret = KErrSendto;
		goto close;
		}
	if (ret >= 0)
		{
		ret = 0;
		}

	close:
	ioctl(sockfd, SIOCIFSTOP, &ifr);
	close(sockfd);
	return ret;
	}

void StripStar(char *aString)
{
	TInt len = strlen(aString);
	TInt index;
	
	for (index = 0; index < len; index++)
		{
		if ( aString[index] == '*' )
			{
			aString[index] = ' ';
			}
		}
}


TInt CTestIfioctls::ConnectToUrlUsingConnection()
	{
	ifreq ifr;
	TInt sockfd;
	TInt ret = KErrNone;	
	struct sockaddr_in destAddr, selfAddr;	
	struct in_addr *addrp;
	
	TPtrC accessPointName,url;
	_LIT( KParameter1, "Parameter1" );
    TBool res = GetStringFromConfig(ConfigSection(), KParameter1, accessPointName );
    
    _LIT( KParameter2, "Parameter2" );
    res = GetStringFromConfig(ConfigSection(), KParameter2, url );
    
	
	// Name of the interface
	TBuf8<256> asciiBuffer;
	asciiBuffer.Copy(accessPointName);

	TInt len = asciiBuffer.Length();
	Mem::Copy(ifr.ifr_name, asciiBuffer.Ptr(), len);
	ifr.ifr_name[len] = 0;
	
	StripStar(ifr.ifr_name);
	
	struct hostent *hp = 0;
	
	sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);	
    if (sockfd < 0)
        {
        ret = KErrSocket;
        goto close;
        }
	ret = ioctl(sockfd,SIOCSIFNAME, &ifr);
	if (ret != KErrNone)
		{
		ret = KErrIoctl;
		goto close;
		}
	ret = ioctl(sockfd, SIOCIFSTART , &ifr);
	if (ret != KErrNone)
		{
		goto close;
		}
	
	
	char urlBuf[25];
	asciiBuffer.Copy(url);

	len = asciiBuffer.Length();
	Mem::Copy((void *)urlBuf, asciiBuffer.Ptr(), len);
	urlBuf[len] = 0;
	hp = gethostbyname((const char*) urlBuf );
	if (hp != NULL)
		{
		addrp = (struct in_addr*)(hp->h_addr_list[0]);
		}
	else
		{
		ret = 0;
		goto close;
		}
	
	selfAddr.sin_family = AF_INET;
	selfAddr.sin_addr.s_addr = INADDR_ANY;
	selfAddr.sin_port = htons(KTestPort);	/* echo */
	
	ret = bind(sockfd,(struct sockaddr*)&selfAddr, sizeof(selfAddr));
	if (ret != KErrNone)
		{
		ret = KErrBind;
		goto close;
		}
	
	destAddr.sin_family = AF_INET;
	destAddr.sin_addr = *addrp;
	destAddr.sin_port = htons(KTestPort);	/* http */
	ret = connect(sockfd, (struct sockaddr*)&destAddr, sizeof(destAddr));
	if (ret != KErrNone)
		{
		ret = KErrConnect;
		goto close;
		}

	close:
	ioctl(sockfd, SIOCIFSTOP, &ifr);
	close(sockfd);
	return ret;
	}

/*ioctl test for coverage*/
TInt CTestIfioctls::ioctltest()
	{
	int fd1 = 0;
	int ret = 0;
	int fperm = O_RDWR;
	fd1 = open("CON:", fperm);
	if (fd1 < 0)
		{
		_LIT( Kinfo1, "error in open()" );
		INFO_PRINTF1(Kinfo1);
		return fd1;
		}
	ret = ioctl(fd1, IOC_OUT);
	if (ret < 0)
		{
		_LIT( Kinfo1, "error in ioctl()" );
		INFO_PRINTF1(Kinfo1);
		INFO_PRINTF2(_L("errno = %d"), errno);
		if (errno == ENOSYS)
			{
			_LIT( Kinfo1, "ioctl_completion() not supported on tty console");
			INFO_PRINTF1(Kinfo1);
			return KErrNone;
			}
		return ret;
		}
		
	return KErrNone;
	}
	
	
/*read test for coverage 
//this is supposed to be a manual test
//This is beacuse we cannot automate key pressing characters
//to the console*/
TInt CTestIfioctls::readtest()
	{
	int fd1 = 0;
	int ret = 0;
	int fperm = O_RDONLY;
	char buffer1[9] = "open iam";
	fd1 = open("CON:", fperm);
	if (fd1 < 0)
		{
		_LIT( Kinfo1, "error in open()" );
		INFO_PRINTF1(Kinfo1);
		return fd1;
		}
	ret = read(fd1, &buffer1, 4);
	if (ret < 0)
		{
		close(fd1);
		_LIT( Kinfo2, "error in read()" );
		INFO_PRINTF1(Kinfo2);
		return ret;
		}	
	close(fd1);
	return KErrNone;
	}

// Util function
void GetIpFromDHCPServer(void)
    {
    RSocketServ rSockServer;
    if(KErrNone==rSockServer.Connect())
        {
        RConnection rConnect;
        if(KErrNone==rConnect.Open(rSockServer))
            {
            TRequestStatus status; 
            rConnect.Start(status);
                
            User::WaitForRequest(status); 
            }
        } 
    }

// Util function
TInt GetIfrName(char* ifrname, int size)
    {
    char* tInfr = 0;
    TBuf8<KMaxName> ifbuf;
    
	GetIpFromDHCPServer();
    TAutoClose<RSocketServ> ss;
    ss.iObj.Connect();
    
    TAutoClose<RSocket> sock;
    sock.iObj.Open(ss.iObj, _L("udp"));
    
    sock.iObj.SetOpt(KSoInetEnumInterfaces, KSolInetIfCtrl);

    TProtocolDesc in;
    sock.iObj.Info(in);
    
    TPckgBuf<TSoInetInterfaceInfo> info, next;

    TInt res=sock.iObj.GetOpt(KSoInetNextInterface, KSolInetIfCtrl, info);
    if(res!=KErrNone)
       	return KErrGeneral;
    
        
    while(res==KErrNone)
        {
		
        res=sock.iObj.GetOpt(KSoInetNextInterface, KSolInetIfCtrl, next);
	
		if(info().iState != EIfUp || info().iFeatures&KIfIsLoopback || info().iName.Left(4) == _L("eth6")) 
			{
			info = next; continue;	
			}
		
		ifbuf.Copy(info().iName);
		tInfr = (char*) ifbuf.Ptr();
		if( tInfr &&  (size > info().iName.Length()) )
			{
			tInfr[info().iName.Length()] = '\0';		
			strcpy(ifrname, tInfr);
			}
			 
        TName address;
	    info().iAddress.Output(address);
	    
        info().iNetMask.Output(address);
               
        if(res==KErrNone)
            {
            info = next;
         	}
        }
	return KErrNone;
    }

/**
* Function Name		: TestAddDelRoute
* Description		: Add and delete a static route 
* Return Value		: KErrNone
*/
TInt CTestIfioctls::TestAddDelRoute()
{
	struct rtentry rt;
	int ret=KErrNone;
	int sockid;
	char ifrname[25];
	
	memset (&ifrname,0,sizeof(ifrname));
	memset (&rt,0,sizeof(struct rtentry));
	sockid=socket ( AF_INET, SOCK_DGRAM, 0 );
	
	ret = GetIfrName(ifrname,  sizeof(ifrname));
	if (ret == KErrGeneral)
		{
		INFO_PRINTF1(_L("GetOpt fails"));
		return KErrGeneral;
		}
	
	if (!ifrname || ifrname[0] == '\0') 
		{
        INFO_PRINTF1(_L("invalid ifrname"));
    	return KErrGeneral;
    	}
    
	rt.rt_dev=ifrname;
	memset( &rt.rt_dst, 0, sizeof( struct sockaddr_in ) );
	((struct sockaddr_in * )&rt.rt_dst)->sin_family = AF_INET;
	((struct sockaddr_in * )&rt.rt_dst)->sin_addr.s_addr=inet_addr("225.0.0.0");
    ((struct sockaddr_in * )&rt.rt_dst)->sin_port = htons( 6000 );	

	memset( &rt.rt_gateway, 0, sizeof( struct sockaddr_in ) );
	((struct sockaddr_in * )&rt.rt_gateway)->sin_family = AF_INET;	
	((struct sockaddr_in * )&rt.rt_gateway)->sin_addr.s_addr=inet_addr("169.254.39.111");
	((struct sockaddr_in * )&rt.rt_gateway)->sin_port = htons( 6000 );	

	memset( &rt.rt_genmask, 0, sizeof( struct sockaddr_in ) );
	((struct sockaddr_in * )&rt.rt_genmask)->sin_family = AF_INET;	
	((struct sockaddr_in * )&rt.rt_genmask)->sin_addr.s_addr=inet_addr("255.255.0.0");
    ((struct sockaddr_in * )&rt.rt_genmask)->sin_port = htons( 6000 );	
    	
	ret=ioctl(sockid, SIOCADDRT, &rt);
	if(ret == 0)
		{
		ret=ioctl(sockid, SIOCDELRT, &rt);	
		if(ret<0)
			{
			INFO_PRINTF2(_L("ioctl() -SIOCDELRT failed: %d\n"), errno);
			ret = KErrGeneral;	
			}
		}
	else
		{
		INFO_PRINTF2(_L("ioctl() -SIOCADDRT failed: %d\n"), errno);
		ret = KErrGeneral;
		}	
	
	close(sockid);
	return ret;	
}

/**
* Function Name		: TestAddDelRouteNegative1
* Description		: Pass NULL for interface name
* Return Value		: KErrNotFound by ioctl() and KErrNone by the test case
*/
TInt CTestIfioctls::TestAddDelRouteNegative1()
	{
	struct rtentry rt;
	int ret=KErrNone;
	int sockid;
		
	memset (&rt,0,sizeof(struct rtentry));
	sockid=socket ( AF_INET, SOCK_DGRAM, 0 );
	
	rt.rt_dev=NULL;
	
	memset( &rt.rt_dst, 0, sizeof( struct sockaddr_in ) );
	((struct sockaddr_in * )&rt.rt_dst)->sin_family = AF_INET;
	((struct sockaddr_in * )&rt.rt_dst)->sin_addr.s_addr=inet_addr("");
    ((struct sockaddr_in * )&rt.rt_dst)->sin_port = htons( 0 );	

	memset( &rt.rt_gateway, 0, sizeof( struct sockaddr_in ) );
	((struct sockaddr_in * )&rt.rt_gateway)->sin_family = AF_INET;	
	((struct sockaddr_in * )&rt.rt_gateway)->sin_addr.s_addr=inet_addr("");
	((struct sockaddr_in * )&rt.rt_gateway)->sin_port = htons( 0 );	

	memset( &rt.rt_genmask, 0, sizeof( struct sockaddr_in ) );
	((struct sockaddr_in * )&rt.rt_genmask)->sin_family = AF_INET;	
	((struct sockaddr_in * )&rt.rt_genmask)->sin_addr.s_addr=inet_addr("");
    ((struct sockaddr_in * )&rt.rt_genmask)->sin_port = htons( 0 );	
    	
	ret=ioctl(sockid, SIOCADDRT, &rt);
	if(ret == KErrNotFound)
		{
		ret = KErrNone;
		}
	else
		{
		INFO_PRINTF2(_L("ioctl() - SIOCADDRT failed: %d\n"), errno);
		ret = KErrGeneral;
		}	
	
	close(sockid);
	return ret;	
	}


/**
* Function Name		: TestAddDelRouteNegative2
* Description		: Pass invalid name for interface
* Return Value		: KErrNotFound by ioctl() and KErrNone by the test case
*/
TInt CTestIfioctls::TestAddDelRouteNegative2()
	{
	struct rtentry rt;
	int ret=KErrNone;
	int sockid;
	char ifrname[25]="eth[0x000000]";	
	memset (&rt,0,sizeof(struct rtentry));
	sockid=socket ( AF_INET, SOCK_DGRAM, 0 );
	
	
	rt.rt_dev=ifrname;
	
	memset( &rt.rt_dst, 0, sizeof( struct sockaddr_in ) );
	((struct sockaddr_in * )&rt.rt_dst)->sin_family = AF_INET;
	((struct sockaddr_in * )&rt.rt_dst)->sin_addr.s_addr=inet_addr("");
    ((struct sockaddr_in * )&rt.rt_dst)->sin_port = htons( 0 );	

	memset( &rt.rt_gateway, 0, sizeof( struct sockaddr_in ) );
	((struct sockaddr_in * )&rt.rt_gateway)->sin_family = AF_INET;	
	((struct sockaddr_in * )&rt.rt_gateway)->sin_addr.s_addr=inet_addr("");
	((struct sockaddr_in * )&rt.rt_gateway)->sin_port = htons( 0 );	

	memset( &rt.rt_genmask, 0, sizeof( struct sockaddr_in ) );
	((struct sockaddr_in * )&rt.rt_genmask)->sin_family = AF_INET;	
	((struct sockaddr_in * )&rt.rt_genmask)->sin_addr.s_addr=inet_addr("");
    ((struct sockaddr_in * )&rt.rt_genmask)->sin_port = htons( 0 );	
    	
	ret=ioctl(sockid, SIOCADDRT, &rt);
	if(ret == KErrNotFound)
		{
		INFO_PRINTF1(_L("ioctl() - SIOCADDRT failed with expected error value"));
		ret = KErrNone;
		}
	else
		{
		INFO_PRINTF2(_L("ioctl() - SIOCADDRT failed: %d\n"), errno);
		ret = KErrGeneral;
		}	
	
	close(sockid);
	return ret;	
	}

/**
* Function Name		: TestMacAddress
* Description		: Gets the MAC address of the device
* Return Value		: KErrNone
*/	
TInt CTestIfioctls::TestMacAddress()
{
    int sd, ret=KErrNone;
    struct ifreq ifr;
    unsigned char *a;
	char ifrname[25];
	
	memset (&ifrname,0,sizeof(ifrname));	
	ret = GetIfrName(ifrname,  sizeof(ifrname));
	if (ret == KErrGeneral)
		{
		INFO_PRINTF1(_L("GetOpt fails"));
		return KErrGeneral;
		}
	
    if (!ifrname || ifrname[0] == '\0') 
    	{
        INFO_PRINTF1(_L("invalid ifrname"));
        return KErrGeneral;
        }
    
    memset(&ifr, 0, sizeof(ifr));
        
    sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    strncpy(&ifr.ifr_name[0], ifrname, strlen(ifrname));
    
    if (ioctl(sd, SIOCGIFHWADDR, &ifr) < 0) 
    	{
        INFO_PRINTF2(_L("ioctl() -SIOCGIFHWADDR failed: %d\n"), errno);
    	ret = KErrGeneral;
    	}
    
    a = (unsigned char *) &ifr.ifr_hwaddr.sa_data;
    INFO_PRINTF7(_L("%02x:%02x:%02x:%02x:%02x:%02x"), a[0],a[1],a[2],a[3],a[4],a[5]);
    
    return ret;	
}

//Util function
void CTestIfioctls::ReadStringParam(char* aString)
	{
	_LIT( KSl, "Param%d" );
   	TBuf<8> pNameBuf;
    TPtrC string;
    pNameBuf.Format(KSl,++iParamCount);
	TBool res = GetStringFromConfig(ConfigSection(), pNameBuf, string);
	if(!res)
	 	{
	 	_LIT(Kerr , "Unable to retrieve string parameter") ;
	 	INFO_PRINTF1(Kerr);
	  	}
	TBuf8<256> bufstring;
	bufstring.Copy(string);
	TInt paramLength=string.Length();
	char* text=(char *)(bufstring.Ptr());
 	*(text+paramLength)='\0';
	strcpy(aString,text);
	return;
	}


/**
* Function Name		: TestMacAddressNegative1
* Description		: Pass the wrong interface name for ioctl()
* Return Value		: 
*/	
TInt CTestIfioctls::TestMacAddressNegative1()
	{
	int sd, ret=KErrNone;
    struct ifreq ifr;
	char ifrname[25];
	
	ReadStringParam(ifrname);
    	
	memset(&ifr, 0, sizeof(ifr));
        
    sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    
    if(sd < 0)
    	{
    	INFO_PRINTF2(_L("socket open failed with errno: %d"), errno);
    	return KErrGeneral;
    	}

    strncpy(&ifr.ifr_name[0], ifrname, strlen(ifrname));
    
          
    if (ioctl(sd, SIOCGIFHWADDR, &ifr) < 0 && errno == ENODEV) 
       	{
        INFO_PRINTF2(_L("ioctl()-SIOCGIFHWADDR returns expected error value %d"), errno);
    	ret = KErrNone;
    	}
    else
    	{
    	INFO_PRINTF1(_L("ioctl()-SIOCGIFHWADDR fails for wrong interface name"));
    	ret = KErrGeneral;
    	}
    
    return ret;
	}

// negative test case :: tests the ioctl operation on the open file descriptor

TInt CTestIfioctls::Testioctlfile()
	{
	int fd,x,param=0,res=KErrNone;
	fd = open("c:\\test.txt",O_CREAT|O_RDONLY);
	if(fd<0)
		{
		INFO_PRINTF2(_L("file not opened because of errno :: %d"),errno);
		return KErrGeneral;
		}
	x=ioctl (fd, FIONREAD,(void *)param);

	if(x==-1)
		{
		INFO_PRINTF1(_L("ioctl operation passed on open file descriptor"));
		}
	else
		{
		INFO_PRINTF1(_L("ioctl operation failed on open file descriptor"));
		res=KErrGeneral;
		}
	close(fd);
	unlink("c:\\test.txt");
	return res;
	}


// negative test case :: tests the ioctl operation on the STDIN

TInt CTestIfioctls::Testioctl1()
	{
	int x,param=0,res=KErrNone;
	
	x=ioctl (0, FIONREAD,(void *)param);

	if(x==-1)
		{
		INFO_PRINTF1(_L("ioctl operation passed on STDIN"));
		}
	else
		{
		INFO_PRINTF1(_L("ioctl operation failed on STDIN"));
		res=KErrGeneral;
		}

    return res;
    }

TInt CTestIfioctls::GetIapName(char * aIapName, int len)
    {
    _LIT(KIAPSectionName, "SectionIAPDetails");
    _LIT(KIAPName,"IAPName");
    TPtrC iapName;
    TBool res = GetStringFromConfig(KIAPSectionName, KIAPName, iapName);
    if (!res)
        {
        INFO_PRINTF1(_L("Unable to read the iapname fro the ini file.")) ;    
        return KErrGeneral;
        }
    TPtr8 iap((unsigned char *)aIapName, len);
    iap.Copy(iapName);
    iap.ZeroTerminate();
    return KErrNone;
    }

TInt CTestIfioctls::StartIap(const char *aIapName, int &fd)
    {
    TPtr8 iapName8((TUint8 * )aIapName,strlen(aIapName),strlen(aIapName)+1);
    TBuf<IFNAMSIZ> iapName16;
    iapName16.Copy(iapName8);
    INFO_PRINTF2(_L("starting iap = %S"), &iapName16);

    if((fd = socket(AF_INET, SOCK_DGRAM , 0)) < 0)
        {
        INFO_PRINTF2(_L("Error creating scocket errno = %d\n "),errno);
        return -1;
        }

    if(ioctl(fd,SIOCSIFNAME,aIapName) == -1)
        {
        INFO_PRINTF2(_L("unable to set the interface name, reason = %d\n"), errno);
        close(fd);
        return -1;
        }

    if(ioctl(fd,SIOCIFSTART,aIapName) == -1)
        {
        INFO_PRINTF2(_L("unable to start the interface, reason = %d\n"),errno);
        close(fd);
        return -1;
        }
    return KErrNone;
    }

TInt CTestIfioctls::TestGetIfIPAddr()
    {
    char iapName[IFNAMSIZ];
    GetIapName(iapName, sizeof(iapName));
    int fd;
    ifreq ifr;


    if(StartIap(iapName, fd) != KErrNone)
        {
        INFO_PRINTF2(_L("unable to start the iap, reason = %d\n"),errno);
        return -1;
        }
    strcpy(ifr.ifr_name,iapName);
    if(ioctl(fd,SIOCGIFADDR,&ifr) == -1) //getting the interface ip
        {
        INFO_PRINTF2(_L("unable to get ip of the interface, reason = %d\n"),errno);
        close(fd);
        return -1;
        }
    char address[50];

    if(inet_ntop(ifr.ifr_ifru.ifru_addr.sa_family,&(ifr.ifr_ifru.ifru_addr.sa_data),address,sizeof(address)) == NULL)
        {
        INFO_PRINTF2(_L("cannot convert to address to string, reason = %d \n"), errno);
        close(fd);
        return -1;
        }
    TPtr8 ipAddr8((TUint8*)address,strlen(address),strlen(address)+1);
    TBuf<50> ipAddr16;
    ipAddr16.Copy(ipAddr8);
    INFO_PRINTF3(_L("family = %d, ipaddr = %S\n"),ifr.ifr_ifru.ifru_addr.sa_family,&ipAddr16);

    sockaddr_in addr;
    memcpy(&addr,&ifr.ifr_ifru.ifru_addr,sizeof(sockaddr_in));
    addr.sin_port = 12346;

    if (bind(fd,(sockaddr*)&addr,sizeof(addr)) < 0)
        {
        INFO_PRINTF2(_L("Error binding to socket, errno = %d\n"),errno);
        close(fd);
        return -1;
        }
    close(fd);
    return KErrNone;

    }

void CTestIfioctls::printFlags(TInt flags)
    {
    if(flags & IFF_UP)
        {
        INFO_PRINTF1(_L("\t\tThe inteface is up\n"));
        }
    else
        {
        INFO_PRINTF1(_L("\t\tThe inteface is down\n"));
        }
    if(flags & IFF_LOOPBACK)
        {
        INFO_PRINTF1(_L("\t\tThe inteface a loopback\n"));
        }
    if(flags & IFF_POINTOPOINT)
        {
        INFO_PRINTF1(_L("\t\tThe inteface a P2P\n"));
        }
    if(flags & IFF_BROADCAST)
        {
        INFO_PRINTF1(_L("\t\tThe inteface a Broadcast\n"));
        }
    }

TInt CTestIfioctls::TestGetIfAttributes()
    {
    char iapName[IFNAMSIZ];
    GetIapName(iapName, sizeof(iapName));
    int fd;
    ifreq ifr;


    if(StartIap(iapName, fd) != KErrNone)
        {
        INFO_PRINTF2(_L("unable to start the iap, reason = %d\n"),errno);
        return -1;
        }
    strcpy(ifr.ifr_name,iapName);

    if(ioctl(fd,SIOCGIFFLAGS,&ifr) == -1)
        {
        INFO_PRINTF2(_L("unable to get the flags for iap , reason = %d\n"),errno);
        close(fd);
        return -1;
        }

    printFlags(*((int *)ifr.ifr_ifru.ifru_flags));

    if(ioctl(fd,SIOCGIFMTU,&ifr) == -1)
        {
        INFO_PRINTF2(_L("unable to get the mtu for the iap, reason = %d"),errno);
        close(fd);
        return -1;
        }
    INFO_PRINTF2(_L("The current MTU  = %d\n"),ifr.ifr_ifru.ifru_mtu);

    if(ioctl(fd,SIOCGIFNETMASK,&ifr) == -1)
        {
        INFO_PRINTF2(_L("unable to get the netmask for the iap reason = %d\n"), errno);
        close(fd);
        return -1;
        }
    char addr[50];
    addr[0] = '\0';

    if(inet_ntop(ifr.ifr_ifru.ifru_addr.sa_family,&(ifr.ifr_ifru.ifru_addr.sa_data),addr,sizeof(addr)) == NULL)
        {
        INFO_PRINTF2(_L("cannot convert to address to string, error no = %d\n"),errno);
        close(fd);
        return -1;
        }
    TPtr8 addr8((TUint8 *)addr, strlen(addr), strlen(addr)+1);
    TBuf<50> addr16;
    addr16.Copy(addr8);
    INFO_PRINTF2(_L("netmask  for the iap = %S \n"),&addr16);

    if(ioctl(fd,SIOCGIFDEFGATEWAY,&ifr) == -1)
        {
        INFO_PRINTF2(_L("unable to get the gateway for the iap, reason = %d\n"),errno);
        close(fd);
        return -1;
        }
    addr[0] = '\0';
    if(inet_ntop(ifr.ifr_ifru.ifru_addr.sa_family,&(ifr.ifr_ifru.ifru_defgatewayaddr),addr,sizeof(addr)) == NULL)
        {
        INFO_PRINTF2(_L("cannot convert to address to string, error no = %d\n"),errno);
        close(fd);
        return -1;
        }
    addr8.Set((TUint8 *)addr, strlen(addr), strlen(addr)+1);
    addr16.Copy(addr8);
    INFO_PRINTF2(_L("gateway  for the iap = %S\n"),&addr16);
    close(fd);
    return KErrNone;
    }

TInt CTestIfioctls::TestSetIfAttributes()
    {
    char iapName[IFNAMSIZ];
    GetIapName(iapName, sizeof(iapName));
    int fd;
    ifreq ifr;


    if(StartIap(iapName, fd) != KErrNone)
        {
        INFO_PRINTF2(_L("unable to start the iap, reason = %d\n"),errno);
        return -1;
        }
    strcpy(ifr.ifr_name,iapName);


    ifreq ifr1;
    strcpy(ifr1.ifr_name,iapName);

    if(ioctl(fd,SIOCGIFMTU,&ifr) == -1)
        {
        INFO_PRINTF2(_L("unable to get the mtu for the iap, reason = %d"),errno);
        close(fd);
        return -1;
        }
    ifr.ifr_ifru.ifru_mtu++;

    if(ioctl(fd,SIOCSIFMTU,&ifr) == -1)
        {
        INFO_PRINTF2(_L("unable to set the mtu for the iap, reason = %d"),errno);
        close(fd);
        return -1;
        }

    if(ioctl(fd,SIOCGIFMTU,&ifr1) == -1)
        {
        INFO_PRINTF2(_L("unable to get the mtu for the iap , reason = %d"),errno);
        close(fd);
        return -1;
        }

    if(ifr.ifr_ifru.ifru_mtu != ifr1.ifr_ifru.ifru_mtu)
        {
        INFO_PRINTF2(_L("unable to set the mtu for the iap = %s"),ifr.ifr_name);
        close(fd);
        return -1;
        }
    close(fd);
    return KErrNone;
    }

void CTestIfioctls::FreeDnsSuffixes(char ** suffixes)
    {
    for(int i = 0; suffixes[i]; i++)
        {
        delete [] suffixes[i];
        }
    delete []suffixes;
    }

#define MAX_SUFFIXES  3
#define SUFFIXLEN   50
TInt CTestIfioctls::TestSetIfDNSSuffix()
    {
    char iapName[IFNAMSIZ];
    //    ifreq ifr1;
    GetIapName(iapName, sizeof(iapName));
    int fd;

    struct if_dns_suffixes dns_suffixes;
    strcpy(dns_suffixes.if_name,iapName);

    if(StartIap(iapName, fd) != KErrNone)
        {
        INFO_PRINTF2(_L("unable to start the iap, reason = %d\n"),errno);
        return -1;
        }

    char **&suffixes = dns_suffixes.suffixes;

    suffixes = new char*[MAX_SUFFIXES+1];
    suffixes[MAX_SUFFIXES] = NULL;

    _LIT(KDNSSuffix, "DNSSuffix");

    for(int i = 0; i < MAX_SUFFIXES; i++)
        {
        TPtrC suffix16;
        TBuf<20> suffixTag(KDNSSuffix);
        suffixTag.AppendNum(i);
        suffixes[i] = NULL;
        TBool res = GetStringFromConfig(ConfigSection(), suffixTag, suffix16);
        if (!res)
            {
            INFO_PRINTF1(_L("Unable to read the iapname from the ini file.")) ;    
            FreeDnsSuffixes(suffixes);
            close(fd);
            return KErrGeneral;
            }
        suffixes[i] = new char[suffix16.Length() + 1];
        TPtr8 suffix8((TUint8*)suffixes[i],suffix16.Length() + 1);
        suffix8.Copy(suffix16);
        suffix8.ZeroTerminate();
        }

    if(ioctl(fd,SIOCSETDNSSUFFIX,&dns_suffixes) == -1)
        {
        INFO_PRINTF2(_L("unable to set the dbs suffixes , reason = %d\n"),errno);
        close(fd);
        FreeDnsSuffixes(suffixes);
        return -1;
        }
    _LIT(KHostname1, "Hostname1");
    TPtrC hostname16;
    char hostname[50];
    TPtr8 hostname8((TUint8*)hostname, sizeof(hostname));

    TBool res = GetStringFromConfig(ConfigSection(), KHostname1, hostname16);
    if (!res)
        {
        INFO_PRINTF1(_L("Unable to read the hostname from the ini file.")) ;    
        FreeDnsSuffixes(suffixes);
        close(fd);
        return KErrGeneral;
        }
    hostname8.Copy(hostname16);
    hostname8.ZeroTerminate();
    hostent * hentry;
    ifreq defaultif;
    strcpy(defaultif.ifr_name, iapName);
    if(setdefaultif(&defaultif) != KErrNone)
        {
        INFO_PRINTF2(_L("setdefaultif failed, reason = %d "),errno) ;    
        FreeDnsSuffixes(suffixes);
        close(fd);
        return KErrGeneral;
        }

    if((hentry = gethostbyname(hostname)) == NULL)
        {
    INFO_PRINTF3(_L("getbyhostname failed for %S with errno = %d"),&hostname16,errno) ;    
       // FreeDnsSuffixes(suffixes);
       // close(fd);
     //   return KErrGeneral;

        } 
    _LIT(KHostname2, "Hostname2");

 res = GetStringFromConfig(ConfigSection(), KHostname2, hostname16);
    if (!res)
        {
        INFO_PRINTF1(_L("Unable to read the hostname from the ini file.")) ;    
        FreeDnsSuffixes(suffixes);
        close(fd);
        return KErrGeneral;
        }
    hostname8.Copy(hostname16);
    hostname8.ZeroTerminate();
    if((hentry = gethostbyname(hostname)) == NULL)
        {
    INFO_PRINTF3(_L("getbyhostname failed  for %S  with errno = %d "),&hostname16,errno) ;    
       // FreeDnsSuffixes(suffixes);
       // close(fd);
       // return KErrGeneral;

        } 

    hostname8.Copy(_L8("2IND04966"));
      hostname8.ZeroTerminate();
      if((hentry = gethostbyname(hostname)) == NULL)
          {
          INFO_PRINTF3(_L("getbyhostname failed for %s, errno  =  %d "),&hostname8, errno) ;    
          } 
    
    
    FreeDnsSuffixes(suffixes);
    close(fd);
    return KErrNone;

    }


TInt CTestIfioctls::TestGetIfDNSSuffix()
    {
    char iapName[IFNAMSIZ];
    GetIapName(iapName, sizeof(iapName));
    int fd;

    if(StartIap(iapName, fd) != KErrNone)
        {
        INFO_PRINTF2(_L("unable to start the iap, reason = %d\n"),errno);
        return -1;
        }

    struct if_dns_suffixes dns_suffixes;
    strcpy(dns_suffixes.if_name,iapName);

    if(ioctl(fd,SIOCGETDNSSUFFIX,&dns_suffixes) == -1)
        {
        INFO_PRINTF2(_L("unable to get the dns suffixes , reason = %d\n"),errno);
        close(fd);
        return -1;
        }

    INFO_PRINTF1(_L("printing dns suffixes"));
    for(int i = 0; dns_suffixes.suffixes[i]; i++)
        {
        TPtr8 suffix8((TUint8 *)dns_suffixes.suffixes[i],strlen(dns_suffixes.suffixes[i]),strlen(dns_suffixes.suffixes[i])+1);
        TBuf<SUFFIXLEN> suffix16;
        suffix16.Copy(suffix8);
        INFO_PRINTF3(_L("suffixes %d =  %S"),i,&suffix16);
        }
    freednssuffixes(&dns_suffixes);
    close(fd);
    return KErrNone;
    }

TInt CTestIfioctls::TestGetNameServers()
    {
    if_name_servers dns_server;
    char iapName[IFNAMSIZ];
    GetIapName(iapName, sizeof(iapName));
    int sockfd;
    strcpy(dns_server.if_name, iapName);

    if(StartIap(iapName, sockfd) != KErrNone)
        {
        INFO_PRINTF2(_L("unable to start the iap, reason = %d\n"),errno);
        return -1;
        }

    TInt ret = ioctl(sockfd, SIOCGNAMESERVER, &dns_server);
    if(ret == -1)
        {
        INFO_PRINTF2(_L("IOCTL option failed with errno =%d"), errno);
        close(sockfd);
        return errno;
        }
    char addr[50];
    addr[0] = '\0';

    if(inet_ntop(dns_server.nameserver1.sa_family,&(dns_server.nameserver1.sa_data),addr,sizeof(addr)) == NULL)
        {
        INFO_PRINTF2(_L("cannot convert to address to string, error no = %d\n"),errno);
        close(sockfd);
        return -1;
        }
    TPtr8 addr8((TUint8 *)addr, strlen(addr), strlen(addr)+1);
    TBuf<50> addr16;
    addr16.Copy(addr8);
    INFO_PRINTF2(_L("nameserver2  for the iap = %S \n"),&addr16);
    if(inet_ntop(dns_server.nameserver2.sa_family,&(dns_server.nameserver2.sa_data),addr,sizeof(addr)) == NULL)
        {   
        INFO_PRINTF2(_L("cannot convert to address to string, error no = %d\n"),errno);
        close(sockfd);
        return -1;
        }
    addr8.Set((TUint8 *)addr, strlen(addr), strlen(addr)+1 );
    addr16.Copy(addr8);
    INFO_PRINTF2(_L("nameserver2  for the iap = %S \n"),&addr16);
    close(sockfd);

        return KErrNone;
    }

TInt CTestIfioctls::TestSetNameServers()
    {
    if_name_servers dns_server;

    char iapName[IFNAMSIZ];
    GetIapName(iapName, sizeof(iapName));

    memset(&dns_server,0, sizeof(dns_server));
    strcpy(dns_server.if_name, iapName);
    TPtrC nameServer16;
    _LIT(KNameSrv1, "NameServer1");
    _LIT(KNameSrv2, "NameServer2");

    TBool res = GetStringFromConfig(ConfigSection(), KNameSrv1, nameServer16);
    if (!res)
        {
        INFO_PRINTF1(_L("Unable to read the nameserver1 from the ini file.")) ;    
        return KErrGeneral;
        }
    char nameServer1[50];
    TPtr8 nameServer8((TUint8 *)nameServer1, sizeof(nameServer1));
    nameServer8.Copy(nameServer16);
    nameServer8.ZeroTerminate();
    res = GetStringFromConfig(ConfigSection(), KNameSrv2, nameServer16);
    if (!res)
        {
        INFO_PRINTF1(_L("Unable to read nameserver2 from the ini file.")) ;    
        return KErrGeneral;
        }

    char nameServer2[50];
    nameServer8.Set((TUint8 *)nameServer2,  0, sizeof(nameServer2));
    nameServer8.Copy(nameServer16);
    nameServer8.ZeroTerminate();
    
    dns_server.nameserver1.sa_family = AF_INET;
    dns_server.nameserver2.sa_family = AF_INET;
    TInt addr1 = inet_addr(nameServer1);
    TInt addr2 = inet_addr(nameServer2);
    unsigned char * ptr = (unsigned char *)&addr1;
    dns_server.nameserver1.sa_data[0] = ptr[0];
    dns_server.nameserver1.sa_data[1] = ptr[1];
    dns_server.nameserver1.sa_data[2] = ptr[2];
    dns_server.nameserver1.sa_data[3] = ptr[3];
   
    ptr = (unsigned char *)&addr2;
    dns_server.nameserver2.sa_data[0] = ptr[0];
    dns_server.nameserver2.sa_data[1] = ptr[1];
    dns_server.nameserver2.sa_data[2] = ptr[2];
    dns_server.nameserver2.sa_data[3] = ptr[3];
    
    TInt sockfd;
    if(StartIap(iapName, sockfd) != KErrNone)
        {
        INFO_PRINTF2(_L("unable to start the iap, reason = %d\n"),errno);
        return -1;
        }


    TInt ret = ioctl(sockfd, SIOCSNAMESERVER, &dns_server);
    if(ret == -1)
        {
        INFO_PRINTF2(_L("IOCTL option failed with errno =%d"), errno);
        close(sockfd);
        return errno;
        }

    return KErrNone;

    }

//Testcase added to enumerate routes configured on the device.
//Use Ioctl option SIOCENUMROUTES to get the route details.
//PreCondition: User needs to allocate space for the buffer.
TInt CTestIfioctls::TestRouteIoctl()
    {
    rtconf rtc;
    TInt ret = 0;
    rtc.rt_len = 0;
    TInt sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if(sockfd < 0)
        {
        INFO_PRINTF2(_L("Unable to create the socket errno =%d"), errno);
        return -1;
        }
    if((ret = ioctl (sockfd, SIOCENUMROUTES,&rtc)) == -1)
        {
        INFO_PRINTF2(_L("Unable to get the routes configured, errno = %d"), errno);
        close(sockfd);
        return -1;
        }

    if (rtc.rt_len == 0)
        {
        INFO_PRINTF1(_L("No routes were found,"));
        close(sockfd);
        return KErrNone;
        }
    if((rtc.rtc_buf = (caddr_t)malloc( rtc.rt_len )) == NULL)
        {
        INFO_PRINTF1(_L("Unable to allocate memory "));
        close(sockfd);
        return KErrNoMemory;
        }
    
    INFO_PRINTF1(_L("Now will fetch the routes!\n"));
    if((ret = ioctl (sockfd, SIOCENUMROUTES,&rtc)) == -1)
        {
        INFO_PRINTF2(_L("Unable to get the routs configured, errno = %d"), errno);
        close(sockfd);
        free(rtc.rtc_buf);
        return -1;
        }
    close(sockfd);
    free(rtc.rtc_buf);
    return KErrNone;
    }


//With the route_entry buffer size zero, it should return the number of routes present on the system
//To use this ioctl effectively, we can find the number of routes by passing length as Zero and then
//pass the count*sizeof(route_entry) as the len the next time to fecth the route information.
TInt CTestIfioctls::TestNumberOfRoutesIoctl()
    {
    rtconf rtc;
    rtc.rt_len = 0;
    TInt ret = 0;

    TInt sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if(sockfd < 0)
        {
        INFO_PRINTF2(_L("Unable to create the socket errno =%d"), errno);
        return -1;
        }
    if((ret = ioctl (sockfd, SIOCENUMROUTES,&rtc)) == -1)
        {
        INFO_PRINTF2(_L("Unable to get the routs configures, errno = %d"), errno);
        return -1;
        }

    INFO_PRINTF2(_L("The number of routes available is %d\n"), rtc.rt_len/sizeof(route_entry));
    close(sockfd);
    return KErrNone;

    }


