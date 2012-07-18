#include "stdafx.h"

double minor4(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double term1a = ( 4 * A_1 * A_2 * A_3 ) - ( A_3 * B_1 * B_1 ) - ( A_2 * B_2 * B_2 );
	double term1b = ( B_1 * B_2 * B_3 ) - ( A_1 * B_3 * B_3 );
	double term1 = term1a + term1b;

	double term2 = - B_1 * ( cleangood - a ) - B_3 * ( leisuregood - c ) - 2 * A_2 * ( dirtygood - b );
	double term3 = - 2 * A_1 * ( cleangood - a ) - B_1 * ( dirtygood - b ) - B_2 * ( leisuregood - c );
	double term4 = - B_2 * ( cleangood - a ) - B_3 * ( dirtygood - b ) - 2 * A_3 * ( leisuregood - c );

	double minor4 = 2 * term1 * ( ( dirtygood - b ) * term2 + ( cleangood - a ) * term3 + ( leisuregood - c ) * term4 );
	return minor4;
}

double minor3(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double term1a = 4 * A_1 * A_2 - B_1 * B_1;
	double term1b = -2 * A_1 * cleangood - B_2 * ( leisuregood - c );
	double term1c = B_1 * cleangood + B_3 * ( leisuregood - c );
	double term1 = a * term1a + 2 * A_2 * term1b + B_1 * term1c;

	double term2 = - 2 * A_1 * ( cleangood - a ) - B_1 * ( dirtygood - b ) - B_2 * ( leisuregood - c );
	double term3 = B_1 * ( cleangood - a ) + 2 * A_2 * ( dirtygood - b ) + B_3 * ( leisuregood - c );

	double term4a = - B_3 * ( leisuregood - c ) - 2 * A_2 * ( dirtygood - b );
	double term4b = B_1 * ( dirtygood - b ) + B_2 * ( leisuregood - c );
	double term4 = 2 * A_1 * term4a + B_1 * term4b;

	double minor3 = - term1 * term2 + term3 * term4;
	return minor3;
}

double minor2(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double term1 = - 2 * A_1 * ( cleangood - a );
	double term2 = - B_1 * ( dirtygood - b );
	double term3 = - B_2 * ( leisuregood - c );

	double minor2 = - ( term1 + term2 + term3 ) * ( term1 + term2 + term3 );
	return minor2;
}