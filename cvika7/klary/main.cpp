#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Monster{
public:
    Monster(string nameInp, int heads, int clawDmg)
        :name(nameInp),
        heads_count(heads),
        claw_damage(clawDmg){
    }
    virtual int Attack(){
        return Monster::claw_damage;
    };
    virtual void Cut(){
        heads_count--;
    };
    virtual ostream& Print(ostream& os) const{
        os<< "Jmeno prisery: " << name << endl << "Pocet Hlav: " << heads_count << endl << "Sila drapu: "<< claw_damage << endl;
        return os;
    };
    friend ostream& operator<< (ostream& os, const Monster&tmp){
        return tmp.Print(os);
    };
protected:
    string name;
    int heads_count;
    int claw_damage;
};

class Dragon : public Monster {
public:
    Dragon(string nameInp, int heads, int clawDmg, int flameDmg) : flame_damage(flameDmg), Monster(nameInp, heads, clawDmg) {}
     // Damage of a flame from one head. To get total damage, multiply this by // number of heads.
    int Attack(){
      int x = Monster::claw_damage+(Monster::heads_count*flame_damage);
      return x;
    };
    ostream& Print(ostream& os){
        Monster::Print(os);
        os << "Ohen dmg: " << flame_damage<< endl;
        return os;
    }
private:
    int flame_damage;
};

class Hydra : public Monster{
public:
    Hydra( const string nameInp, int heads, int clawDmg, int headFac) : head_cut_factor(headFac), Monster(nameInp, heads, clawDmg) {}
    void Cut(){
        Monster::heads_count--;
        Monster::heads_count+=head_cut_factor;
    }
    ostream& Print(ostream& os){
        Monster::Print(os);
        os << "Faktor hlav: " << head_cut_factor<< endl;
        return os;
    }
private:
    int head_cut_factor; // Number of heads that will grow when one head is cutted ------- look at this atrocity, off.
};


int main() {
    Hydra hydra("hydra", 5, 1000, 2); // name, heads_count, claw_damage, head_cut_factor
    Dragon dragon("dragon", 3, 5000, 200); //  name, heads_count, claw_damage, flame_damage

    // A
 cout<<dragon.Attack()<<endl; // 5600
 cout<<hydra.Attack()<<endl; // 1000

    // B
 hydra.Cut();
 dragon.Cut();
 cout<<hydra.Attack()<<endl;  // 1000
 cout<<dragon.Attack()<<endl; // 5400

    // C
 cout<<hydra<<endl;
 cout<<dragon<<endl;

    // D
    vector<Monster*> pole;
    pole.push_back( new Hydra( "Hydra1" , rand()%500, rand()%500000, rand()%50000000) );// name, heads_count, claw_damage, head_cut_factor)
    pole.push_back( new Hydra( "Dragon1" , rand()%500, rand()%500000, rand()%50) );
    pole.push_back( new Hydra( "Dragon2" , rand()%500, rand()%500000, rand()%50) );
    pole.push_back( new Hydra( "Hydra2" , rand()%500, rand()%500000, rand()%50) );
    pole.push_back( new Hydra( "Hydra3" , rand()%500, rand()%500000, rand()%50) );
    pole.push_back( new Hydra( "Dragon3" , rand()%500, rand()%500000, rand()%50) );
    pole.push_back( new Hydra( "Dragon4" , rand()%500, rand()%500000, rand()%50) );
    for( const Monster* content : pole ){
        cout << *content;
    }
    for( const Monster* content : pole ){
        delete content;
    }
    // Create vector of monsters.
    // Insert some hydras and dragons into the vector.
    // Print all monsters in the vector.
}