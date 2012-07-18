#include "stdafx.h"

double mux(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double term1 = 2 * A_1 * ( cleangood - a );
	double term2 = B_1 * ( dirtygood - b );
	double term3 = B_2 * ( leisuregood - c );

	double mux = term1 + term2 + term3;
	return mux;
}

double muy(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double term1 = 2 * A_2 * ( dirtygood - b );
	double term2 = B_1 * ( cleangood - a );
	double term3 = B_3 * ( leisuregood - c );

	double muy = term1 + term2 + term3;
	return muy;
}

double mul(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double term1 = 2 * A_3 * ( leisuregood - c );
	double term2 = B_2 * ( cleangood - a );
	double term3 = B_3 * ( dirtygood - b );

	double mul = term1 + term2 + term3;
	return mul;
}