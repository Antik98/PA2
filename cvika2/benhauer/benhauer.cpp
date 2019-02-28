#include <iostream>
#include <algorithm>
#include "datePrint.h"
using namespace std;

struct Date
{
	int year,
	    month,
	    day;
};

/**
 * Function print the date in format DD. MM. YYYY passed as argument.
 * @param[in] d Date to be printed.
 */
// void datePrint ( const Date & d )
// {
// 	cout << d . day << ". " << d . month << ". " << d . year << endl;
// }

/**
 * Compare two Date structures
 * @param[in] d1 Date structure
 * @param[in] d2 Date structure
 * @return true if d1 < d2, otherwise false
 */
bool dateCompare ( const Date & d1, const Date & d2 )
{
	if(d1.year==d2.year){
        if(d1.month==d2.month){
            if(d1.day>=d2.day){
                return 0;
            }else{
                return 1;
            }
        }else if(d1.month>d2.month){
            return 1;
        }else{
            return 0;
        }
    }else if(d1.year>d2.year){
        return 1;
    }else{
        return 0;
    }
}

int main ()
{
	static const size_t ARRAY_LEN = 5;
	Date array [ ARRAY_LEN ] = {
		Date { 1901, 1, 23 },
		Date { 1900, 2, 23 },
		Date { 1900, 1, 24 },
		Date { 1901, 2, 23 },
		Date { 1900, 1, 23 }
	};

	for ( size_t i = 0; i < ARRAY_LEN; ++i )
		Date::print( array[ i ] );

	#ifdef SHOW_SORTED

	cout << endl;

	sort( array, array + ARRAY_LEN, dateCompare );
	for ( size_t i = 0; i < ARRAY_LEN; ++i )
		Date::print( array[ i ] );

	#endif

	return 0;
}
