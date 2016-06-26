// quick.cpp -- sort the sequence with the quicksort mothed.
#include <iostream>
#include <ctime>
#include <cstdlib>
const int L =100001;    // the length of the array 
const int Max = 10000000; // the biggest number of the array
void quicksort(int arr[],int,int);
int main()
{
  using namespace std;
  cout << "The original sequence is: " << endl;
  srand(time(0));
  int rand_arr[L];
  int i;
  for ( i = 0; i < L; i++)
    {   
      rand_arr[i] = rand()%Max + 1;
      //rand_arr[i] = 1;
      cout << rand_arr[i] << "  ";
      if ((i%10) == 9)	cout << endl;
    }
  cout << endl;
  quicksort(rand_arr,0,L-1);
  cout << "\nThe sequence after sorting is: " << endl;
  for (i = 0; i < L; i++)
    {   
      cout << rand_arr[i] << "  ";
      if ((i%10) == 9)
	cout << endl;
    }
  cout << endl; 
  // cout << "\nThere have been experienced " << count 
  //     << " exchange.\n\n";
  return 0;
}

void quicksort(int arr[],int r,int s)
{
  int d = s - r;
  int temp;
  if ( d == 1)
    {
      if (arr[r] > arr[s])
	{     
	  temp = arr[r];
	  arr[r] = arr[s];
	  arr[s] = temp;
	}
    }
  else if ( d > 1)
    {
      int mid = rand()%(d+1)+r;
      temp = arr[r];
      arr[r] = arr[mid];
      arr[mid] = temp;
      int q = 1;
      int i=r+1,j;
      while ((i <= s) && (arr[i++] < arr[r]));
      j = i;
      --i;
      if (arr[i] > arr[r])
	i--;
      while (j <= s)
	{         
	  while ((j <=s) && (arr[j++] > arr[r]));
	  if (arr[--j] < arr[r])
	    {	     
	      ++i;
	      temp = arr[i];
	      arr[i] = arr[j];
	      arr[j] = temp;
	    }
	  else if ((arr[j] == arr[r]) && (q ==1))
	    {
	      ++i;
	      temp = arr[i];
	      arr[i] = arr[j];
	      arr[j] = temp;
	    }
	  q = -q;
	  ++j;
	}
      mid = i;
      temp = arr[r];
      arr[r] = arr[mid];
      // std::cout << "mid = " << mid << std::endl;
      arr[mid] = temp;
      if (i == s)
	mid = mid - 1;
      else if (i == r)
	mid = mid + 1;
      quicksort(arr,r,mid-1);
      quicksort(arr,mid+1,s);   
    }
}
