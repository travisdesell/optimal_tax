#include "stdafx.h"

double dxdpnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dxdp1a = ( A_2 * dirtyprice ) - ( A_1 * netwage );
	dxdp1a *= dxdp1a;
	double dxdp1b = ( A_2 * dirtyprice ) + ( A_1 * netwage );
	double dxdp1 = a * dxdp1a * dxdp1b;

	double dxdp2a = ( netwage * ( c - time_endowment ) ) - virtual_inc + ( b * dirtyprice );
	double dxdp2 = A_3 * A_3 * A_3 * cleanprice * cleanprice * dxdp2a;

	double dxdp3a = ( A_2 * dirtyprice ) + ( A_1 * netwage );
	double dxdp3b = ( 2 * virtual_inc ) + ( a * cleanprice ) - ( 2 * b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dxdp3 = A_3 * A_3 * cleanprice * dxdp3a * dxdp3b;

	double dxdp4a = - ( 3 * virtual_inc ) + ( 2 * a * cleanprice ) + ( 3 * b * dirtyprice ) - ( 3 * netwage * ( time_endowment - c ) );
	double dxdp4 = 2 * A_1 * A_2 * dirtyprice * netwage * dxdp4a;

	double dxdp5a = - virtual_inc - ( 2 * a * cleanprice ) + ( b * dirtyprice ) - ( netwage * ( time_endowment - c ) );
	double dxdp5 = A_2 * A_2 * dirtyprice * dirtyprice * dxdp5a;

	double dxdp6a = - virtual_inc - ( 2 * a * cleanprice ) + ( b * dirtyprice ) - ( netwage * ( time_endowment - c ) );
	double dxdp6 = A_1 * A_1 * netwage * netwage * dxdp6a;

	double dxdpnum = A_3 * ( dxdp1 + dxdp2 + dxdp3 + ( A_3 * ( dxdp4 + dxdp5 + dxdp6 ) ) );
	return dxdpnum;
}
