#include "stdafx.h"

double demandy(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double term1a = ag_exp - ( a * cleanprice ) + ( b * dirtyprice );
	double term1b = A_2 * b * cleanprice * cleanprice;
	double term1c = A_1 * dirtyprice * ( ag_exp - ( a * cleanprice ) );
	double term1 = ( ( - B_1 * cleanprice * term1a ) + 2 * ( term1b + term1c ) ) * wage;

	double term2a = tot_inc - ( wage * ( time_endowment - c ) );
	double term2 = ( B_3 * cleanprice * cleanprice * term2a ) - ( B_2 * cleanprice * dirtyprice * term2a );

	double demandy = ( term1 + term2 ) / ( 2 * wage * den );
	return demandy;
}