//
// Created by phamducm on 3/15/19.
//

#ifndef CHLUDIL_COMPLEX_H
#define CHLUDIL_COMPLEX_H

#include <iostream>
using namespace std;

class Complex {
public:
    Complex(int, int);
    ~Complex();
    int CIm;
    int CRe;
    Complex operator + (Complex l){
        return Complex(this->CRe+l.CRe,this->CIm + l.CIm);
    }
    Complex operator - (Complex l){
        return Complex(this->CRe-l.CRe,this->CIm - l.CIm);
    }
    friend ostream& operator << (ostream&os,const Complex&dc);
    Complex operator + (int d,Complex l){
        return Complex(l+l.CRe,this->CIm + l.CIm);
    }
};

Complex::Complex(int l=0, int d=0){
    this->CRe = l;
    this->CIm = d;
}
Complex::~Complex() {
}

ostream& operator <<(ostream &os, const Complex &dc) {
    os<<dc.CRe;
    os<< " + " <<dc.CIm<< "i" << endl;
    return os;
}
#endif //CHLUDIL_COMPLEX_H
