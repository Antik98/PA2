#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

string tolower(string retezec){ // comparison of strings
    string tmp;
    for(int i=0; i<retezec.end()-retezec.begin() ; i++){
        if(retezec[i]>='A' && retezec[i] <='Z'){
            tmp.push_back(retezec[i]- ('Z'-'z'));
        }else{
            tmp.push_back(retezec[i]);
        }
    }
    return tmp;
}


class CPozemek{ // should be used as the original template

public:
    CPozemek();
    CPozemek(const string &mesto, const string &ulice, const string &region, unsigned int id);

    string mesto;
    string ulice;
    string region;
    unsigned int id;
    void operator=(const CPozemek&);
    string majitel;
};

CPozemek::CPozemek()
        :id(0){}

CPozemek::CPozemek(const string &mesto, const string &ulice, const string &region, unsigned int id)
    : mesto(mesto),
      ulice(ulice),
      region(region),
      id(id) {}

class CIterator {
public:
    CIterator()
            : curIdx(0),
              endIdx(0) {}

    bool AtEnd(void) const{ // checks if 0 is not empty
        if(seznam.empty()){
            return (curIdx==endIdx);
        }
        return (curIdx==endIdx+1);
    }
    void Next(void){
        curIdx++;
    }
    string City(void) const{
        return seznam[curIdx]->mesto;
    }
    string Addr(void) const{
        return seznam[curIdx]->ulice;
    }
    string Region(void) const{
        return seznam[curIdx]->region;
    }
    unsigned ID(void) const{
        return seznam[curIdx]->id;
    }
    string Owner(void) const{
        return seznam[curIdx]->majitel;
    }

    vector<CPozemek*> seznam;

    unsigned long curIdx;
    unsigned long endIdx;
private:

};

class CLandRegister {
public:
    CLandRegister()
            :maxNumPozemek(1000),
             lastIdxPozemek(0),
             zeroIdxFilled(0){
        pole.resize(maxNumPozemek);
        orderPole.resize(maxNumPozemek);
    }
    ~CLandRegister(){  // TODO
        ownerPole.clear();
    }
    bool Add(const string &city,
             const string &addr,
             const string &region,
             unsigned int id);

    bool Del(const string &city,
             const string &addr);

    bool Del(const string &region,
             unsigned int id);

    bool GetOwner(const string &city,
                  const string &addr,
                  string &owner) const;

    bool GetOwner(const string &region,
                  unsigned int id,
                  string &owner) const;

    bool NewOwner(const string &city,
                  const string &addr,
                  const string &owner);

    bool NewOwner(const string &region,
                  unsigned int id,
                  const string &owner);

    unsigned Count(const string &owner) const;

    CIterator ListByAddr(void) const;

    CIterator ListByOwner(const string &owner) const;

    vector<CPozemek*> pole;
    vector<vector<CPozemek*>> ownerPole;
    vector<CPozemek*> orderPole;

    void operator=(const CLandRegister&);

