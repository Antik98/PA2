#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class InvalidRangeException
{
};
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX

class CRange{
public:
    CRange();
    CRange( long long int low, long long int high);
    long long int lo;
    long long int hi;
};
CRange::CRange(long long int low, long long int high){
    if(low<=high){
        lo=low;
        hi=high;
    }else{
        throw InvalidRangeException();
    }
}

class CRangeList
{
public:
    CRangeList(){};
    bool Includes(const long long int) const;
    bool Includes(const CRange) const;
    CRangeList& operator +=(const CRange);
    CRangeList& operator +=(const CRangeList);
    CRangeList& operator -=(const CRange);
    CRangeList& operator -=(const CRangeList);
    CRangeList operator =(const CRange);
    CRangeList operator =(const CRangeList);
    CRangeList operator +(const CRange) const;
    CRangeList operator +(const CRangeList) const;
    CRangeList operator -(const CRange) const;
    CRangeList operator -(const CRangeList) const;

    bool operator ==(const CRangeList&) const;
    bool operator !=(const CRangeList&) const;
    friend CRangeList operator + (const CRange first, const CRange second);
    friend CRangeList operator - (const CRange first, const CRange second);
    friend const ostringstream& operator<<(ostringstream& os, const CRangeList& list);

private:
    vector<CRange> pole;
};

bool compareRangeLo(CRange first, CRange second){
    return (first.lo<second.lo);
}
long long int max (long long int first, long long int second){
    if (first>=second){
        return first;
    }else{
        return second;
    }
}
bool findRangeNum(CRange first, long long int second){
    return (first.lo<second);
}

CRangeList& CRangeList::operator+=(const class CRange origrange) {
    CRange range = origrange;
    if(this->pole.empty()){
        pole.push_back(range);
    }else {
        auto it = lower_bound(pole.begin(), pole.end(), range, compareRangeLo);

        if (it == pole.begin()) {

            for (auto findHiBorder = it; findHiBorder < pole.end(); ++findHiBorder) {
                //todo could overflow
                if (range.hi < findHiBorder->lo - 1) { // doesnt touch the next one, break
                    break;
                } else if (range.hi > findHiBorder->lo && range.hi > findHiBorder->hi) {// engulfs it
                    pole.erase(findHiBorder);
                    findHiBorder--;
                } else { // collides with one
                    if (range.hi < findHiBorder->hi) {
                        range.hi = findHiBorder->hi;
                        pole.erase(findHiBorder);
                        break;
                    } else {
                        pole.erase(findHiBorder);
                        break;
                    }
                }
            }
            pole.insert(it, range);
       }else if (it == pole.end()){
            auto prevIt = it;
            if(it!=pole.begin()){
                prevIt = prevIt - 1;
            }

            if((prevIt)->hi>range.lo || (prevIt)->hi+1 == range.lo){ // engulfs the one before it
                if((prevIt)->hi < range.hi){
                    (prevIt)->hi = range.hi;
                }
            }else{
                pole.insert(it,range);
            }
       }else{
            auto prevIt = it;
            if(it!=pole.begin()){
                prevIt = prevIt - 1;
            }
            if(range .lo  > prevIt->hi + 1 && range.hi  < it->lo -1) // it fits between two intervals without merging, simple
                pole.insert(it, range);
            else{ // first extend the lo, then hi
                for( auto findLoBorder = prevIt; findLoBorder>=pole.begin(); findLoBorder--){
                    //todo could overflow
                    if (findLoBorder->hi+1 < range.lo){ // doesnt colide with this one
                        break;
                    }else if(findLoBorder->hi > range.lo && findLoBorder->lo > range.lo ){ // engulf this one
                        it--;
                        pole.erase(findLoBorder);
                        findLoBorder++;
                    }else{ // collides with an interval
                        if(range.lo > findLoBorder->lo){
                            range.lo=findLoBorder->lo;
                            it--;
                            pole.erase(findLoBorder);
                            break;
                        }else{
                            it--;
                            pole.erase(findLoBorder);
                            break;
                        }
                    }
                }

                for (auto findHiBorder = it ; findHiBorder<pole.end();++findHiBorder){
                    //todo could overflow
                    if(range.hi < findHiBorder->lo - 1){ // doesnt touch the next one, break
                        break;
                    }else if( range.hi > findHiBorder->lo && range.hi > findHiBorder->hi){// engulfs it
                        pole.erase(findHiBorder);
                        findHiBorder--;
                    }else{ // collides with one
                        if(range.hi < findHiBorder->hi){
                            range.hi=findHiBorder->hi;
                            pole.erase(findHiBorder);
                            break;
                        }else{
                            pole.erase(findHiBorder);
                            break;
                        }
                    }
                }
                pole.insert(it, range);
            }
       }
    }
    return *this;
}

