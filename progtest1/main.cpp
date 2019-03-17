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
    CImage();
    int vyska;
    int sirka;
    enum endian_ {littleEndian, bigEndian};
    endian_ endian;
    int kanal;
    int bPerKanal;
    vector<vector<uint64_t>> pole;
    uint16_t hlavicka[4];
};
CImage::CImage()
        :vyska(0),
         sirka(0),
         endian(littleEndian){
    for (int i = 0; i < 4 ; i++)
        hlavicka[i]=0;
}
void printImg(const CImage imgFile){
    int tmp=0;
    for(int i =0 ; i<imgFile.vyska;i++){
        for(int l=0;l<imgFile.sirka;l++){
            cout<<setw(2) << setfill('0') << hex <<(int)imgFile.pole[i][l];
            tmp++;
            if(!(tmp%imgFile.sirka))
                putchar('\n');
            else{
                putchar(' ');
            }
        }
    }
}
bool readFile(CImage &imgFile, const char* fileName){
    ifstream in;
    in.open(fileName,ios::binary);
    if(in.fail() || !fileName){
        return false;
    }

    if (in.is_open()){

        in.read((char*)&imgFile.hlavicka[0],8); // Reading 8 bytes of header

        cout << "Type of endian: ";                     // Parsing inputs of header
        if(imgFile.hlavicka[0] == ENDIAN_LITTLE) {
            cout << "Little Endian" << endl;
            imgFile.endian = CImage::littleEndian;
        }else if(imgFile.hlavicka[0]==ENDIAN_BIG){
            cout<< "Big Endian"<< endl;
            imgFile.endian = CImage::bigEndian;
        }else{
            cout<< "Chyba v endianu" << endl;
            return false;
        }

        if (imgFile.endian == CImage::littleEndian){
            imgFile.sirka=imgFile.hlavicka[1];
            imgFile.vyska=imgFile.hlavicka[2];
        }else{
            imgFile.sirka=(imgFile.hlavicka[1] & 0xFF00)>>8;
            imgFile.vyska=(imgFile.hlavicka[2] & 0xFF00)>>8;
        }
        cout << "Size of image :" << dec << imgFile.sirka*imgFile.vyska << endl;
        cout << "Sirka : " << imgFile.sirka << endl;
        cout << "Vyska: " << imgFile.vyska<< endl;
        uint16_t tmp;
        if(imgFile.endian==CImage::littleEndian){
            tmp = imgFile.hlavicka[3];
        }else{
            tmp = (imgFile.hlavicka[3] & 0xFF00)>>8;
        }

        imgFile.kanal=tmp & 0b11;
        imgFile.bPerKanal=(tmp & 0b11100)>>2;
        if(tmp &0b1111111111100000){
            cout<< "spatna imgFile.hlavicka";
            return false;
        }
        //Setting input as readable && ruling out invalid inputs
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


        imgFile.pole.resize(static_cast<uint64_t>(imgFile.vyska));//resizing based on picture
        for(int i=0;i<imgFile.vyska;i++){
            imgFile.pole[i].resize(static_cast<uint64_t>(imgFile.sirka));
        }

        in.seekg(8,ios::beg);                                // setting cursor after header
        for(int i =0 ; i<imgFile.vyska;i++){
            for(int l=0;l<imgFile.sirka;l++){
                if(!in.read((char*)&imgFile.pole[i][l],imgFile.bPerKanal/8*imgFile.kanal)){ // reading binary file into 2D array
                    return false;
                }
            }
        }
        printImg(imgFile);

        uint64_t tmpPixel; // checking for bytes of full read, potential error
        if(in.read((char*)&tmpPixel,1)){
            cout<< "Nasel se bit prevysujici pole"<< endl;
            return false;
        }
    }else{
        return false;
    }
    in.close();
    return true;
}