    bool checkDupe(const string &city,
                   const string &addr,
                   const string &region,
                   unsigned int id) const;
private:
    bool zeroIdxFilled;
    unsigned long lastIdxPozemek;
    unsigned long maxNumPozemek;
};
bool CLandRegister::checkDupe(const string &city, const string &addr, const string &region, unsigned int id) const {
    for (int i = 0 ; i<=lastIdxPozemek; i++){
        if(pole[i]->mesto==city && pole[i]->ulice ==addr){
            return true;
        }
        if(pole[i]->region==region && pole[i]->id ==id){
            return true;
        }
    }
    return false;
}
bool CLandRegister::Add(const string &city, const string &addr, const string &region, unsigned int id) {
    if(zeroIdxFilled && checkDupe(city, addr, region, id))
        return false;

    if (lastIdxPozemek+1 >= maxNumPozemek){ // check if vector overflowing
        maxNumPozemek*=2;
        pole.resize(maxNumPozemek);
        orderPole.resize(maxNumPozemek);
    }

    if(!zeroIdxFilled){ // is first added?
        CPozemek* tmp= new CPozemek(city, addr, region, id);
        pole.insert(pole.begin(), tmp);
        orderPole[0]=tmp;
        zeroIdxFilled=true;
        return true;
    }
    CPozemek* tmp= new CPozemek(city, addr, region, id);
    for (unsigned long long int i =0 ; i<= lastIdxPozemek; i++){ // adding from the front, check on the way if a suitable spot is availible if it is... shuffle the rest to the back, if not add at the end
        if (pole[i]->mesto==city){
            if(pole[i]->ulice > addr){
                lastIdxPozemek++;
                CPozemek* tmp= new CPozemek(city, addr, region, id);
                pole.insert(pole.begin()+i, tmp);
                break;
            }
        }else if (pole[i]->mesto > city){
            lastIdxPozemek++;
            CPozemek* tmp= new CPozemek(city, addr, region, id);
            pole.insert(pole.begin()+i, tmp);
            break;
        }else{
            continue;
        }
    }
    orderPole[lastIdxPozemek]=tmp;
    return true;
}
bool CLandRegister::Del(const string &region, unsigned int id) {
    /*For each input in array of pole, find it using provided information, delete  using the same infromation from ownerPole, later delete also from orderPole*/

    for (int i = 0 ; i<=lastIdxPozemek;i++){
        if (pole[i]->region == region && pole[i]->id== id){
            if(!pole[i]->majitel.empty()){     // has an owner
                unsigned long long n=0;
                while(1){
                    if(tolower(ownerPole[n][0]->majitel)==tolower(pole[i]->majitel)){ // i already have a vector with this owner
                        for (int l =0 ; l<ownerPole[n].size(); l++){
                            if (ownerPole[n][l]->region == region && ownerPole[n][l]->id == id){
                                ownerPole[n].erase(ownerPole[n].begin()+l);
                                break;
                            }
                        }
                        break;
                    }else if(ownerPole.at(n)==ownerPole.back()){ // i dont have a vector with this owner
                        cout << "Found exception, shouldve deleted but couldnt find a owner vector" << endl;
                        break;
                    }
                    n++;
                }
                pole.erase(pole.begin()+i);
                break;
            }
        }

    }
    for (int i = 0 ; i<=lastIdxPozemek;i++){
        if (orderPole[i]->region == region && orderPole[i]->id == id){
            delete orderPole[i];
            orderPole.erase(orderPole.begin()+i);

            if(lastIdxPozemek!=0) // lastIdxPozemek goes down , has to check if deleted last one
                lastIdxPozemek--;
            else
                zeroIdxFilled=false;

            return true;
        }
    }

    return false;
}

bool CLandRegister::Del(const string &city,const string &addr) {
    for (int i = 0 ; i<=lastIdxPozemek;i++){
        if (pole[i]->mesto == city && pole[i]->ulice == addr){

            if(!pole[i]->majitel.empty()){// has an owner
                unsigned long long n=0;
                while(1){
                    if(tolower(ownerPole[n][0]->majitel)==tolower(pole[i]->majitel)){ // i already have a vector with this owner
                        for (int l =0 ; l<ownerPole[n].size(); l++){
                            if (ownerPole[n][l]->mesto == city && ownerPole[n][l]->ulice == addr){
                                ownerPole[n].erase(ownerPole[n].begin()+l);
                                break;
                            }
                        }
                        break;
                    }else if(ownerPole.at(n)==ownerPole.back()){ // i dont have a vector with this owner
                        cout << "Found exception, shouldve deleted but couldnt find a owner vector" << endl;
                        break;
                    }
                    n++;
                }
                pole.erase(pole.begin()+i);
                break;
            }
        }
    }
    for (int i = 0 ; i<=lastIdxPozemek;i++){
        if (orderPole[i]->mesto == city && orderPole[i]->ulice == addr){
            delete orderPole[i];
            orderPole.erase(orderPole.begin()+i);

            if(lastIdxPozemek!=0) // lastIdxPozemek goes down , has to check if deleted last one
                lastIdxPozemek--;
            else
                zeroIdxFilled=false;

            return true;
        }
    }

    return false;
}

bool CLandRegister::GetOwner(const string &city, const string &addr, string &owner) const {
    for (int i = 0 ; i<=lastIdxPozemek;i++){
        if (pole[i]->mesto == city && pole[i]->ulice == addr){ // found pozemek
            if(pole[i]->majitel.empty()){ // if requested is empty, owned by state, clear owner return true
                owner.clear();
                return true;
            }else {
                owner = pole[i]->majitel;
                return true;
            }
        }
    }
    return false;
}

