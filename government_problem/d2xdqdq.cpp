#include "stdafx.h"

double d2xdqdq(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double terma = B_2 * cleanprice * ( tot_inc - ( wage * ( time_endowment - c ) ) );
	double termb = B_3 * cleanprice * ( tot_inc - ( wage * ( time_endowment - c ) ) );

	double term1a = ( 2 * a * A_1 * cleanprice ) - ( 2 * A_1 * ag_exp ) - ( b * B_1 * cleanprice ) + ( 6 * A_1 * b * dirtyprice );
	double term1 = A_2 * A_2 * cleanprice * cleanprice * cleanprice * ( ( wage * term1a ) + terma );

	double term2a = ( b * B_1 * B_1 * cleanprice * wage ) - ( A_1 * termb );
	double term2b = ( A_1 * wage * ( ( a * cleanprice ) - ag_exp ) ) + terma;
	double term2 = A_1 * dirtyprice * dirtyprice * dirtyprice * ( term2a + ( B_1 * term2b ) );
	
	double term3a = B_1 * B_1 * cleanprice * cleanprice * wage * ( ( a * cleanprice ) - ag_exp );
	double term3b = 3 * A_1 * dirtyprice * wage * ( ag_exp - ( a * cleanprice ) + ( b * dirtyprice ) ) + ( cleanprice * termb );
	double term3c1 = 2 * A_1 * wage * ( ( - 3 * ag_exp ) + ( 3 * a * cleanprice ) + ( b * dirtyprice ) );
	double term3c = ( - 3 * cleanprice * termb ) + ( dirtyprice * ( term3c1 + 3 * terma ) );
	double term3 = A_2 * cleanprice * ( term3a + ( B_1 * cleanprice * term3b ) + ( A_1 * dirtyprice * term3c ) );

	double d2xdqdq = ( term1 + term2 - term3 ) / ( wage * den * den * den );
	return d2xdqdq;
}