#include <iostream>
#include "point.h"
#include "rectangle.h"


int main()
{
    Point p( 10, 2 );
    Rectangle r( p, 0, 0 );
    Rectangle q( Point(), 3, 10 );

    return 0;
}
