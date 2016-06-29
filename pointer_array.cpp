#include<iostream>
#include<cstdlib>
using namespace std;
void output(int *[],int *, int);
int main(int argc,char * argv[])
{
  int m=atoi(argv[1]);
  int *p[m];
  int *q = new int [m];
  output(p,q,m);
  delete [] q;
  return 0;
}
void output(int *p[],int *q, int m)
{
  
  for(int i=0;i<m;++i)
    p[i] = &q[i];
  for(int i=0;i<m;++i)
    cout << p[i] << "  ";
  cout<<endl;
}
# C-C-
