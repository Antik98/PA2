#include <iostream>
#include <string>
using namespace std;
int main() {
    string s[100];
    int i = 0;
         while(getline(cin,s[i++]))
         {
          if(!(cin.good()))
              return 34;
         }

    for(int l=0;l<=i;l++){
        cout << s[l] << " - " << l << endl;

    }
    return 0;
}