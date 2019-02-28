#include <iostream>
using namespace std;


int main() {
    int input1,radku, sloupcu;
    int** pole= nullptr;
    cout << "Vstup:" << endl;
    cin >> input1;
    if(!cin || input1<=0){
        cout << "Nevhodny vstup" << endl;
        return 1;
    }
    bool liche=false;
    int cursize = input1;
    pole = new int* [input1/2+1];
    for(int i = 0; i<input1/2 ; i++){

        if(i<0){
            cout << "Pozor zaporne pole" << endl;
            return 1;
        }

        pole[i]=new int[cursize];
        for (int l = 0 ; l<cursize ; l++){
            pole[i][l]=l;

            if(l<0){
                cout << "Pozor zaporne pole" << endl;
                return 1;
            }
        }
        cursize /=2;
    }
    cursize = input1;
    cout<< "Výstup:" << endl ;
    for(int d=0;d<input1/2;d++){


        if(d<0){
            cout << "Pozor zaporne pole" << endl;
            return 1;
        }


        for (int m=0; m<cursize;m++){


            if(m<0){
                cout << "Pozor zaporne pole" << endl;
                return 1;
            }


            cout<< pole[d][m];
            if(m+1 != cursize){
                cout<<",";
            }
        }
        cursize /=2;
        cout<<endl;
    }
    for(int d=0;d<input1/2;d++){
        delete pole[d];
    }
    delete pole;

    return 0;
}