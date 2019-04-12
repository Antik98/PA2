//
//  main.cpp
//  Inheritance
//
//  Created by Petr Pauš on 16/04/2018.
//  Copyright © 2018 Petr Pauš. All rights reserved.
//

#include <iostream>
#include "classes.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    CCopier kopirka(1000,100, 555);
    kopirka.aboutMe();
    kopirka.copy();
    
    CLibrary knihovna(1001, 4, 2);
    knihovna.aboutMe();
    
    CCopier *ptr0 = new CCopier(1002, 100, 666);
    ptr0->aboutMe();
    ptr0->copy();
    CEquipment *ptr1 = new CCopier(1003, 100, 777);     //nelze pro normalni dedeni, pouze pro virtualni
                                                        //nelze delete bez virtualniho desctrutoru
    
    cout << "Equipment id: " << ptr1->getId() << endl;
    ptr1->aboutMe();
    //ptr1->scan();       //nelze;
    
    CPrinter *ptr2 = new CCopier(1004,200,999);
    ptr2->aboutMe();
    
    delete ptr0;
    delete ptr1;        //segfault (bez virtualniho destructoru), nutny polymorfizmus
    //delete ptr2;          // zase error;
    return 0;
}
