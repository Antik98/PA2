#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "point.h"

/**
 * @brief The Rectangle class U dokumentace ke tride by mel byt popis toho co trida zvladne, k cemu je atp.
 */
class Rectangle
{
public:
    /**
     * @brief Rectangle Implicitni konstruktor vytvori obdelnik na pozici [0,0]
     * s nulovou vyskou a sirkou.
     */
           Rectangle();
    /**
     * @brief Rectangle Konstruktor s parametry
     * @param topLeft Pozice leveho horniho rohu
     * @param width Kladna sirka, jinak vyjimka (+ typ vyjimky)
     * @param height Kladna vyska, jinak vyjimka
     */
           Rectangle( Point topLeft, int width, int height );
    /**
     * @brief topLeft Getter i setter pro levy horni roh obdelnika
     * @return Reference na levy horni roh obdelnika
     */
    Point& topLeft();
    /**
     * @brief width Getter pro sirku
     * @return Sirka obdelnika
     */
    int    width() const;
    /**
     * @brief height Getter pro vysku
     * @return Vyska obdelnika
     */
    int    height() const;
    /**
     * @brief setWidth Setter pro sirku
     * @param width Nova sirka obdelnika
     * @return true pokud je nova hodnota kladna, jinak false
     */
    bool   setWidth( int width );
    /**
     * @brief setHeight Setter pro vysku
     * @param height Nova vyska obdelnika
     * @return true pokud je nova hodnota kladna, jinak false
     */
    bool   setHeight( int height );
    /**
     * @brief translate Posune obdelnik o offset
     * @param offset Posunuti obdelnika, muze mit zaporne hodnoty
     */
    void   translate( Point offset );

// private = kontrolovany pristup jen pres rozhrani,
// nikdo nam nebude menit interni stav pod rukama
// pokud nenapisu ani public ani private, pak ma trida vse private
private:
    // private polozky se obvykle nedokumentuji, ale mohou
    Point m_topLeft;
    int   m_width;
    int   m_height;
};

#endif // RECTANGLE_H
