#ifndef POINT_H
#define POINT_H


class Point
{
private:
    int m_x;
    int m_y;
public:
    Point();
    // vyzkousejte co provede
    // explicit Point();
    Point( int x, int y);
    // klicovym slovem default explicitne rikame kompilatoru, ze chceme aby vytvoril trivialni dtor
    ~Point() = default;

    // reference mi umozni souradnici rovnou menit,
    // nepotrebuji specialni setter (pouze pokud nepotrbuji kontrolovat nastavenou hodnotu!)
    int& x();
    int& y();

    // pokud mam "const Point p" pak se vola tato verze,
    // musi byt zaruceno, ze nemeni interni stav tridy, proto ma na konci hlavicky const
    // vracet zde referenci je zbytecne, nicmene pro slozitejsi objekty nez je "int" je lepsi predavat referenci
    const int& x() const;
    const int& y() const;
};

#endif // POINT_H
