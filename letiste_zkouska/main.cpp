#include <iostream>
#include <cassert>

using namespace std;

class CFlightList {
public:
    CFlightList():m_List(nullptr){
    }
    CFlightList(CFlightList& copy):m_List(nullptr){
        CAirport* iterator=copy.m_List;
        if(iterator){
            this->m_List=new CAirport(copy.m_List->m_Name);
            while(iterator){
                
                iterator=iterator->m_Next;
            }
        }
    }
    CFlightList(const CFlightList &src) {

    }

    ~CFlightList() {

    }


    bool Add (const string & from, const string & to) {
        if(from.empty() || to.empty()){
            return false;
        }
        if(from==to){
            return false;
        }
        CAirport * curIt=m_List;
        CAirport * prevIt= nullptr;
        bool addedFrom=false;
        if(!curIt){
            curIt=new CAirport(from);
            m_List=curIt;
            addedFrom=true;
        }
        while(curIt){
            if(curIt->m_Name==from){ // finds the from dest
                for(int i =0 ; i<curIt->m_Nr; i++){ // goes through destinations
                    if(curIt->m_Dest[i]->m_Name==to){ // found to, exists
                        return false;
                    }
                }
                // add destination, better check if Airport exists
                CAirport * findIterator=m_List;
                bool airportExists=false;
                while(findIterator){
                    if(findIterator->m_Name==to){ // airport exists, take its pointer and push it into destination
                        addDest(curIt, findIterator);
                        addDest(findIterator, curIt);
                        return true;
                    }
                    findIterator=findIterator->m_Next;
                } // airport doesnt exist, add it at the back
                CAirport* lastAirport=m_List;
                while(lastAirport->m_Next){
                    lastAirport=lastAirport->m_Next;
                }
                CAirport *temp=new CAirport(to);
                lastAirport->m_Next=temp;
                addDest(curIt, temp);
                addDest(temp, curIt);
                return true;
            }
            prevIt=curIt;
            curIt=curIt->m_Next; // move onto next
        }// at end, airport does not exist

        if(!addedFrom){
            CAirport *tempAdd = new CAirport(from);
            prevIt->m_Next= tempAdd;
            this->Add(from,to);
            return true;
        }
    }

    friend ostream & operator << (ostream & os, const CFlightList & src);
private:
    struct CAirport {
        static const int MAXSIZE = 100;
        CAirport(string Nm_Name) : m_Name(Nm_Name), m_Nr(0), m_Next(NULL) {};
        CAirport * m_Next;
        string m_Name;
        int m_Nr;
        CAirport * m_Dest [MAXSIZE];
    };
    bool addDest(CAirport* iterator, CAirport* dest);
    friend class CTester;
    CAirport * m_List;
};

ostream & operator << (ostream & os, const CFlightList & src) {
    for (CFlightList::CAirport * tmp = src.m_List; tmp; tmp = tmp->m_Next) {
        os << tmp->m_Name << "[" << tmp->m_Nr << "]:";
        for (int i=0; i!=tmp->m_Nr; i++) {
            os << tmp->m_Dest[i]->m_Name << "[" << tmp->m_Dest[i]->m_Nr << "]";
            os << ", ";
        }
        os << endl;
    }
    return os;
}

bool CFlightList::addDest(CFlightList::CAirport *iterator, CFlightList::CAirport *dest) {
    if(iterator->m_Nr==0){
        iterator->m_Dest[0]=dest;
        iterator->m_Nr++;
        return true;
    }
    iterator->m_Dest[iterator->m_Nr]=dest;
    iterator->m_Nr++;
    return false;
}

int main (){
    CFlightList f0;

    assert(f0.Add("Prague", "Berlin") == true);
    assert(f0.Add("Prague", "Berlin") == false);
    assert(f0.Add("Prague", "London") == true);
    assert(f0.Add("London", "Berlin") == true);
    assert(f0.Add("Berlin", "London") == false);
    assert(f0.Add("Berlin", "Berlin") == false);
    assert(f0.Add("New York", "Oslo") == true);

    cout << f0 << endl;
    /*
    Prague[2]:Berlin[2], London[2],
    Berlin[2]:Prague[2], London[2],
    London[2]:Prague[2], Berlin[2],
    New York[1]:Oslo[1],
    Oslo[1]:New York[1],
    */

    CFlightList f1 (f0);

    assert(f1.Add("Paris", "Wien") == true);

    cout << f0 << endl;
    /*
    Prague[2]:Berlin[2], London[2],
    Berlin[2]:Prague[2], London[2],
    London[2]:Prague[2], Berlin[2],
    New York[1]:Oslo[1],
    Oslo[1]:New York[1],
    */
    cout << f1 << endl;
    /*
    Prague[2]:Berlin[2], London[2],
    Berlin[2]:Prague[2], London[2],
    London[2]:Prague[2], Berlin[2],
    New York[1]:Oslo[1],
    Oslo[1]:New York[1],
    Paris[1]:Wien[1],
    Wien[1]:Paris[1],
    */
}