/*!!!!!!!!!!!!!!!!!!!!!!!!!!!! NASTAVENI BONUSOVYHCH VYPISU!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//#define PRINT_DETAIL
#include "Povolani.h"

/*#include "Kejklir.h"
#include "Zved.h"
#include "Valecnik.h"
#include "Alchymista.h"
#include "Carodej.h"
#include "Mag.h"
#include "Hranicar.h"
#include "Lupic.h"
#include "Druid.h"
#include "Saman.h"
#include "Vedmak.h"*/

#include <iostream>

/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
/* VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV */
/*
 * ladici vzpisy:
		#ifndef PRINT_DETAIL
		std::cout << "Zarikavac::Mystika() " << std::endl;
		#endif
 *
 *  vypisy jsou schvalne tupe, aby definovaly vnitrni metody
 *
 *
 * z duvodu kratkosti jsou tridy implememntovany jen v *.h
 * ==> MAIN INFO na (+) je dole
 */

int main()
{
    Bojovnik * B = new Bojovnik(3);
    std::cout << "Mystika:   " << B->Mystika()				<< std::endl;
    std::cout << "Boj:       " << B->BojNaBlizko()			<< std::endl;
    std::cout << "Strelba:   " << B->BojNaDalku_strelba()	<< std::endl;
    std::cout << "Vrh:       " << B->BojNaDalku_vrh()		<< std::endl;
    std::cout << "Smlouvani: " << B->Smlouvani()			<< std::endl;

    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl << std::endl;
//
//    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!BONUSOVY OBSAH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//    Lovec * L = new Lovec(4);
//    L->print();
//    std::cout << "Mystika:   " << L->Mystika()				<< std::endl;
//    std::cout << "Boj:       " << L->BojNaBlizko()			<< std::endl;
//    std::cout << "Strelba:   " << L->BojNaDalku_strelba()	<< std::endl;
//    std::cout << "Vrh:       " << L->BojNaDalku_vrh()		<< std::endl;
//    std::cout << "Smlouvani: " << L->Smlouvani()			<< std::endl;
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl << std::endl;
//
//    Mastickar * M = new Mastickar(5);
//    M->print();
//    std::cout << "Mystika:   " << M->Mystika()				<< std::endl;
//    std::cout << "Boj:       " << M->BojNaBlizko()			<< std::endl;
//    std::cout << "Strelba:   " << M->BojNaDalku_strelba()	<< std::endl;
//    std::cout << "Vrh:       " << M->BojNaDalku_vrh()		<< std::endl;
//    std::cout << "Smlouvani: " << M->Smlouvani()			<< std::endl;
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl << std::endl;
//
//    Zarikavac * Z = new Zarikavac(5);
//    Z->print();
//    std::cout << "Mystika:   " << Z->Mystika()				<< std::endl;
//    std::cout << "Boj:       " << Z->BojNaBlizko()			<< std::endl;
//    std::cout << "Strelba:   " << Z->BojNaDalku_strelba()	<< std::endl;
//    std::cout << "Vrh:       " << Z->BojNaDalku_vrh()		<< std::endl;
//    std::cout << "Smlouvani: " << Z->Smlouvani()			<< std::endl;
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl << std::endl;
//
//    Kejklir * K = new Kejklir(3);
//    K->print();
//    std::cout << "Mystika:   " << K->Mystika()				<< std::endl;
//    std::cout << "Boj:       " << K->BojNaBlizko()			<< std::endl;
//    std::cout << "Strelba:   " << K->BojNaDalku_strelba()	<< std::endl;
//    std::cout << "Vrh:       " << K->BojNaDalku_vrh()		<< std::endl;
//    std::cout << "Smlouvani: " << K->Smlouvani()			<< std::endl;
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl;
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl;
//
//    Bojovnik	B2(3);
//    Lovec		L2(1);
//
//    Povolani  druzina2[5];
//    druzina2[0] = B2;
//    druzina2[1] = L2;
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl;
//
//    std::cout << std::endl << "vypis cyklem 1:      " << std::endl << std::endl;
//
//    for (int i = 0; i < 2; i++)
//        druzina2[i].print();
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl;
//
//    Povolani * druzina[5];
//    druzina[0] = B;
//    druzina[1] = L;
//    druzina[2] = M;
//    druzina[3] = K;
//    druzina[4] = Z;
//
//    std::cout << std::endl << "vypis cyklem 2:      " << std::endl << std::endl;
//
//    for (int i = 0; i < 5; i++)
//        druzina[i]->print();
//
//    for (int i = 0; i < 5; i++)
//        std::cout << "uroven mystiky " << i << "-te postavy: " << druzina[i]->Mystika() << std::endl;
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl;
//
//    std::cout << std::endl << "vypis cyklem 3:      " << std::endl << std::endl;
//
//    for (int i = 0; i < 5; i++)
//        std::cout << *druzina[i] << "," << druzina[i]->BojNaBlizko() << "*" << std::endl;
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl;
//
//    std::cout << "test vypisy: " << std::endl  << std::endl;
//    B->print();
//    std::cout << "---------------------" << std::endl;
//    druzina[0]->print();
//    std::cout << "---------------------" << std::endl;
//    std::cout << *B << std::endl;
//    std::cout << "---------------------" << std::endl;
//    std::cout << B << std::endl;
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl;
//
//
///* !!!!!!!!!!!!!!!!!!!!!!!!!!!!BONUSOVY OBSAH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
///* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
///* VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV */
///* CVIKO+ */
//
//
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl;
//    std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl;
//    Alchymista * RL = new Alchymista(8, 5, 5);
//    RL->print();
//    std::cout << "Mystika:            " << RL->Mystika()				<< std::endl;
//    std::cout << "Boj:                " << RL->BojNaBlizko()			<< std::endl; /* tady bude problem :)*/
//    std::cout << "Strelba:            " << RL->BojNaDalku_strelba()		<< std::endl;
//    std::cout << "Vrh:                " << RL->BojNaDalku_vrh()			<< std::endl;
//    std::cout << "Smlouvani:          " << RL->Smlouvani()				<< std::endl;
//    std::cout << "Alchymie:           " << RL->Alchymie()				<< std::endl;
//    std::cout << "Ozivovani golemu	  " << RL->OzivovaniGolemu()		<< std::endl;
//
//
//    //std::cout << std::endl << "/*--------------------------------------------------*/: " << std::endl << std::endl;
//
//    Carodej * GB = new Carodej(6, 4, 5);
//    GB->print();
//    std::cout << "Mystika:            " << GB->Mystika()				<< std::endl;
//    std::cout << "Boj:                " << GB->BojNaBlizko()			<< std::endl;
//    std::cout << "Strelba:            " << GB->BojNaDalku_strelba()		<< std::endl;
//    std::cout << "Vrh:                " << GB->BojNaDalku_vrh()			<< std::endl;
//    std::cout << "Smlouvani:          " << GB->Smlouvani()				<< std::endl;
//    std::cout << "Magie Ohne:         " << GB->MagieOhne()				<< std::endl;
//    std::cout << "Magie Vetru:        " << GB->MagieVetru()				<< std::endl;
//
//
//dalsu moznosti rozsireni (+/2):
//1) Virtualni metody povolani (=>*pln�* zvirtualizovat!)
//2) Abstraktni metody
//      - jak to udelat s return 0 metodami?
//	  - nechybi v navrhu neco?
//3) Polymorfni struktura v postave na ukladani mno�iny povolani
//4) Vyjimka pri chybnem pokusu o vytvoreni povolani s Ur1+Ur2 < 5
//
//
//testovaci postavy:
//Postava * AntonSpelec		= new Postava(L);
//
//Postava * GandalfBily		= new Postava(Zarikavac(5), Bojovnik(5), Carodej(5));
//
//Postava * BarbarConan		= new Postava(K , Bojovnik(5), Valecnik(5, K, Bojovnik(5)));
//
//Postava * BroukPytlik		= new Postava(Bojovnik(1), Lovec(1), Zarikavac(1), Mastickar(2), Kejklir(1));
//
//Postava * ErrorErrorovic	= new Postava(Alchymista(5,1,1));
//




    return 0;
}