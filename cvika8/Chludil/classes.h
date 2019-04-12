#ifndef classes_h
#define classes_h

#include <cstdlib>
#include <iostream>

using namespace std;
class CEquipment
{
  int m_id;
public:
  CEquipment(int id):m_id(id) 
  { cout << "Vytvoreno CEquipment(" << id << ");"<<endl; };
  int getId() {return m_id;};
  virtual void aboutMe() 
  { cout << "Ja jsem CEquipment, id="<<m_id<<endl; };
  virtual ~CEquipment() { cout << "CEquipment konci" << endl;};
};

class CFurniture: public CEquipment
{
protected:
  int m_legs;
public:
  CFurniture(int id, int legs):CEquipment(id),m_legs(legs)
  { cout << "CFurniture("<<id<< ", " <<legs<< ");"<<endl;};
   int getLegs() { return m_legs; };
   void aboutMe() 
  { cout << "Ja jsem CFurniture, id="<<getId()<< ", legs="<<m_legs<< endl; }; 
  ~CFurniture() { cout << "CFurniture konci" << endl;};
};

class CLibrary: public CFurniture
{
  int m_shelves;
public:
  CLibrary(int id, int legs, int shelves)
    :CFurniture(id, legs),m_shelves(shelves)
  { cout << "CLibrary("<<id<< ", " <<legs<< ", " << shelves<<");"<<endl;};
  int getShelves() {return m_shelves;};
  void aboutMe() 
  { cout << "Ja jsem CLibrary, id="<<getId()<< ", legs="<<m_legs<< ", shelves="<< m_shelves<< endl; }; 
  ~CLibrary() { cout << "CLibrary konci" << endl;};
};


#endif
