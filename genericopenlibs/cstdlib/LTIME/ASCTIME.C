/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* FUNCTION
* <<asctime>>---format time as string
* INDEX
* asctime
* INDEX
* _asctime_r
* ANSI_SYNOPSIS
* #include <time.h>
* char *asctime(const struct tm *<[clock]>);
* char *asctime_r(const struct tm *<[clock]>, char *<[buf]>);
* TRAD_SYNOPSIS
* #include <time.h>
* char *asctime(<[clock]>)
* struct tm *<[clock]>;
* char *asctime_r(<[clock]>)
* struct tm *<[clock]>;
* char *<[buf]>;
* Format the time value at <[clock]> into a string of the form
* . Wed Jun 15 11:38:07 1988\n\0
* The string is generated in a static buffer; each call to <<asctime>>
* overwrites the string generated by previous calls.
* RETURNS
* A pointer to the string containing a formatted timestamp.
* PORTABILITY
* ANSI C requires <<asctime>>.
* <<asctime>> requires no supporting OS subroutines.
* 
*
*/



#include <time.h>
#include <sys/reent.h>

#ifndef _REENT_ONLY

/**
Convert tm structure to string.
Converts data pointed by tim_p to a string containing time and date in readable format.
@return A pointer to the string containing the date
and time information in readable format.
The string pointed is statically allocated and 
shared by ctime and asctime functions. 
Each time one of these functions is called the content of the string is overwritten.
@param tim_p Pointer to tm structure containing time and date information to be converted.
*/
EXPORT_C char *
asctime (const struct tm *tim_p)
{
  return asctime_r (tim_p, _REENT->_asctime);
}

#endif
