#include "stdafx.h"

double dxdMnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c) {

	double dxdmnum = A_3 * ( ( A_3 * cleanprice ) - ( A_2 * dirtyprice ) - ( A_1 * netwage ) );
	return dxdmnum;
}
