#include<iostream>
#include<cstdlib>
using namespace std;
int main(int argc,char * argv[])
{
  int m=atoi(argv[1]);
  int n=atoi(argv[2]);
  int (*p)[n]=(int (*)[n])new int[m*n];
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
  cout<<endl;
  delete [] (int*)p;
  return 0;
}
# C-C-
# C-C-
