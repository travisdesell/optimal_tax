#include "stdafx.h"

double dydqnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dydq1a = ( A_3 * cleanprice ) - ( A_1 * netwage );
	dydq1a *= dydq1a;
	double dydq1b = ( A_3 * cleanprice ) + ( A_1 * netwage );
	double dydq1 = b * dydq1a * dydq1b;

	double dydq2a = - virtual_inc + ( a * cleanprice ) - ( netwage * ( time_endowment - c ) );
	double dydq2 = A_2 * A_2 * A_2 * dirtyprice * dirtyprice * dydq2a;

	double dydq3a = ( 2 * virtual_inc ) - ( 2 * a * cleanprice ) + ( b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dydq3b = ( A_3 * cleanprice ) + ( A_1 * netwage );
	double dydq3 = A_2 * A_2 * dirtyprice * dydq3a * dydq3b;

	double dydq4a = - ( 3 * virtual_inc ) + ( 3 * a * cleanprice ) + ( 2 * b * dirtyprice ) - ( 3 * netwage * ( time_endowment - c ) );
	double dydq4 = 2 * A_1 * A_3 * cleanprice * netwage * dydq4a;

	double dydq5a = - virtual_inc + ( a * cleanprice ) - ( 2 * b * dirtyprice ) - ( netwage * ( time_endowment - c ) );
	double dydq5 = A_3 * A_3 * cleanprice * cleanprice * dydq5a;

	double dydq6a = - virtual_inc + ( a * cleanprice ) - ( 2 * b * dirtyprice ) - ( netwage * ( time_endowment - c ) );
	double dydq6 = A_1 * A_1 * netwage * netwage * dydq6a;

	double dydqnum = A_2 * ( dydq1 + dydq2 + dydq3 + ( A_2 * ( dydq4 + dydq5 + dydq6 ) ) );
	return dydqnum;
}