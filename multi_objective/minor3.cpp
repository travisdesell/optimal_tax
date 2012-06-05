#include "stdafx.h"

double minor3(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c) {

	double minor3a = ( a * A_1 ) + ( A_3 * ( c - leisuregood ) ) - ( A_1 * cleangood );
	double minor3b = ( A_2 * ( c - leisuregood ) ) + ( A_1 * ( b - dirtygood ) );
	
	double minor3 = 2 * A_1 * minor3a * minor3b;
	return minor3;
}