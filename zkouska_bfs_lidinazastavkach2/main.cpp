#include <iostream>
#include <map>
#include <set>
#include <cassert>
#include <queue>
#include <sstream>


using namespace std;

class CStation{
public:
    set <string> neighbors;
};

class CTrain {
public:
    CTrain(void) {
        // todo
    }

    ~CTrain(void) {
        for(auto &x: stations){
            delete x.second;
        }
    }

    bool exists(const string &name) const {
        return (stations.find(name)!=stations.end());
    }

    void Add(istream &iss) {
        string newStation="";
        string prev="";
        while (getline(iss, newStation)){
            if(newStation.empty()){
                continue;
            }
            if(!exists(newStation)){
                stations.insert(make_pair(newStation, new CStation()));
            }
            if(!prev.empty()){
                stations[prev]->neighbors.insert(newStation);
                stations[newStation]->neighbors.insert(prev);
            }
            prev = newStation;
        }
    }
    int distTo(const string &from,const string &to){
        queue<pair<string, int>> q;
        set<string> visited;
        q.push(make_pair(from, 0));
        while(!q.empty()){
            if(q.front().first==to){
                return q.front().second;
            }
            if(exists(q.front().first)){
                for(const auto &x : stations[q.front().first]->neighbors){
                    if(visited.find(x)==visited.end()) {
                        q.push(make_pair(x, q.front().second + 1));
                        visited.insert(x);
                    }
                }
            }
            q.pop();
        }
        return -1;
    }
    set<string> Dest(const vector<string> &inpStations, int &cost) {
        if(inpStations.size()==1){
            cost=0;
            set<string> tmp;
            tmp.insert(*(inpStations.begin()));
            return tmp;
        }
        set<pair<string, int> > prices;
        for(const auto &x: stations){
            int finalPrice=0;
            bool foundMeetStation=true;
            for(const auto &l: inpStations){
                int price=distTo(x.first, l);
                if(price>=0){
                    finalPrice+=price;
                }else{
                    foundMeetStation=false;
                    break;
                }
            }
            if(foundMeetStation){
                if(finalPrice<(*prices.begin()).second){
                    prices.clear();
                    prices.insert(make_pair(x.first, finalPrice));
                }else if(finalPrice== (*prices.begin()).second){
                    prices.insert(make_pair(x.first, finalPrice));
                }
            }else{
                continue;
            }
        }
        set<string> ret;
        for(const auto &x:prices){
            ret.insert(x.first);
            cost=x.second;
        }
        return ret;
    }

private:
    map<string, CStation*> stations;

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