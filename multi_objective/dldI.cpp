#include "stdafx.h"

double dldI(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den1 = ( B_3 * B_3 * cleanprice * cleanprice ) + ( 4 * A_3 * B_1 * cleanprice * dirtyprice ) - ( 4 * A_1 * A_3 * dirtyprice * dirtyprice );
	double den2 = ( B_2 * B_2 * dirtyprice * dirtyprice ) - ( 2 * B_1 * B_2 * dirtyprice * netwage ) + ( B_1 * B_1 * netwage * netwage );
	double den3 = ( B_2 * cleanprice * dirtyprice ) + ( B_1 * cleanprice * netwage ) - ( 2 * A_1 * dirtyprice * netwage );
	double den4 = ( A_3 * cleanprice * cleanprice ) + ( netwage * ( ( A_1 * netwage ) - ( B_2 * cleanprice ) ) );
	double den = den1 + den2 - ( 2 * B_3 * den3 ) - ( 4 * A_2 * den4 );

	double num1 = ( 2 * A_1 * B_3 * dirtyprice ) + ( B_1 * B_1 * netwage );
	double num2 = ( B_3 * cleanprice ) + ( B_2 * dirtyprice );
	double num3 = ( B_2 * cleanprice ) - ( 2 * A_1 * netwage );
	double num = num1 - ( B_1 * num2 ) + ( 2 * A_2 * num3 );

	double dldI = num / den;
	return dldI;
}