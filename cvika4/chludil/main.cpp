#include <iostream>
#include "Complex.h"
using namespace std;

int main ()
{
    Complex x(1,1), y(2,2), z;

    float a = 1.2;
    z = a;

    cout << z << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    z = x + y;
    cout << "x + y = " << z << endl;

    z = x - y;
    cout << "x - y = " << z << endl;
    cout << "x + 1 = " << x+1 << endl;
    cout << "2 + x = " << 2+x << endl;

    return 0;
}