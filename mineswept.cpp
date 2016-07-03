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
  int  ord;
  node * next;
public:  node() {ord=0;next=0;}
  node(int p, node * t = 0)  {ord=p;next=t;}
  node * add(int p)
  {next = new node (p);return next;}
  int get_ord() {return ord;}
  node * get_next() {return next;}
  void set_next(node * pnode) {next=pnode;}
  ~node() {};
};
class hdtl
{
private:
  int num;
  int ord;
  node * head;
  node * tail;
public: hdtl() {head=0;tail=0;num=1;ord=0;}
  hdtl(node * p,int n1, int n2)
  {head=p;tail=p;num=n1;ord=n2;}
  hdtl(node * p1, node * p2,int n1, int n2)
  {head=p1;tail=p2;num=n1;ord=n2;}
  node * get_head() {return head;}
  node * get_tail() {return tail;}
  int get_num() {return num;}
  int get_ord() {return ord;}
  void seth(node * h)  {head = h;}
  void setl(node * t)  {tail = t;}
  void setn(int n) {num=n;}
  void seto(int o) {ord=o;}
  void add(int p) {tail=tail->add(p);num++;}
  int joint(hdtl * h1)
  {
    if (num>h1->get_num())
      {
	tail->set_next(h1->get_head());
	tail = h1->get_tail();
	num +=h1->get_num();
	h1->seto(ord);
      }
    else
      {
	node * temp=h1->get_tail();
	temp->set_next(head);
	h1->setl(tail);
	h1->setn(num+h1->get_num());
	ord=h1->get_ord();
      }
    return ord;
  }
  ~hdtl() {};
};
typedef node * linkn;
typedef hdtl * linkh;
void arrange(int *, int, int, int, int, int);
void atob(int *, int *, int, int, int);
void inic(linkh *,int, int);
void btoc(int *, linkh *, int, int);
void output(int *, int, int);
void outputc(linkh *, int, int,int);
void output_list(linkh *, int *, int, int);
// the "set" function is the most important funtion here.
void set(int, int, int, int, int [], int *, linkh *);
int up(int, linkh *);
int main(int argc, char *argv[])
{
  using namespace std;
  int m=atoi(argv[1]);
  int n=atoi(argv[2]);
  if (m<6||n<6)
    cout << "Error, the region is at least 10*10" << endl;
  else if (m>1000||n>30)
    cout << "Error, the region is at most 100*30" << endl;
  else
    {
      int num=atoi(argv[3]);
      int temp = m*n;
      if (num > temp-9)
	cout << "Error. There are too few landmines or too many landmines.\n";
      else
	{
	  srand(time(0));
	  int * arr=new int [num];  // the information of positions of landmines
	  // brr store the information of distribution of landmines.
	  int * brr=new int [m*n]; 
	  linkh * crr=new linkh [m*n];
	  int * p=new int [m*n];
	  int (*drr)[n]=(int (*)[n]) p;
	  // initialize drr.
	  for (int i=0;i<m;i++)
	    for (int j=0;j<n;j++)
	      drr[i][j]=999;
	  int fa=rand()%m+1;
	  int fb=rand()%n+1;
	  //int fa=5;
	  //int fb=5;
	  arrange(arr,m,n,num,fa,fb);
	  atob(arr,brr,num,m,n);
	  output(brr,m,n);
	  inic(crr,m,n);
	  btoc(brr,crr,m,n);
	  //outputc(crr,m,n,1);
	  output_list(crr,brr,m,n);
	  //getd(m+2,n+2,brr,crr[0].get_head());
	  //output(brr,m+2,n+2);
	  delete [] arr;
	  delete [] brr;
	  delete [] crr;
	  delete [] drr;
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
  //using namespace std;
  srand(time(0));
  int temp,sub,len=a*b;
  int * trr = new int [len];
  for (int i=0;i<len;i++)
    trr[i]=i;
  // the first click position has nine different situations:
  //    top_left       top_middle       top_right  (1*)
  // middle_left    middle_middle    middle_right  (2*)
  // bottom_left    bottom_middle    bottom_right  (3*)
  int is=fa-3, id=fa, js=fb-3, jd=fb; // middle_middle
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
  for (int i=id;i>is;i--)
    for (int j=jd;j>js;j--)
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
  int *p = new int[(m+2)*(n+2)];
  int (*trr)[n+2] = (int (*)[n+2]) p;
  for (int i=0;i<m+2;i++)
    for (int j=0;j<n+2;j++)
      trr[i][j]=0;
  int ti,tis,tid,tj,tjs,tjd;
  for (int i=0;i<num;i++)
    {
      tis=arr[i]/n;
      tjs=arr[i]%n;
      tid = tis+3;
      tjd = tjs+3;
      for (ti=tis;ti<tid;ti++)
	for (tj=tjs;tj<tjd;tj++)
	  trr[ti][tj]++;
    }
  for (int i=0;i<num;i++)
    {
      ti=arr[i]/n+1;
      tj=arr[i]%n+1;
      trr[ti][tj]=999;
    }
  for (int i=0;i<m;i++)
    for (int j=0;j<n;j++)
      brr[i][j]=trr[i+1][j+1];
  delete [] trr;
}
void inic(linkh *crr,int m, int n)
{
  int N=n*m;
  for (int i=0;i<N;i++)
    crr[i] = new hdtl(new node(i),1,i);
}
void outputc(linkh *p,int m, int n, int s)
{
  using namespace std;
  linkh (*crr)[n] =(linkh (*)[n]) p;
  for (int i=0;i<m;i++)
    {
      for (int j=0;j<n;j++)
	switch (s)
	  {
	  case 0:
	    cout << crr[i][j]->get_num() << "  ";
	    break;
	  case 1:
	    cout << crr[i][j]->get_ord() << "  ";
	    break;
	  case 2:
	    cout << crr[i][j]->get_head() << "  ";
	    break;
	  case 3:
	    cout << crr[i][j]->get_tail() << "  ";
	    break;
	  default:
	    cout << "error, the fourth parameter must be 0,1,2,3" << endl;
	  }
      cout << endl;
    }
  cout << endl;
}
void btoc(int *p, linkh *crr, int m, int n)
{
  int (*brr)[n]=(int (*)[n]) p;
  linkn pt;
  // the four corners, the four edges and the center rigion
  int cor1[7]={6,0,1,1,0,0,-1};                           // top_left
  int cor2[7]={6,1,0,0,-1,-1,0};                          // top_right
  int cor3[7]={6,-1,0,0,1,1,0};                           // bottom_left
  int cor4[7]={6,0,-1,-1,0,0,1};                          // bottom_right
  int matu[11]={10,0,-1,1,0,0,1,0,1,-1,0};                // up
  int matd[11]={10,0,-1,-1,0,0,1,0,1,1,0};                // down  
  int matl[11]={10,-1,0,0,1,1,0,1,0,0,-1};                // left
  int matr[11]={10,-1,0,0,-1,1,0,1,0,0,1};                // right 
  int matc[17]={16,-1,1,0,-1,0,-1,1,0,1,0,0,1,0,1,-1,0};  // center
  // the four corners
  set(0,0,m,n,cor1,p,crr);            // top_left
  set(0,n-1,m,n,cor2,p,crr);          // top_right
  set(m-1,0,m,n,cor3,p,crr);          // bottom_left
  set(m-1,n-1,m,n,cor4,p,crr);        // bottom_right
  for (int i=1;i<n-1;i++)             // up
    set(0,i,m,n,matu,p,crr);        
  for (int i=1;i<n-1;i++)             // down
    set(m-1,i,m,n,matd,p,crr);
  for (int i=1;i<m-1;i++)             // left
    set(i,0,m,n,matl,p,crr);
  for (int i=1;i<m-1;i++)             // right
    set(i,n-1,m,n,matr,p,crr);
  for (int i=1;i<n-1;i++)             // center
    for (int j=1;j<m-1;j++)
      set(i,j,m,n,matc,p,crr);
}
int up(int ch, linkh *crr)
{
  int fa=crr[ch]->get_ord();
  int ffa=crr[fa]->get_ord();
  while (fa!=ffa)
    {
      crr[fa]->setn(crr[fa]->get_num()-crr[ch]->get_num());
      crr[ch]->seto(ffa);
      ch=ffa;
      fa=crr[ch]->get_ord();
      ffa=crr[fa]->get_ord();
    }
  return fa;
}
void set(int is,int js, int m, int n, int mat[], int * p, linkh * crr)
{
  int (*brr)[n]=(int (*)[n]) p;
  int sub=is*n+js;
  int len=mat[0];
  if (brr[is][js]==0)
    {
      sub = up(sub,crr);
      int tsub;
      for (int k=1;k<=len;k++,k++)
	{
	  is += mat[k];
	  js += mat[k+1];
	  tsub = is*n+js;	  
	  if (brr[is][js]==0)
	    {
	      tsub = up(tsub,crr);
	      if (sub!=tsub)
		sub = (crr[sub]->joint(crr[tsub]));
	    }
	  else
	    crr[sub]->add(tsub);
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
  cout << endl;
}
void output_list(linkh * crr, int * brr, int m, int n)
{
  int N=m*n,sub;
  for (sub=0;sub<N;sub++)
    if (brr[sub]==0&&crr[sub]->get_ord()==sub)
      break;
  node * head = crr[sub]->get_head();
  int * arr = new int[N];
  for (int i=0;i<N;i++)
    arr[i]=999;
  int ed = crr[sub]->get_num();
  for (int i=0;i<ed;i++)
    {		     
      sub = head->get_ord();
      arr[sub] = brr[sub];
      head=head->get_next();
    }
  output(arr,m,n);
  delete [] arr;
}
