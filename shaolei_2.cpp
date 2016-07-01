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

class node
{
private:
  int * pt;
  node * next;
public:  node() {pt=0;next=0;}
  node(int * p, node * t)
  {pt=p;next=t;}
  node * add(int * p)
  {next = new node (p,0);return next;}
  ~node();
};
class hdtl
{
private:
  node * head;
  node * tail;
public: hdtl() {head=0;tail=0;}
  hdtl(node * p1, node * p2)
  {head=p1;tail=p2;}
  void joint(hdtl * h1)
  {
    (this->tail)->next = h1->head;
    this->tail = h1->tail;
    h1=this;
  }
  void seth(node * h)
  {this->head = h;}
  void setl(node * t)
  {this->tail = t;}
  ~hdtl();
};

struct node
{
  int * num;
  node * next;
};
class mylist
{
private:
  node * pnode;
public:  mylist() {pnode->num=0;pnode->next=0;}
  mylist(int * p, node * t)
  {pnode->num=p;pnode->next=t;}
  node * add(int * p)
  {pnode->next = new node (p,0);return pnode->next;}
  ~mylist();
};
class hdtl
{
private:
  node * head;
  node * tail;
public: hdtl() {head=0;tail=0;}
  hdtl(node * p1, node * p2)
  {head=p1;tail=p2;}
  void joint(hdtl * h1)
  {
    (this->tail)->next = h1->head;
    this->tail = h1->tail;
    h1=this;
  }
  void seth(node * h)
  {this->head = h;}
  void setl(node * t)
  {this->tail = t;}
  ~hdtl();
};
typedef node * linkn;
typedef hdtl * linkh;
void arrange(int *, int, int, int, int, int);
void atob(int *, int *, int, int, int);
void btoc(int *, linkh, int, int);
void output(int *, int, int);
void set(int, int, int, int, int, int [], int *,linkh);
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
	  int * arr=new int [num];  // the information of positions of landmines
	  // brr store the information of distribution of landmines.
	  int * brr=new int [(m+2)*(n+2)]; 
	  linkh crr = new hdtl [m*n];
	  int fa=rand()%m+1;
	  int fb=rand()%n+1;
	  arrange(arr,m,n,num,fa,fb);
	  atob(arr,brr,num,m+2,n+2);
	  output(brr,m+2,n+2);
	  //btoc(brr,crr,t,m,n);
	  //output(crr,m,n);
	  delete (int *)arr;
	  delete (int *)brr;
	  delete (linkh)crr;
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
  int temp,sub;
  for (int i=0;i<len;i++)
    trr[i]=i;
  for (int i=is;i<id;i++)
    for (int j=js;j<jd;j++)
      {
	len--;
	sub=i*b+j;
	temp = trr[sub];
	trr[sub] = trr[len];
	trr[len] = temp;
      }
  // begin arrange landmines
  while (n>0)
    {
      sub=rand()%len;
      len--;
      n--;
      temp = trr[sub];
      trr[sub] = trr[len];
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
void btoc(int *p, linkh crr, int m, int n)
{
  int (*brr)[n]=(int (*)[n]) p;
  // the four corners, the four edges and the center rigion
  int cor1[6]={0,1,1,0,0,-1};            // top_left
  int cor2[6]={1,0,0,-1,-1,0};           // top_right
  int cor3[6]={-1,0,0,1,1,0};            // bottom_left
  int cor4[6]={0,-1,-1,0,0,1};           // bottom_right
  int matt[10]={-1,0,0,1,1,0,1,0,0,-1};  // top
  int matb[10]={-1,0,0,-1,1,0,1,0,0,1};  // bottom
  int matl[10]={0,-1,1,0,0,1,0,1,-1,0};  // left
  int matr[10]={0,-1,-1,0,0,1,0,1,1,0};  // right
  int matc[16]={-1,1,0,-1,0,-1,1,0,1,0,0,1,0,1,-1,0};  //center
  // the four corners
  if (brr[1][1]==0)      // up_left
    set(1,1,1,n,3,cor1,brr,crr);
  if (brr[1][n]==0)      // up_right
    set(1,n,1,n,3,cor2,brr,crr);   
  if (brr[m][1]==0)      // down_left
    set(m,1,m,n,3,cor3,brr,crr);
  if (brr[m][n]==0)      // down_right
    set(m,n,m,n,3,cor4,brr,crr);
  // the four edges;
  for (int i=2;i<n;i++)  // top
    {
      if (brr[1][i]==0) 
	{
	  if (brr[1][i-1]!=0)
	    set(1,i,1,n,5,matt,brr,crr);
	  else
	    {	      
	      pt=crr[i-2]->tail;
	      pt=(pt->next=new node(&brr[1][i+1],0));
	      pt=(pt->next=new node(&brr[2][i+1],0));
	      crr[i-2]->tail=pt;
	      crr[i-1]=crr[i-2];
	    }
	}
    }
  if (brr[1][n-1]==0)
    crr[n-1]=crr[n-2];
  for (int i=2;i<m;i++)  // left
    {
      if (brr[i][1]==0)  
	{
	  if (brr[i-1][1]!=0)
	    set(i,1,i,n,5,matl,brr,crr);
	  else
	    {	      
	      pt=crr[(i-2)*n]->tail;
	      pt=(pt->next=new node(&brr[i+1][1],0));
	      pt=(pt->next=new node(&brr[i+1][2],0));
	      crr[(i-2)*n]->tail=pt;
	      crr[(i-1)*n]=crr[(i-2)*n];
	    }
	}      
    }
  if (brr[m-1][1]==0)
    crr[(m-1)*n]=crr[(m-2)*n];
  for (int i=2;i<m;i++)  // right
    {
      if (brr[i][n]==0)  
	{
	  if (brr[i-1][n]!=0)
	    set(i,n,i,n,5,matr,brr,crr);
	  else
	    {	      
	      pt=crr[(i-1)*n-1]->tail;
	      pt=(pt->next=new node(&brr[i+1][1],0));
	      pt=(pt->next=new node(&brr[i+1][2],0));
	      crr[(i-1)*n-1]->tail=pt;
	      crr[i*n-1]=crr[(i-1)*n-1];
	    }
	}      
    }
  if (brr[m-1][n]==0)
    crr[m*n-1]=crr[(m-1)*n-1];
  // the center region 
}
void set(int is,int js, int i, int n, int len, int mat[], int * brr, linkh crr)
{
  pt = new node (&brr[is][js],0);
  crr[(i-1)*n]->seth(pt);
  for (int j=0;j<len;j++,j++)
    {
      is += mat[j];
      js += mat[j+1];
      pt->add(&brr[is][js]);
    }
  crr[(i-1)*n]->setl(pt);
  delete pt;
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
