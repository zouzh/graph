// primer_num.cpp -- computer the number of primers which are less than
//                   number N.
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <ctime>
int main(int argc, char *argv[])
{
  using namespace std;
  int n = atoi(argv[1]);
  int len;
  if (n<100)
    len = n;
  else if (n<1000000)
    len = int (sqrt(n));
  else
    {
      len = int (sqrt(n));
      len = int (1.5*len/log(len));
    }
  int arr[len];
  for (int i=0; i<len;i++)
    arr[i]=0;
  if (n<2)
    cout << "There exists no primer." << endl;
  else if(n<3)
    cout << "There exists one primer." << endl;
  else if(n<5)
    cout << "There exists two primer." << endl;
  else
    {
      int count=2;
      arr[0]=2;
      arr[1]=3;
      clock_t st = clock();
      int i=5;
      for (;i<n;i=i+2)
	{
	  int flag=0;
	  int sq=int (sqrt(i+1));
	  for (int j=1;arr[j]<=sq;j++)
	    if (i%arr[j]==0)
	      {
		flag=1;
		break;
	      }
	  if (flag==0)
	    {
	      if (count < len)
		{
		  arr[count]=i;
		  count++;
		}
	      else
		{
		  i=i+2;
		  count++;
		  break;
		}
	    }
	}
      for (;i<n;i=i+2)
	{
	  int flag=0;
	  int sq=int (sqrt(i+1));
	  for (int j=1;arr[j]<=sq;j++)
	    if (i%arr[j]==0)
	      {
		flag=1;
		break;
	      }
	  if (flag==0)
	    count++;
	}
      clock_t ed = clock();
      cout << "Time is: " << (double) (ed -st) / CLOCKS_PER_SEC
	   << endl;
      cout << "There exists " << count << " primer within " << n
	   << endl;
    }
  return 0;
}

# number_theory
