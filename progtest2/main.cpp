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
    string majitel;
};
struct SMestoUlice{
    string mesto;
    string ulice;
};
struct SRegionId{
    string region;
    unsigned int id;
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
            :zeroIdxFilled(0),
             lastIdxPozemek(0),
             maxNumPozemek(1000){
    }
    ~CLandRegister(){
        for(unsigned int l=0;l<ownerPole.size();l++){
            ownerPole[l].clear();
            ownerPole[l].shrink_to_fit();
        }
        ownerPole.clear();
        ownerPole.shrink_to_fit();
        pole.shrink_to_fit();
        for(unsigned long i=0;i<pole.size(); i++){
            delete pole[i];
        }
        pole.clear();
        pole.shrink_to_fit();

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
    vector<CPozemek*> pole2;
    vector<vector<CPozemek*>> ownerPole;

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

bool compareCityAddr(const CPozemek* first, const SMestoUlice& tmp ){
    if(first->mesto < tmp.mesto)
        return true;
    if(first->mesto == tmp.mesto)
        return (first->ulice < tmp.ulice);
    return false;
}
bool compareRegionId(const CPozemek* first,const SRegionId &tmp ){
    if(first->region < tmp.region)
        return true;
    if(first->region == tmp.region)
        return (first->id < tmp.id);

    return false;
}
bool compareCityAddr2(const CPozemek* first, const CPozemek* tmp ){
    if(first->mesto < tmp->mesto)
        return true;
    if(first->mesto == tmp->mesto)
        return (first->ulice < tmp->ulice);
    return false;
}
bool compareRegionId2(const CPozemek* first,const CPozemek * tmp ){
    if(first->region < tmp->region)
        return true;
    if(first->region == tmp->region)
        return (first->id < tmp->id);

    return false;
}
bool findOwner(const vector<CPozemek*> first,const string owner ){
    if(tolower(first[0]->majitel) < tolower(owner))
        return true;
    return false;
}

bool CLandRegister::checkDupe(const string &city, const string &addr, const string &region, unsigned int id) const {

    CPozemek* orig=new CPozemek();
    orig->mesto=city;
    orig->ulice=addr;

    CPozemek* orig2=new CPozemek;
    orig2->region=region;
    orig2->id=id;

    if (pole.empty()){
        return false;
    }

    bool it = binary_search(pole.begin(), pole.end(), orig, compareCityAddr2); // returns true if found
    bool it2= binary_search(pole2.begin(), pole2.end(), orig2, compareRegionId2);
    delete orig;
    delete orig2;

    if( it|| it2){
        return true;
    }

    return false;
}

bool CLandRegister::Add(const string &city, const string &addr, const string &region, unsigned int id) {
    if(city.empty()|| addr.empty() || region.empty())
        return false;

    if(zeroIdxFilled && checkDupe(city, addr, region, id))
        return false;

    if(!zeroIdxFilled){ // is first added?
        CPozemek* tmp= new CPozemek(city, addr, region, id);
        pole.push_back(tmp);
        pole2.push_back(tmp);
        vector<CPozemek*> tmpVec;
        ownerPole.push_back(tmpVec);
        ownerPole[0].push_back(tmp);
        zeroIdxFilled=true;
        return true;
    }

    CPozemek* tmp= new CPozemek(city, addr, region, id);

    auto insertTargetCityAddr = lower_bound(pole.begin(), pole.end(), tmp , compareCityAddr2);
    lastIdxPozemek++;
    pole.insert(insertTargetCityAddr, tmp);

    auto insertTargetRegionId = lower_bound(pole2.begin(), pole2.end(), tmp, compareRegionId2);
    pole2.insert(insertTargetRegionId, tmp);

    if (ownerPole.empty()){
        vector<CPozemek*> vecTmp;
        ownerPole.push_back(vecTmp);
        ownerPole[0].push_back(tmp);
    }else{
        string owner = "";

        auto findStateOwned = lower_bound(ownerPole.begin(),ownerPole.end(), owner, findOwner );

        if ((findStateOwned == ownerPole.end()) || (owner < ownerPole[findStateOwned-ownerPole.begin()][0]->majitel)){
            // nenasel jsem stat vlastnene pole... musim vytvorit
            vector<CPozemek*> vecTmp2;
            ownerPole.insert(findStateOwned, vecTmp2);
            ownerPole[findStateOwned-ownerPole.begin()].push_back(tmp);
        }else{
            ownerPole[findStateOwned-ownerPole.begin()].push_back(tmp);
        }

    }
    return true;

}
bool CLandRegister::Del(const string &region, unsigned int id) {
    /*For each input in array of pole, find it using provided information, delete  using the same infromation from ownerPole, later delete also from orderPole*/
    if(region.empty())
        return false;

    SRegionId regId;
    regId.region=region;
    regId.id=id;


    auto findTarget2 = lower_bound(pole2.begin(),pole2.end(), regId, compareRegionId);

    if ((findTarget2 == pole2.end()) || (region < pole2[findTarget2-pole2.begin()]->region)){ // if not found ret false
        return false;
    }

    if (pole2[findTarget2-pole2.begin()]->region == region && pole2[findTarget2-pole2.begin()]->id== id) {
        SMestoUlice CityAddr;
        CityAddr.mesto=pole2[findTarget2 - pole2.begin()]->mesto;
        CityAddr.ulice=pole2[findTarget2 - pole2.begin()]->ulice;
        auto findTarget = lower_bound(pole.begin(),pole.end(), CityAddr, compareCityAddr);

        // has an owner

        string owner = pole[findTarget - pole.begin()]->majitel;
        auto ownerTarget = lower_bound(ownerPole.begin(), ownerPole.end(), owner, findOwner);
        if ((ownerTarget == ownerPole.end()) || (owner < ownerPole[ownerTarget-ownerPole.begin()][0]->majitel)){
            cout << "Exception found... mel jsem najit ownera ktery mel existovat" << endl;
        }

        // has an owner
        for (unsigned long l = 0; l < ownerPole[ownerTarget-ownerPole.begin()].size(); l++) {
            if (ownerPole[ownerTarget-ownerPole.begin()][l]->region == region && ownerPole[ownerTarget-ownerPole.begin()][l]->id == id) {
                ownerPole[ownerTarget-ownerPole.begin()].erase(ownerPole[ownerTarget-ownerPole.begin()].begin() + l);
                if(ownerPole[ownerTarget-ownerPole.begin()].empty()){
                    ownerPole.erase(ownerTarget);
                }
                break;
            }
        }

        pole2.erase(findTarget2);
        delete pole[findTarget-pole.begin()];
        pole.erase(findTarget);

        if(lastIdxPozemek!=0) // lastIdxPozemek goes down , has to check if deleted last one
            lastIdxPozemek--;
        else
            zeroIdxFilled=false;
        return true;
    }
    return false;
}

bool CLandRegister::Del(const string &city,const string &addr) {
    if(city.empty()|| addr.empty() )
        return false;

    SMestoUlice CityAddr;
    CityAddr.mesto=city;
    CityAddr.ulice=addr;

    auto findTarget = lower_bound(pole.begin(),pole.end(), CityAddr, compareCityAddr);

    if ((findTarget == pole.end()) || (city < pole[findTarget-pole.begin()]->mesto)){
        return false;
    }
    if (pole[findTarget-pole.begin()]->mesto == city && pole[findTarget-pole.begin()]->ulice== addr) {
        SRegionId RegId;
        RegId.region=pole[findTarget - pole.begin()]->region;
        RegId.id=pole[findTarget - pole.begin()]->id;
        auto findTarget2 = lower_bound(pole2.begin(),pole2.end(), RegId, compareRegionId);

        string owner = pole[findTarget - pole.begin()]->majitel;
        auto ownerTarget = lower_bound(ownerPole.begin(), ownerPole.end(), owner, findOwner);
        if ((ownerTarget == ownerPole.end()) || (owner < ownerPole[ownerTarget-ownerPole.begin()][0]->majitel)){
            cout << "Exception found... mel jsem najit ownera ktery mel existovat" << endl;
        }

        // has an owner
        for (unsigned long l = 0; l < ownerPole[ownerTarget-ownerPole.begin()].size(); l++) {
            if (ownerPole[ownerTarget-ownerPole.begin()][l]->mesto == city && ownerPole[ownerTarget-ownerPole.begin()][l]->ulice == addr) {
                ownerPole[ownerTarget-ownerPole.begin()].erase(ownerPole[ownerTarget-ownerPole.begin()].begin() + l);
                if(ownerPole[ownerTarget-ownerPole.begin()].empty()){
                    ownerPole.erase(ownerTarget);
                }
                break;
            }
        }
        pole2.erase(findTarget2);
        delete pole[findTarget-pole.begin()];
        pole.erase(findTarget);
        if(lastIdxPozemek!=0) // lastIdxPozemek goes down , has to check if deleted last one
            lastIdxPozemek--;
        else
            zeroIdxFilled=false;

        return true;
    }
    return false;
}

bool CLandRegister::GetOwner(const string &city, const string &addr, string &owner) const {
    if(city.empty()|| addr.empty())
        return false;

    SMestoUlice tmp;
    tmp.mesto=city;
    tmp.ulice=addr;

    auto it = lower_bound(pole.begin(), pole.end(), tmp, compareCityAddr);
    if ((it == pole.end()) || (city < pole[it-pole.begin()]->mesto)){
        return false;
    }
    if(pole[it-pole.begin()]->mesto==city && pole[it-pole.begin()]->ulice == addr){
        if(pole[it-pole.begin()]->majitel.empty()){
            owner.clear();
            return true;
        }else {
            owner=pole[it-pole.begin()]->majitel;
            return true;
        }
    }
    return false;
}

bool CLandRegister::GetOwner(const string &region, unsigned int id, string &owner) const {
    if(region.empty())
        return false;

    SRegionId tmp;
    tmp.region=region;
    tmp.id=id;

    auto it = lower_bound(pole2.begin(), pole2.end(), tmp, compareRegionId);
    if ((it == pole2.end()) || (region < pole2[it-pole2.begin()]->region)){
        return false;
    }
    if(pole2[it-pole2.begin()]->region == region && pole2[it-pole2.begin()]->id==id){
        if(pole2[it-pole2.begin()]->majitel.empty()){
            owner.clear();
            return true;
        }else {
            owner=pole2[it-pole2.begin()]->majitel;
            return true;
        }
    }
    return false;
}

bool CLandRegister::NewOwner(const string &region, unsigned int id, const string &owner) { // TODO
    if(region.empty())
        return false;
    string prevOwner;
    SRegionId RegId;
    RegId.region=region;
    RegId.id=id;

    auto targetRegId = lower_bound(pole2.begin(), pole2.end(), RegId, compareRegionId); // have to check, if we found nothing return false
    if ((targetRegId == pole2.end()) || (region < pole2[targetRegId-pole2.begin()]->region)){ // didnt find one, create one and pushback
        return false;
    }


    prevOwner =pole2[targetRegId-pole2.begin()]->majitel;
    if (tolower(owner) == tolower(prevOwner) ){ // already the owner
        return false;
    }

    auto targetPrevOwner = lower_bound(ownerPole.begin(), ownerPole.end(), prevOwner, findOwner);
    if ((targetPrevOwner == ownerPole.end()) || (tolower(prevOwner) < tolower(ownerPole[targetPrevOwner-ownerPole.begin()][0]->majitel))){ // didnt find one, create one and pushback
        cout << "nenaslo se co se melo" << endl;
        return false;
    }else{ // found the vector of the old owner.. find exact , delete
        for(long unsigned int i = 0; i<ownerPole[targetPrevOwner-ownerPole.begin()].size() ; i++){
            if(ownerPole[targetPrevOwner-ownerPole.begin()][i]->region==region && ownerPole[targetPrevOwner-ownerPole.begin()][i]->id==id) {// got the old owner, delete, if vector empty delete it too
                ownerPole[targetPrevOwner-ownerPole.begin()].erase(ownerPole[targetPrevOwner-ownerPole.begin()].begin() + i);
                if(ownerPole[targetPrevOwner-ownerPole.begin()].empty()){
                    ownerPole.erase(targetPrevOwner);
                }
                break;
            }
        }
    }
    pole2[targetRegId-pole2.begin()]->majitel=owner;
    CPozemek* tmp=pole2[targetRegId-pole2.begin()];
    auto targetOwner = lower_bound(ownerPole.begin(), ownerPole.end(), owner, findOwner); // find vector of owner , now check whether we find duplicate
    if ((targetOwner == ownerPole.end()) || tolower(owner) < tolower(ownerPole[targetOwner-ownerPole.begin()][0]->majitel)){ // didnt find one, create one and pushback
        vector<CPozemek*> tmpVec;
        tmpVec.push_back(tmp);// insert the pointer
        ownerPole.insert(targetOwner,tmpVec); //insert the new vector
    }else{//found one
        ownerPole[targetOwner-ownerPole.begin()].push_back(tmp); // insert the pointer
    }

    return true;
}

bool CLandRegister::NewOwner(const string &city, const string &addr, const string &owner) {
    if(city.empty()|| addr.empty())
        return false;

    string prevOwner;
    SMestoUlice CitAddr;
    CitAddr.mesto=city;
    CitAddr.ulice=addr;

    auto targetCitAddr = lower_bound(pole.begin(), pole.end(), CitAddr, compareCityAddr); // have to check, if we found nothing return false
    if ((targetCitAddr == pole.end()) || (city < pole[targetCitAddr-pole.begin()]->mesto)){ // didnt find one, create one and pushback
        return false;
    }


    prevOwner =pole[targetCitAddr-pole.begin()]->majitel;
    if (tolower(owner) == tolower(prevOwner) ){ // already the owner
        return false;
    }

    auto targetPrevOwner = lower_bound(ownerPole.begin(), ownerPole.end(), prevOwner, findOwner);
    if ((targetPrevOwner == ownerPole.end()) || (tolower(prevOwner) < tolower(ownerPole[targetPrevOwner-ownerPole.begin()][0]->majitel))){ // didnt find one, create one and pushback
        cout << "nenaslo se co se melo" << endl;
        return false;
    }else{ // found the vector of the old owner.. find exact , delete
        for(long unsigned int i = 0; i<ownerPole[targetPrevOwner-ownerPole.begin()].size() ; i++){
            if(ownerPole[targetPrevOwner-ownerPole.begin()][i]->mesto==city && ownerPole[targetPrevOwner-ownerPole.begin()][i]->ulice==addr) {// got the old owner, delete, if vector empty delete it too
                ownerPole[targetPrevOwner-ownerPole.begin()].erase(ownerPole[targetPrevOwner-ownerPole.begin()].begin() + i);
                if(ownerPole[targetPrevOwner-ownerPole.begin()].empty()){
                    ownerPole.erase(targetPrevOwner);
                }
                break;
            }
        }
    }
    pole[targetCitAddr-pole.begin()]->majitel=owner;
    CPozemek* tmp=pole[targetCitAddr-pole.begin()];
    auto targetOwner = lower_bound(ownerPole.begin(), ownerPole.end(), owner, findOwner); // find vector of owner , now check whether we find duplicate
    if ((targetOwner == ownerPole.end()) || (tolower(owner) < tolower(ownerPole[targetOwner-ownerPole.begin()][0]->majitel))){ // didnt find one, create one and pushback
        vector<CPozemek*> tmpVec;
        tmpVec.push_back(tmp);// insert the pointer
        ownerPole.insert(targetOwner,tmpVec); //insert the new vector
    }else{//found one
        ownerPole[targetOwner-ownerPole.begin()].push_back(tmp); // insert the pointer
    }

    return true;

}

unsigned CLandRegister::Count(const string &owner) const {
    auto ownerTarget = lower_bound(ownerPole.begin(), ownerPole.end(), owner, findOwner);

    if ((ownerTarget == ownerPole.end()) || (tolower(owner) < tolower(ownerPole[ownerTarget-ownerPole.begin()][0]->majitel))){ // didnt find one
        return 0;
    }
    if(tolower(ownerPole[ownerTarget-ownerPole.begin()][0]->majitel)==tolower(owner)){ // i already have a vector with this owner
        return ((unsigned)ownerPole[ownerTarget-ownerPole.begin()].size());
    }
    return 0;
}

CIterator CLandRegister::ListByAddr(void) const {
    CIterator tmp;
    tmp.endIdx=lastIdxPozemek;
    tmp.curIdx=0;
    if(!pole.empty()){
        tmp.seznam.resize(lastIdxPozemek+1);
        tmp.seznam=pole;
    }
    return tmp;
}

CIterator CLandRegister::ListByOwner(const string &owner) const {
    CIterator tmp;
    tmp.curIdx=0;
    auto ownerTarget = lower_bound(ownerPole.begin(), ownerPole.end(), owner, findOwner);
    if ((ownerTarget == ownerPole.end()) || (owner < ownerPole[ownerTarget-ownerPole.begin()][0]->majitel)){
        tmp.endIdx=0;
        return tmp;
    }
    if (ownerPole[ownerTarget-ownerPole.begin()].size()>0){
        tmp.endIdx=ownerPole[ownerTarget-ownerPole.begin()].size()-1;
    }else{
        tmp.endIdx=0;
    }
    tmp.seznam=ownerPole[ownerTarget-ownerPole.begin()];

    return tmp;

}

#ifndef __PROGTEST__

static void test0(void) {
    CLandRegister x;
    string owner;


    assert (!x.Del("Librec", 4552));
    assert (!x.Del("Librec", 4552));
    assert (!x.Del("Librec", 4552));
    assert (!x.NewOwner("Tklppabprnmcca", 737869, "Michal Dvorak"));
    assert (x.Add("Prague", "Thakurova", "Dejvice", 12345));
    assert (!x.Add("Prague", "Thakurova", "Dejvice", 12345));
    assert (!x.Add("Prague", "Thakurova", "Dejvice", 12345));
    assert (!x.Add("Prague", "Thakurova", "Dejvice", 12345));

    assert (x.Add("Prague", "Evropska", "Vokovice", 12345));
    assert (x.Add("Prague", "Technicka", "Dejvice", 9873));
    assert (x.Add("Plzen", "Evropska", "Plzen mesto", 78901));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));

