#include "stdafx.h"

double dxdqnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dxdq1 = ( A_3 * cleanprice ) - ( A_1 * netwage );
	dxdq1 = b * dxdq1 * dxdq1 * dxdq1;

	double dxdq2a = - virtual_inc + ( a * cleanprice ) + ( netwage * ( c - time_endowment ) );
	double dxdq2 = A_2 * A_2 * A_2 * dirtyprice * dirtyprice * dxdq2a;

	double dxdq3 = A_2 * ( ( A_3 * cleanprice ) - ( A_1 * netwage ) );

	double dxdq4a = - ( 3 * virtual_inc ) + ( 3 * a * cleanprice ) + ( 2 * b * dirtyprice ) - ( 3 * netwage * ( time_endowment - c ) );
	double dxdq4 = A_1 * netwage * dxdq4a;

	double dxdq5a = - virtual_inc + ( a * cleanprice ) - ( 2 * b * dirtyprice ) - ( netwage * ( time_endowment - c ) );
	double dxdq5 = A_3 * cleanprice * dxdq5a;

	double dxdq6a = - ( 2 * virtual_inc ) + ( 2 * a * cleanprice ) + ( 3 * b * dirtyprice ) - ( 2 * netwage * ( time_endowment - c ) );
	double dxdq6 = A_1 * netwage * dxdq6a;

	double dxdq7a = ( 2 * virtual_inc ) - ( 2 * a * cleanprice ) + ( b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dxdq7 = A_3 * cleanprice * dxdq7a;

	double dxdqnum = - A_3 * ( dxdq1 + dxdq2 + ( dxdq3 * ( dxdq4 + dxdq5 ) ) + ( A_2 * A_2 * dirtyprice * ( dxdq6 + dxdq7 ) ) );
	return dxdqnum;
}