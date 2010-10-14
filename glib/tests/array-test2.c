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


#include <sys/stat.h>

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <stdio.h>
#include <glib.h>
#include <glib/gprintf.h>
#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/

static gint psort (gconstpointer a, gconstpointer b)
{
  if(**(guint32**)a == **(guint32**)b)
	  return 0;
  else
	return **(guint32**)a < **(guint32**)b ? -1 : 1;
}


static gint psort_userdata (gconstpointer a, gconstpointer b, gpointer user_data)
{
    if(**(guint32**)a == **(guint32**)b)
	   return 0;
	else
	   return **(guint32**)a < **(guint32**)b ? -1 : 1;
}

gboolean compare_pointer_array(GPtrArray *parray1, gint* array2, gint size )
{

	int i;
	int* val;
	if ( size != parray1->len)
		return FALSE;
	for ( i = 0; i < size ; i++)
	{
		val = (int*)g_ptr_array_index(parray1, i) ;
		if(val == NULL)
			return FALSE;
		if ( *val != array2[i])
			return FALSE;
	}

	return TRUE;


}
void test_pointer_array_remove_range()
{
	GPtrArray *gparray;
    const gint ARRAY_SIZE = 15;
    const gint ARRAY_SIZE_AFTER_REMOVE_RANGE = 12; /*removing 3 elements starting from index 3*/

    gint array[ARRAY_SIZE]= {99,88,77,33,44,11,66,22,0,39,1,9,100,2,73};
    gint array_after_remove_range[ARRAY_SIZE_AFTER_REMOVE_RANGE ]= {99,88,77,66,22,0,39,1,9,100,2,73};
    gboolean ret;
    int i;


	gparray = g_ptr_array_new ();
 	if(gparray == NULL)
 	{
 		g_print( "Pointer Array Not created");
 		assert_failed = 1;
 		return;
 	}

 	/*Add elements to array*/
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		g_ptr_array_add (gparray, &(array[i]));
		g_print( "Ptr Array element at index %d is %d",i, array[i]);
	}

	g_ptr_array_remove_range(gparray,3,3);

	g_print( "AFTER DELETING THE RANGE");

	/*Print the garray pointer->values*/
	for(i=0;i<gparray->len;i++)
	{
        gpointer val = g_ptr_array_index (gparray,i);	
        g_print( "Ptr Array element at index %d is %d",i,  *((int*)val));	
	}

	ret = compare_pointer_array(gparray, array_after_remove_range, ARRAY_SIZE_AFTER_REMOVE_RANGE );

    if(ret != TRUE)
    {
		g_print( "Pointer Array Elements not properly deleted by g_ptr_array_remove_range");
		assert_failed = 1;
		g_ptr_array_free(gparray,TRUE);
		return ;
	}
 	g_ptr_array_free (gparray, TRUE);
}


void sort_pointer_array()
{

	GPtrArray *gparray;
    const gint ARRAY_SIZE = 15;

    gint array[ARRAY_SIZE]= {99,88,77,33,44,11,66,22,0,39,1,9,100,2,73};
    gint sorted_array[ARRAY_SIZE]= { 0,1,2,9,11,22,33,39,44,66,73,77,88,99,100};
    int i;
    gboolean ret;

	/* Test to sort the pointer array*/
	gparray = g_ptr_array_new ();
	if(gparray == NULL)
	{
		g_print( "Pointer Array not created");
		assert_failed = 1;
		g_ptr_array_free(gparray,TRUE);
		return ;
	}

	for (i = 0; i < ARRAY_SIZE; i++)
	{
		g_ptr_array_add (gparray, &array[i]);
		g_print( "Ptr Array element at index %d is %d",i, array[i]);
	}

	g_ptr_array_sort(gparray,psort);

	/*Print the sorted Array*/
	g_print( "SORTED ARRAY");

	for(i=0;i<gparray->len;i++)
	{
        gpointer val = g_ptr_array_index (gparray,i);
        g_print( "Ptr Array element at index %d is %d",i, *((int*)val));
	}


	ret = compare_pointer_array(gparray, sorted_array, ARRAY_SIZE);
    if(ret != TRUE)
    {
		g_print( "Pointer Array Elements not sorted by g_ptr_array_sort");
		assert_failed = 1;
		g_ptr_array_free(gparray,TRUE);
		return ;
	}
	g_ptr_array_free (gparray, TRUE);
}


void sort_pointer_array_with_data()
{

	GPtrArray *gparray;
    const gint ARRAY_SIZE = 15;

    gint array[ARRAY_SIZE]= {99,88,77,33,44,11,66,22,0,39,1,9,100,2,73};
    gint sorted_array[ARRAY_SIZE]= { 0,1,2,9,11,22,33,39,44,66,73,77,88,99,100};
    int i;
    gboolean ret;

	/* Test to sort the pointer array*/
	gparray = g_ptr_array_new ();
	if(gparray == NULL)
	{
		g_print( "Pointer Array not created");
		assert_failed = 1;
		g_ptr_array_free(gparray,TRUE);
		return ;
	}

	for (i = 0; i < ARRAY_SIZE; i++)
	{
		g_ptr_array_add (gparray, &array[i]);
		
		g_print( "Ptr Array element at index %d is %d",i, array[i]);
	}

	g_ptr_array_sort_with_data(gparray,psort_userdata, NULL);


	/*Print the sorted Array*/
	g_print( "SORTED ARRAY");

	for(i=0;i<gparray->len;i++)
	{
        gpointer val = g_ptr_array_index (gparray,i);
        g_print( "Ptr Array element at index %d is %d",i, *((int*)val) );
	}


	ret = compare_pointer_array(gparray, sorted_array, ARRAY_SIZE);

    if(ret != TRUE)
    {
		g_print( "Pointer Array Elements not sorted by g_ptr_array_sort");
		assert_failed = 1;
		g_ptr_array_free(gparray,TRUE);
		return ;
	}
	g_ptr_array_free (gparray, TRUE);
}


int main (void)
{
    #ifdef __SYMBIAN32__
    g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
    g_set_print_handler(mrtPrintHandler);
    #endif /*__SYMBIAN32__*/
    
    g_print("Test array2-test Start");
    test_pointer_array_remove_range();
	sort_pointer_array();
	sort_pointer_array_with_data();

	if(assert_failed)
		g_print("Test array2-test Failed");
	else
		g_print("Test array2-test Successful");

    #if __SYMBIAN32__
    testResultXml("array2-test");
    #endif /* EMULATOR */
	return 0;
}
