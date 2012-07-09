#include "stdafx.h"

double dydpnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dydp1 = ( A_2 * dirtyprice ) - ( A_1 * netwage );
	dydp1 = a * dydp1 * dydp1 * dydp1;

	double dydp2a = - virtual_inc + ( b * dirtyprice ) + ( netwage * ( c - time_endowment ) );
	double dydp2 = A_3 * A_3 * A_3 * cleanprice * cleanprice * dydp2a;

	double dydp3 = A_3 * ( ( A_2 * dirtyprice ) - ( A_1 * netwage ) );

	double dydp4a = - ( 3 * virtual_inc ) + ( 2 * a * cleanprice ) + ( 3 * b * dirtyprice ) - ( 3 * netwage * ( time_endowment - c ) );
	double dydp4 = A_1 * netwage * dydp4a;

	double dydp5a = - virtual_inc - ( 2 * a * cleanprice ) + ( b * dirtyprice ) - ( netwage * ( time_endowment - c ) );
	double dydp5 = A_2 * dirtyprice * dydp5a;

	double dydp6a = - ( 2 * virtual_inc ) + ( 3 * a * cleanprice ) + ( 2 * b * dirtyprice ) - ( 2 * netwage * ( time_endowment - c ) );
	double dydp6 = A_1 * netwage * dydp6a;

	double dydp7a = ( 2 * virtual_inc ) + ( a * cleanprice ) - ( 2 * b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dydp7 = A_2 * dirtyprice * dydp7a;

	double dydpnum = - A_2 * ( dydp1 + dydp2 + ( dydp3 * ( dydp4 + dydp5 ) ) + ( A_3 * A_3 * cleanprice * ( dydp6 + dydp7 ) ) );
	return dydpnum;
}

