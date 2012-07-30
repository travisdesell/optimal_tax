#include "stdafx.h"
#include "math.h"

double swf_fb(double cleanprice, double dirtyprice, double wage_h, double wage_l, double pop_h, double pop_l, double time_endowment, double tot_inch, double tot_incl, double ag_exph, double ag_expl, double mu, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c, double eta) {

	double term_h = pop_h * pow(indirectutility(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c), 1-eta);
	double term_l = pop_l * pow(indirectutility(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c), 1-eta);

	double term_bc = ( pop_h * ( tot_inch - ag_exph ) ) + ( pop_l * ( tot_incl - ag_expl ) ) - 93;

	double swf_fb = ( 1 / ( 1 - eta ) ) * ( term_h + term_l ) + ( mu * term_bc );
	return swf_fb;
}

double foc_inc(double cleanprice, double dirtyprice, double wage, double pop, double time_endowment, double tot_inc, double ag_exp, double mu, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c, double eta) {

	double term1 = pow(indirectutility(cleanprice, dirtyprice, wage, time_endowment, tot_inc, ag_exp, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c), -eta);
	double term2 = pop * term1 * dvdI(cleanprice, dirtyprice, wage, time_endowment, tot_inc, ag_exp, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	double foc_inc = term2 + ( mu * pop );
	return foc_inc;
}

double foc_exp(double cleanprice, double dirtyprice, double wage, double pop, double time_endowment, double tot_inc, double ag_exp, double mu, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c, double eta) {

	double term1 = pow(indirectutility(cleanprice, dirtyprice, wage, time_endowment, tot_inc, ag_exp, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c), -eta);
	double term2 = pop * term1 * dvdm(cleanprice, dirtyprice, wage, time_endowment, tot_inc, ag_exp, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	double foc_exp = term2 - ( mu * pop );
	return foc_exp;
}

double bgtcnst(double pop_h, double pop_l, double tot_inch, double tot_incl, double ag_exph, double ag_expl, double revenue) { 

	double bgtcnst = ( pop_h * ( tot_inch - ag_exph ) ) + ( pop_l * ( tot_incl - ag_expl ) ) - revenue;
	return bgtcnst;
}
