#include "stdafx.h"

double mux(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c) {

	double mux = A_1 * ( dirtygood - b ) + A_2 * ( leisuregood - c );
	return mux;
}
