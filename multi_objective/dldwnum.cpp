#include "stdafx.h"

double dldwnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dldw1a = ( A_3 * cleanprice ) - ( A_2 * dirtyprice );
	dldw1a *= dldw1a;
	double dldw1b = ( A_3 * cleanprice ) + ( A_2 * dirtyprice );
	double dldw1 = dldw1a * dldw1b * ( c - time_endowment );

	double dldw2a = - virtual_inc + ( a * cleanprice ) + ( b * dirtyprice );
	double dldw2 = A_1 * A_1 * A_1 * netwage * netwage * dldw2a;

	double dldw3a = ( A_3 * cleanprice ) + ( A_2 * dirtyprice );
	double dldw3b = ( 2 * virtual_inc ) - ( 2 * a * cleanprice ) - ( 2 * b * dirtyprice ) - ( netwage * ( time_endowment - c ) );
	double dldw3 = A_1 * A_1 * netwage * dldw3a * dldw3b;

	double dldw4a = - ( 3 * virtual_inc ) + ( 3 * a * cleanprice ) + ( 3 * b * dirtyprice ) - ( 2 * netwage * ( time_endowment - c ) );
	double dldw4 = 2 * A_2 * A_3 * cleanprice * dirtyprice * dldw4a;

	double dldw5a = - virtual_inc + ( a * cleanprice ) + ( b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dldw5 = A_3 * A_3 * cleanprice * cleanprice * dldw5a;

	double dldw6a = - virtual_inc + ( a * cleanprice ) + ( b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dldw6 = A_2 * A_2 * dirtyprice * dirtyprice * dldw6a;

	double dldwnum = A_1 * ( dldw1 + dldw2 + dldw3 + ( A_1 * ( dldw4 + dldw5 + dldw6 ) ) );
	return dldwnum;
}
