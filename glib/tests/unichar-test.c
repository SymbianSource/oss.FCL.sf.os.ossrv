// Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <sys/stat.h>
#include <glib.h>
#include <errno.h>
#include <glib/gprintf.h>
#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/

int main (int argc, char *argv[])
{  
    gunichar ret;
    gunichar mark = 0x0BCA; //spacing mark. Tamil letter. 
    gunichar title = 0x01F2; //Latin letter.
    gunichar square = 0x25A1; //white square
    gunichar space = 0x200B; //zero width space
    gunichar tel_symbol = 0x32C0; //telegraphic symbol for january
    gunichar CR = 0x000D; //carriage return
    GUnicodeBreakType type;
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
    
    g_print("Test unichar-test Start");
    g_unichar_get_mirror_char('(', &ret);
    
    if(!(')' == ret))
        {
        g_print("g_unichar_get_mirror_char didnt work as expected");
        assert_failed = 1;
        }
    
    
    if(!g_unichar_ismark(mark))
        {
        g_print("g_unichar_ismark didnt work as expected");
        assert_failed = 1;
        }
    
    if(!g_unichar_istitle(title))
        {
        g_print("g_unichar_istitle didnt work as expected");
        assert_failed = 1;
        }
    
    if(!g_unichar_isdefined(square))
        {
        g_print("g_unichar_isdefined didnt work as expected");
        assert_failed = 1;
        }
    
    if(!g_unichar_iszerowidth(space))
        {
        g_print("g_unichar_iszerowidth didnt work as expected");
        assert_failed = 1;
        }
    
    if(!g_unichar_iswide(tel_symbol))
        {
        g_print("g_unichar_iswide didnt work as expected");
        assert_failed = 1;
        }
    
    if(!g_unichar_iswide_cjk(tel_symbol))
        {
        g_print("g_unichar_iswide_cjk didnt work as expected");
        assert_failed = 1;
        }
    
    ret = g_unichar_totitle('a');
    if(!(ret == 'A'))
        {
        g_print("g_unichar_totitle didnt work as expected");
        assert_failed = 1;
        }
    
    type = g_unichar_break_type(CR);
    if(type != G_UNICODE_BREAK_CARRIAGE_RETURN)
        {
        g_print("g_unichar_break_type didnt work as expected");
        assert_failed = 1;
        }
    
	if(assert_failed)
          g_print("Test unichar-test Failed");
    else
          g_print("Test unichar-test Successful");
	
    #if __SYMBIAN32__
    testResultXml("unichar-test");
    #endif /* EMULATOR */
	return 0;
}
