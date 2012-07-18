#include "stdafx.h"

double dldq(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den1 = ( B_3 * B_3 * cleanprice * cleanprice ) + ( 4 * A_3 * B_1 * cleanprice * dirtyprice ) - ( 4 * A_1 * A_3 * dirtyprice * dirtyprice );
	double den2 = ( B_2 * B_2 * dirtyprice * dirtyprice ) - ( 2 * B_1 * B_2 * dirtyprice * netwage ) + ( B_1 * B_1 * netwage * netwage );
	double den3 = ( B_2 * cleanprice * dirtyprice ) + ( B_1 * cleanprice * netwage ) - ( 2 * A_1 * dirtyprice * netwage );
	double den4 = ( A_3 * cleanprice * cleanprice ) + ( netwage * ( ( A_1 * netwage ) - ( B_2 * cleanprice ) ) );
	double den = den1 + den2 - ( 2 * B_3 * den3 ) - ( 4 * A_2 * den4 );

	double dqterm1 = ( 2 * B_2 * B_2 * dirtyprice ) + ( 4 * A_1 * B_3 * netwage );
	double dqterm2 = ( B_1 * cleanprice ) - ( 2 * A_1 * dirtyprice );
	double dqterm3 = ( B_3 * cleanprice ) + ( B_1 * netwage );
	double dqterm = dqterm1 + ( 4 * A_3 * dqterm2 ) - ( 2 * B_2 * dqterm3 );

	double dlterm1 = ( B_3 * B_3 * c * cleanprice * cleanprice ) + ( 2 * A_1 * B_3 * virtual_inc * dirtyprice ) - ( 2 * a * A_1 * B_3 * cleanprice * dirtyprice );
	double dlterm2 = ( - 2 * B_2 * B_3 * c * cleanprice * dirtyprice ) - ( 2 * A_1 * b * B_3 * dirtyprice * dirtyprice ) - ( 4 * A_1 * A_3 * c * dirtyprice * dirtyprice );
	double dlterm3 = ( B_2 * B_2 * c * dirtyprice * dirtyprice ) + ( 2 * A_1 * B_3 * netwage * dirtyprice * ( time_endowment + c ) );
	double dlterm4a = virtual_inc - ( a * cleanprice ) - ( b * dirtyprice ) + ( netwage * time_endowment );
	double dlterm4 = B_1 * B_1 * netwage * dlterm4a;
	double dlterm5a = virtual_inc - ( a * cleanprice ) - ( b * dirtyprice ) + ( netwage * ( time_endowment + c ) );
	double dlterm5b = ( A_3 * c * cleanprice * cleanprice ) + ( A_1 * netwage * dlterm4a );
	double dlterm5 = ( B_2 * cleanprice * dlterm5a ) - ( 2 * dlterm5b );
	double dlterm6a = ( - 4 * A_3 * c * cleanprice ) + ( B_2 * dlterm5a );
	double dlterm6 = ( B_3 * cleanprice * dlterm5a ) + ( dirtyprice * dlterm6a );
	double dlterm = dlterm1 + dlterm2 + dlterm3 + dlterm4 + ( 2 * A_2 * dlterm5 ) - ( B_1 * dlterm6 );

	double dldqterm1a = virtual_inc - ( a * cleanprice ) - ( 2 * b * dirtyprice ) + ( netwage * ( time_endowment + c ) );
	double dldqterm1 = ( - cleanprice * ( ( b * B_3 ) + ( 4 * A_3 * c ) ) ) + ( B_2 * dldqterm1a );
	double dldqterm2a = ( A_2 * b * cleanprice ) + ( B_3 * c * cleanprice ) - ( B_2 * c * dirtyprice );
	double dldqterm2b = ( - 4 * A_3 * c * dirtyprice ) + ( 2 * A_2 * b * netwage ) + ( B_3 * dldqterm1a );
	double dldqterm2 = ( B_2 * dldqterm2a ) - ( A_1 * dldqterm2b );
	double dldqterm = ( b * B_1 * B_1 * netwage ) + ( B_1 * dldqterm1 ) + ( 2 * dldqterm2 );
	
	double dldq = ( - ( ( den * dldqterm ) + ( dqterm * dlterm ) ) ) / ( den * den );
	return dldq;
}