CRangeList& CRangeList::operator-=(const CRange origrange) {
    CRange range = origrange;
    if(this->pole.empty()){

    }else{
        auto it = lower_bound(pole.begin(), pole.end(), range, compareRangeLo);
        auto prevIt = it;
        if(it!=pole.begin()){
            prevIt = prevIt - 1;
        }

        
        if (it == pole.begin()){
            if(prevIt->lo< range.lo && prevIt->hi > range.hi){
                CRange tmp(range.hi+1, prevIt->hi);
                prevIt->hi=range.lo-1;
                pole.insert(it,tmp);
            }else {

                for (auto findHiBorder = it; findHiBorder < pole.end(); findHiBorder++) {
                    if (range.hi < findHiBorder->lo) { // doesnt touch the next one, break
                        break;
                    } else if (range.hi >= findHiBorder->lo && range.hi >= findHiBorder->hi) {// engulfs it
                        pole.erase(findHiBorder);
                        findHiBorder--;
                    } else { // collides with one
                        findHiBorder->lo = range.hi + 1;
                    }
                }
            }
        }else if(it == pole.end()){ // at the back checks if overlaps with the one before it
            if(prevIt->lo< range.lo && prevIt->hi > range.hi){
                CRange tmp(range.hi+1, prevIt->hi);
                prevIt->hi=range.lo-1;
                pole.insert(it,tmp);
            }else {

                for (auto findLoBorder = prevIt; findLoBorder >= pole.begin(); findLoBorder--) {
                    if (findLoBorder->hi < range.lo) { // doesnt colide with this one
                        break;
                    } else if (findLoBorder->hi >= range.lo && findLoBorder->lo >= range.lo) { // engulf this one
                        pole.erase(findLoBorder);
                        findLoBorder++;
                    } else { // collides with an interval
                        findLoBorder->hi = range.lo - 1;
                        break;
                    }
                }
            }
        }else{
            if(range .lo > prevIt->hi && range.hi < it->lo){// it fits between two intervals without merging, simple

            }else if(prevIt->lo< range.lo && prevIt->hi > range.hi){
                CRange tmp(range.hi+1, prevIt->hi);
                prevIt->hi=range.lo-1;
                pole.insert(it,tmp);
            }else{ // first extend the lo, then hi
                    for( auto findLoBorder = prevIt; findLoBorder>=pole.begin(); findLoBorder--){
                        if (findLoBorder->hi < range.lo){ // doesnt colide with this one
                            break;
                        }else if(findLoBorder->hi >= range.lo && findLoBorder->lo >= range.lo ){ // engulf this one
                            pole.erase(findLoBorder);
                            findLoBorder++;
                        }else{ // collides with an interval
                            findLoBorder->hi=range.lo-1;
                            break;
                        }
                    }

                    for (auto findHiBorder = it ; findHiBorder<pole.end();findHiBorder++){
                        if(range.hi < findHiBorder->lo){ // doesnt touch the next one, break
                            break;
                        }else if( range.hi >= findHiBorder->lo && range.hi >= findHiBorder->hi){// engulfs it
                            pole.erase(findHiBorder);
                            findHiBorder--;
                        }else{ // collides with one
                            findHiBorder->lo=range.hi+1;
                            break;
                        }
                    }
                }
            }
        }
    return *this;
}

