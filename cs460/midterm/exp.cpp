#include <iostream>
#include <math.h>


using namespace std;

int main () {

  int a = 5, b = 3, c = 7, d = 2, e = 6;
  float x = 1.1, y = 2.2, z;

  //  z = 2 * a/b + (4.5 * c / d)-(d + e)/x * y;

  float t1 = 4.5 * c;
  float t2 = t1/d;
  int t3 = d + e;
  int t4 = 2 * a;
  int t5 = t4/b;
  float t6 = t3/x;
  float t7 = t6 * y;
  float t8 = t2 + t5;
  z = t8 - t7;
 
  cout << "value of z is: " << z << endl;

  return 0;
}
