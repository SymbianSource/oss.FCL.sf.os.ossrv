 
// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <algorithm>
#include <iostream>

#ifdef MAIN 
#define setunon0_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int setunon0_test(int, char**)
{
  int failures=0;
  cout<<"Results of setunon0_test:"<<endl;
int v1[3] = { 13, 18, 23 };
int v2[4] = { 10, 13, 17, 23 };
int result[7] = { 0, 0, 0, 0, 0, 0, 0 };

  set_union((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);
  for(int i = 0; i < 7; i++)
    cout << result[i] << ' ';
  cout << endl;
  
  if(10!=result[0])
    failures++;
  else if(13!=result[1])
    failures++;
  else if(17!=result[2])
    failures++;
  else if(18!=result[3])
    failures++;
  else if(23!=result[4])
    failures++;
  else if(0!=result[5])
    failures++;
  else if(0!=result[6])
    failures++;
       
   if(failures)
     return 1;
   else
      return 0;
}


