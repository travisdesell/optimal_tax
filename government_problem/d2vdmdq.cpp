#include "stdafx.h"

double d2vdmdq(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double terma = tot_inc - ( wage * ( time_endowment - c ) );
	double termb = ( - ag_exp + ( a * cleanprice ) + ( b * dirtyprice ) ) * wage;

	double term1a = ( - B_1 * cleanprice ) + ( A_1 * dirtyprice );
	double term1 = ( A_2 * cleanprice * cleanprice ) + ( dirtyprice * term1a );

	double term2a = ( b * B_1 * B_1 * wage ) + ( B_1 * B_2 * terma );
	double term2b = - 2 * A_1 * ( ( 2 * A_2 * b * wage ) + ( B_3 * terma ) );
	double term2 = term2a + term2b;
	double term3 = ( - B_1 * cleanprice ) + ( 2 * A_1 * dirtyprice );

	double term4a = B_1 * B_1 * termb;
	double term4b = - 2 * A_1 * B_3 * dirtyprice * terma;
	double term4c1 = ( B_3 * cleanprice ) + ( B_2 * dirtyprice );
	double term4c = B_1 * term4c1 * terma;
	double term4d = - 2 * A_2 * ( ( 2 * A_1 * termb ) + ( B_2 * cleanprice * terma ) );
	double term4 = term4a + term4b + term4c + term4d;

	double d2vdmdq = ( ( term1 * term2 ) - ( term3 * term4 ) ) / ( 2 * wage * den * den );
	return d2vdmdq;
}