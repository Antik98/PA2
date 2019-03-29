#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <cassert>

using namespace std;

void task_1() {
    string guests_names = "Peter Joan Nancy Thomas Joan Charlie Charlie Charlie Hannah";
    // Creating stream of names so you can use it in a similar way as if the names are written in stdin.
    stringstream names_stream(guests_names);
    string name;
    set <string> guests;
    // Example of work with stringstream. Remember that this stream can be read only
    // once!!! (e.g. you should delete this while cycle or do something useful in it).
    while (names_stream >> name) {
        cout << name << endl;
        guests.insert(name);

    }
    // TODO: Count how many guests are on the party.
    int number_of_guests=guests.size();
    assert(number_of_guests==6);
}


void task_2() {
    set<string> guests = {"Joan", "Peter", "Augustin", "Mark", "Elizabeth"};
    vector<string> long_names;
    const int long_name_threshold = 6;  // Names at least this long are considered to be
    // "long names".
    long int numLongNames=count_if(guests.begin(), guests.end(),[](string tmp) {
        return (tmp.size() > long_name_threshold);
    });
    long_names.resize(numLongNames);

    copy_if(guests.begin(), guests.end(),long_names.begin(), [](string tmp){
       return (tmp.size()>long_name_threshold);
    });

    // TODO: Use copy_if with lambda function to get all long names
    // TIP: First count how many names will be long (with count_if) and resize the vector to this size.

    // long_names should contain "Augustin" and "Elizabeth".
}


void task_3() {
    // Records of points awarded during contests.
    vector<pair<string, int>> records = {{"Ada",   5},
                                         {"Mark",  2},
                                         {"Tomas", 7},
                                         {"Tomas", 2},
                                         {"Ada",   1},
                                         {"Mark",  6},
                                         {"Mark",  7},
                                         {"Tomas", 2},
                                         {"Ada",   4},
                                         {"Mark",  2}};

    // Example work with vector of pairs:
    map<string, int> tmp;
    for (const auto &record: records) {  // & to avoid unnecessary copying.
        cout << record.first << ": " << record.second << endl;
        auto key = tmp.find(record.first);
        if(key == tmp.end()){
           tmp.insert(record);
        }else{
            key->second+= record.second;
        }

    }

    // TODO: Find out who earned the most points.
    // It should be Mark, because he has 17 points in total.
}


void task_4() {
    vector<string> guests = {"aDA", "mARK", "tHOMAS", "aUGUSTIN"};

    // TODO: With function "transform" rewrite names.

    // Guests should contain "Ada", "Mark", "Thomas" and "Augustin".
}


void task_5() {

    // vector<???> records;
    // TODO: Fill records with values, eg.
    //      "John", 46.2, 'A'
    //      "Mary", 76.2, 'B'
    //      "Elizabeth", 36.2, 'A'
    //      "Jean", 47.2, 'C'

    // TODO: Print the records.

}


void task_6() {
    vector<int> best_smiles = {1, 4, 5, 1, 4, 6, 7, 4}; // Participants with the best
    // smiles

    // TODO: Pick participants for the next round (duplicities) in linear time (you can
    //  use different containers).

    // Participants for the next round should be numbers 1 and 4
}

//
//  /*TODO*/ quot_and_rem(int a, int b){
//    return /*TODO*/;
//  }

void task_7() {
    int q, r;
//    /*TODO*/  = quot_and_rem(10, 3);
    // assert (q==3 && r==1)
    // q = a / b
    // r = a % b
}

int main() {
    task_1();
    task_2();
    task_3();
    /*task_4();
    task_5();
    task_6();
    task_7();*/
    return 0;
}