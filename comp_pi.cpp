// comp_pi.cpp -- computer pi
//                notes *
//                there is a eqution : tan(pi/4) = tan(4*alpha-beta)
//                                     tan(alpha) = 1/5, tan(beta) = 1/239
//                and because the antitangent function has following
//                Taylor seriers:
//                arctan(x) = x - x^3/3 + x^5/5 - x^7/7 + ...
//                alpha = (1/5) - (1/5)^3/3 + (1/5)^5/5 - ... and
//                beta =(1/239) - (1/239)^3/3 + (1/239)^5/5 - ...
//                in the end, we can get pi :
//                pi = 4*(4*alpha - beta)
#include <iostream>
#include <cstdlib>
#include <cmath>
int main()
{
  using namespace std;
  double r1=1.0/(5.0*5.0), r2=1.0/(239.0*239.0);// it should be 1.0/(5.0*5.0)...
  double alpha=1.0/5.0, beta=1.0/239.0, pi;     // otherwise r1 = 0;
  double er = 1e-6, er1=alpha, er2=beta, i=1.0; 
  int s=-1;
  do
    {
      er1 *= r1;
      er1 = er1*i/(i+2.0);
      alpha += s*er1;
      s=-s;
      i=i+2.0;
    } while (er1>er);
  i=1.0,s=-1;
  do 
    {
      er2 *= r2;
      er2 = er2*i/(i+2.0);
      beta += s*er2;
      s=-s;
      i=i+2.0;
    } while (er2>er);
  pi = 16.0*alpha - 4.0*beta;
  int n = 12;             // the number of digits of precision is n, which is
                          // after the decimal point.
  // set the output format
  ios_base::fmtflags orig =
    cout.setf(ios_base::fixed, ios_base::floatfield);
  std::streamsize prec = cout.precision(n);;
  cout << "pi is : " << pi << endl;
  // restore original format
  cout.setf(orig, ios_base::floatfield);
  cout.precision(prec);
  return 0;
}
# matrix
