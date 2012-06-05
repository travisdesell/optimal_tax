#include "stdafx.h"

double dldqnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dldq1 = ( A_3 * cleanprice ) - ( A_1 * netwage );
	dldq1 = - b * dldq1 * dldq1 * dldq1;

	double dldq2a = - virtual_inc + ( a * cleanprice ) - ( netwage * ( time_endowment - c ) );
	double dldq2 = A_2 * A_2 * A_2 * dirtyprice * dirtyprice * dldq2a;

	double dldq3a = - ( 2 * virtual_inc ) + ( 2 * a * cleanprice ) + ( 3 * b * dirtyprice ) - ( 2 * netwage * ( time_endowment - c ) );
	double dldq3 = A_3 * cleanprice * dldq3a;

	double dldq4a = ( 2 * virtual_inc ) - ( 2 * a * cleanprice ) + ( b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dldq4 = A_1 * netwage * dldq4a;

	double dldq5 = A_2 * ( ( A_3 * cleanprice ) - ( A_1 * netwage ) );

	double dldq6a = virtual_inc - ( a * cleanprice ) + ( 2 * b * dirtyprice ) + ( netwage * (time_endowment - c ) );
	double dldq6 = A_1 * netwage * dldq6a;

	double dldq7a = ( 3 * virtual_inc ) - ( 3 * a * cleanprice ) - ( 2 * b * dirtyprice ) + ( 3 * netwage * ( time_endowment - c ) );
	double dldq7 = A_3 * cleanprice * dldq7a;

	double dldqnum = - A_1 * ( dldq1 + dldq2 + ( A_2 * A_2 * dirtyprice * ( dldq3 + dldq4 ) ) + ( dldq5 * ( dldq6 + dldq7 ) ) );
	return dldqnum;
}