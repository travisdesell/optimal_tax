#include "stdafx.h"

double d2ydIdq(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double term1 = ( - A_2 * B_2 * cleanprice * cleanprice ) + ( B_1 * B_3 * cleanprice * cleanprice );
	double term2 = A_1 * dirtyprice * ( ( B_2 * dirtyprice ) - ( 2 * B_3 * cleanprice ) );

	double d2ydIdq = ( cleanprice * ( term1 + term2 ) ) / ( 2 * wage * den * den );
	return d2ydIdq;
}