#include "stdafx.h"
#include "math.h"

double swf_fbext(double cleanprice, double dirtyprice, double wage_h, double wage_l, double pop_h, double pop_l, double time_endowment, double tot_inch, double tot_incl, double ag_exph, double ag_expl, double mu, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c, double eta, double revenue, double phi) {
	// Externality
	double externality_h = phi * pop_h * demandy(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double externality_l = phi * pop_l * demandy(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	// Utility Term
	double innerutil_h = indirectutility(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;
	double innerutil_l = indirectutility(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;

	double term_h = pop_h * pow(innerutil_h, 1-eta);
	double term_l = pop_l * pow(innerutil_l, 1-eta);

	// Buget Constraint
	double termbc_h = ( tot_inch - ag_exph ) + ( dirtyprice - 1 ) * demandy(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double termbc_l = ( tot_incl - ag_expl ) + ( dirtyprice - 1 ) * demandy(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double term_bc = ( pop_h * termbc_h ) + ( pop_l * termbc_l ) - revenue;

	double swf_fbext = ( 1 / ( 1 - eta ) ) * ( term_h + term_l ) + ( mu * term_bc );
	return swf_fbext;
}

double foc_incexth(double cleanprice, double dirtyprice, double wage_h, double wage_l, double pop_h, double pop_l, double time_endowment, double tot_inch, double tot_incl, double ag_exph, double ag_expl, double mu, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c, double eta, double revenue, double phi) {
	// Externality
	double externality_h = phi * pop_h * demandy(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double externality_l = phi * pop_l * demandy(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	// Utility Term
	double innerutil_h = indirectutility(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;
	double innerutil_l = indirectutility(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;

	// Derivatives
	double termutil = pop_h * pow(innerutil_h, -eta) * dvdI(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	
	double termexth = pop_h * pow(innerutil_h, -eta) * phi * pop_h * dydI(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double termextl = pop_l * pow(innerutil_l, -eta) * phi * pop_l * dydI(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	double term_bc = mu * pop_h * ( 1 + ( dirtyprice - 1 ) * dydI(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) );

	double foc_incexth = termutil - termexth - termextl + term_bc;
	return foc_incexth;
}

double foc_incextl(double cleanprice, double dirtyprice, double wage_h, double wage_l, double pop_h, double pop_l, double time_endowment, double tot_inch, double tot_incl, double ag_exph, double ag_expl, double mu, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c, double eta, double revenue, double phi) {
	// Externality
	double externality_h = phi * pop_h * demandy(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double externality_l = phi * pop_l * demandy(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	// Utility Term
	double innerutil_h = indirectutility(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;
	double innerutil_l = indirectutility(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;

	// Derivatives
	double termutil = pop_l * pow(innerutil_l, -eta) * dvdI(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	double termexth = pop_h * pow(innerutil_h, -eta) * phi * pop_h * dydI(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double termextl = pop_l * pow(innerutil_l, -eta) * phi * pop_l * dydI(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	double term_bc = mu * pop_l * ( 1 + ( dirtyprice - 1 ) * dydI(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) );

	double foc_incextl = termutil - termexth - termextl + term_bc;
	return foc_incextl;
}

double foc_expexth(double cleanprice, double dirtyprice, double wage_h, double wage_l, double pop_h, double pop_l, double time_endowment, double tot_inch, double tot_incl, double ag_exph, double ag_expl, double mu, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c, double eta, double revenue, double phi) {
	// Externality
	double externality_h = phi * pop_h * demandy(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double externality_l = phi * pop_l * demandy(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	// Utility Term
	double innerutil_h = indirectutility(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;
	double innerutil_l = indirectutility(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;

	// Derivatives
	double termutil = pop_h * pow(innerutil_h, -eta) * dvdm(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	
	double termexth = pop_h * pow(innerutil_h, -eta) * phi * pop_h * dydm(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double termextl = pop_l * pow(innerutil_l, -eta) * phi * pop_l * dydm(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	double term_bc = mu * pop_h * ( - 1 + ( dirtyprice - 1 ) * dydm(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) );

	double foc_expexth = termutil - termexth - termextl + term_bc;
	return foc_expexth;
}

double foc_expextl(double cleanprice, double dirtyprice, double wage_h, double wage_l, double pop_h, double pop_l, double time_endowment, double tot_inch, double tot_incl, double ag_exph, double ag_expl, double mu, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c, double eta, double revenue, double phi) {
	// Externality
	double externality_h = phi * pop_h * demandy(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double externality_l = phi * pop_l * demandy(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	// Utility Term
	double innerutil_h = indirectutility(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;
	double innerutil_l = indirectutility(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;

	// Derivatives
	double termutil = pop_l * pow(innerutil_l, -eta) * dvdm(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	
	double termexth = pop_h * pow(innerutil_h, -eta) * phi * pop_h * dydm(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double termextl = pop_l * pow(innerutil_l, -eta) * phi * pop_l * dydm(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	double term_bc = mu * pop_l * ( - 1 + ( dirtyprice - 1 ) * dydm(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) );

	double foc_expextl = termutil - termexth - termextl + term_bc;
	return foc_expextl;
}

double foc_bgtcnst(double cleanprice, double dirtyprice, double wage_h, double wage_l, double pop_h, double pop_l, double time_endowment, double tot_inch, double tot_incl, double ag_exph, double ag_expl, double mu, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c, double eta, double revenue, double phi) {
	// Externality
	double externality_h = phi * pop_h * demandy(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double externality_l = phi * pop_l * demandy(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	// Utility Term
	double innerutil_h = indirectutility(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;
	double innerutil_l = indirectutility(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) - externality_h - externality_l;

	// Externality Derivative
	double termexth = phi * pop_h * dydq(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double termextl = phi * pop_l * dydq(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	// Utility Derivatives
	double termutil_ha = demandy(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * dydm(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double termutil_h = pop_h * pow(innerutil_h, -eta) * ( - termutil_ha - termexth - termextl );

	double termutil_la = demandy(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * dydm(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double termutil_l = pop_l * pow(innerutil_l, -eta) * ( - termutil_la - termexth - termextl );

	double term_bch = demandy(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) + ( dirtyprice - 1 ) * dydq(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
	double term_bcl = demandy(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) + ( dirtyprice - 1 ) * dydq(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

	double foc_bgtcnst = ( termutil_h + termutil_l ) + mu * ( term_bch + term_bcl );
	return foc_bgtcnst;
}

