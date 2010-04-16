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
           #include <iostream>
           #include <set>
           #include <vector>

           template<class T>
           inline void printElements(const T& coll, const char* msg = "")
           {
           typename T::const_iterator it;
           std::cout << msg;
           for(it = coll.begin(); it != coll.end(); ++it) {
           std::cout << *it << ' ';
           }
           std::cout << std:: endl;
           }

           int main(int /* argc */, char** /* argv */)
           {
           std::set<int> set1, set2;
           std::vector<int> aVector;

           aVector.push_back(1);
           aVector.push_back(1);

           set1.insert(aVector.begin(), aVector.end());

           set2.insert(1);
           set2.insert(1);

           printElements(aVector, "vector: ");
           printElements(set1, "set1 : ");
           printElements(set2, "set2 : ");

           return 0;
           }
# if 0
# include <iostream>
main()
{
  // std::stringstream tstr;
  std::cout<<"hello world\n";
}
# endif
