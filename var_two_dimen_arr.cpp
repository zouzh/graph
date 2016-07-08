#include<iostream>
#include<cstdlib>
void output(int *,int a, int b);
using namespace std;
int main(int argc, char* argv[])
{
  int m=atoi(argv[1]);
  int n=atoi(argv[2]);
  int * q = new int [m*n];
  output(q,m,n);
  cout<<endl;
  delete q;
  return 0;
}
void output(int *q,int m, int n)
{
  int (*p)[n]=(int (*)[n]) q;
  for(int i=0;i<m;++i)
    {
      for(int j=0;j<n;++j)
	{
	  p[i][j]=i*j;
	}
    }
  for(int i=0;i<m;++i)
    {
      for(int j=0;j<n;++j)
	cout<<p[i][j]<<' ';
    }
}
# C-C-
