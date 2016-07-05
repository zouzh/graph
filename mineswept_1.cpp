// mineswept.cpp --
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "landmine.cpp"
const char mark = '*';
const char unmark = '%';
void output(char *, int, int);
void inic(linkh *,int, int);
int open(int, char *, char *, linkh *, int, int, int, int);
void assign(char *, int, int, int, int);
int quick_open(int,char*,char*,linkh*,int,int,int,int);
int opt(int,char*,char*,linkh*,int []);
/*
void output_first(linkh *, int *, int, int, int , int);
void output_max(linkh *, int *, int, int);
void output_all(linkh *, int *, int, int);
*/
int main()
{
  using namespace std;
  cout << "<<<<<-------------------------------------------------->>>>>>\n\n" ;
  cout << "                 Welcome to the mineswept\n\n";
  cout << "  Please enter the size of the game region and the number \n "
       << "        of landmines (e.g.  10 10 10):\n\n>>";
  int m,n,num;
  cin >> m >> n >> num;
  bool flag=1;
  while (flag)
    {
      if (m<6||n<6)
	{
	  cout << "\n  Error, the region is at least 6*6(6<= m,n <= 30)\n\n";
	  cout << "   Please enter another three numbers\n\n>>";
	  cin >> m >> n >> num;
	}
      else if (m>30||n>30)
	{
	  cout << "\n   Error, the region is at most 30*30(6< m,n <= 30)\n\n";
	  cout << "   Please enter another three numbers\n\n>>";
	  cin >> m >> n >> num;
	}
      else if (num>(n*m-9))
	{
	  cout << "\n   Error, There are  too many landmines(num<=n*m-9).\n\n";
	  cout << "   Please enter another three numbers\n\n>>";
	  cin >> m >> n >> num;
	}
      else
	flag=0;
    }
  flag=1;
  char * reg=new char [m*n];
  for (int i=0;i<m*n;i++)
    reg[i]=unmark;
  char ch = ' ';
  int chtemp = (3*n-8)/2;
  for (int i=2;i<chtemp;i++)
    cout << ch ;
  cout << "Now, game begin.\n\n";
  output(reg,m,n);
  srand(time(0));
  int fa = rand()%m+1;
  int fb = rand()%n+1;
  cout << "     please hit your first click (e.g.  "
       << fa << " " << fb << "):  ";
  cin >> fa >> fb;
  while (flag)
    {
      if (fa>m)
	{
	  cout << "\n   Error, the x- must be less or equal row number.\n\n";
	  cout << "   Please enter another postion "
	       << " (x <= " << m << " and y <= " << m << ")\n\n>>";
	  cin >> fa >> fb;
	}
      else if (fb>n)
	{
	  cout << "\n   Error, the y- must be less or equal column number.\n\n";
	  cout << "   Please enter another postion "
	       << " (x <= " << m << " and y <= " << m << ")\n\n>>";
	  cin >> fa >> fb;
	}
      else
	flag=0;
    }
  cout << endl;
  flag=1;
  //output(reg,m,n);
  // brr store the information of distribution of landmines.
  int N=m*n;
  char * brr=new char [N];
  linkh * crr=new linkh [N];
  int count = 0,as = 0;
  int fnl=N-num;
  inic(crr,m,n);
  transf(brr,crr,m,n,num,fa,fb);
  cout << "\n<<<<<------------------------------------------------>>>>>\n\n";
  cout << "                         some notes                       \n\n";
  cout << "   When you play the game, you must enter 3 numbers\n"
       << "every time. The first number is x-coordinate, the second\n"
       << "number is y-coordinate, and the last one is the status flag.\n"
       << "The status flag has three options:\n"
       << "0:   represent that you want to open the position. This might\n"
       << "     let you step at landmines. Be careful!\n"
       << "1:   represent that you want to (un)mark the position\n"
       << "2:   only work on the open position. This will help you sweep \n"
       << "     mines. It opens the position according to the flags that \n"
       << "     you marked. It may let you step at landmines. Be careful!\n\n"; 
  count=open(count,reg,brr,crr,m,n,fa,fb);
  cout << "Now, continue your game\n\n";
  while (count<fnl)
    {
      output(reg,m,n);
      cout << ">>";
      cin >> fa >> fb >> as;
      while (flag)
	if (fa>m||fb>n)
	  {
	    cout << "    The position must be in the game region, \n\n"
		 << "    Please enter another pair of numbers.\n\n>>";
	    cin >> fa >> fb >> as;
	  }
	else if (reg[(fa-1)*n+fb-1]<9)
	  {
	    cout << "    The position has been open, \n\n"
		 << "    Please enter another pair of numbers.\n\n>>";
	    cin >> fa >> fb >> as;
	  }
	else
	  flag=0;
      flag=1;
      while (flag)
	{
	  int sub = (fa-1)*n+fb-1;
	switch (as)
	  {
	  case 0:
	    {
	      if (reg[sub]==unmark)
		{count=open(count,reg,brr,crr,m,n,fa,fb);flag=0;}
	      else if (reg[sub]==mark)
		{
		  cout << "    This option can't work on marked position.\n\n"
		       << "    If you want to open the position, please \n\n"
		       << "    unmark the position, but it may cause you \n\n"
		       << "    to step on the landmines. Be careful.\n\n>>";
		  cin >> fa >> fb >> as;
		}
	      else
		{
		  cout << "    This option can't work on open position.\n\n"
		       << "    Please try another position. \n\n>>";
		  cin >> fa >> fb >> as;
		}
	      break;
	    }
	  case 1:
	    {
	      if (reg[sub]==mark||reg[sub]==unmark)
		{assign(reg,m,n,fa,fb);flag=0;}
	      else
		{
		  cout << "    This option can't work on open position.\n\n"
		       << "    Please try another position. \n\n>>";
		  cin >> fa >> fb >> as;
		}
	      break;
	    }
	  case 2:
	    {
	      if (reg[sub]!=unmark && reg[sub]!=mark)
		{
		  if ((int)(reg[sub]-'0')!=0)
		    {count=quick_open(count,reg,brr,crr,m,n,fa,fb);flag=0;}
		  else
		    {
		      cout << "    The place around this position has "
			   << "been all open.\n\n    "
			   << "Please try another position.\n\n>>";
		      cin >> fa >> fb >> as;
   		    }
		}
	      else
		{
		  cout << "    This option only works on open position.\n\n"
		       << "    You may try " << fa << " " << fb
		       << " 1.\n\n>>";
		  cin >> fa >> fb >> as;
		}
	      break;
	    }
	  default:
	    {
	      cout << "    There is no such status. Try again.\n\n"
		   << "    You may try " << fa << " " << fb
		   << " 1.\n\n>>";
	      cin >> fa >> fb >> as;
	      break;
	    }
	  }
	}
    }
  if (count==fnl)
    {      
      output(brr,m,n);
      cout << " Congraduations. YOU WIN the GAME.\n\n";
    }
  return 0;
}
// output the array.
void output(char *p, int a, int b)
{
  char (*crr)[b]=(char (*)[b]) p;
  using namespace std;
  cout << "        ";
  for (int i=0;i<b;i++)
    if (i<9)
      cout << i+1 << "  ";
    else
      cout << i+1 << " ";
  cout << "\n\n";
  for (int i=0;i<a;i++)
    {
      if (i<9)
	cout << "   " << i+1 << ":   ";
      else
	cout << "  " << i+1 << ":   ";
      for (int j=0;j<b;j++)
	cout << (char)crr[i][j] << "  ";
      cout << endl;
    }
  cout << endl << endl;
}
// initialize the crr array.
void inic(linkh *crr,int m, int n)
{
  int N=n*m;
  for (int i=0;i<N;i++)
    crr[i] = new hdtl(new node(i),1,i);
}
int open(int c,char*arr,char*brr,linkh*crr,int m,int n,int fa,int fb)
{
  using namespace std;
  int N=m*n;
  int sub = (fa-1)*n+fb-1;
  if (brr[sub]==mine)
    {
      output(brr,m,n);
      cout << "     Boom! You STEP on the landmines. GAME OVER.\n\n";
      c=m*n;
    }
  else if (brr[sub]=='0')
    {
      sub = up(sub,crr);
      node * head = crr[sub]->get_head();
      int ed = crr[sub]->get_num();
      for (int i=0;i<ed;i++)
	{
	  sub = head->get_ord();
	  if (arr[sub]==unmark)
	    c++;
	  arr[sub] = brr[sub];
	  head=head->get_next();
	}
    }
  else
    {
      arr[sub] = brr[sub];
      c++;
    }
  return c;
}
void assign(char *arr, int m, int n, int a, int b)
{
  using namespace std;
  int sub = (a-1)*n+b-1;
  if (arr[sub]==unmark)
    arr[sub]=mark;
  else
    arr[sub]=unmark;
}

