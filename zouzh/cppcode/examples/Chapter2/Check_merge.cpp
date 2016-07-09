//Check_merge.cpp -- First randly generate number-pairs whose range 
//are from m to n, then use the number-pairs to check and build
//network until the network is connected as a whole.
#include <iostream>
#include <ctime>
#include <cstdlib>
const int m =101, n =990;   // the range of the array 
void checkmerge(int,int);
void output_arr(int a[][2],int);
void connect_arr(int a[][2],int,int);
//using namespace std;
int main(int argc,char* argv[])
{
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  checkmerge(m,n);
}
void checkmerge(int a,int b)
{
  if (a>b)
    {
      int temp = a;
      a = b;
      b = temp;
    }
  int L = b-a+1;
  int net_arr[L][2];
  for (int i = 0; i < L; i++)
    {
      net_arr[i][0] = a+i;
      net_arr[i][1] = 1;
    }
  output_arr(net_arr,L);
  connect_arr(net_arr,L,a);
  output_arr(net_arr,L);
}
void output_arr(int arr[][2],int n)
{
  using namespace std;
  int i=0,j=0;
  while (i < n)
    {
      while (i%20!=19 && i < n)
	{
	  cout << arr[i][0] << " ";
	  i = i + 1;
	}
      if (i%20 == 19 && i < n)
	{
	  cout << arr[i][0] << " ";
	  i = i + 1;
	  cout << endl;
	}
      else 
	 {
	   cout << endl;
	 }
     
      while (j%20!=19 && j < n)
	{
	  cout << arr[j][1] << "   ";
	  j = j + 1;
	}
       if (j%20 == 19 && j < n )
	{
	  cout << arr[j][1] << "   ";
	  j = j + 1;
	  cout << endl;
	}
       else 
	 {
	   cout << endl;
	 }
    }
}
void connect_arr(int arr[][2],int n, int a)
{
  srand(time(0));
  int cnt = 1;
  while (cnt < n)
    {
      int a1 = rand()%n + a;
      int a2 = rand()%n + a;
      int temp = arr[a1-a][0]-a;
      while (arr[temp][0] != arr[a1-a][0])
	{
	  arr[temp][1] -= arr[a1-a][1];
	  arr[a1-a][0] = arr[temp][0];
	  temp = arr[temp][0]-a;
	}
      temp = arr[a2-a][0]-a;
      while (arr[temp][0] != arr[a2-a][0])
	{
	  arr[temp][1] -= arr[a2-a][1];
	  arr[a2-a][0] = arr[temp][0];
	  temp = arr[temp][0] - a;
	}
      if (arr[a1-a][0]!= arr[a2-a][0])
	{
	  cnt++;
	  int temp1 = arr[a1-a][0]-a;
	  int temp2 = arr[a2-a][0]-a;
	  if (arr[temp1][1] < arr[temp2][1])
	    {
	      arr[temp1][0] = arr[temp2][0];
	      arr[temp2][1] += arr[temp1][1];
	      
	    }
	  else  
	    {
	      arr[temp2][0] = arr[temp1][0];
	      arr[temp1][1] += arr[temp2][1];
	    }
	}
      std::cout << a1 << "  " << a2 << std::endl;
      output_arr(arr,n);
    }
}
// 
// else 
//	{ 
//	  cout << endl;
//	}
