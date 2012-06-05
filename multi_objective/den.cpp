#include "stdafx.h"

double den(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double den1 = A_3 * A_3 * cleanprice * cleanprice;
	double den2 = ( A_2 * dirtyprice ) - ( A_1 * netwage );
	den2 *= den2;
	double den3 = - 2 * A_3 * cleanprice * ( ( A_2 * dirtyprice ) + ( A_1 * netwage ) );

	double den = ( den1 + den2 + den3 );
	den *= den;

	return den;
}