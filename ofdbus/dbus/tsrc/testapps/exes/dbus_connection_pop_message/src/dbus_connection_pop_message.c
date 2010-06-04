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



#include<stdio.h>  

#include <dbus/dbus.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int var_arg_ret_val = -3;

#define LOG_FILE "c:\\logs\\dbus_connection_pop_message_log1.txt"
#include "std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__

void create_xml(int result)
	{
	if(result)
		assert_failed = 1;
	
	testResultXml("dbus_connection_pop_message");
    close_log_file();
	}

int handle_error(DBusError* error)
	{
	std_log(LOG_FILENAME_LINE,"%s", error->name);
	std_log(LOG_FILENAME_LINE,"%s", error->message);
	dbus_error_free(error); 
	create_xml(1);
	return 1; 
	} 

int main()
{
	DBusConnection* connection;
		DBusError error; 
		DBusMessage* msg;
		DBusMessage*pop_message;
		DBusMessage* reply = NULL;
		char error_name[40];
		char error_msg[40];
		dbus_int32_t no = 5;
		
		dbus_error_init(&error);
		
		connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
	
		if(!connection)
		{
			sprintf(error_name, "Error_name : %s", error.name);
			std_log(LOG_FILENAME_LINE, "Connection is not been established");
			sprintf(error_msg, "Error_msg : %s", error.message);
			create_xml(1);
			return 1;
		}  
		msg = dbus_message_new_method_call("Test.Method.Call1", "/Test/Method/Object", "test.Method.Call", "dbus_connection_pop_message0");
		if(msg == NULL)
			{ 
			std_log(LOG_FILENAME_LINE, "Message is NULL");
			create_xml(1);
			return 1;
			}
	
		reply = dbus_connection_send_with_reply_and_block(connection, msg, 10000, &error);
		if(!reply){
		std_log(LOG_FILENAME_LINE, "No reply");
		create_xml(1);
			return handle_error(&error);
			}
		dbus_message_get_args(reply, &error, DBUS_TYPE_INT32, &no, DBUS_TYPE_INVALID);
	
		std_log(LOG_FILENAME_LINE, "Borrowed message");
	
		pop_message =  dbus_connection_pop_message (connection )   ;
		
		std_log(LOG_FILENAME_LINE, "Pop message is been executed succesfully");
		std_log(LOG_FILENAME_LINE, "Checking for the message in the Queue");
		pop_message = dbus_connection_borrow_message (connection );
		if(pop_message == NULL)
			{
			std_log(LOG_FILENAME_LINE, "Queue is empty as the pop message is removed the message from the Queue");
			
			std_log(LOG_FILENAME_LINE, "Success");
					create_xml(0);
					dbus_message_unref(msg);
				dbus_connection_unref(connection);
			  
					   
				return 0;
		}
		else
			{
				
				std_log(LOG_FILENAME_LINE, "Test case Failed");
			
				create_xml(1);
				return 1;	
				
			}
	}