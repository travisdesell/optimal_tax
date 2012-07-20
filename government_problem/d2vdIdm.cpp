#include "stdafx.h"

double d2vdIdm(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double term1 = ( - 2 * A_2 * B_2 * cleanprice ) + ( B_1 * B_3 * cleanprice );
	double term2 = ( B_1 * B_2 * dirtyprice ) - ( 2 * A_1 * B_3 * dirtyprice );

	double d2vdIdm = ( term1 + term2 ) / ( 2 * wage * den );
	return d2vdIdm;
}