bool flipH(CImage *imgFile){
    /*cout<< "Pred flipem : "<< endl;   // debugging, printing file
    printImg(*imgFile);
    */
    int sirkaFlip=imgFile->sirka-1;
    int vyskaFlip= imgFile->vyska-1;
    if (sirkaFlip<0 || vyskaFlip<0){
        cout << "Error vyskaflip blbe" << endl;// potential error, perhaps img could be very small
        return false;
    }
    if(imgFile->vyska==0){
        return true;
    }
    for (int y = 0; y <imgFile->vyska; y++) {
        for (int x = 0; x < imgFile->sirka/2; x++) {
            uint64_t temp = imgFile->pole[y][x];
            imgFile->pole[y][x]=imgFile->pole[y][sirkaFlip-x];
            imgFile->pole[y][sirkaFlip-x]=temp;
        }
    }

    /*cout<< endl<< "Po flipu : "<< endl;
    printImg(*imgFile);
    cout<< endl<< "reference: "<< endl;

    CImage tmp;
    readFile(tmp, "ref_00.img");
    printImg(tmp);*/

    return true;
}
bool flipV(CImage *imgFile){

    int sirkaFlip=imgFile->sirka-1;
    int vyskaFlip= imgFile->vyska-1;
    if (sirkaFlip<0 || vyskaFlip<0){
        cout << "Error vyskaflip blbe" << endl;// potential error, perhaps img could be very small
        return false;
    }
    if(imgFile->sirka==0){
        return true;
    }
    for (int y = 0; y < imgFile->vyska/2; y++) {
        for (int x = 0; x < imgFile->sirka; x++) {
            uint64_t temp = imgFile->pole[y][x];
            imgFile->pole[y][x]=imgFile->pole[vyskaFlip-y][x];
            imgFile->pole[vyskaFlip-y][x]=temp;
        }
    }
    return true;
}
bool saveFile(CImage *imgFile, const char *dstFileName){
    ofstream outFile;
    outFile.open(dstFileName, ios::binary|ios::out);
    if(!outFile.good() || !dstFileName || !outFile) // possible not able to create file
        return false;

    for(int i =0 ; i< 4;i++) {
        outFile.write((char *) &imgFile->hlavicka[i], 2); // writing header
    }
    for(int i =0 ; i<imgFile->vyska;i++){
        for(int l=0;l<imgFile->sirka;l++){
            outFile.write((char*)&imgFile->pole[i][l], imgFile->kanal*imgFile->bPerKanal/8); // writing rest of image
        }
    }
    outFile.close();
    if(!outFile.good()){
        return false;
    }
    return true;
}

bool flipImage(const char *srcFileName,
               const char *dstFileName,
               bool flipHorizontal,
               bool flipVertical) {
    CImage imgFile;
    if(!srcFileName || !dstFileName){
        return false;
    }

    if(!readFile(imgFile, srcFileName)){
        return false;
    }
    if(flipHorizontal && !flipVertical){
        if(!flipH(&imgFile)) return false;
    }else if (!flipHorizontal && flipVertical){
        if(!flipV(&imgFile)) return false;
    }else if(flipHorizontal && flipVertical){
        if(!flipH(&imgFile)) return false;
        if(!flipV(&imgFile)) return false;
    }
    if(!saveFile(&imgFile,dstFileName)){
        return false;
    }
    return true;
}

#ifndef __PROGTEST__

bool identicalFiles(const char *fileName1,
                    const char *fileName2) {
    CImage input1;
    CImage input2;
    if(!readFile(input1, fileName1)){
        return false;
    }
    if(!readFile(input2, fileName2)){
        return false;
    }
    if ((input1.sirka!=input2.sirka)||(input1.vyska!=input2.vyska)){
        return false;
    }
    for(int i =0 ; i<input1.vyska;i++){
        for(int l=0;l<input1.sirka;l++){
            if(input1.pole[i][l]!=input2.pole[i][l]){
                return false;
            }
        }
    }
    return true;
}


int main(void) {

    assert ( flipImage ( "input_00.img", "output_00.img", true, false )
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

    /*// extra inputs (optional & bonus tests)
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