bool CRangeList::Includes( const long long int tmp) const {
    if (pole.empty()){
        return false;
    }

    auto it = lower_bound(pole.begin(), pole.end(), tmp, findRangeNum);

    auto prevIt = it;
    if(it!=pole.begin()){
        prevIt = prevIt - 1;
    }
    if(it == pole.begin()){
        return false;
    }
    if (prevIt->hi >= tmp || it->lo== tmp){
        return true;
    }
    return false;
}

bool CRangeList::Includes( const CRange tmp) const {
    if (pole.empty()){
        return false;
    }
    if(tmp.lo == tmp.hi){
        if(Includes(tmp.lo)){
            return true;
        }else{
            return false;
        }
    }

    auto it = lower_bound(pole.begin(), pole.end(), tmp, compareRangeLo);
    auto prevIt = it;
    if(it!=pole.begin()){
        prevIt = prevIt - 1;
    }

    if (it== pole.begin()){ // dont know if this is necessary, pretty much if it reaches begin should be false
        if(it->lo>tmp.lo){
            return false;
        }
    }else if(it == pole.end()){
        if((prevIt)->lo < tmp.lo && (prevIt)->hi > tmp.hi){
            return true;
        }
        return false;
    }else{
        if((prevIt)->lo < tmp.lo && (prevIt)->hi > tmp.hi){
            return true;
        }
        return false;
    }
    return false;
}

CRangeList operator + (const CRange first, const CRange second) {
    CRangeList tmp;
    tmp.pole.push_back(first);
    tmp += second;
    return tmp;
}
CRangeList operator - (const CRange first, const CRange second)  {
    CRangeList tmp;
    tmp.pole.push_back(first);
    tmp -= second;
    return tmp;
}

const ostringstream& operator<<(ostringstream& os, const CRangeList& list) {
    os<<"{";
    for(unsigned int i = 0 ; i < list.pole.size(); i++){
        if(list.pole.at(i).lo == list.pole.at(i).hi){
            os<< list.pole.at(i).lo;
        }else{
            os << "<" << list.pole.at(i).lo << ".." << list.pole.at(i).hi << ">";
        }
        if(i+1 != list.pole.size() ){
            os << ",";
        }
    }
    os<<"}";
    return os;
}

CRangeList& CRangeList::operator+=(const CRangeList tmp) {
    for(auto it = tmp.pole.begin(); it < tmp.pole.end(); it++){
        *this += *it;
    }
    return *this;
}

CRangeList& CRangeList::operator-=(const CRangeList tmp) {
    for(auto it = tmp.pole.begin(); it < tmp.pole.end(); it++){
        *this -= *it;
    }
    return *this;
}

CRangeList CRangeList::operator+(const CRange tmp) const {
    CRangeList tmpList = *this;
    tmpList += tmp;
    return tmpList;
}

CRangeList CRangeList::operator+(const  CRangeList tmp) const {
    CRangeList tmpList = *this;
    for(auto it = tmp.pole.begin(); it < tmp.pole.end(); it++){
        tmpList += *it;
    }
    return tmpList;
}

CRangeList CRangeList::operator-(const CRange tmp) const {
    CRangeList tmpList = *this;
    tmpList -= tmp;
    return tmpList;
}

CRangeList CRangeList::operator-( const CRangeList tmp) const {
    CRangeList tmpList = *this;
    for(auto it = tmp.pole.begin(); it < tmp.pole.end(); it++){
        tmpList -= *it;
    }
    return tmpList;
}

CRangeList CRangeList::operator=(const CRange tmp) {
    pole.clear();
    pole.push_back(tmp);
    return *this;
}

CRangeList CRangeList::operator=(const CRangeList tmp) {
    pole.clear();
    for(auto it = tmp.pole.begin(); it<tmp.pole.end(); it++){
        pole.push_back(*it);
    }
    return *this;
}

