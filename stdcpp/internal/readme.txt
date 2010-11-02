/*
Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this 
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, 
  this list of conditions and the following disclaimer in the documentation 
  and/or other materials provided with the distribution.
* Neither the name of Nokia Corporation nor the names of its contributors 
  may be used to endorse or promote products derived from this software 
  without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
This readme describes the way to run stdcpp test cases.

When running the stdcpp test cases please take care of the following:

Steps to be followed to test stdcpp module.

1. The following are manual test cases:
        a. testapps\stlport\manual\stlport_istmit- STIF based test.Prints instructions on screen. Please follow them. If nothing is printed it is considered as failed.
        b. testapps\tstdcpp\io_manual - Each test cases in independent exe. Execute separately one by one .To execute the particular exe open "Eshell" and type the exe name and enter. Prints instructions on screen. Please follow them. If nothing is printed it is considered as failed.
       c. testapps\tstdcpp\multithread\manual - One test case i.e. independent exe Execute it  independently in "Eshell"  by typing the exe name (multi_thread_manual.exe).Prints instructions on screen. Please follow them.Check for multi_thread_manual.xml file generated in \epoc32\winscw\c\LOGS\ for "PASS" or "FAIL".

2. To generate the ATS test drops for complete stdcpp\internal\testapps first build stdcpp from stdcpp\group folder then build all the testapps from stdcpp\internal\testapps\group folder . After that use the batch file "genatsmodules.bat" placed in stlport\internal\. Follow the below mentioned steps.
                1) Place attached files in stdcpp/internal folder
                2) run following command 
                        genatsmodules.bat stdcpp
                        genatsmodules.bat session stdcpp scarfe
                        genatsmodules.bat session stdcpp winsspd
                        genatsmodules.bat session stdcpp zeus

This will generate the "ATSINPUT" folder.       


3. To run the test drop in ATS copy the path till "ATSINPUT" and mention the xml filename of worker on which you want to test the testdrop.
                For example:To test on Winsspd " ..\ATSINPUT\stdcpp_winsspd_testsession.xml"