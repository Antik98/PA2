#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
using namespace std;
class CStation{
public:
    CStation()=default;
    CStation(string name):name(name){};
    string name;
    set<string> destinations;
    friend ostream & operator << (ostream & os, CStation& station) {
        os<< "Station name: " << station.name << endl;
        for(auto x: station.destinations){
            os<< "\t";
            os<< x << endl;
        }
        return os;
    }
};
class CTrain{
public:
    CTrain() = default;
    ~CTrain()= default;

    //Add
    void Add(istringstream &iss);
    //Dest
    set<string> Dest (const string & from, int maxCost);

private:
    map<string, CStation> stations;
};

void CTrain::Add(istringstream &iss) {
    string tmpName;
    getline(iss,tmpName);
    auto findIt=stations.find(tmpName);
    map<string,CStation>::iterator prevIt;
    if(findIt == stations.end()){ // station does not exist
        pair<map<string, CStation>::iterator, bool> ret = stations.insert(make_pair(tmpName, CStation(tmpName)));
        prevIt=ret.first;
    }else{
        prevIt=findIt;
    }

    string newStation;
    while(getline(iss, newStation)){
        auto iterator=stations.find(newStation);
        if(iterator == stations.end()){ // station does not exist
            CStation tmpStation(newStation);
            tmpStation.destinations.insert(prevIt->first);
            prevIt->second.destinations.insert(tmpStation.name);
            auto tmpMapIt=stations.insert(make_pair(tmpStation.name, tmpStation));
            cout << tmpStation;
            iterator=tmpMapIt.first;
        }else{// station does exist
            // now see if destination station exist
            prevIt->second.destinations.insert(iterator->first);
            iterator->second.destinations.insert(prevIt->first);
            cout << iterator->second;
        }
        prevIt=iterator;
    }

}

set<string> CTrain::Dest(const string &from, int maxCost) {
    set<string> ret;
    queue<string> q;
    auto it = stations.find(from);
    if (it == stations.end() || maxCost<0){
        return ret;
    }else{
        ret.insert(from);
        cout << stations[from];
        for(int i = 0; i <maxCost; i++){
            for (auto & x: ret){
                q.push(x);
            }
            while(!q.empty()){
                for(auto d:stations[q.front()].destinations){
                    ret.insert(d);
                }
                q.pop();
            }
        }
    }
}


int main(){
    CTrain t0;
    istringstream iss;
    iss . clear ();
    iss . str ("Forest Hill\nNational Museum\nWhite City\nChina Town\nWembley\nNew Cross\n");
    t0 . Add ( iss );
    iss . clear ();
    iss . str ("Lady Palace\nKings Cross\nOldTown\nNew Cross\nNew Aley\n");
    t0 . Add ( iss );
    iss . clear ();
    iss . str ("ZOO\nChina Town\nKings Cross\nFantom Bridge\n");
    t0 . Add ( iss );


    set<string> s = (t0.Dest("National Museum", 1));
/*Forest Hill
  National Museum
  White City*/

    set<string> t = (t0.Dest("China Town", 0));
/*China Town*/

    set<string> u = (t0.Dest("China Town", 2));
/*China Town
  Fantom Bridge
  Kings Cross
  Lady Palace
  National Museum
  New Cross
  Old Town
  Wembley
  White City
  ZOO*/

    set<string> v = (t0.Dest("ZOO", 2));
/*China Town
  Kings Cross
  Wembley
  White City
  ZOO*/

}