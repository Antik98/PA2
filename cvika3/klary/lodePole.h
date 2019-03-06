//
// Created by phamducm on 3/6/19.
//

class lodePole {
public:
    lodePole(int x, int y);
    ~lodePole();
    void printPole () const;
private:
    int sirka;
    int delka;
    int** more;
};

using namespace std;
lodePole::lodePole(int x, int y) {
    int** pole=new int* [x];
    enum{voda,potopenaLod,lod};
    this->delka = x;
    this->sirka = y;
    for (int i =0;i<x;i++){
        pole[i]= new int[y];
    }
    for(int i = 0; i<x;i++){
        for (int l=0;l<y;l++){
            pole[i][l]=voda;
        }
    }
    this->more=pole;
}
void lodePole::printPole() const {
    for(int i = 0; i<this->delka;i++){
        for (int l=0;l<this->sirka;l++){
            std::cout << this->more[i][l];
        }
        std::cout<< endl;
    }
}
lodePole::~lodePole() {
    for (int i=0; i< this->delka;i++){
        delete[] this->more[i];
    }
    delete[] this->more;
}