    assert(x.Add("", "", "", 0);
    assert(x.NewOwner("", "", "new"));
    assert(x.GetOwner("", "", owner) && owner== "new");
    assert(x.NewOwner("", "", ""));
    assert(x.GetOwner("", "", owner) && owner== "");
    assert(x.Del ("",0));
/*    assert (x.Del("Liberec", "Evropska"));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Librec", 4552));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Liberec", "Evropska"));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Librec", 4552));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Liberec", "Evropska"));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Librec", 4552));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Liberec", "Evropska"));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Librec", 4552));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Liberec", "Evropska"));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Librec", 4552));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Liberec", "Evropska"));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Librec", 4552));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Liberec", "Evropska"));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Librec", 4552));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Liberec", "Evropska"));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Librec", 4552));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Liberec", "Evropska"));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.Del("Librec", 4552));

    assert (x.Add("Liberec", "Evropska", "Librec", 4552));
    assert (x.NewOwner("Liberec", "Evropska","CVUT"));
    assert (x.NewOwner("Liberec", "Evropska","Michal Dvorak"));
    assert (x.NewOwner("Librec", 4552,"CVUT"));
    assert (x.NewOwner("Librec", 4552,"Michal Dvorak"));
    assert (x.NewOwner("Librec", 4552,"CVUT"));
    assert (x.NewOwner("Liberec", "Evropska","Michal Dvorak"));
    assert (x.NewOwner("Liberec", "Evropska","CVUT"));
    assert (x.NewOwner("Liberec", "Evropska","Michal Dvorak"));
    assert (x.NewOwner("Librec", 4552,"CVUT"));
    assert (x.NewOwner("Librec", 4552,"Michal Dvorak"));
    assert (x.NewOwner("Librec", 4552,"CVUT"));
    assert (x.NewOwner("Liberec", "Evropska","Michal Dvorak"));
    assert (x.NewOwner("Liberec", "Evropska","CVUT"));
    assert (x.NewOwner("Liberec", "Evropska","Michal Dvorak"));
    assert (x.NewOwner("Librec", 4552,"CVUT"));
    assert (x.NewOwner("Librec", 4552,"Michal Dvorak"));
    assert (x.NewOwner("Librec", 4552,"CVUT"));
    assert (x.NewOwner("Liberec", "Evropska","Michal Dvorak"));
    assert (x.NewOwner("Liberec", "Evropska","CVUT"));
    assert (x.NewOwner("Liberec", "Evropska","Michal Dvorak"));
    assert (x.NewOwner("Librec", 4552,"CVUT"));
    assert (x.NewOwner("Librec", 4552,"Michal Dvorak"));
    assert (x.NewOwner("Librec", 4552,"CVUT"));
    assert (x.NewOwner("Liberec", "Evropska","Michal Dvorak"));
    assert (x.Del("Librec", 4552));
    assert (x.Add("Liberec", "Evropska", "Librec", 4552));*/


    assert (x.Add("Tklppabprisjdofnmcca", "Ahoj", "Tklppabprnmcca", 737869));
    assert (!x.Add("Tklppabprisjdofnmcca", "Ahoj", "Tklppabprnmcca", 737869));
    assert (x.NewOwner("Tklppabprnmcca", 737869, "Michal Dvorak"));

    assert (!x.NewOwner("sdfsdfsdf", 7347869, "Michal Dvorak"));

    assert (x.GetOwner("Tklppabprnmcca", 737869, owner) && owner == "Michal Dvorak");
    assert (x.Del("Tklppabprnmcca", 737869));

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
