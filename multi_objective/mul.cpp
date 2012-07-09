#include "stdafx.h"

double mul(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c) {

	double mul = A_2 * ( cleangood - a ) + A_3 * ( dirtygood - b );
	return mul;
}