
using namespace std;

#include "cshop.h"

void showList ( const list< pair<int,int> > & l )
{
   for(list<pair<int,int> >::const_iterator it = l . begin (); it != l . end (); ++it )
    cout << it -> first << " Kc " << it -> second << 'x' << endl;
}

int main(int argc, char *argv[])
{
  CShop  s;
  bool   ok;
  int    price;

  s.Buy("Pila",300,10);
  s.Buy("Kladivo",100,20);
  s.Buy("Hrebiky",150,15);
  s.Buy("Pila",500,3);
  s.Buy("Kladivo",80,14);
  s.Buy("Pila",100,10);
  s.Buy("Kladivo",120,4);
  s.Buy("Vrtak",1,5000);
  s.Buy("Kladivo",100,4);
  s.Buy("Kladivo",80,10);

  showList(s.List ( "Pila" ));
  cout << endl;
/*

  ok = s.Sell ( "Pila", 5, price );
  cout << "ok:" <<ok << " cena:" << price << endl;
  showList(s.List ( "Pila" ));
  cout << endl;

  ok = s.Sell ( "Pila", 10, price );
  cout << "ok:" <<ok << " cena:" << price << endl;
  showList(s.List ( "Pila" ));
  cout << endl;

  ok = s.Sell ( "Hrebiky", 20, price );
  cout << "ok:" <<ok << " cena:" << price << endl;

  ok = s.Sell ( "Pripinacek", 100, price );
  cout << "ok:" <<ok << " cena:" << price << endl;

  showList(s.List ( "Pila" ));
  cout << endl;

  ok = s.Sell ( "Hrebiky", 20, price );
  cout << "ok:" <<ok << " cena:" << price << endl;
  cout << endl;
  showList(s.List ( "Hrebiky" ) );
  cout << endl;
  showList (s.List ( "Kladivo" ) );
*/

  return EXIT_SUCCESS;
}
