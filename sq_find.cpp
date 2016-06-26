// sq_find.cpp -- find the integer n which has the following properties:
//                There exist integer m satisfy mod(m^2,n)=n-1.
//                e.g the integer 5 has the property: mod(2^2,5)=4
//                while integer 3 doesn't have this property,because:
//                mod(0^2,3)=0 !=2 ;
//                mod(1^2,3)=1 !=2 ;
//                mod(2^2,3)=1 !=2 ;
#include <iostream>
#include <cstdlib>
int main(int argc, char *argv[])
{
  using namespace std;
  int n = atoi(argv[1]);
  cout << "The integers which have the property and are less than "
       << n << " are: " << endl;
  int count = 0;
  int temp;
  for (int i = 1; i <=n ; i++)
    {   
      for (int j = 0; j < i; j++)
	{
	  temp = j*j+1;
	  if (temp%i==0)
	    {
	      count++;
	      cout << i << "  ";
	      if (count%10 == 0)
		cout << endl;
	      break;
	    }
	}
    }
  cout << endl;
  cout << "The total number of such integers is "
       << count << endl;
  return 0;
}

# number_theory
