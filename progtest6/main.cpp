#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;
#endif /* __PROGTEST__ */
class CComponent{
public:
    virtual ostream& print(ostream& os){}
};

class CComputer{
public:
    CComputer(string name) : pcName(name){};
    CComputer& AddAddress(string addr){
            pcAddr.push_back(addr);
            return *this;
    }
    template<typename T>
    CComputer& AddComponent(T comp){
        compV.push_back(make_unique<T>(comp));
        return *this;
    }
    string pcName;
    list<string> pcAddr;
    vector<unique_ptr<CComponent>> compV;
};
class CNetwork {
public:
    CNetwork & AddComputer(const CComputer & inpComputer){
        pcM.insert(make_pair(inpComputer.pcName,inpComputer));
        return *this;
    }
    CNetwork(string inp) : netName(inp){}
private:
    string netName;
    map<string,CComputer> pcM;
};

class CCPU : public CComponent {
public:
    CCPU(){}
    CCPU(int cores, int mhz) : cores(cores), speed(mhz){}
    ostream& print(ostream& os) const {
        os<< "CPU, "<< cores <<" cores @ "<< speed <<"MHz";
        return os;
    }
private:
    int cores;
    int speed;

};
class CMemory : public CComponent{
public:
    CMemory(int inpS):size(inpS){}
    virtual ostream& print(ostream& os){
        os<< "Memory, "<< size <<" MiB";
        return os;
    }
private:
    int size;

};

class CDisk : public CComponent{
public:
    static int const MAGNETIC = 1;
    static int const SSD = 2;
    CDisk (int typeI, int size) : size(size){
        if(typeI == 1){
            isMagnetic=true;
        }else{
            isMagnetic=false;
        }
    }
    CDisk & AddPartition(int size, string dir){
        partitV.emplace_back(make_pair(size,dir));
        return *this;
    }
private:
    bool isMagnetic;
    int size;
    vector<pair<int,string>> partitV;
};

#ifndef __PROGTEST__
template<typename _T>
string toString ( const _T & x )
{
    ostringstream oss;
    oss << x;
    return oss . str ();
}

