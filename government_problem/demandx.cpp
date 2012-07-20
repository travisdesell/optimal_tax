#include "stdafx.h"

double demandx(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double term1a = 2 * A_2 * cleanprice * ( ag_exp - ( b * dirtyprice ) );
	double term1b = 2 * a * A_1 * dirtyprice;
	double term1c = ag_exp + ( a * cleanprice ) - ( b * dirtyprice );
	double term1 = wage * ( term1a + dirtyprice * ( term1b - ( B_1 * term1c ) ) );

	double term2a = tot_inc - ( wage * ( time_endowment - c ) );
	double term2 = ( - B_3 * cleanprice * dirtyprice * term2a ) + ( B_2 * dirtyprice * dirtyprice * term2a );

	double demandx = ( term1 + term2 ) / ( 2 * wage * den );
	return demandx;
}