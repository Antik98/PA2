#include "rectangle.h"
#include <stdexcept>


Rectangle::Rectangle():
    Rectangle({0,0},0,0) // delegace konstruktoru, proc psat jednu vec desetkrat...
{
}
/*---------------------------------------------------*/
Rectangle::Rectangle(Point topLeft, int width, int height):
    m_topLeft(topLeft),
    m_width(width),
    m_height(height)
{
    if( m_width < 0 || m_height < 0 )
    {
        // bud vyhozeni vyjimky
        throw std::invalid_argument("Negative width or height received.");
        // nebo defaultni hodnoty
        //m_width = m_height = 0;
        /* hypoteticky lze nastavit nejakou interni promennou,
           ktera znaci objekt v nevalidnim stavu, ale pak je potreba to
           pri kazde praci s objektem kontrolovat a reagovat na to */
    }

}
/*---------------------------------------------------*/
Point &Rectangle::topLeft()
{
    return m_topLeft;
}
/*---------------------------------------------------*/
int Rectangle::width() const
{
    return m_width;
}
/*---------------------------------------------------*/
int Rectangle::height() const
{
    return m_height;
}
/*---------------------------------------------------*/
bool Rectangle::setWidth(int width)
{
    if( width < 0 )
        return false;
    m_width = width;
    return true;
}
/*---------------------------------------------------*/
bool Rectangle::setHeight( int height )
{
    if( height < 0 )
        return false;
    m_height = height;
    return true;
}
/*---------------------------------------------------*/
void Rectangle::translate( Point offset )
{
    // na dalsim cviceni uvidite jak udelat, aby fungovalo
    // m_topLeft + offset
    m_topLeft.x() += offset.x();
    m_topLeft.y() += offset.y();
}
/*---------------------------------------------------*/