int main ( void )
{
    CNetwork n ( "FIT network" );
    n . AddComputer (
            CComputer ( "progtest.fit.cvut.cz" ) .
                    AddAddress ( "147.32.232.142" ) .
                    AddComponent ( CCPU ( 8, 2400 ) ) .
                    AddComponent ( CCPU ( 8, 1200 ) ) .
                    AddComponent ( CDisk ( CDisk::MAGNETIC, 1500 ) . AddPartition ( 50, "/" ) . AddPartition ( 5, "/boot" ). AddPartition ( 1000, "/var" ) ) .
                    AddComponent ( CDisk ( CDisk::SSD, 60 ) . AddPartition ( 60, "/data" )  ) .
                    AddComponent ( CMemory ( 2000 ) ).
                    AddComponent ( CMemory ( 2000 ) ) ) .
            AddComputer (
            CComputer ( "edux.fit.cvut.cz" ) .
                    AddAddress ( "147.32.232.158" ) .
                    AddComponent ( CCPU ( 4, 1600 ) ) .
                    AddComponent ( CMemory ( 4000 ) ).
                    AddComponent ( CDisk ( CDisk::MAGNETIC, 2000 ) .
                    AddPartition ( 100, "/" )   .
                    AddPartition ( 1900, "/data" ) ) ) .
            AddComputer (
            CComputer ( "imap.fit.cvut.cz" ) .
                    AddAddress ( "147.32.232.238" ) .
                    AddComponent ( CCPU ( 4, 2500 ) ) .
                    AddAddress ( "2001:718:2:2901::238" ) .
                    AddComponent ( CMemory ( 8000 ) ) );
    assert ( toString ( n ) ==
             "Network: FIT network\n"
             "+-Host: progtest.fit.cvut.cz\n"
             "| +-147.32.232.142\n"
             "| +-CPU, 8 cores @ 2400MHz\n"
             "| +-CPU, 8 cores @ 1200MHz\n"
             "| +-HDD, 1500 GiB\n"
             "| | +-[0]: 50 GiB, /\n"
             "| | +-[1]: 5 GiB, /boot\n"
             "| | \\-[2]: 1000 GiB, /var\n"
             "| +-SSD, 60 GiB\n"
             "| | \\-[0]: 60 GiB, /data\n"
             "| +-Memory, 2000 MiB\n"
             "| \\-Memory, 2000 MiB\n"
             "+-Host: edux.fit.cvut.cz\n"
             "| +-147.32.232.158\n"
             "| +-CPU, 4 cores @ 1600MHz\n"
             "| +-Memory, 4000 MiB\n"
             "| \\-HDD, 2000 GiB\n"
             "|   +-[0]: 100 GiB, /\n"
             "|   \\-[1]: 1900 GiB, /data\n"
             "\\-Host: imap.fit.cvut.cz\n"
             "  +-147.32.232.238\n"
             "  +-2001:718:2:2901::238\n"
             "  +-CPU, 4 cores @ 2500MHz\n"
             "  \\-Memory, 8000 MiB\n" );
    CNetwork x = n;
    auto c = x . FindComputer ( "imap.fit.cvut.cz" );
    assert ( toString ( *c ) ==
             "Host: imap.fit.cvut.cz\n"
             "+-147.32.232.238\n"
             "+-2001:718:2:2901::238\n"
             "+-CPU, 4 cores @ 2500MHz\n"
             "\\-Memory, 8000 MiB\n" );
    c -> AddComponent ( CDisk ( CDisk::MAGNETIC, 1000 ) .
            AddPartition ( 100, "system" ) .
            AddPartition ( 200, "WWW" ) .
            AddPartition ( 700, "mail" ) );
    assert ( toString ( x ) ==
             "Network: FIT network\n"
             "+-Host: progtest.fit.cvut.cz\n"
             "| +-147.32.232.142\n"
             "| +-CPU, 8 cores @ 2400MHz\n"
             "| +-CPU, 8 cores @ 1200MHz\n"
             "| +-HDD, 1500 GiB\n"
             "| | +-[0]: 50 GiB, /\n"
             "| | +-[1]: 5 GiB, /boot\n"
             "| | \\-[2]: 1000 GiB, /var\n"
             "| +-SSD, 60 GiB\n"
             "| | \\-[0]: 60 GiB, /data\n"
             "| +-Memory, 2000 MiB\n"
             "| \\-Memory, 2000 MiB\n"
             "+-Host: edux.fit.cvut.cz\n"
             "| +-147.32.232.158\n"
             "| +-CPU, 4 cores @ 1600MHz\n"
             "| +-Memory, 4000 MiB\n"
             "| \\-HDD, 2000 GiB\n"
             "|   +-[0]: 100 GiB, /\n"
             "|   \\-[1]: 1900 GiB, /data\n"
             "\\-Host: imap.fit.cvut.cz\n"
             "  +-147.32.232.238\n"
             "  +-2001:718:2:2901::238\n"
             "  +-CPU, 4 cores @ 2500MHz\n"
             "  +-Memory, 8000 MiB\n"
             "  \\-HDD, 1000 GiB\n"
             "    +-[0]: 100 GiB, system\n"
             "    +-[1]: 200 GiB, WWW\n"
             "    \\-[2]: 700 GiB, mail\n" );
    assert ( toString ( n ) ==
             "Network: FIT network\n"
             "+-Host: progtest.fit.cvut.cz\n"
             "| +-147.32.232.142\n"
             "| +-CPU, 8 cores @ 2400MHz\n"
             "| +-CPU, 8 cores @ 1200MHz\n"
             "| +-HDD, 1500 GiB\n"
             "| | +-[0]: 50 GiB, /\n"
             "| | +-[1]: 5 GiB, /boot\n"
             "| | \\-[2]: 1000 GiB, /var\n"
             "| +-SSD, 60 GiB\n"
             "| | \\-[0]: 60 GiB, /data\n"
             "| +-Memory, 2000 MiB\n"
             "| \\-Memory, 2000 MiB\n"
             "+-Host: edux.fit.cvut.cz\n"
             "| +-147.32.232.158\n"
             "| +-CPU, 4 cores @ 1600MHz\n"
             "| +-Memory, 4000 MiB\n"
             "| \\-HDD, 2000 GiB\n"
             "|   +-[0]: 100 GiB, /\n"
             "|   \\-[1]: 1900 GiB, /data\n"
             "\\-Host: imap.fit.cvut.cz\n"
             "  +-147.32.232.238\n"
             "  +-2001:718:2:2901::238\n"
             "  +-CPU, 4 cores @ 2500MHz\n"
             "  \\-Memory, 8000 MiB\n" );
    return 0;
}
#endif /* __PROGTEST__ */
