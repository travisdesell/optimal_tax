#include "stdafx.h"

double dldw(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {

	double den1 = ( B_3 * B_3 * cleanprice * cleanprice ) + ( 4 * A_3 * B_1 * cleanprice * dirtyprice ) - ( 4 * A_1 * A_3 * dirtyprice * dirtyprice );
	double den2 = ( B_2 * B_2 * dirtyprice * dirtyprice ) - ( 2 * B_1 * B_2 * dirtyprice * netwage ) + ( B_1 * B_1 * netwage * netwage );
	double den3 = ( B_2 * cleanprice * dirtyprice ) + ( B_1 * cleanprice * netwage ) - ( 2 * A_1 * dirtyprice * netwage );
	double den4 = ( A_3 * cleanprice * cleanprice ) + ( netwage * ( ( A_1 * netwage ) - ( B_2 * cleanprice ) ) );
	double den = den1 + den2 - ( 2 * B_3 * den3 ) - ( 4 * A_2 * den4 );

	double dwterm1 = ( 4 * A_1 * B_3 * dirtyprice ) + ( 2 * B_1 * B_1 * netwage );
	double dwterm2 = ( B_3 * cleanprice ) + ( B_2 * dirtyprice );
	double dwterm3 = ( B_2 * cleanprice ) - ( 2 * A_1 * netwage );
	double dwterm = dwterm1 - ( 2 * B_1 * dwterm2 ) + ( 4 * A_2 * dwterm3 );

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

	double dldwterm1 = 2 * A_2 * B_2 * cleanprice * ( time_endowment + c );
	double dldwterm2 = - B_1 * ( ( B_3 * cleanprice ) + ( B_2 * dirtyprice ) ) * ( time_endowment + c );
	double dldwterm3 = virtual_inc - ( a * cleanprice ) - ( b * dirtyprice ) + ( 2 * time_endowment * netwage );
	double dldwterm4 = ( B_3 * dirtyprice * ( time_endowment + c ) ) - ( 2 * A_2 * dldwterm3 );
	double dldwterm = dldwterm1 + dldwterm2 + ( B_1 * B_1 * dldwterm3 ) + ( 2 * A_1 * dldwterm4 );

	double dldw = ( ( den * dldwterm ) - ( dwterm * dlterm ) ) / ( den * den );
	return dldw;
}