bool CLandRegister::GetOwner(const string &region, unsigned int id, string &owner) const {
    for (int i = 0 ; i<=lastIdxPozemek;i++){
        if (pole[i]->region == region && pole[i]->id == id){
            if(pole[i]->majitel.empty()){
                owner.clear();
                return true;
            }else{
                owner = pole[i]->majitel;
                return true;
            }
        }
    }
    return false;
}

bool CLandRegister::NewOwner(const string &region, unsigned int id, const string &owner) {
    for (int i = 0;i<=lastIdxPozemek;i++){
        if (pole[i]->region == region && pole[i]->id == id){
            if(tolower(pole[i]->majitel)==tolower(owner))
                return false;

            if (!(pole[i]->majitel.empty())) {
                for(int d=0; d<ownerPole.size();d++){
                    if(tolower(ownerPole[d][0]->majitel)==tolower(pole[i]->majitel)){
                        for(int s=0;s<ownerPole[d].size();s++){
                            if(ownerPole[d][s]->region == region && ownerPole[d][s]->id == id){ // found the exact one to be renamed
                                ownerPole[d].erase(ownerPole[d].begin()+s); // if deleted leaves empty vector delete it too
                                if(ownerPole[d].empty()){
                                    ownerPole.erase(ownerPole.begin()+d);
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            
            pole[i]->majitel = owner;
            // check if i dont already have a vector for this owner
            if(!ownerPole.empty()){
                unsigned long long n=0;

                while(1){
                    if(tolower(ownerPole[n][0]->majitel)==tolower(pole[i]->majitel)){ // i already have a vector with this owner
                        ownerPole[n].push_back(pole[i]);
                        return true;
                    }

                    if(ownerPole.at(n)==ownerPole.back()){ // i dont have a vector with this owner
                        vector<CPozemek*> tmp;
                        tmp.push_back(pole[i]);
                        ownerPole.push_back(tmp);
                        return true;
                    }
                    n++;
                }
            }else{
                //i dont so i create a vector for him
                vector<CPozemek*> tmp;
                tmp.push_back(pole[i]);
                ownerPole.push_back(tmp);
                return true;
            }
        }
    }
    return false;
}

bool CLandRegister::NewOwner(const string &city, const string &addr, const string &owner) {
    for (int i = 0;i<=lastIdxPozemek;i++){
        if (pole[i]->mesto == city && pole[i]->ulice == addr){
            if(tolower(pole[i]->majitel)==tolower(owner))
                return false;
            // have to delete him from wht previous vector
            if (!(pole[i]->majitel.empty())) {
                for(int d=0; d<ownerPole.size();d++){
                    if(tolower(ownerPole[d][0]->majitel)==tolower(owner)){
                        for(int s=0;s<ownerPole[d].size();s++){
                            if(ownerPole[d][s]->mesto == city && ownerPole[d][s]->ulice == addr){
                                ownerPole[d].erase(ownerPole[d].begin()+s);
                                if(ownerPole[d].empty()){
                                    ownerPole.erase(ownerPole.begin()+d);
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            pole[i]->majitel = owner;
            // check if i dont already have a vector for this owner
            if(!ownerPole.empty()){
                unsigned long long n=0;

                while(1){
                    if(tolower(ownerPole[n][0]->majitel)==tolower(owner)){ // i already have a vector with this owner
                        ownerPole[n].push_back(pole[i]);
                        return true;
                    }

                    if(ownerPole.at(n)==ownerPole.back()){ // i dont have a vector with this owner
                        vector<CPozemek*> tmp;
                        tmp.push_back(pole[i]);
                        ownerPole.push_back(tmp);
                        return true;
                    }
                    n++;
                }
            }else{
                //i dont so i create a vector for him
                vector<CPozemek*> tmp;
                tmp.push_back(pole[i]);
                ownerPole.push_back(tmp);
                return true;
            }
        }
    }
    return false;
}

unsigned CLandRegister::Count(const string &owner) const {
    if(owner.empty()){
        if(!zeroIdxFilled){
            return 0;
        }else{
            return lastIdxPozemek+1;
        }
    }
    if(!ownerPole.empty()){
        unsigned long long n=0;
        while(1){
            if(tolower(ownerPole[n][0]->majitel)==tolower(owner)){ // i already have a vector with this owner
                return ((unsigned)ownerPole[n].size());
            }

            if(ownerPole.at(n)==ownerPole.back()){ // i dont have a vector with this owner
                return 0;
            }
            n++;
        }
    }
    return 0;
}
void CLandRegister::operator=(const CLandRegister &original) {
    lastIdxPozemek=original.lastIdxPozemek;
    zeroIdxFilled=original.zeroIdxFilled;
    for(int i =0 ; i<=lastIdxPozemek; i++){
        pole[i]=original.pole[i];
    }
}

CIterator CLandRegister::ListByAddr(void) const {
    CIterator tmp;
    tmp.endIdx=lastIdxPozemek;
    tmp.curIdx=0;
    tmp.seznam.resize(lastIdxPozemek+1);
    for (int i =0 ; i<=lastIdxPozemek;i++){
        tmp.seznam[i]=pole[i];
    }
    return tmp;
}

CIterator CLandRegister::ListByOwner(const string &owner) const {
    CIterator tmp;
    tmp.curIdx=0;

    if (owner.empty()){ // checks wheter requested owner is empty -- gives everyting
        tmp.seznam.resize(lastIdxPozemek+1);
        for(int i =0;i<=lastIdxPozemek ; i++){
            tmp.seznam[i]=orderPole[i];
        }
        tmp.endIdx=lastIdxPozemek;
        return tmp;
    }

    if(!ownerPole.empty()){ // checks if vector for owners is empty (no owners set yet)
        unsigned long long n=0;
        while(1){
            if(tolower(ownerPole[n][0]->majitel)==tolower(owner)){             // i already have a vector with this owner
                tmp.seznam.resize(ownerPole[n].size());
                tmp.endIdx=ownerPole[n].size()-1;
                tmp.seznam=ownerPole[n];                // copied the prepared vector for this
                return tmp;
            }

            if(ownerPole.at(n)==ownerPole.back()){          // i dont have a vector with this owner
                break;
            }
            n++;
        }
    }
    tmp.endIdx=0;
    return tmp;
}

#ifndef __PROGTEST__

static void test0(void) {
    CLandRegister x;
    string owner;

    assert (x.Add("Prague", "Thakurova", "Dejvice", 12345));
    assert (x.Add("Prague", "Evropska", "Vokovice", 12345));
    assert (x.Add("Prague", "Technicka", "Dejvice", 9873));
    assert (x.Add("Plzen", "Evropska", "Plzen mesto", 78901));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    CIterator i0 = x.ListByAddr();
    assert (!i0.AtEnd()
            && i0.City() == "Liberec"
            && i0.Addr() == "Evropska"
            && i0.Region() == "Librec"
            && i0.ID() == 4552
            && i0.Owner() == "");
    i0.Next();
    assert (!i0.AtEnd()
            && i0.City() == "Plzen"
            && i0.Addr() == "Evropska"
            && i0.Region() == "Plzen mesto"
            && i0.ID() == 78901
            && i0.Owner() == "");
    i0.Next();
    assert (!i0.AtEnd()
            && i0.City() == "Prague"
            && i0.Addr() == "Evropska"
            && i0.Region() == "Vokovice"
            && i0.ID() == 12345
            && i0.Owner() == "");
    i0.Next();
    assert (!i0.AtEnd()
            && i0.City() == "Prague"
            && i0.Addr() == "Technicka"
            && i0.Region() == "Dejvice"
            && i0.ID() == 9873
            && i0.Owner() == "");
    i0.Next();
    assert (!i0.AtEnd()
            && i0.City() == "Prague"
            && i0.Addr() == "Thakurova"
            && i0.Region() == "Dejvice"
            && i0.ID() == 12345
            && i0.Owner() == "");
    i0.Next();
    assert (i0.AtEnd());

    assert (x.Count("") == 5);
    CIterator i1 = x.ListByOwner("");
    assert (!i1.AtEnd()
            && i1.City() == "Prague"
            && i1.Addr() == "Thakurova"
            && i1.Region() == "Dejvice"
            && i1.ID() == 12345
            && i1.Owner() == "");
    i1.Next();
    assert (!i1.AtEnd()
            && i1.City() == "Prague"
            && i1.Addr() == "Evropska"
            && i1.Region() == "Vokovice"
            && i1.ID() == 12345
            && i1.Owner() == "");
    i1.Next();
    assert (!i1.AtEnd()
            && i1.City() == "Prague"
            && i1.Addr() == "Technicka"
            && i1.Region() == "Dejvice"
            && i1.ID() == 9873
            && i1.Owner() == "");
    i1.Next();
    assert (!i1.AtEnd()
            && i1.City() == "Plzen"
            && i1.Addr() == "Evropska"
            && i1.Region() == "Plzen mesto"
            && i1.ID() == 78901
            && i1.Owner() == "");
    i1.Next();
    assert (!i1.AtEnd()
            && i1.City() == "Liberec"
            && i1.Addr() == "Evropska"
            && i1.Region() == "Librec"
            && i1.ID() == 4552
            && i1.Owner() == "");
    i1.Next();
    assert (i1.AtEnd());

    assert (x.Count("CVUT") == 0);
    CIterator i2 = x.ListByOwner("CVUT");
    assert (i2.AtEnd());

    assert (x.NewOwner("Prague", "Thakurova", "CVUT"));
    assert (x.NewOwner("Dejvice", 9873, "CVUT"));
    assert (x.NewOwner("Plzen", "Evropska", "Anton Hrabis"));
    assert (x.NewOwner("Librec", 4552, "Cvut"));
    assert (x.GetOwner("Prague", "Thakurova", owner) && owner == "CVUT");
    assert (x.GetOwner("Dejvice", 12345, owner) && owner == "CVUT");
    assert (x.GetOwner("Prague", "Evropska", owner) && owner == "");
    assert (x.GetOwner("Vokovice", 12345, owner) && owner == "");
    assert (x.GetOwner("Prague", "Technicka", owner) && owner == "CVUT");
    assert (x.GetOwner("Dejvice", 9873, owner) && owner == "CVUT");
    assert (x.GetOwner("Plzen", "Evropska", owner) && owner == "Anton Hrabis");
    assert (x.GetOwner("Plzen mesto", 78901, owner) && owner == "Anton Hrabis");
    assert (x.GetOwner("Liberec", "Evropska", owner) && owner == "Cvut");
    assert (x.GetOwner("Librec", 4552, owner) && owner == "Cvut");
    CIterator i3 = x.ListByAddr();
    assert (!i3.AtEnd()
            && i3.City() == "Liberec"
            && i3.Addr() == "Evropska"
            && i3.Region() == "Librec"
            && i3.ID() == 4552
            && i3.Owner() == "Cvut");
    i3.Next();
    assert (!i3.AtEnd()
            && i3.City() == "Plzen"
            && i3.Addr() == "Evropska"
            && i3.Region() == "Plzen mesto"
            && i3.ID() == 78901
            && i3.Owner() == "Anton Hrabis");
    i3.Next();
    assert (!i3.AtEnd()
            && i3.City() == "Prague"
            && i3.Addr() == "Evropska"
            && i3.Region() == "Vokovice"
            && i3.ID() == 12345
            && i3.Owner() == "");
    i3.Next();
    assert (!i3.AtEnd()
            && i3.City() == "Prague"
            && i3.Addr() == "Technicka"
            && i3.Region() == "Dejvice"
            && i3.ID() == 9873
            && i3.Owner() == "CVUT");
    i3.Next();
    assert (!i3.AtEnd()
            && i3.City() == "Prague"
            && i3.Addr() == "Thakurova"
            && i3.Region() == "Dejvice"
            && i3.ID() == 12345
            && i3.Owner() == "CVUT");
    i3.Next();
    assert (i3.AtEnd());

    assert (x.Count("cvut") == 3);
    CIterator i4 = x.ListByOwner("cVuT");
    assert (!i4.AtEnd()
            && i4.City() == "Prague"
            && i4.Addr() == "Thakurova"
            && i4.Region() == "Dejvice"
            && i4.ID() == 12345
            && i4.Owner() == "CVUT");
    i4.Next();
    assert (!i4.AtEnd()
            && i4.City() == "Prague"
            && i4.Addr() == "Technicka"
            && i4.Region() == "Dejvice"
            && i4.ID() == 9873
            && i4.Owner() == "CVUT");
    i4.Next();
    assert (!i4.AtEnd()
            && i4.City() == "Liberec"
            && i4.Addr() == "Evropska"
            && i4.Region() == "Librec"
            && i4.ID() == 4552
            && i4.Owner() == "Cvut");
    i4.Next();
    assert (i4.AtEnd());

    assert (x.NewOwner("Plzen mesto", 78901, "CVut"));
    assert (x.Count("CVUT") == 4);
    CIterator i5 = x.ListByOwner("CVUT");
    assert (!i5.AtEnd()
            && i5.City() == "Prague"
            && i5.Addr() == "Thakurova"
            && i5.Region() == "Dejvice"
            && i5.ID() == 12345
            && i5.Owner() == "CVUT");
    i5.Next();
    assert (!i5.AtEnd()
            && i5.City() == "Prague"
            && i5.Addr() == "Technicka"
            && i5.Region() == "Dejvice"
            && i5.ID() == 9873
            && i5.Owner() == "CVUT");
    i5.Next();
    assert (!i5.AtEnd()
            && i5.City() == "Liberec"
            && i5.Addr() == "Evropska"
            && i5.Region() == "Librec"
            && i5.ID() == 4552
            && i5.Owner() == "Cvut");
    i5.Next();
    assert (!i5.AtEnd()
            && i5.City() == "Plzen"
            && i5.Addr() == "Evropska"
            && i5.Region() == "Plzen mesto"
            && i5.ID() == 78901
            && i5.Owner() == "CVut");
    i5.Next();
    assert (i5.AtEnd());

    assert (x.Del("Liberec", "Evropska"));
    assert (x.Del("Plzen mesto", 78901));
    assert (x.Count("cvut") == 2);
    CIterator i6 = x.ListByOwner("cVuT");
    assert (!i6.AtEnd()
            && i6.City() == "Prague"
            && i6.Addr() == "Thakurova"
            && i6.Region() == "Dejvice"
            && i6.ID() == 12345
            && i6.Owner() == "CVUT");
    i6.Next();
    assert (!i6.AtEnd()
            && i6.City() == "Prague"
            && i6.Addr() == "Technicka"
            && i6.Region() == "Dejvice"
            && i6.ID() == 9873
            && i6.Owner() == "CVUT");
    i6.Next();
    assert (i6.AtEnd());

    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
}

static void test1(void) {
    CLandRegister x;
    string owner;

    assert (x.Add("Prague", "Thakurova", "Dejvice", 12345));
    assert (x.Add("Prague", "Evropska", "Vokovice", 12345));
    assert (x.Add("Prague", "Technicka", "Dejvice", 9873));
    assert (!x.Add("Prague", "Technicka", "Hradcany", 7344));
    assert (!x.Add("Brno", "Bozetechova", "Dejvice", 9873));
    assert (!x.GetOwner("Prague", "THAKUROVA", owner));
    assert (!x.GetOwner("Hradcany", 7343, owner));
    CIterator i0 = x.ListByAddr();
    assert (!i0.AtEnd()
            && i0.City() == "Prague"
            && i0.Addr() == "Evropska"
            && i0.Region() == "Vokovice"
            && i0.ID() == 12345
            && i0.Owner() == "");
    i0.Next();
    assert (!i0.AtEnd()
            && i0.City() == "Prague"
            && i0.Addr() == "Technicka"
            && i0.Region() == "Dejvice"
            && i0.ID() == 9873
            && i0.Owner() == "");
    i0.Next();
    assert (!i0.AtEnd()
            && i0.City() == "Prague"
            && i0.Addr() == "Thakurova"
            && i0.Region() == "Dejvice"
            && i0.ID() == 12345
            && i0.Owner() == "");
    i0.Next();
    assert (i0.AtEnd());

    assert (x.NewOwner("Prague", "Thakurova", "CVUT"));
    assert (!x.NewOwner("Prague", "technicka", "CVUT"));
    assert (!x.NewOwner("prague", "Technicka", "CVUT"));
    assert (!x.NewOwner("dejvice", 9873, "CVUT"));
    assert (!x.NewOwner("Dejvice", 9973, "CVUT"));
    assert (!x.NewOwner("Dejvice", 12345, "CVUT"));
    assert (x.Count("CVUT") == 1);
    CIterator i1 = x.ListByOwner("CVUT");
    assert (!i1.AtEnd()
            && i1.City() == "Prague"
            && i1.Addr() == "Thakurova"
            && i1.Region() == "Dejvice"
            && i1.ID() == 12345
            && i1.Owner() == "CVUT");
    i1.Next();
    assert (i1.AtEnd());

    assert (!x.Del("Brno", "Technicka"));
    assert (!x.Del("Karlin", 9873));
    assert (x.Del("Prague", "Technicka"));
    assert (!x.Del("Prague", "Technicka"));
    assert (!x.Del("Dejvice", 9873));
}

int main(void) {
    test0();
    test1();
    return 0;
}

#endif /* __PROGTEST__ */