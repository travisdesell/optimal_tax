#include "stdafx.h"

double dldMnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dldmnum = A_1 * ( - ( A_3 * cleanprice ) - ( A_2 * dirtyprice ) + ( A_1 * netwage ) );
	return dldmnum;
}