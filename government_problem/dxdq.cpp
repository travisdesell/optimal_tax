#include "stdafx.h"

double dxdq(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double terma = tot_inc - ( wage * ( time_endowment - c ) );
	double term1 = - 2 * A_2 * A_2 * b * cleanprice * cleanprice * cleanprice * wage;

	double term2a = ( - 2 * ag_exp ) + ( 2 * a * cleanprice ) + ( b * dirtyprice );
	double term2b = ag_exp - ( a * cleanprice ) + ( 2 * b * dirtyprice );
	double term2c = ( - B_3 * cleanprice * cleanprice * terma ) + ( 2 * B_2 * cleanprice * dirtyprice * terma );
	double term2 = ( wage * ( ( 2 * A_1 * dirtyprice * term2a ) + ( B_1 * cleanprice * term2b ) ) ) + term2c;

	double term3a = ( b * B_1 * B_1 * cleanprice * wage ) - ( A_1 * B_3 * cleanprice * terma );
	double term3b = ( A_1 * wage * ( ( a * cleanprice ) - ag_exp ) ) + ( B_2 * cleanprice * terma );
	double term3 = dirtyprice * dirtyprice * ( term3a + ( B_1 * term3b ) );

	double dxdq = ( term1 + ( A_2 * cleanprice * term2 ) - term3 ) / ( 2 * wage * den * den );
	return dxdq;
}