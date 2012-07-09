#include "stdafx.h"

double muy(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c) {

	double muy = A_1 * ( cleangood - a ) + A_3 * ( leisuregood - c );
	return muy;
}