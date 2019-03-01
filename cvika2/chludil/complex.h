//
// Created by phamducm on 3/1/19.
//

#include <iostream>
using namespace std;
class Complex{
public:
    Complex(double _a, double _b);
    void print();
    Complex add(Complex a, Complex b);
    Complex sub(Complex a, Complex b);
    Complex nasobeni(Complex a, Complex b);
    Complex deleni(Complex a, Complex b);
private:
    double m_re;
    double m_im;

};
Complex::Complex(double _a=0, double _b=0){
    this->m_re = _a;
    this->m_im = _b;
}
void Complex::print() {
    cout<< this-> m_re<< "+" << this->m_im << "i" <<endl;
}
Complex Complex::add(Complex a, Complex b) {
    this->m_re=a.m_re+b.m_re;
    this->m_im=a.m_im+b.m_im;
}
Complex Complex::sub(Complex a, Complex b) {
    this->m_re=a.m_re-b.m_re;
    this->m_im=a.m_im-b.m_im;
}
Complex Complex::nasobeni(Complex a, Complex b) {
    this->m_re=a.m_re*b.m_re;
    this->m_im=a.m_im*b.m_im;
}
Complex Complex::deleni(Complex a, Complex b){
    if(b.m_re ==0 || b.m_im ==0){
        cout<<"delim nulou" << endl;
    }

    this->m_re=a.m_re/b.m_re;
    this->m_im=a.m_im/b.m_im;
}