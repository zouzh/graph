// mineswept.cpp -- achieve mineswept using c++
//                the region of game is at least 10*10, and at most 30*30
//                when someone begin the game, he won't step at landmine
//                and there hasn't any landmine around the first
//                click position. So we must arrange the landmine randomly
//                after the gamer click the game region. 
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "mineswept.h"
const char mine = '*';
void arrange(int *, int, int, int, int, int);
void atob(int *, char *, int, int, int);
void btoc(char *, linkh *, int, int);
// the "set" function is the most important funtion here.
void set(int, int, int, int, const int [], char *, linkh *);
int up(int, linkh *);
// the four corners, the four edges and the center rigion
const int cor1[7]={6,0,1,1,0,0,-1};                           // top_left
const int cor2[7]={6,1,0,0,-1,-1,0};                          // top_right
const int cor3[7]={6,-1,0,0,1,1,0};                           // bottom_left
const int cor4[7]={6,0,-1,-1,0,0,1};                          // bottom_right
const int matu[11]={10,0,-1,1,0,0,1,0,1,-1,0};                // up
const int matd[11]={10,0,-1,-1,0,0,1,0,1,1,0};                // down  
const int matl[11]={10,-1,0,0,1,1,0,1,0,0,-1};                // left
const int matr[11]={10,-1,0,0,-1,1,0,1,0,0,1};                // right 
const int matc[17]={16,-1,1,0,-1,0,-1,1,0,1,0,0,1,0,1,-1,0};  // center
void transf(char *brr,linkh *crr,int m,int n,int num,int fa,int fb)
{
  int * arr=new int [num];
  arrange(arr,m,n,num,fa,fb);
  atob(arr,brr,num,m,n);
  btoc(brr,crr,m,n);
  delete [] arr;
}
// arrange the landmines randomly.
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
// According to the distribution of landmines, computer
// the number of landmines around specific position.
// and store the information in brr array.
void atob(int *arr, char *q, int num, int m, int n)
{
  char (*brr)[n]=(char (*)[n]) q;
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
      trr[ti][tj]=9;
    }
  for (int i=0;i<m;i++)
    for (int j=0;j<n;j++)
      if (trr[i+1][j+1]!=9)
	brr[i][j]=(char)trr[i+1][j+1]+'0';
      else
	brr[i][j]=mine;
  delete [] trr;
}
// partition the region according to the distrution of
// the landmines. It's the most difficult part of the mineswept
// game. Because something when we click the game region,
// a large block will be open, and the shape of the block may
// be very wired. the information stores in crr array.
void btoc(char *p, linkh *crr, int m, int n)
{
  using namespace std;
  char (*brr)[n]=(char (*)[n]) p;
  linkn pt;
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
  for (int i=1;i<m-1;i++)             // center
    for (int j=1;j<n-1;j++)
      set(i,j,m,n,matc,p,crr);
}
// move the node up to the root
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
// partition the game region, it is the main function which makes
// the mineswept design work.
void set(int is,int js, int m, int n, const int mat[], char * p, linkh * crr)
{
  char (*brr)[n]=(char (*)[n]) p;
  int sub=is*n+js;
  int len=mat[0];
  if (brr[is][js]=='0')
    {
      sub = up(sub,crr);
      int tsub;
      for (int k=1;k<=len;k++,k++)
	{
	  is += mat[k];
	  js += mat[k+1];
	  tsub = is*n+js;
	  if (brr[is][js]=='0')
	    tsub=up(tsub,crr);
	  if (sub!=tsub)
	    {
	      if (brr[is][js]=='0')
		sub = (crr[sub]->joint(crr[tsub]));
	      else if (sub!=up(tsub,crr))
		{
		  crr[sub]->add(tsub);
		  crr[tsub]->seto(sub);
		}
	    }
	}
    }
}
