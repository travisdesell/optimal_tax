#include "stdafx.h"

double dxdwnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dxdw1a = ( A_3 * cleanprice ) - ( A_2 * dirtyprice );
	dxdw1a = dxdw1a * dxdw1a * dxdw1a;
	double dxdw1 = ( c - time_endowment ) * dxdw1a;

	double dxdw2a = - virtual_inc + ( a * cleanprice ) + ( b * dirtyprice );
	double dxdw2 = A_1 * A_1 * A_1 * netwage * netwage * dxdw2a;

	double dxdw3a = - ( 2 * virtual_inc ) + ( 2 * a * cleanprice ) + ( 2 * b * dirtyprice ) - ( 3 * netwage * ( time_endowment - c ) );
	double dxdw3 = A_2 * dirtyprice * dxdw3a;

	double dxdw4a = ( 2 * virtual_inc ) - ( 2 * a * cleanprice ) - ( 2 * b * dirtyprice ) - ( netwage * ( time_endowment - c ) );
	double dxdw4 = A_3 * cleanprice * dxdw4a;

	double dxdw5 = A_1 * ( ( A_3 * cleanprice ) - ( A_2 * dirtyprice ) );

	double dxdw6a = - ( 3 * virtual_inc ) + ( 3 * a * cleanprice ) + ( 3 * b * dirtyprice ) - ( 2 * netwage * ( time_endowment - c ) );
	double dxdw6 = A_2 * dirtyprice * dxdw6a;

	double dxdw7a = - virtual_inc + ( a * cleanprice ) + ( b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dxdw7 = A_3 * cleanprice * dxdw7a;

	double dxdwnum = - A_3 * ( dxdw1 + dxdw2 + ( A_1 * A_1 * netwage * ( dxdw3 + dxdw4 ) ) + ( dxdw5 * ( dxdw6 + dxdw7 ) ) );
	return dxdwnum;
}