bool CRangeList::operator==(const CRangeList &tmp) const {
    if(pole.size()!=tmp.pole.size()){
        return false;
    }
    for(unsigned int i = 0; i<pole.size(); i++ ){
        if (pole.at(i).lo != tmp.pole.at(i).lo || pole.at(i).hi != tmp.pole.at(i).hi ){
            return false;
        }
    }
    return true;
}

bool CRangeList::operator!=(const CRangeList &tmp) const {
    if(pole.size()!=tmp.pole.size()){
        return true;
    }
    for(unsigned int i = 0; i<pole.size(); i++ ){
        if (pole.at(i).lo != tmp.pole.at(i).lo || pole.at(i).hi != tmp.pole.at(i).hi ){
            return true;
        }
    }
    return false;
}


#ifndef __PROGTEST__
string             toString                                ( const CRangeList& x )
{
    ostringstream oss;
    oss << x;
    return oss . str ();
}

int                main                                    ( void )
{
    CRangeList a, b;


    assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
    a = CRange ( 5, 10 );
    a += CRange ( 25, 100 );
    assert ( toString ( a ) == "{<5..10>,<25..100>}" );
    a += CRange ( -5, 0 );
    a += CRange ( 8, 50 );
    assert ( toString ( a ) == "{<-5..0>,<5..100>}" );
    a += CRange ( 101, 105 ) + CRange ( 120, 150 ) + CRange ( 160, 180 ) + CRange ( 190, 210 );
    assert ( toString ( a ) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}" );
    a += CRange ( 106, 119 ) + CRange ( 152, 158 );
    assert ( toString ( a ) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}" );
    a += CRange ( -3, 170 );
    a += CRange ( -30, 1000 );
    assert ( toString ( a ) == "{<-30..1000>}" );
    b = CRange ( -500, -300 ) + CRange ( 2000, 3000 ) + CRange ( 700, 1001 );
    a += b;
    assert ( toString ( a ) == "{<-500..-300>,<-30..1001>,<2000..3000>}" );
    a -= CRange ( -400, -400 );
    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}" );
    a -= CRange ( 10, 20 ) + CRange ( 900, 2500 ) + CRange ( 30, 40 ) + CRange ( 10000, 20000 );
    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    try
    {
        a += CRange ( 15, 18 ) + CRange ( 10, 0 ) + CRange ( 35, 38 );
        assert ( "Exception not thrown" == NULL );
    }
    catch ( const InvalidRangeException & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown" == NULL );
    }
    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    b = a;
    assert ( a == b );
    assert ( !( a != b ) );
    b += CRange ( 2600, 2700 );
    assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    assert ( a == b );
    assert ( !( a != b ) );
    b += CRange ( 15, 15 );
    assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}" );
    assert ( !( a == b ) );
    assert ( a != b );
    assert ( b . Includes ( 15 ) );
    assert ( b . Includes ( 2900 ) );
    assert ( b . Includes ( CRange ( 15, 15 ) ) );
    assert ( b . Includes ( CRange ( -350, -350 ) ) );
    assert ( b . Includes ( CRange ( 100, 200 ) ) );
    assert ( !b . Includes ( CRange ( 800, 900 ) ) );
    assert ( !b . Includes ( CRange ( -1000, -450 ) ) );
    assert ( !b . Includes ( CRange ( 0, 500 ) ) );
    a += CRange ( -10000, 10000 ) + CRange ( 10000000, 1000000000 );
    assert ( toString ( a ) == "{<-10000..10000>,<10000000..1000000000>}" );
    b += a;
    assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
    b -= a;
    assert ( toString ( b ) == "{}" );
    b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
    assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );
    b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );
    assert ( toString ( b ) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}" );

#ifdef EXTENDED_SYNTAX
    CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
  assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
  ostringstream oss;
  oss << setfill ( '=' ) << hex << left;
  for ( const auto & v : x + CRange ( -100, -100 ) )
    oss << v << endl;
  oss << setw ( 10 ) << 1024;
  assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );
#endif /* EXTENDED_SYNTAX */
    return 0;
}
#endif /* __PROGTEST__ */
