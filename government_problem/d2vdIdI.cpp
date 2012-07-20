#include "stdafx.h"

double d2vdIdI(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double term1 = ( 4 * A_2 * A_3 * cleanprice * cleanprice ) - ( B_3 * B_3 * cleanprice * cleanprice ) + ( 2 * B_2 * B_3 * cleanprice * dirtyprice );
	double term2 = ( - 4 * A_3 * B_1 * cleanprice ) + ( 4 * A_1 * A_3 * dirtyprice ) - ( B_2 * B_2 * dirtyprice );

	double d2vdIdI = ( term1 + dirtyprice * term2 ) / ( 2 * wage * wage * den );
	return d2vdIdI;
}