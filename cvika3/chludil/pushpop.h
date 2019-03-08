//
// Created by phamducm on 3/8/19.
//

#ifndef CHLUDIL_PUSHPOP_H
#define CHLUDIL_PUSHPOP_H

#include <iostream>
using namespace std;
class pushpop {
public:
    pushpop();

    ~pushpop();

    bool push(int c);

    void printQueue();

private:
    struct Element {
        int hodnota;
        pushpop *t_next;
    };
    pushpop *t_first;
    pushpop *t_last;
};
#endif //CHLUDIL_PUSHPOP_H
