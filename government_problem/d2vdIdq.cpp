#include "stdafx.h"

double d2vdIdq(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double terma = tot_inc - ( wage * ( time_endowment - c ) ) ;
	double termb = ag_exp - ( a * cleanprice ) - ( 2 * b * dirtyprice );
	double termc = ag_exp - ( a * cleanprice ) + ( 2 * b * dirtyprice );
	double termd = ( - 2 * ag_exp ) + ( 2 * a * cleanprice ) + ( b * dirtyprice );
	double terme = ( 2 * ag_exp ) - ( 2 * a * cleanprice ) + ( b * dirtyprice );
	double termf = A_1 * wage * ( - ag_exp + ( a * cleanprice ) );

	double term1 = - 2 * A_2 * A_2 * b * B_2 * cleanprice * cleanprice * cleanprice * wage;
	double term2a = ( B_3 * cleanprice * ( ag_exp - ( a * cleanprice ) ) ) + ( b * B_2 * dirtyprice * dirtyprice );
	double term2 = - B_1 * B_1 * cleanprice * wage * term2a;

	double term3a1 = ( b * B_1 * cleanprice ) + ( 2 * A_1 * termb );
	double term3a = B_3 * cleanprice * wage * term3a1;
	double term3b = 2 * B_2 * B_2 * cleanprice * dirtyprice * terma;
	double term3c1 = ( 2 * A_1 * dirtyprice * termd ) + ( B_1 * cleanprice * termc );
	double term3c = B_2 * ( ( wage * term3c1 ) - ( 2 * B_3 * cleanprice * cleanprice * terma ) );
	double term3 = A_2 * cleanprice * ( term3a + term3b + term3c );

	double term4a = - B_3 * cleanprice * cleanprice * terma;
	double term4b = termf + ( B_2 * cleanprice * terma );
	double term4 = 2 * A_1 * B_3 * dirtyprice * ( term4a + ( dirtyprice * term4b ) );

	double term5a = A_1 * B_3 * cleanprice * dirtyprice * wage * terme;
	double term5b = B_3 * B_3 * cleanprice * cleanprice * cleanprice * terma;
	double term5c = - B_2 * dirtyprice * dirtyprice * term4b;
	double term5 = B_1 * ( term5a + term5b + term5c );

	double d2vdIdq = - ( term1 + term2 + term3 + term4 + term5 ) / ( 2 * wage * wage * den * den );
	return d2vdIdq;
}