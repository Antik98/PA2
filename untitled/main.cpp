#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <cassert>
using namespace std;



class CMHD{
    map<string, set<int>> stations;
    map<int, set<string>> routes;
public:
    CMHD();
    bool Add(istringstream& iss);
    set<string> Dest(string from, int);

};

CMHD::CMHD() {

}

bool CMHD::Add(istringstream &iss) {
    int curRouteIndex=routes.size();
    set<string> routeIns;
    while(iss.good()){
        string stationName="";
        iss >> stationName;
        if(stationName.empty()) // empty name skip
            continue;
        auto iter=stations.find(stationName);
        if(iter==stations.end()){ // station does not exist
            set<int> tmpRoutesSet;
            tmpRoutesSet.insert(curRouteIndex);
            stations.insert(make_pair(stationName,tmpRoutesSet));
        }else{ // station does exist
            iter->second.insert(curRouteIndex);
        }
        routeIns.insert(stationName);
    }
    routes.insert(make_pair(curRouteIndex,routeIns));
}

set<string> CMHD::Dest(string from, int jumps) {
    queue<pair<set<string>, int>> que;
    set<string> ret;
    bool firstExpansion=true;
    if(jumps<0){
        return ret;
    }
    set<string> tmpSet;
    tmpSet.insert(from);
    que.push(make_pair(tmpSet,0));
    while (!que.empty()){
        if(que.front().second>jumps){
            que.pop();
        }else{
            set<int> routesExpanded;
            for(auto x:que.front().first){
                set<string> pushSet=que.front().first;
                int pushJump;
                if(firstExpansion)
                    pushJump=que.front().second;
                else{
                    pushJump=que.front().second+1;
                }
                firstExpansion=false;
                for(auto i: stations[x]){
                    if(routesExpanded.find(i)==routesExpanded.end()){
                        for(auto l:routes[i]){
                            pushSet.insert(l);
                        }
                        routesExpanded.insert(i);
                    }
                }
                que.push(make_pair(pushSet,pushJump));
            }
            que.pop();
        }
        if(que.front().second==jumps){
            ret=que.front().first;
            return ret;
        }
    }
    return ret;
}


int main ( void )
{
    CMHD city;
    istringstream iss;
    iss.clear();

    iss . str ( "A\nB\nC\nD\nE\n" );
    city . Add ( iss );
    iss . clear();

    iss . str ( "B\nC\nF\nH\n" );
    city . Add ( iss );
    iss . clear();

    iss . str ( "F\nG\nI\nJ\nK\nN\n" );
    city . Add ( iss );
    iss . clear();

    iss . str ( "H\nL\n" );
    city . Add ( iss );
    iss . clear();

    iss . str ( "L\nM\nN\nO\n" );
    city . Add ( iss );
    iss . clear();

    iss . str ( "P\nQ\nR\nN\nS" );
    city . Add ( iss );
    iss . clear();


    assert ( city . Dest ( "S", 0 ) == set < string > ( {"S", "N", "R", "Q", "P"} ) );

    assert ( city . Dest ( "S", 1 ) == set < string > ( { "S", "N", "R", "Q", "P",
                                                          "O", "M", "L",
                                                          "K", "J", "I", "G", "F" } ) );

    assert ( city . Dest ( "N", 0 ) == set < string > ( { "S", "N", "R", "Q", "P",
                                                          "O", "M", "L",
                                                          "K", "J", "I", "G", "F" } ) );

    assert ( city . Dest ( "N", 1 ) == set < string > ( { "S", "N", "R", "Q", "P",
                                                          "O", "M", "L",
                                                          "K", "J", "I", "G", "F",
                                                          "H", "F", "C", "B" } ) );

    assert ( city . Dest ( "N", 2 ) == set < string > ( { "S", "N", "R", "Q", "P",
                                                          "O", "M", "L",
                                                          "K", "J", "I", "G", "F",
                                                          "H", "F", "C", "B",
                                                          "A", "D", "E" } ) );

    assert ( city . Dest ( "unknown", 0 ) == set < string > ( { "unknown" } ) );
    assert ( city . Dest ( "unknown", 1 ) == set < string > ( { "unknown" } ) );
    assert ( city . Dest ( "unknown", 2 ) == set < string > ( { "unknown" }) );

    return 0;
}

