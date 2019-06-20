#include <iostream>
#include <map>
#include <set>
#include <cassert>
#include <queue>
#include <sstream>


using namespace std;

class CStation{
public:
    set<string> neighbors;
};

class CTrain {
public:
    CTrain(void) {
        // todo
    }

    ~CTrain(void) {
        for(auto x : stations){
            delete x.second;
        }
    }
    bool exists(string name){
        return (stations.find(name)!=stations.end());
    }
    void Add(istream &iss) {
        string newStation;
        string prev="";
        while(getline(iss, newStation)){
            if(!exists(newStation)){
                stations.insert(pair<string,CStation*>(newStation, new CStation()));
            }
            if(!prev.empty()){// prev has to exist to add neighbors
                stations[newStation]->neighbors.insert(prev);
                stations[prev]->neighbors.insert(newStation);
            }
            prev=newStation;
        }

    }

    int distTo (const string &from , const string & to){
        set<string> visited;
        queue<pair<string, int>> q;
        q.push(make_pair(from,0));
        int finalDist;
        while(!q.empty()){
            if(q.front().first==to){ // found a way to the destination
                finalDist=q.front().second;
                return finalDist;
            }
            for(const auto & d : stations[q.front().first]->neighbors){ // expands neighbors, checks if visited before
                if(visited.find(d)==visited.end()){
                    q.push(make_pair(d,q.front().second+1));
                    visited.insert(d);
                }
            }
            q.pop();
        }
        return -1;
    }

    set<string> Dest(const vector<string> &inpStations, int &cost) {
        set<pair<string, int>>ret;
        if(inpStations.size()==1){
            set<string> tmp;
            tmp.insert(*inpStations.begin());
            cost=0;
            return tmp;
        }
        for (const auto & x : stations){ // goes through all stations
            int finalPrice=0;
            bool foundDestForAll=true;
            for (const auto & l: inpStations){ // goes through each of the candidates
                int price=distTo(x.first, l);
                if(price>=0){
                    finalPrice+=price;
                }else{
                    foundDestForAll=false;
                }
            }
            if(foundDestForAll){
                if(ret.empty()){
                    ret.insert(make_pair(x.first, finalPrice));
                }else{
                    if(ret.begin()->second>finalPrice){
                        ret.clear();
                        ret.insert(make_pair(x.first,finalPrice));
                    }else if(ret.begin()->second>=finalPrice){
                        ret.insert(make_pair(x.first,finalPrice));
                    }
                }
            }
        }
        set<string> trueRet;
        if(!ret.empty()){ // returns final price
            cost=(*ret.begin()).second;
            for(const auto &x : ret){
                trueRet.insert(x.first);
            }
        }
        return trueRet;
    }

private:
    map<string,CStation*> stations;
};

int main ( void )
{
    CTrain t0;
    istringstream iss;

    iss . clear ();
    iss . str (
            "1\n"
            "2\n"
            "3\n"
            "4\n"
            "5\n"
            "6\n"
            "7\n"
            "8\n" );
    t0 . Add ( iss );
    iss . clear ();
    iss . str (
            "12\n"
            "11\n"
            "4\n"
            "9\n"
            "10\n" );
    t0 . Add ( iss );
    iss . clear ();
    iss . str (
            "15\n"
            "11\n"
            "13\n"
            "14\n" );
    t0 . Add ( iss );
    iss . clear ();
    iss . str (
            "7\n"
            "16\n"
            "17\n" );
    t0 . Add ( iss );
    iss . clear ();
    iss . str (
            "20\n"
            "19\n"
            "17\n"
            "18\n" );
    t0 . Add ( iss );
    iss . clear ();
    iss . str (
            "21\n"
            "22\n"
            "23\n"
            "25\n"
            "24\n"
            "21\n" );
    t0 . Add ( iss );
    iss . clear ();
    iss . str (
            "26\n"
            "27\n"
            "28\n" );
    t0 . Add ( iss );
    iss . clear ();
    iss . str (
            "27\n"
            "29\n"
            "30\n" );
    t0 . Add ( iss );

    int cost = 5381;
    assert ( t0 . Dest ({ "2", "5", "11" }, cost ) == set <string> ({ "4" })
             && cost == 4 );
    assert ( t0 . Dest ({ "12", "10" }, cost ) == set <string> ({ "10", "9", "4", "11", "12" })
             && cost == 4 );
    assert ( t0 . Dest ({ "2", "9", "19" }, cost ) == set <string> ({ "4" })
             && cost == 9 );
    assert ( t0 . Dest ({ "15", "12", "13" }, cost ) == set <string> ({ "11" })
             && cost == 3 );
    cost = 5381;
    assert ( t0 . Dest ({ "21", "26" }, cost ) == set <string> ()
             && cost == 5381 );
    cost = 1256;
    assert ( t0 . Dest ({ "10", "28" }, cost ) == set <string> ()
             && cost == 1256 );
    assert ( t0 . Dest ({ "21", "25" }, cost ) == set <string> ({ "21", "24", "25" })
             && cost == 2 );
    assert ( t0 . Dest ({ "21", "21" }, cost ) == set <string> ({ "21" })
             && cost == 0 );
    assert ( t0 . Dest ({ "23", "21" }, cost ) == set <string> ({ "21", "22", "23" })
             && cost == 2 );
    assert ( t0 . Dest ({ "12", "20" }, cost ) == set <string> ({ "12", "11", "4", "5", "6", "7", "16", "17", "19", "20" })
             && cost == 9 );
    assert ( t0 . Dest ({ "50" }, cost ) == set <string> ({ "50" })
             && cost == 0 );
    assert ( t0 . Dest ({ "13", "10" }, cost ) == set<string> ({ "10", "11", "13", "4", "9" })
             && cost == 4 );
    assert ( t0 . Dest ({ "17", "19" }, cost ) == set<string> ({ "17", "19" })
             && cost == 1 );
    cost = 1999;
    assert ( t0 . Dest ({ "29", "25" }, cost ) == set<string> ()
             && cost == 1999 );
    assert ( t0 . Dest ({ "8", "5" }, cost ) == set<string> ({ "5", "6", "7", "8" })
             && cost == 3 );
    assert ( t0 . Dest ({ "4", "4" }, cost ) == set<string> ({ "4" })
             && cost == 0 );

    return 0;
}