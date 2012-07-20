#include "stdafx.h"

double dydq(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double terma = tot_inc - ( wage * ( time_endowment - c ) );
	double termb = ag_exp - ( a * cleanprice );

	double term1a = ( A_1 * dirtyprice ) - ( B_1 * cleanprice );
	double term1 = ( A_2 * cleanprice * cleanprice ) + ( dirtyprice * term1a );

	double term2a = ( 2 * A_1 * termb ) - ( b * B_1 * cleanprice );
	double term2 = ( wage * term2a ) - ( B_2 * cleanprice * terma );

	double term3a = ( 2 * A_1 * dirtyprice ) - ( B_1 * cleanprice );
	double term3b1 = ag_exp - ( a * cleanprice ) + ( b * dirtyprice );
	double term3b2 = ( A_2 * b * cleanprice * cleanprice ) + ( A_1 * dirtyprice * termb );
	double term3b = ( - B_1 * cleanprice * term3b1 ) + ( 2 * term3b2 );
	double term3c = ( B_3 * cleanprice * cleanprice * terma ) - ( B_2 * cleanprice * dirtyprice * terma );
	double term3 = term3a * ( ( wage * term3b ) + term3c );

	double dydq = ( ( term1 * term2 ) - term3 ) / ( 2 * wage * den * den );
	return dydq;
}