#include <iostream>
#include <cstdlib>
int main(int argc,char *argv[])
{
  int t_bits=32;
  int m=atoi(argv[1]);
  int n=atoi(argv[2]);
  int temp=m^n;
  int a=0;
  while (temp){
    a += temp^((temp>>1)<<1);
    temp >>= 1;
  }
  std::cout << "There are " << a << " different bits between " << m
	    << " and " << n << ". \n";
  return 0;
}
