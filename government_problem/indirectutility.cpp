#include "stdafx.h"
#include "formulas.h"

double indirectutility(double cleanprice, double dirtyprice, double wage, double time_endowment, double tot_inc, double ag_exp, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c) {
	
	double term1 = A_1 * ( demandx(cleanprice, dirtyprice, wage, time_endowment, ag_exp, tot_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - a ) * ( demandx(cleanprice, dirtyprice, wage, time_endowment, ag_exp, tot_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - a );
	double term2 = A_2 * ( demandy(cleanprice, dirtyprice, wage, time_endowment, ag_exp, tot_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - b ) * ( demandy(cleanprice, dirtyprice, wage, time_endowment, ag_exp, tot_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - b );
	double term3 = A_3 * ( ( time_endowment - ( tot_inc / wage ) ) - c ) * ( ( time_endowment - ( tot_inc / wage ) ) - c );

	double term4 = B_1 * ( demandx(cleanprice, dirtyprice, wage, time_endowment, ag_exp, tot_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - a ) * ( demandy(cleanprice, dirtyprice, wage, time_endowment, ag_exp, tot_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - b );
	double term5 = B_2 * ( demandx(cleanprice, dirtyprice, wage, time_endowment, ag_exp, tot_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - a ) * ( ( time_endowment - ( tot_inc / wage ) ) - c );
	double term6 = B_3 * ( demandy(cleanprice, dirtyprice, wage, time_endowment, ag_exp, tot_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - b ) * ( ( time_endowment - ( tot_inc / wage ) ) - c );

	double indirectutility = term1 + term2 + term3 + term4 + term5 + term6;
	return indirectutility;
}