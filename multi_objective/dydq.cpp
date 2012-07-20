#include "stdafx.h"

double dydq(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den1 = ( B_3 * B_3 * cleanprice * cleanprice ) + ( 4 * A_3 * B_1 * cleanprice * dirtyprice ) - ( 4 * A_1 * A_3 * dirtyprice * dirtyprice );
	double den2 = ( B_2 * B_2 * dirtyprice * dirtyprice ) - ( 2 * B_1 * B_2 * dirtyprice * netwage ) + ( B_1 * B_1 * netwage * netwage );
	double den3 = ( B_2 * cleanprice * dirtyprice ) + ( B_1 * cleanprice * netwage ) - ( 2 * A_1 * dirtyprice * netwage );
	double den4 = ( A_3 * cleanprice * cleanprice ) + ( netwage * ( ( A_1 * netwage ) - ( B_2 * cleanprice ) ) );
	double den = den1 + den2 - ( 2 * B_3 * den3 ) - ( 4 * A_2 * den4 );

	double dqterm1 = ( 2 * B_2 * B_2 * dirtyprice ) + ( 4 * A_1 * B_3 * netwage );
	double dqterm2 = ( B_1 * cleanprice ) - ( 2 * A_1 * dirtyprice );
	double dqterm3 = ( B_3 * cleanprice ) + ( B_1 * netwage );
	double dqterm = dqterm1 + ( 4 * A_3 * dqterm2 ) - ( 2 * B_2 * dqterm3 );

	double dyterm1 = ( b * B_3 * B_3 * cleanprice * cleanprice ) + ( 2 * A_1 * B_3 * virtual_inc * netwage ) - ( 2 * a * A_1 * B_3 * cleanprice * netwage );
	double dyterm2 = ( - 2 * b * B_1 * B_3 * cleanprice * netwage ) + ( 2 * A_1 * b * B_3 * dirtyprice * netwage ) - ( 4 * A_1 * A_2 * b * netwage * netwage );
	double dyterm3 = ( b * B_1 * B_1 * netwage * netwage ) + ( 2 * A_1 * B_3 * netwage * netwage * ( time_endowment - c ) );
	double dyterm4a = virtual_inc - ( a * cleanprice ) + ( netwage * ( time_endowment - c ) );
	double dyterm4 = B_2 * B_2 * dirtyprice * dyterm4a;
	double dyterm5a1 = virtual_inc - ( a * cleanprice ) + ( b * dirtyprice ) + ( netwage * ( time_endowment - c ) );
	double dyterm5a = B_1 * cleanprice * dyterm5a1;
	double dyterm5b = ( A_2 * b * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dyterm4a );
	double dyterm5 = dyterm5a - ( 2 * dyterm5b );
	double dyterm6a = B_3 * cleanprice * dyterm5a1;
	double dyterm6b = ( - 4 * A_2 * b * cleanprice ) + ( B_1 * dyterm5a1 );
	double dyterm6 = dyterm6a + ( netwage * dyterm6b );
	double dyterm = dyterm1 + dyterm2 + dyterm3 + dyterm4 + ( 2 * A_3 * dyterm5 ) - ( B_2 * dyterm6 );

	double dydqterm1 = virtual_inc - ( a * cleanprice ) + ( netwage * ( time_endowment - c ) );
	double dydqterm2a = ( B_3 * cleanprice ) + ( B_1 * netwage );
	double dydqterm2 = ( 2 * A_3 * b * B_1 * cleanprice ) - ( b * B_2 * dydqterm2a );
	double dydqterm3 = ( 2 * b * B_3 * netwage ) - ( 4 * A_3 * dydqterm1 );
	double dydqterm = dydqterm2 + ( B_2 * B_2 * dydqterm1 ) + ( A_1 * dydqterm3 );

	double dydq = ( ( den * dydqterm ) - ( dqterm * dyterm ) ) / ( den * den );
	return dydq;
}