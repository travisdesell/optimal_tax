#include "stdafx.h"

double dydm(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den = ( A_2 * cleanprice * cleanprice ) + ( A_1 * dirtyprice * dirtyprice ) - ( B_1 * cleanprice * dirtyprice );
	double num = ( B_1 * cleanprice ) - ( 2 * A_1 * dirtyprice );

	double dydm = - num / ( 2 * den );
	return dydm;
}