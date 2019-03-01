//
// Created by phamducm on 3/1/19.
//

#include <iostream>
#include "complex.h"


using namespace std;
int main (){
    Complex A(0);
    Complex B(1.5, 2.78);
    Complex C(1);
    B.print();
    C.print();
    cout<<endl;
    cout<<"Scitani"<< endl;
    A.add(B,C);
    A.print();
    cout<<endl;
    cout<<"Odcitani"<<endl;
    A.sub(B,C);
    A.print();
    cout<<endl;
    cout<<"Nasobeni"<<endl;
    A.nasobeni(B,C);
    A.print();
    cout<<endl;
    cout<<"Deleni"<<endl;
    A.deleni(B,C);
    A.print();
}