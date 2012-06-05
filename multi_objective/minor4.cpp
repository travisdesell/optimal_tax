#include "stdafx.h"

double minor4(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c) {

	double minor4a = a * ( ( A_2 * ( c - leisuregood ) ) + ( A_1 * ( b - dirtygood ) ) );
	double minor4b = A_3 * ( c - leisuregood ) * ( b - dirtygood );
	double minor4c = cleangood * ( ( - A_1 * b ) - ( A_2 * c ) + ( A_2 * leisuregood ) + ( A_1 * dirtygood ) );

	double minor4 = - 4 * A_1 * A_2 * A_3 * ( minor4a + minor4b + minor4c );
	return minor4;
}
