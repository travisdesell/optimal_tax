#include "stdafx.h"

double dxdp(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den1 = ( B_3 * B_3 * cleanprice * cleanprice ) + ( 4 * A_3 * B_1 * cleanprice * dirtyprice ) - ( 4 * A_1 * A_3 * dirtyprice * dirtyprice );
	double den2 = ( B_2 * B_2 * dirtyprice * dirtyprice ) - ( 2 * B_1 * B_2 * dirtyprice * netwage ) + ( B_1 * B_1 * netwage * netwage );
	double den3 = ( B_2 * cleanprice * dirtyprice ) + ( B_1 * cleanprice * netwage ) - ( 2 * A_1 * dirtyprice * netwage );
	double den4 = ( A_3 * cleanprice * cleanprice ) + ( netwage * ( ( A_1 * netwage ) - ( B_2 * cleanprice ) ) );
	double den = den1 + den2 - ( 2 * B_3 * den3 ) - ( 4 * A_2 * den4 );

	double dpterm1 = ( 2 * B_3 * B_3 * cleanprice ) + ( 4 * A_3 * B_1 * dirtyprice );
	double dpterm2 = ( B_2 * dirtyprice ) + ( B_1 * netwage );
	double dpterm3 = ( - 8 * A_3 * cleanprice ) + ( 4 * B_2 * netwage );
	double dpterm = dpterm1 - ( 2 * B_3 * dpterm2 ) + ( A_2 * dpterm3 );

	double dxterm1a = ( B_3 * cleanprice ) + ( B_2 * dirtyprice ) - ( B_1 * netwage );
	double dxterm1 = ( - 2 * A_3 * cleanprice * dirtyprice ) + ( netwage * dxterm1a );
	double dxterm2a = cleanprice * ( ( 2 * A_2 * b ) + ( a * B_1 ) + ( B_3 * c ) );
	double dxterm2b = - dirtyprice * ( ( 2 * a * A_1 ) + ( b * B_1 ) + ( B_2 * c ) );
	double dxterm2c = ( ( B_3 * cleanprice ) - ( B_2 * dirtyprice ) ) * ( ( netwage * time_endowment ) + virtual_inc );
	double dxterm2 = - netwage * ( dxterm2a + dxterm2b ) + dxterm2c;
	double dxterm3 = ( B_2 * dirtyprice * dirtyprice ) - ( B_3 * cleanprice * dirtyprice ) + ( 2 * A_2 * cleanprice * netwage ) - ( B_1 * dirtyprice * netwage );
	double dxterm4a = 2 * A_3 * cleanprice * ( ( netwage * ( time_endowment - c ) ) + virtual_inc );
	double dxterm4b = ( 2 * a * A_1 * netwage ) - ( b * B_3 * cleanprice ) + ( b * B_1 * netwage );
	double dxterm4c = ( a * cleanprice ) + ( netwage * ( time_endowment - c ) ) + virtual_inc;
	double dxterm4 = dxterm4a + ( netwage * ( dxterm4b - ( B_2 * dxterm4c ) ) );
	double dxterm = ( dxterm1 * dxterm2 ) - ( dxterm3 * dxterm4 );

	double term1 = ( - b * dirtyprice ) + virtual_inc + ( netwage * ( time_endowment - c ) );
	double term2 = ( 2 * a * cleanprice ) - ( b * dirtyprice ) + virtual_inc + ( netwage * ( time_endowment - c ) );

	double dxdp1 = ( 2 * A_3 * B_1 * virtual_inc * dirtyprice ) + ( 4 * a * A_3 * B_1 * cleanprice * dirtyprice ) - ( 4 * a * A_1 * A_3 * dirtyprice * dirtyprice );
	double dxdp2 = ( - 2 * A_3 * b * B_1 * dirtyprice * dirtyprice ) + ( a * B_2 * B_2 * dirtyprice * dirtyprice ) - ( 2 * a * B_1 * B_2 * dirtyprice * netwage );
	double dxdp3 = ( 2 * A_3 * B_1 * dirtyprice * netwage * ( time_endowment - c ) ) + ( a * B_1 * B_1 * netwage * netwage );
	double dxdp4 = 2 * B_3 * B_3 * cleanprice * term1;
	double dxdp5 = B_3 * ( - B_2 * dirtyprice * term2 + ( netwage * ( ( 4 * a * A_1 * dirtyprice ) - ( B_1 * term2 ) ) ) );
	double dxdp6 = 2 * A_2 * ( ( 4 * A_3 * cleanprice * term1 ) + ( netwage * ( ( 2 * a * A_1 * netwage ) - ( B_2 * term2 ) ) ) );
	double dxdpterm = dxdp1 + dxdp2 + dxdp3 + dxdp4 + dxdp5 - dxdp6;
	
	double dxdp = ( - ( cleanprice * dpterm * dxterm ) - ( den * dxterm ) + ( cleanprice * netwage * den * dxdpterm ) ) / ( cleanprice * cleanprice * netwage * den * den );
	return dxdp;
}