#include "stdafx.h"

double dxdw(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den1 = ( B_3 * B_3 * cleanprice * cleanprice ) + ( 4 * A_3 * B_1 * cleanprice * dirtyprice ) - ( 4 * A_1 * A_3 * dirtyprice * dirtyprice );
	double den2 = ( B_2 * B_2 * dirtyprice * dirtyprice ) - ( 2 * B_1 * B_2 * dirtyprice * netwage ) + ( B_1 * B_1 * netwage * netwage );
	double den3 = ( B_2 * cleanprice * dirtyprice ) + ( B_1 * cleanprice * netwage ) - ( 2 * A_1 * dirtyprice * netwage );
	double den4 = ( A_3 * cleanprice * cleanprice ) + ( netwage * ( ( A_1 * netwage ) - ( B_2 * cleanprice ) ) );
	double den = den1 + den2 - ( 2 * B_3 * den3 ) - ( 4 * A_2 * den4 );

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

	double dwterm1 = ( 4 * A_1 * B_3 * dirtyprice ) + ( 2 * B_1 * B_1 * netwage );
	double dwterm2 = ( B_3 * cleanprice ) + ( B_2 * dirtyprice );
	double dwterm3 = ( B_2 * cleanprice ) - ( 2 * A_1 * netwage );
	double dwterm = dwterm1 - ( 2 * B_1 * dwterm2 ) + ( 4 * A_2 * dwterm3 );

	double dxdwterm1 = ( 2 * A_3 * B_1 * virtual_inc * dirtyprice ) + ( 2 * a * A_3 * B_1 * cleanprice * dirtyprice ) - ( 4 * a * A_1 * A_3 * dirtyprice * dirtyprice );
	double dxdwterm2 = ( - 2 * A_3 * b * B_1 * dirtyprice * dirtyprice ) + ( a * B_2 * B_2 * dirtyprice * dirtyprice ) - ( 4 * a * B_1 * B_2 * dirtyprice * netwage );
	double dxdwterm3 = ( 4 * A_3 * B_1 * dirtyprice * netwage * ( time_endowment - c ) ) + ( 3 * a * B_1 * B_1 * netwage * netwage );
	double dxdwterm4a = virtual_inc - ( b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dxdwterm4 = B_3 * B_3 * cleanprice * dxdwterm4a;
	double dxdwterm5a = virtual_inc + ( a * cleanprice ) - ( b * dirtyprice ) + ( 2 * netwage * ( time_endowment - c ) );
	double dxdwterm5b1 = ( 2 * virtual_inc ) + ( 2 * a * cleanprice ) - ( 2 * b * dirtyprice ) + ( 3 * netwage * ( time_endowment - c ) );
	double dxdwterm5b = ( - 8 * a * A_1 * dirtyprice ) + ( B_1 * dxdwterm5b1 );
	double dxdwterm5 = ( B_2 * dirtyprice * dxdwterm5a ) + ( netwage * dxdwterm5b );
	double dxdwterm6a = - 4 * A_3 * cleanprice * dxdwterm4a;
	double dxdwterm6b = ( - 6 * a * A_1 * netwage ) + ( B_2 * dxdwterm5b1 );
	double dxdwterm6 = dxdwterm6a + ( 2 * netwage * dxdwterm6b );
	double dxdwterm = dxdwterm1 + dxdwterm2 + dxdwterm3 + dxdwterm4 - ( B_3 * dxdwterm5 ) + ( A_2 * dxdwterm6 );

	double dxdw = ( ( - netwage * dwterm * dxterm ) - ( den * dxterm ) + ( cleanprice * netwage * den * dxdwterm ) ) / ( cleanprice * netwage * netwage * den * den );
	return dxdw;
}