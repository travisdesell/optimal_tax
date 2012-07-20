#include "stdafx.h"

double dvdI(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );
	
	double terma = tot_inc - ( wage * ( time_endowment - c ) );
	double termb = ( ag_exp - ( a * cleanprice ) - ( b * dirtyprice ) ) * wage;

	double term1 = - B_3 * B_3 * cleanprice * cleanprice * terma;
	double term2 = 2 * A_2 * cleanprice * ( - B_2 * termb + 2 * A_3 * cleanprice * terma );
	double term3a = ( B_1 * cleanprice ) - ( 2 * A_1 * dirtyprice );
	double term3 = B_3 * ( term3a * termb + ( 2 * B_2 * cleanprice * dirtyprice * terma ) );

	double term4a1 = ( B_1 * cleanprice ) - ( A_1 * dirtyprice );
	double term4a = - 4 * A_3 * term4a1 * terma;
	double term4b = ( - B_1 * termb ) + ( B_2 * dirtyprice * terma );
	double term4 = dirtyprice * ( term4a - ( B_2 * term4b ) );

	double dvdI = ( term1 + term2 + term3 + term4 ) / ( 2 * wage * wage * den );
	return dvdI;
}