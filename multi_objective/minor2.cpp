#include "stdafx.h"

double minor2(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c) {

	double minor2 = ( A_2 * ( c - leisuregood ) ) + ( A_1 * ( b - dirtygood ) );
	minor2 = - minor2 * minor2;
	return minor2;
}