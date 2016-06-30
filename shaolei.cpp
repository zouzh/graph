// shaolei.cpp -- achieve shaolei using c++
//                the region of game is at least 10*10, and at most 30*30
//                when someone begin the game, he won't step at landmine
//                and there hasn't any landmine around the first
//                click position. So we must arrange the landmine randomly
//                after the gamer click the game region. 
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
struct node    // first type of linked list
{
  // int num;
  int * num;
  node *next;
  //node * down;
  //node * right;
  //node * totail;
  //node (int n, node *d, node * r, node * t)
  //{num=n; down=d; right=r;totail=t;}
  //node (int n, node * t)
  //{num=n; next=t;}
  node (int * n,node * t)
  {num = n;next = t;}
    
};
struct dot     // second type of linked list
{
  int item;
  dot * next;
  dot (int n, dot *t)
  {item=n;next=t;}
};
struct retn     // third type of linked list
{
  node * tohead;
  retn (node *t)
  {tohead=t;}
};
typedef node *linkn;
typedef dot *linkd;
typedef retn *linkr;
void arrange(int *, int, int, int, int, int);
void atob(int *, int *, int, int, int);
void btoc(int *, linkn [], linkn, int, int);
void output(int *, int, int);
int main(int argc, char *argv[])
{
  using namespace std;
  int m=atoi(argv[1]);
  int n=atoi(argv[2]);
  if (m<10||n<10)
    cout << "Error, the region is at least 10*10" << endl;
  else if (m>100||n>30)
    cout << "Error, the region is at most 100*30" << endl;
  else
    {
      int num=atoi(argv[3]);
      int temp = m*n;
      if (num < temp*0.1 || num > temp*0.8)
	cout << "Error. There are too few landmines or too many landmines.\n";
      else
	{
	  srand(time(0));
	  int *arr=new int [num];  // the information of positions of landmines
	  // brr store the information of distribution of landmines.
	  int *brr=new int [(m+2)*(n+2)]; 
	  linkn crr[m*n];
	  linkn t;                // first type of linked list
	  int fa=rand()%m+1;
	  int fb=rand()%n+1;
	  //int fa=1,fb=n-1;
	  arrange(arr,m,n,num,fa,fb);
	  atob(arr,brr,num,m+2,n+2);
	  output(brr,m+2,n+2);
	  //btoc(brr,crr,t,m,n);
	  //output(crr,m,n);
	  delete arr;
	  delete brr;
	}
    }
  return 0;
}
// arr is information of position of landmines,
// n is the number of landmines,
// a is row number, b is the column number,
// (fa,fb) is the first click position.
void arrange(int *arr,int a, int b, int n, int fa, int fb)
{
  srand(time(0));
  // the first click position has nine different situations:
  //    top_left       top_middle       top_right  (1*)
  // middle_left    middle_middle    middle_right  (2*)
  // bottom_left    bottom_middle    bottom_right  (3*)
  int is=fa-2, id=fa+1, js=fb-2, jd=fb+1; // middle_middle
  if (fa==1)       // (1*)
    is++;    
  else if (fa==a)  // (3*)
    id--;
  // else          // (2*) except middle_middle
  if (fb==1)
    js++;
  else if (fb==b)
    jd--;
  // eliminate the position around the first click;
  int len=a*b;
  int * trr = new int [len];
  int temp,pt;
  for (int i=0;i<len;i++)
    trr[i]=i;
  for (int i=is;i<id;i++)
    for (int j=js;j<jd;j++)
      {
	len--;
	pt=i*b+j;
	temp = trr[pt];
	trr[pt] = trr[len];
	trr[len] = temp;
      }
  // begin arrange landmines
  while (n>0)
    {
      pt=rand()%len;
      len--;
      n--;
      temp = trr[pt];
      trr[pt] = trr[len];
      trr[len] = temp;
      arr[n] = temp;
    }
  delete [] trr;
}
// According to arr, computer the number of landmines
// around the given position, and store the information
// in brr.
void atob(int *arr, int *q, int num, int m, int n)
{
  int (*brr)[n]=(int (*)[n]) q;
  for (int i=0;i<m;i++)
    for (int j=0;j<n;j++)
      brr[i][j]=0;
  int bi,bis,bid,bj,bjs,bjd;
  for (int i=0;i<num;i++)
    {
      bis=arr[i]/(n-2);
      bjs=arr[i]%(n-2);
      bid = bis+3;
      bjd = bjs+3;
      for (bi=bis;bi<bid;bi++)
	for (bj=bjs;bj<bjd;bj++)
	  brr[bi][bj]++;
    }
   for (int i=0;i<num;i++)
    {
      bi=arr[i]/(n-2)+1;
      bj=arr[i]%(n-2)+1;
      brr[bi][bj]=999;
    }
}
void btoc(int *p, linkn crr[], linkn t, int m, int n)
{
  int (*brr)[n]=(int (*)[n]) p;
  int sub;
  linkn pt;
  //t = new node(-1,0);
  //t->right = t;
  //t->totail = t;
  //linkn x=t;
  // the four corners
  if (brr[1][1]==0)
    {
      crr[0]=(linkn)&brr[1][1];
      pt = new node ((linkn)&brr[1][2]);
      pt=(pt->next=new node((linkn)&brr[2][2]));
      pt=(pt->next=new node((linkn)&brr[2][1]));
      //pt=(pt->next=new node((linkn)&brr[1][1]));
      pt=(pt->next=new node(0));
    }
  if (brr[1][n]==0)
    {
      crr[n-1]=(linkn)&brr[1][n];
      pt = new node ((linkn)&brr[2][n]);
      pt=(pt->next=new node((linkn)&brr[2][n-1]));
      pt=(pt->next=new node((linkn)&brr[1][n-1]));
      //pt=(pt->next=new node((linkn)&brr[1][n]));
      pt=(pt->next=new node(0));
    }
  if (brr[m][1]==0)
    {
      crr[(m-1)*n]=(linkn)&brr[m][1];
      pt = new node ((linkn)&brr[m-1][1]);
      pt=(pt->next=new node((linkn)&brr[m-1][2]));
      pt=(pt->next=new node((linkn)&brr[m][2]));
      //pt=(pt->next=new node((linkn)&brr[m][1]));
      pt=(pt->next=new node(0));
    }
  if (brr[m][n]==0)
    {
      crr[m*n-1]=(linkn)&brr[m][n];
      pt = new node ((linkn)&brr[m][n-1]);
      pt=(pt->next=new node((linkn)&brr[m-1][n-1]));
      pt=(pt->next=new node((linkn)&brr[m-1][n]));
      //pt=(pt->next=new node((linkn)&brr[m][n]));
      pt=(pt->next=new node(0));
    }
  // the four sides
  int matt[5][2]={-1,0,0,1,1,0,1,0,0,-1};//top
  int matb[5][2]={-1,0,0,-1,1,0,1,0,0,1};//bottom
  int matl[5][2]={0,-1,1,0,0,1,0,1,-1,0};//left
  int matr[5][2]={0,-1,-1,0,0,1,0,1,1,0};//right
  for (int i=2;i<m;i++)
    {
      int is=1,js=i;
      if (brr[1][i]==0)  // top
	{
	  for (int j=0;j<5;j++)
	    {
	      is += matt[i][0];
	      js += matt[i][1];
	      if (brr[is][js]==0)
		{
		  
		  break;
		}
	    }
	}
      is=1,js=i;
      if (brr[m][i]==0)  // bottom
	{
	  for (int j=0;j<5;j++)
	    {
	    }
	}
    }
  for (int i=2;i<n;i++)
    {
      
    }
  // the center region 
  for (int i=2;i<m;i++)
    for (int j=2;j<n;j++)
      {
	sub = (i-1)*n+j-1;
	if (brr[i][j]==0)
	  {
	    
	  }
	else
	  {
	    crr[sub] = 0;
	  }
      }
}
void output(int *p, int a, int b)
{
  int (*crr)[b]=(int (*)[b]) p;
  using namespace std;
  for (int i=0;i<a;i++)
    {
      for (int j=0;j<b;j++)
	{
	  if (crr[i][j]==999)
	    cout << " " << crr[i][j];
	  else
	    cout << "   "<< crr[i][j];
	}
      cout << endl;
    }
}




# game
