#include <iostream>
#include <cstring>
#include <cstdlib>
void rebez(float arr[][2],int i,int j,int k,int l);
void output(float arr[][2],int n);
int main()
{
  float a[4]={0.0,1.0,2.0,3.0};
  float b[4]={0.0,1.0,1.0,0.0};
  int m=4,n=10;
  int pw=4;
  int L=(m-1)*pw+1;
  int cnt=0;
  float bez[L][2];
  for (int i=0;i<m;i++)
    {
      bez[cnt][0]=a[i];
      bez[cnt][1]=b[i];
      cnt +=pw;
    }
  output(bez,L);
  rebez(bez,0,L-1,m,pw);
  output(bez,L);
  return 0;
}
void rebez(float y[][2],int st,int ed,int L,int pw)
{
  while (pw>1)
    {
      int m=2*L-1;
      float fy[m][2];
      int cnt=0;
      int dnt=st;
      for (int i=0;i<L;i++)
	{
	  fy[cnt][0]=y[dnt][0];
	  fy[cnt][1]=y[dnt][1];
	  cnt += 2;
	  dnt += pw;
	}
      for (int i=1;i<L;i++)
	{
	  int cnt = i;
	  for (int j=i;j<L;j++)
	    {
	      fy[cnt][0] =(fy[cnt+1][0]+fy[cnt-1][0])/2.0;
	      fy[cnt][1] =(fy[cnt+1][1]+fy[cnt-1][1])/2.0;
	      cnt += 2;
	    }
	}
      pw >>= 1;
      int mid =(st+ed)/2;
      y[mid][0]=fy[L-1][0];
      y[mid][1]=fy[L-1][1];
      int cnt1=pw+st;
      int cnt2=pw+mid;
      for (int i=1;i<L-1;i++)
	{
	  y[cnt1][0]=fy[i][0];
	  y[cnt2][0]=fy[i+L-1][0];
	  y[cnt1][1]=fy[i][1];
	  y[cnt2][1]=fy[i+L-1][1];
	  cnt1 +=pw;
	  cnt2 +=pw;
	}
      rebez(y,st,mid,L,pw);
      rebez(y,mid,ed,L,pw);
      break;
    }
}

void output(float arr[][2],int n)
{
  using namespace std;
  for (int i=0;i<n;i++)
    {
      cout << arr[i][0] << "  ";
      if (i%10==9)
	cout << endl;
    }
  cout << endl;
  for (int i=0;i<n;i++)
    {
      cout << arr[i][1] << "  ";
      if (i%10==9)
	cout << endl;
    }
  cout << endl;
}
# curve_fitting