int quick_open(int c,char*arr,char*brr,linkh*crr,int m,int n,int fa,int fb)
{
  int is=1,js=1;
  if (fa==1)       // (1*)
    is--;    
  else if (fa==m)  // (3*)
    is++;
  // else          // (2*) except middle_middle
  if (fb==1)
    js--;
  else if (fb==n)
    js++;
  // eliminate the position around the first click;
  int as=is*3+js;
  switch(as)
    {
    case 0:
      {
	int len=cor1[0]+5;
	int * mat=new int [len];
	for (int i=0;i<=cor1[0];i++) {mat[i]=cor1[i];}
	mat[len-4]=m;mat[len-3]=n;mat[len-2]=fa;mat[len-1]=fb;
	c=opt(c,arr,brr,crr,mat);
	delete mat;
	break;
      }
    case 1:
      {
	int len=matu[0]+5;
	int * mat=new int [len];
	for (int i=0;i<=matu[0];i++) {mat[i]=matu[i];}
	mat[len-4]=m;mat[len-3]=n;mat[len-2]=fa;mat[len-1]=fb;
	c=opt(c,arr,brr,crr,mat);
	delete mat;
	break;
      }
    case 2:
      {
	int len=cor2[0]+5;
	int * mat=new int [len];
	for (int i=0;i<=cor2[0];i++) {mat[i]=cor2[i];}
	mat[len-4]=m;mat[len-3]=n;mat[len-2]=fa;mat[len-1]=fb;
	c=opt(c,arr,brr,crr,mat);
	delete mat;
      }
    case 3:
      {
	int len=matl[0]+5;
	int * mat=new int [len];
	for (int i=0;i<=matl[0];i++) {mat[i]=matl[i];}
	mat[len-4]=m;mat[len-3]=n;mat[len-2]=fa;mat[len-1]=fb;
	c=opt(c,arr,brr,crr,mat);
	delete mat;
	break;
      }
    case 4:
      {
	int len=matc[0]+5;
	int * mat=new int [len];
	for (int i=0;i<=matc[0];i++) {mat[i]=matc[i];}
	mat[len-4]=m;mat[len-3]=n;mat[len-2]=fa;mat[len-1]=fb;
	c=opt(c,arr,brr,crr,mat);
	delete mat;
	break;
      }
    case 5:
      {
	int len=matr[0]+5;
	int * mat=new int [len];
	for (int i=0;i<=matr[0];i++) {mat[i]=matr[i];}
	mat[len-4]=m;mat[len-3]=n;mat[len-2]=fa;mat[len-1]=fb;
	c=opt(c,arr,brr,crr,mat);
	delete mat;
	break;
      }
    case 6:
      {
	int len=cor3[0]+5;
	int * mat=new int [len];
	for (int i=0;i<=cor3[0];i++) {mat[i]=cor3[i];}
	mat[len-4]=m;mat[len-3]=n;mat[len-2]=fa;mat[len-1]=fb;
	c=opt(c,arr,brr,crr,mat);
	delete mat;
	break;
      }
    case 7:
      {
	int len=matd[0]+5;
	int * mat=new int [len];
	for (int i=0;i<=matd[0];i++) {mat[i]=matd[i];}
	mat[len-4]=m;mat[len-3]=n;mat[len-2]=fa;mat[len-1]=fb;
	c=opt(c,arr,brr,crr,mat);
	delete mat;
	break;
      }
    case 8:
      {
	int len=cor4[0]+5;
	int * mat=new int [len];
	for (int i=0;i<=cor4[0];i++) {mat[i]=cor4[i];}
	mat[len-4]=m;mat[len-3]=n;mat[len-2]=fa;mat[len-1]=fb;
	c=opt(c,arr,brr,crr,mat);
	delete mat;
	break;
      }
    default: break;
    }
  return c;
}
int opt(int c,char*p,char*brr,linkh*crr,int mat[])
{
  using namespace std;
  int len=mat[0]+1;
  int m=mat[len], n=mat[len+1], fa=mat[len+2]-1, fb=mat[len+3]-1;
  char (*reg)[n] = (char (*)[n]) p;
  int is=fa,js=fb;
  int count = 0;
  for (int i=1;i<len;i++,i++)
    {
      is += mat[i];
      js += mat[i+1];
      if (reg[is][js]==mark)
	count ++;
    }
  if (count>(int)(reg[fa][fb]-'0'))
    cout << "    You mark WRONG position, Please check it!\n\n";
  else if (count<(int)(reg[fa][fb]-'0'))
    cout << "    There isn't enough information to determine it.\n\n"
	 << "    Please mark some more positions, and try it again.\n\n";
  else
    {
      is=fa,js=fb;
      for (int i=1;i<=len;i++,i++)
	{
	  is += mat[i];
	  js += mat[i+1];
	  if (reg[is][js]==unmark)
	    c=open(c,p,brr,crr,m,n,is+1,js+1);
	}
    }
  return c;
}
