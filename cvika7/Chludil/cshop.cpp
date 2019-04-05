//
// Created by phamducm on 4/5/19.
//

#include "cshop.h"
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

CShop::CShop() {

}

CShop::~CShop() {

}

void CShop::Buy(const string &name, int price, int  quantity) {
    map<string, vector<pair<int, int> > >::iterator it = m_Storage.find(name);

    if(m_Storage.find(name) == m_Storage.end()){
        vector<pair<int,int>> tmp;
        tmp.push_back(make_pair(price, quantity));
        m_Storage.insert(pair<string, vector<pair<int,int>>> (name, tmp));
    }else{
        vector<pair<int,int>> &tmp = it->second;
        tmp.push_back(make_pair(price, quantity));
    }
}

bool CShop::Sell(const string &, int, int &) {
    return false;
}

const list<pair<int, int> > CShop::List(const string &) const {
    list< pair<int, int>> result;
    map<string,vector<pair<int, int>>>::const_iterator it = m_Storage.find(name);

    if(it != m_Storage.end()){
        vector<pair<int,int>> tmp = it->second;
        for(vector<pair<int,int>>::iterator it2 = tmp.begin(); it2 != tmp.end(); ++it2){
            result.push_back(*it2);
        }
    }

}

