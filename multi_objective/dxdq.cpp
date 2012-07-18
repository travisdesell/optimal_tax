#include "stdafx.h"

double dxdq(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

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

	double dqterm1 = ( 2 * B_2 * B_2 * dirtyprice ) + ( 4 * A_1 * B_3 * netwage );
	double dqterm2 = ( B_1 * cleanprice ) - ( 2 * A_1 * dirtyprice );
	double dqterm3 = ( B_3 * cleanprice ) + ( B_1 * netwage );
	double dqterm = dqterm1 + ( 4 * A_3 * dqterm2 ) - ( 2 * B_2 * dqterm3 );

	double dxdqterm1a = ( b * B_3 * cleanprice ) - ( 4 * a * A_1 * netwage ) - ( b * B_1 * netwage );
	double dxdqterm1 = ( - 2 * a * B_2 * B_2 * dirtyprice ) + ( B_3 * dxdqterm1a );
	double dxdqterm2a = ( 2 * A_2 * b * cleanprice ) - ( 4 * a * A_1 * dirtyprice );
	double dxdqterm2b = virtual_inc + ( a * cleanprice ) - ( 2 * b * dirtyprice ) + ( netwage * ( time_endowment - c ) );
	double dxdqterm2 = dxdqterm2a + ( B_1 * dxdqterm2b );
	double dxdqterm3a = ( A_2 * b ) + ( a * B_1 );
	double dxdqterm3 = ( 2 * netwage * dxdqterm3a ) + ( B_3 * dxdqterm2b );
	double dxdqterm = dxdqterm1 - ( 2 * A_3 * dxdqterm2 ) + ( B_2 * dxdqterm3 );

	double dxdq = - ( ( cleanprice * netwage * ( den * dxdqterm ) ) + ( dqterm * dxterm ) ) / ( cleanprice * netwage * den * den );
	return dxdq;
}