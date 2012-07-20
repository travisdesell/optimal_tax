#include "stdafx.h"

double dvdm(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );

	double terma = tot_inc - ( wage * ( time_endowment - c ) );
	double termb = ( - ag_exp + ( a * cleanprice ) + ( b * dirtyprice ) ) * wage;

	double term1 = ( B_1 * B_1 * termb )  - ( 2 * A_1 * B_3 * dirtyprice * terma );
	double term2a = ( B_3 * cleanprice ) + ( B_2 * dirtyprice );
	double term2 = B_1 * term2a * terma;
	double term3 = - 2 * A_2 * ( 2 * A_1 * termb + B_2 * cleanprice * terma );

	double dvdm = ( term1 + term2 + term3 ) / ( 2 * wage * den );
	return dvdm;
}