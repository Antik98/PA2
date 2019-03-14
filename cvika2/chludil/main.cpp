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
    Complex temp(0);

    cout<<"A = ";
    A.print();
    cout<< "B = ";
    B.print();
    cout<< "C = ";
    C.print();
    cout<<endl;

    cout<<"Scitani"<< endl;
    temp.add(B,C);
    temp.print();
    temp.clear();

    cout<<endl;
    cout<<"Odcitani"<<endl;
    temp.sub(B,C);
    temp.print();
    temp.clear();

    cout<<endl;
    cout<<"Nasobeni"<<endl;
    temp.nasobeni(B,C);
    temp.print();
    temp.clear();

    cout<<endl;
    cout<<"Deleni"<<endl;
    temp.deleni(B,C);
    temp.print();
    temp.clear();

    cout<< endl;
    cout<< "Negace cisla B"<< endl;
    temp.negace(B);
    temp.print();
    temp.clear();

    cout<<endl;
    cout<<"Operace C+=B"<<endl;
    C.copy(&C,&temp);
    C.pluseq(B);
    C.print();
    C.copy(&temp,&C);
    temp.clear();

    cout<<endl;
    cout<<"Operace C-=B"<<endl;
    C.minuseq(B);
    C.print();
}