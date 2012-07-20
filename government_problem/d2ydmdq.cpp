#include "stdafx.h"

double d2ydmdq(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double term1 = ( B_1 * B_1 * cleanprice * cleanprice ) + ( 2 * A_1 * A_1 * dirtyprice * dirtyprice );
	double term2 = - 2 * A_1 * cleanprice * ( ( A_2 * cleanprice ) + ( B_1 * dirtyprice ) );

	double d2ydmdq = - ( term1 + term2 ) / ( 2 * den * den );
	return d2ydmdq;
}