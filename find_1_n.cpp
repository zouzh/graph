// find_1_n.cpp -- find the number x which have only one copy
// which the other ones have n copes.
#include <iostream>
#include <ctime>
#include <cstdlib>
const int MAX = 100;
int find_num(int arr[],int a,int b);
void gen(int arr[], int a,int b);
void output_arr(int arr[],int n);
int main(int argc,char* argv[])
{
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  int sz = m*n+1;
  int arr[sz];
  gen(arr,m,n);
  output_arr(arr,sz);
  int x=find_num(arr,sz,n);
  std::cout << x << std::endl;
  return 0;
}
void gen(int arr[], int a,int b)
{
  srand(time(0));
  for (int i=0;i<a;i++)
    {
      int y = rand()%MAX+1;
      for (int j=0;j<b;j++)
	{
	  int sub = i*b+j;
	  arr[sub] = y;
	}
    }
  arr[a*b] = rand()%MAX+1;
  int sz = a*b+1;
  int y,temp;
  while(sz>1)
    {
      y = rand()%sz;
      sz=sz-1;
      temp = arr[y];
      arr[y] = arr[sz];
      arr[sz] = temp;
    }
}
int find_num(int arr[],int n,int m)
{
  int b = 65;
  int bits[b];
  int y = 0;
  for (int i=0;i<b;i++)
    bits[i] = 0;
  for (int i=0;i<b;i++)
    {
      for (int j=0;j<n;j++)
	{
	  bits[i] += arr[j]%2;
	  arr[j] >>= 1;
	}
      bits[i] = bits[i]%m;
    }
  int sup = 1;
  for (int i=0;i<b;i++)
    {
      y = y + bits[i]*sup;
      sup <<= 1;
    }
  return y;
}
void output_arr(int arr[],int n)
{
  using namespace std;
  for (int i=0;i<n;i++)
    {
      cout << arr[i] << " ";
      if (i%20 == 19)
	cout << endl;
    }
  cout << endl;
}
# sort
