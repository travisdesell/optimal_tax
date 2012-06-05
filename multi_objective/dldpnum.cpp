#include "stdafx.h"

double dldpnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dldp1 = ( A_2 * dirtyprice ) - ( A_1 * netwage );
	dldp1 = - a * dldp1 * dldp1 * dldp1;

	double dldp2a = - virtual_inc + ( b * dirtyprice ) - ( netwage * ( time_endowment - c ) );
	double dldp2 = A_3 * A_3 * A_3 * cleanprice * cleanprice * dldp2a;

	double dldp3a = - ( 2 * virtual_inc ) + ( 3 * a * cleanprice ) + ( 2 * b * dirtyprice ) - ( 2 * netwage * ( time_endowment - c ) );
	double dldp3 = A_2 * dirtyprice * dldp3a;

	double dldp4a = ( 2 * virtual_inc ) + ( a * cleanprice ) - ( 2 * b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dldp4 = A_1 * netwage * dldp4a;

	double dldp5 = A_3 * ( ( A_2 * dirtyprice ) - ( A_1 * netwage ) );

	double dldp6a = virtual_inc + ( 2 * a * cleanprice ) - ( b * dirtyprice ) + ( netwage * ( time_endowment - c ) );
	double dldp6 = A_1 * netwage * dldp6a;

	double dldp7a = ( 3 * virtual_inc ) - ( 2 * a * cleanprice ) - ( 3 * b * dirtyprice ) + ( 3 * netwage * ( time_endowment - c ) );
	double dldp7 = A_2 * dirtyprice * dldp7a;

	double dldpnum = - A_1 * ( dldp1 + dldp2 + ( A_3 * A_3 * cleanprice * ( dldp3 + dldp4 ) ) + ( dldp5 * ( dldp6 + dldp7 ) ) );
	return dldpnum;
}