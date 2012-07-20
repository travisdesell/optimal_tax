#include "stdafx.h"

double d2ydqdq(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double terma = tot_inc - ( wage * ( time_endowment - c ) );
	double term1a = - B_1 * cleanprice * ( ag_exp - ( a * cleanprice ) + ( b * dirtyprice ) );
	double term1b = ( A_2 * b * cleanprice * cleanprice ) + ( A_1 * dirtyprice * ( ag_exp - ( a * cleanprice ) ) );
	double term1c = ( B_3 * cleanprice * cleanprice * terma ) - ( B_2 * cleanprice * dirtyprice * terma );
	double term1 = wage * ( term1a + 2 * term1b ) + term1c;

	double term2 = ( - B_1 * cleanprice ) + ( 2 * A_1 * dirtyprice );
	double term3a = ( - b * B_1 * cleanprice ) + ( 2 * A_1 * ( ag_exp - ( a * cleanprice ) ) );
	double term3 = ( wage * term3a ) - ( B_2 * cleanprice * terma );
	
	double num = ( A_1 * den * term1 ) + ( term2 * ( ( den * term3 ) - ( term2 * term1 ) ) );
	double d2ydqdq = - num / ( wage * den * den * den );
	return d2ydqdq;
}