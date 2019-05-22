#ifndef __PROGTEST__

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>

using namespace std;
class CTrain {
public:
    CTrain(const string &company,
           int speed)
            : m_Company(company),
              m_Speed(speed) {
    }

    //---------------------------------------------------------------------------------------------
    string m_Company;
    int m_Speed;
};

//=================================================================================================
#endif /* __PROGTEST__ */

class NoRouteException {
};

template<typename _T>
bool isNotVisited(_T a, set<_T> list) {    //Helping function, checks whether it is already in path
    if (list.find(a)!=list.end()){
        return false;
    }
    return true;
}

template<typename _T, typename _E>
class CRoute {
    map<_T, vector<pair<_T, _E>>> g;
public:
    CRoute() {}
    ~CRoute() {}
    CRoute & Add(const _T & a, const _T & b, const _E train) {
        if (g.find(a) != g.end()) {                         // finds A point, this means that point is already present in graph, creates a new connection
            g[a].push_back(make_pair(b, train));
        }
        else {                                          // does not find a point, means that point is not yet in graph, creates one and inserts into map
            vector<pair<_T, _E>> tmpV;
            tmpV.push_back(make_pair(b, train));
            g.insert(pair<_T, vector<pair<_T, _E>>>(a, tmpV));
        }
        if (g.find(b) != g.end()) {                         // similar situation as with previous iteration
            g[b].push_back(make_pair(a, train));
        }
        else {
            vector<pair<_T, _E>> tmpV;
            tmpV.push_back(make_pair(a, train));
            g.insert(pair<_T, vector<pair<_T, _E>>>(b, tmpV));
        }
        return *this;
    }
    list<_T> Find(const _T &  src, const _T &  dst, const function <bool(const _E &)> & func = [](const _E &a) {return true; }) {
        vector<_T> path;                          // Function creates helping variables
        queue<vector<_T>> q;                      // path stores the currently checking path, q is a queue of paths ready to be checked (in this situation the last entity in path is the one that needs expanding)
        set<_T> visited;
        path.push_back(src);
        q.push(path);

        if (src == dst)
            return list<_T> { src };
        else if (g.find(src) == g.end() || g.find(dst) == g.end())
            throw NoRouteException();

        while (!q.empty()) {
            path = q.front();
            q.pop();
            _T last = path.back();
            if (last == dst)                     // about to expand the last entity, if entity happens to be the final destination, return path. Using BFS, shortest path guaranteed
                return list<_T>(path.begin(), path.end());

            auto lt = g.find(last)->second;
            for (int i = 0; i <(int)g[last].size(); i++) {
                if (isNotVisited(lt[i].first, visited) && func(g[last][i].second)) {
                    visited.insert(lt[i].first);
                    vector<_T> newpath(path);
                    newpath.push_back(lt[i].first);
                    q.push(newpath);
                }
            }
        }
        throw NoRouteException(); // if queue empties before finding suitable path, exception thrown
    }

    // Find (with optional filter)
};

#ifndef __PROGTEST__

//=================================================================================================

class TrainFilterCompany {
public:
    TrainFilterCompany(const set<string> &companies)
            : m_Companies(companies) {
    }

    //---------------------------------------------------------------------------------------------
    bool operator()(const CTrain &train) const {
        return m_Companies.find(train.m_Company) != m_Companies.end();
    }
    //---------------------------------------------------------------------------------------------
private:
    set<string> m_Companies;
};

//=================================================================================================
class TrainFilterSpeed {
public:
    TrainFilterSpeed(int min,
                     int max)
            : m_Min(min),
              m_Max(max) {
    }

    //---------------------------------------------------------------------------------------------
    bool operator()(const CTrain &train) const {
        return train.m_Speed >= m_Min && train.m_Speed <= m_Max;
    }
    //---------------------------------------------------------------------------------------------
private:
    int m_Min;
    int m_Max;
};

//=================================================================================================
bool NurSchnellzug(const CTrain &zug) {
    return (zug.m_Company == "OBB" || zug.m_Company == "DB") && zug.m_Speed > 100;
}

//=================================================================================================
static string toText(const list<string> &l) {
    ostringstream oss;

    auto it = l.cbegin();
    oss << *it;
    for (++it; it != l.cend(); ++it)
        oss << " > " << *it;
    return oss.str();
}

//=================================================================================================
int main(void) {
    CRoute<string, CTrain> lines;
    lines.Add("Berlin", "Prague", CTrain("DB", 120))
            .Add("Berlin", "Prague", CTrain("CD", 80))
            .Add("Berlin", "Dresden", CTrain("DB", 160))
            .Add("Dresden", "Munchen", CTrain("DB", 160))
            .Add("Munchen", "Prague", CTrain("CD", 90))
            .Add("Munchen", "Linz", CTrain("DB", 200))
            .Add("Munchen", "Linz", CTrain("OBB", 90))
            .Add("Linz", "Prague", CTrain("CD", 50))
            .Add("Prague", "Wien", CTrain("CD", 100))
            .Add("Linz", "Wien", CTrain("OBB", 160))
            .Add("Paris", "Marseille", CTrain("SNCF", 300))
            .Add("Paris", "Dresden", CTrain("SNCF", 250));

    list<string> r1 = lines.Find("Berlin", "Linz");
    assert(toText(r1) == "Berlin > Prague > Linz");

    list<string> r2 = lines.Find("Linz", "Berlin");
    assert(toText(r2) == "Linz > Prague > Berlin");

    list<string> r3 = lines.Find("Wien", "Berlin");
    assert(toText(r3) == "Wien > Prague > Berlin");

    list<string> r4 = lines.Find("Wien", "Berlin", NurSchnellzug);
    assert(toText(r4) == "Wien > Linz > Munchen > Dresden > Berlin");

    list<string> r5 = lines.Find("Wien", "Munchen", TrainFilterCompany(set<string>{"CD", "DB"}));
    assert(toText(r5) == "Wien > Prague > Munchen");

    list<string> r6 = lines.Find("Wien", "Munchen", TrainFilterSpeed(120, 200));
    assert(toText(r6) == "Wien > Linz > Munchen");

    list<string> r7 = lines.Find("Wien", "Munchen", [](const CTrain &x) { return x.m_Company == "CD"; });
    assert(toText(r7) == "Wien > Prague > Munchen");

    list<string> r8 = lines.Find("Munchen", "Munchen");
    assert(toText(r8) == "Munchen");

    list<string> r9 = lines.Find("Marseille", "Prague");
    assert(toText(r9) == "Marseille > Paris > Dresden > Berlin > Prague"
           || toText(r9) == "Marseille > Paris > Dresden > Munchen > Prague");

    try {
        list<string> r10 = lines.Find("Marseille", "Prague", NurSchnellzug);
        assert("Marseille > Prague connection does not exist!!" == NULL);
    }
    catch (const NoRouteException &e) {
    }

    list<string> r11 = lines.Find("Salzburg", "Salzburg");
    assert(toText(r11) == "Salzburg");

    list<string> r12 = lines.Find("Salzburg", "Salzburg", [](const CTrain &x) { return x.m_Company == "SNCF"; });
    assert(toText(r12) == "Salzburg");

    try {
        list<string> r13 = lines.Find("London", "Oxford");
        assert("London > Oxford connection does not exist!!" == NULL);
    }
    catch (const NoRouteException &e) {
    }
    return 0;
}

#endif  /* __PROGTEST__ */
