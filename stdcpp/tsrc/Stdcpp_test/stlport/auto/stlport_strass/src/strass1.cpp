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


 
#include <string>

#ifdef __SYMBIAN32__
int strass1_test(int, char**)
#else
int main()
#endif
      {
      std::string str1 = "string";
      std::string str2;
      str2.assign(str1.begin(), str1.begin() + 3);
           
      if(str2.compare("str")!=0)
        return 1;
      else
        return 0;
      }
