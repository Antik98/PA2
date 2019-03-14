//
// Created by phamducm on 3/8/19.
//
#include <cstdio>
#include "pushpop.h"

pushpop::pushpop() {
    t_first=NULL;
    t_last=NULL;
}
pushpop::~pushpop() {

}


bool pushpop::push(int c) {
    Element * n = new Element;
    if(!n) return false;
    n->hodnota=i;
    n->t_next=NULL;

    if (t_first == NULL){
        t_first=n;
    }else{
        t_last-> next = n;
    }
    t_last=n;
    return true;
}

void pushpop::printQueue() {
    while(){
        cout << this->hodnota << endl;
    }
}
