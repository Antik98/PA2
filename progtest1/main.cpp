#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG = 0x4d4d;
#endif /* __PROGTEST__ */
class CImage{
public:
    int delka;
    int sirka;
    enum endian_ {littleEndian, bigEndian};
    endian_ endian;
    int kanal;
    int bPerKanal;
};



bool printfile(CImage imgFile, string fileName){
    ifstream in;
    in.open(fileName,ios::binary);

    if (in.is_open()){

        //get the starting position
        streampos start = in.tellg();

        // go to the end
        in.seekg(0, ios::end);

        //get the ending position
        streampos end = in.tellg();

        //go back to the start
        in.seekg(0, ios::beg);

        //create a vecotr to hold the data that is resized to the total size of the file
        vector<char> contents;
        //read it in
        uint16_t hlavicka[4];
        in.read((char*)&hlavicka[0],8);

        int l=0;
        int tmp =0; //prvni 8 bitu pryc
        /*enum{littleEndian,bigEndian};
        int endian;
        int sirka;
        int delka;*/
        cout << "Size of image :" << dec << (end - start)-8 << endl;
        cout << "Type of endian: ";
        if(hlavicka[0] == ENDIAN_LITTLE) {
            cout << "Little Endian" << endl;
            imgFile.endian = CImage::littleEndian;
        }else{
            cout<< "Big Endian"<< endl;
            imgFile.endian = CImage::bigEndian;
        }

        if (imgFile.endian == CImage::littleEndian){
            imgFile.sirka=hlavicka[1];
            imgFile.delka=hlavicka[2];
        }else{
            imgFile.sirka=hlavicka[1]<<8;
            imgFile.delka=hlavicka[2]<<8;
        }
        cout << "Sirka : " << imgFile.sirka << endl;
        cout << "Delka: " << imgFile.delka<< endl;

        imgFile.kanal=hlavicka[3] & 0b11;
        imgFile.bPerKanal=(hlavicka[3] & 0b11100)>>2;
        if(hlavicka[3]&0b1111111111100000){
            cout<< "spatna hlavicka";
            return false;
        }

        switch(imgFile.kanal){
            case 0b00:
                imgFile.kanal=1;
                break;
            case 0b10:
                imgFile.kanal=3;
                break;
            case 0b11:
                imgFile.kanal=4;
                break;
            default:
                cout<<"chyba v kanalech";
                return false;
        }
        switch (imgFile.bPerKanal){
            case 0b000:
                imgFile.bPerKanal=1;
                break;
            case 0b011:
                imgFile.bPerKanal=8;
                break;
            case 0b100:
                imgFile.bPerKanal=16;
                break;
            default:
                cout<<"Chyba v bPerKanal" << endl;
                return false;
        }
        cout<< "Kanal: " << imgFile.kanal << endl;
        cout<< "bPerKanal: "<< imgFile.bPerKanal << endl;

        in.seekg(8,ios::beg);
        contents.resize(static_cast<size_t>((end - start)-8));
        in.read(&contents[0], contents.size());

        for(const char& c: contents){
            /*if (tmp == 8){
                cout<< "konec hlavicky" << endl << endl;
                l=0;
            }*/
            /*if(tmp<=8) {
                tmp++;
                continue;
            }*/
            //printbinchar(c);
            cout<<setw(2) << setfill('0') << hex<<(int)c;
            l++;
            tmp++;
            if(!(l%imgFile.sirka))
                putchar('\n');
            else{
                putchar(' ');
            }

        }
    }
    in.close();
    return true;

}


bool flipImage(const char *srcFileName,
               const char *dstFileName,
               bool flipHorizontal,
               bool flipVertical) {
    CImage imgFile;
    printfile(imgFile, srcFileName);
    return true;
}

void printbinchar(char c){
    for(int i=0; i<=5; i++){
        putchar( (1 & (c >> i)) ? '1' : '0' );
    }
    putchar(' ');
}
#ifndef __PROGTEST__

bool identicalFiles(const char *fileName1,
                    const char *fileName2) {
    // DIY
    return true;
}


int main(void) {
    flipImage ( "input_00.img", "output_00.img", true, false );

    /* assert ( flipImage ( "input_00.img", "output_00.img", true, false )
              && identicalFiles ( "output_00.img", "ref_00.img" ) );
     assert ( flipImage ( "input_01.img", "output_01.img", false, true )
              && identicalFiles ( "output_01.img", "ref_01.img" ) );
     assert ( flipImage ( "input_02.img", "output_02.img", true, true )
              && identicalFiles ( "output_02.img", "ref_02.img" ) );
     assert ( flipImage ( "input_03.img", "output_03.img", false, false )
              && identicalFiles ( "output_03.img", "ref_03.img" ) );
     assert ( flipImage ( "input_04.img", "output_04.img", true, false )
              && identicalFiles ( "output_04.img", "ref_04.img" ) );
     assert ( flipImage ( "input_05.img", "output_05.img", true, true )
              && identicalFiles ( "output_05.img", "ref_05.img" ) );
     assert ( flipImage ( "input_06.img", "output_06.img", false, true )
              && identicalFiles ( "output_06.img", "ref_06.img" ) );
     assert ( flipImage ( "input_07.img", "output_07.img", true, false )
              && identicalFiles ( "output_07.img", "ref_07.img" ) );
     assert ( flipImage ( "input_08.img", "output_08.img", true, true )
              && identicalFiles ( "output_08.img", "ref_08.img" ) );
     assert ( ! flipImage ( "input_09.img", "output_09.img", true, false ) );
     // extra inputs (optional & bonus tests)
     assert ( flipImage ( "extra_input_00.img", "extra_out_00.img", true, false )
              && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
     assert ( flipImage ( "extra_input_01.img", "extra_out_01.img", false, true )
              && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
     assert ( flipImage ( "extra_input_02.img", "extra_out_02.img", true, false )
              && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
     assert ( flipImage ( "extra_input_03.img", "extra_out_03.img", false, true )
              && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
     assert ( flipImage ( "extra_input_04.img", "extra_out_04.img", true, false )
              && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
     assert ( flipImage ( "extra_input_05.img", "extra_out_05.img", false, true )
              && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
     assert ( flipImage ( "extra_input_06.img", "extra_out_06.img", true, false )
              && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
     assert ( flipImage ( "extra_input_07.img", "extra_out_07.img", false, true )
              && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
     assert ( flipImage ( "extra_input_08.img", "extra_out_08.img", true, false )
              && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
     assert ( flipImage ( "extra_input_09.img", "extra_out_09.img", false, true )
              && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
     assert ( flipImage ( "extra_input_10.img", "extra_out_10.img", true, false )
              && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
     assert ( flipImage ( "extra_input_11.img", "extra_out_11.img", false, true )
              && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );*/
    return 0;
}

#endif /* __PROGTEST__ */