#include "stdafx.h"

double dydwnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dydw1a = ( A_3 * cleanprice ) - ( A_2 * dirtyprice );
	dydw1a = - dydw1a * dydw1a * dydw1a;
	double dydw1 = ( c - time_endowment ) * dydw1a;

	double dydw2a = - virtual_inc + ( a * cleanprice ) + ( b * dirtyprice );
	double dydw2 = A_1 * A_1 * A_1 * netwage * netwage * dydw2a;

	double dydw3a = - ( 2 * virtual_inc ) + ( 2 * a * cleanprice ) + ( 2 * b * dirtyprice ) - ( 3 * netwage * ( time_endowment - c ) );
	double dydw3 = A_3 * cleanprice * dydw3a;

	double dydw4a = ( 2 * virtual_inc ) - ( 2 * a * cleanprice ) - ( 2 * b * dirtyprice ) - ( netwage * ( time_endowment - c ) );
	double dydw4 = A_2 * dirtyprice * dydw4a;

	double dydw5 = A_1 * ( ( A_3 * cleanprice ) - ( A_2 * dirtyprice ) );

	double dydw6a = - ( 3 * virtual_inc ) + ( 3 * a * cleanprice ) + ( 3 * b * dirtyprice ) - ( 2 * netwage * ( time_endowment - c ) );
	double dydw6 = A_3 * cleanprice * dydw6a;

	double dydw7a = - virtual_inc + ( a * cleanprice ) + ( b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dydw7 = A_2 * dirtyprice * dydw7a;

	double dydwnum = - A_2 * ( dydw1 + dydw2 + ( A_1 * A_1 * netwage * ( dydw3 + dydw4 ) ) - ( dydw5 * ( dydw6 + dydw7 ) ) );
	return dydwnum;
}