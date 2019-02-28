#include <iostream>
#include <algorithm>

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
void datePrint ( const Date & d )
{
	cout << d . day << ". " << d . month << ". " << d . year << endl;
}

/**
 * Compare two Date structures
 * @param[in] d1 Date structure
 * @param[in] d2 Date structure
 * @return true if d1 < d2, otherwise false
 */
bool dateCompare ( const Date & d1, const Date & d2 )
{
	// TODO
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
		datePrint( array[ i ] );

	#ifdef SHOW_SORTED

	cout << endl;

	sort( array, array + ARRAY_LEN, dateCompare );
	for ( size_t i = 0; i < ARRAY_LEN; ++i )
		datePrint( array[ i ] );

	#endif

	return 0;
}
