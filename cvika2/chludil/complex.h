//
// Created by phamducm on 3/1/19.
//

#include <iostream>
using namespace std;
class Complex{
public:
    Complex(double _a=0, double _b=0);
    void print();
    void add(Complex a, Complex b);
    void sub(Complex a, Complex b);
    void nasobeni(Complex a, Complex b);
    void deleni(Complex a, Complex b);
    void negace(Complex a);
    void pluseq(Complex b);
    void minuseq(Complex b);
    void clear();
    void copy(Complex *a, Complex *b);
private:
    double m_re;
    double m_im;

};
Complex::Complex(double _a, double _b){
    this->m_re = _a;
    this->m_im = _b;
}
void Complex::print() {
    if(this->m_im>=0)
        cout<< this-> m_re<< "+" << this->m_im << "i" <<endl;
    else
        cout<< this-> m_re << this->m_im << "i" <<endl;
}
void Complex::add(Complex a, Complex b) {
    this->m_re=a.m_re+b.m_re;
    this->m_im=a.m_im+b.m_im;
}
void Complex::sub(Complex a, Complex b) {
    this->m_re=a.m_re-b.m_re;
    this->m_im=a.m_im-b.m_im;
}
void Complex::nasobeni(Complex a, Complex b) {
    this->m_re=a.m_re*b.m_re;
    this->m_im=a.m_im*b.m_im;
}
void Complex::deleni(Complex a, Complex b){
    if(b.m_re ==0 || b.m_im ==0){
        cout<<"delim nulou!!! pozor" << endl;
    }
    this->m_re=a.m_re/b.m_re;
    this->m_im=a.m_im/b.m_im;
}
void Complex::negace(Complex a) {
    this->m_re=(-1)*a.m_re;
    this->m_im=(-1)*a.m_im;
}
void Complex::pluseq(Complex b) {
    this->m_re=this->m_re+b.m_re;
    this->m_im=this->m_im+b.m_im;
}
void Complex::minuseq(Complex b) {
    this->m_re=this->m_re-b.m_re;
    this->m_im=this->m_im-b.m_im;
}
void Complex::clear() {
    this->m_re=0;
    this->m_im=0;
}
void Complex::copy(Complex *a, Complex *b){
    b->m_re=a->m_re;
    b->m_im=a->m_im;
}