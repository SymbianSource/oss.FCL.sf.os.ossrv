/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   ?Description
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "stlport_equal.h"

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Cstlport_equal::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Cstlport_equal::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Cstlport_equal::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Cstlport_equal::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "equal0_test", Cstlport_equal::equal0_testL ),
        ENTRY( "equal1_test", Cstlport_equal::equal1_testL ),
   		ENTRY( "equal2_test", Cstlport_equal::equal2_testL ),
   		ENTRY( "equalto_test", Cstlport_equal::equalto_testL ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Cstlport_equal::equal0_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cstlport_equal::equal0_testL( CStifItemParser& /*aItem*/ )
    {

      int ret=0;
    ret = equal0_test(0, NULL);
    
     if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;

    }
    
    // -----------------------------------------------------------------------------
// Cstlport_equal::equal1_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cstlport_equal::equal1_testL( CStifItemParser& /*aItem*/ )
    {

      int ret=0;
    ret = equal1_test(0, NULL);
    
     if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;

    }


// -----------------------------------------------------------------------------
// Cstlport_equal::equal2_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cstlport_equal::equal2_testL( CStifItemParser& /*aItem*/ )
    {

      int ret=0;
    ret = equal2_test(0, NULL);
    
     if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;

    }


// -----------------------------------------------------------------------------
// Cstlport_equal::equalto_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cstlport_equal::equalto_testL( CStifItemParser& /*aItem*/ )
    {

      int ret=0;
    ret = equalto_test(0, NULL);
    
     if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;

    }


// -----------------------------------------------------------------------------
// Cstlport_equal::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Cstlport_equal::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
