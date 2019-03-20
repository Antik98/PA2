
#include <iostream>
#include "world.h"
using namespace std;


int main() {

    // Task #1
    //~~~~Well defined world
    CWorld dark( "Dark", 5 );
    std::cout << dark << std::endl;

    //~~~Operators correctly overloaded
    CWorld light( "Light", 11 );
    for( int i = 0; i < 10; ++i )
        light += {i, i, i * 2, i * 5};

    std::cout << light << std::endl;
/*
    ~~~~Copy ctor
    CWorld lightCopy( light );
    ~~~~Assignment operator
    lightCopy = lightCopy += {30, 30, 2, 1};
    std::cout << lightCopy << std::endl;

    lightCopy = dark;
    std::cout << lightCopy << std::endl;*/
    return 0;
}