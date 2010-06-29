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
* Description: 
*
*/




#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <stdio.h>
#include <string.h>
#include "glib.h"

#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/


int main (int   argc,char *argv[])
{
	
	GDate *date1,*date2,*date;
	
	#ifdef __SYMBIAN32__
	g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
	#endif /*__SYMBIAN32__*/

	date = g_date_new_dmy(1,G_DATE_MAY,2003);	
	date1 = g_date_new_dmy(1,G_DATE_MAY,2006);
	date2 = g_date_new_dmy(31,G_DATE_MAY,2006);
	
	g_assert(g_date_days_between(date1,date2) == 30);
	g_assert(g_date_days_between(date2,date1) < 0);
	
	date1 = g_date_new_dmy(1,G_DATE_MAY,2006);
	
	g_assert(g_date_is_first_of_month(date1));
	g_assert(g_date_is_last_of_month(date2));
	
	g_date_order(date2,date1);
	
	g_assert(date2->day == 1 && date2->month == 5 && date2->year == 2006);
	g_assert(date1->day == 31 && date1->month == 5 && date1->year == 2006);
	
	g_date_set_month(date1,G_DATE_JULY);
	g_date_set_year(date1,2007);
	
	g_assert(date1->month == 7);
	g_assert(date1->year == 2007);
	
	g_date_clamp(date,date2,date1);
	
	g_assert(date->day == 1 && date->month == 5 && date->year == 2006);
	
	g_date_set_year(date,2008);
	
	g_date_clamp(date,date2,date1);
	
	g_assert(date->day == 31 && date->month == 7 && date->year == 2007);
	
	#if __SYMBIAN32__
  	testResultXml("date_test");
  	#endif /* EMULATOR */
	
	return 0;
}