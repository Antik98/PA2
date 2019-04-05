//
// Created by phamducm on 4/5/19.
//

#ifndef CHLUDIL_CSHOP_H
#define CHLUDIL_CSHOP_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <algorithm>

using namespace std;

class CShop {
public:
    CShop();
    ~CShop();
    void Buy(const string&, int, int);
    bool Sell(const string&, int, int&);
    const list< pair<int,int> > List(const string&) const ;
private:
    map<string, vector<pair<int, int> > > m_Storage;
    string name;
    int pocet;
    int cena;
};



#endif //CHLUDIL_CSHOP_H
