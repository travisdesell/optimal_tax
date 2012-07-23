#include <cfloat>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "tao/evolutionary_algorithms/particle_swarm.hxx"
#include "tao/evolutionary_algorithms/differential_evolution.hxx"

#include "tao/synchronous_algorithms/parameter_sweep.hxx"
#include "tao/synchronous_algorithms/synchronous_gradient_descent.hxx"
#include "tao/synchronous_algorithms/synchronous_newton_method.hxx"

//from undvc_common
#include "tao/undvc_common/arguments.hxx"
#include "tao/undvc_common/vector_io.hxx"

#include "government_problem/stdafx.h"

using namespace std;

/**
 *  The following parameters are constant.
 */
double A_1 = 2.00;
double A_2 = 2.00;
double A_3 = 2.00;
double B_1 = 2.00;
double B_2 = 2.00;
double B_3 = 2.00;
double a = 67.98208;
double b = 7.113661;
double c = 30;

/* Updated 07/23/2012 */
double cleanprice = 1;
double dirtyprice = 1;
double wage_h = 16.0696;
double wage_l = 10.4980;
double pop_h = 0.40;
double pop_l = 0.60;
double time_endowment = 80;
double eta = 0.10;
double revenue = 126.79;
double constraint_penalty = 0.0001;

ofstream *output_csv;

/* Calculate a penalty for being less than or equal to the bound given*/
double penalty_leq(double max, double value) {
    if (value <= max) return constraint_penalty + (max - value);
    return 0;
}

/* Calculate a penalty for being inside the bounds given */
double penalty_in_inclusive(double min, double max, double value) {
    if (value >= min && value <= max) {
        double diff_min = value - min;  /* difference from the min value */
        double diff_max = max - value;  /* difference from the max value */

        /* return the difference from the closest boundary.  Maybe it should the farthest boundary? */
        if (diff_min > diff_max) return constraint_penalty + diff_max;
        else return constraint_penalty + diff_min;
    }
    return 0;
}

/* Calculate a penalty for being outside the bounds given */
double penalty_out_inclusive(double min, double max, double value) {
    if (value <= min) return constraint_penalty + (min - value);
    if (value >= max) return constraint_penalty + (value - max);
    return 0;
}

double objective_function(const vector<double> &A) {
    double f = 0;
    uint32_t success_count = 0;

	double tot_inch = A[0];
	double tot_incl = A[1];
	double ag_exph = A[2];
	double ag_expl = A[3];
	double mu = A[4];

	double term_h = pop_h * pow(indirectutility(cleanprice, dirtyprice, wage_h, time_endowment, tot_inch, ag_exph, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c), 1-eta);
	double term_l = pop_l * pow(indirectutility(cleanprice, dirtyprice, wage_l, time_endowment, tot_incl, ag_expl, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c), 1-eta);

	double term_bc = ( pop_h * ( tot_inch - ag_exph ) ) + ( pop_l * ( tot_incl - ag_expl ) ) - revenue;

	f = ( 1 / ( 1 - eta ) ) * ( term_h + term_l ) + ( mu * term_bc );
	return f;
}

void check_solution(double tot_inch, double tot_incl, double ag_exph, double ag_expl, double mu) {
	double focinchval = foc_inc(cleanprice, dirtyprice, wage_h, pop_h, time_endowment, tot_inch, ag_exph, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta); 
	double focinclval = foc_inc(cleanprice, dirtyprice, wage_l, pop_l, time_endowment, tot_incl, ag_expl, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta); 
	
	double focexphval = foc_exp(cleanprice, dirtyprice, wage_h, pop_h, time_endowment, tot_inch, ag_exph, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta);
	double focexplval = foc_exp(cleanprice, dirtyprice, wage_l, pop_l, time_endowment, tot_incl, ag_expl, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta);

	double bgtcnstval = bgtcnst(pop_h, pop_l, tot_inch, tot_incl, ag_exph, ag_expl);

	double tot_inch2 = tot_inch - 1;
	double tot_incl2 = tot_incl + 1;
	double ag_exph2 = ag_exph - 1;
	double ag_expl2 = ag_expl + 1;

	double welfare = swf_fb(cleanprice, dirtyprice, wage_h, wage_l, pop_h, pop_l, time_endowment, tot_inch, tot_incl, ag_exph, ag_expl, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta);
	double checkwelfare = swf_fb(cleanprice, dirtyprice, wage_h, wage_l, pop_h, pop_l, time_endowment, tot_inch2, tot_incl2, ag_exph2, ag_expl2, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta);

	(*output_csv) << tot_inch << ", " << tot_incl << ", " << ag_exph << ", " << ag_expl << ", " << mu << ", " << welfare << ", " << focinchval << ", " << focinclval << ", " << focexphval << ", " << focexplval << ", " << bgtcnstval << ", " << checkwelfare << endl;
}



int main(int number_arguments, char **argv) {
    vector<string> arguments(argv, argv + number_arguments);

	output_csv = new ofstream("First-Best Problem.txt");
	(*output_csv) << "Inc_High, Inc_Low, Exp_High, Exp_Low, mu, Welfare, FOC_Inc_H, FOC_Inc_L, FOC_Exp_H, FOC_Exp_L, Bgt Cnst, Welfare2" << endl;

    int number_parameters = 5;
    vector<double> min_bound(number_parameters, 0);
    vector<double> max_bound(number_parameters, 0);

    min_bound[0] = 0;
    max_bound[0] = 800;
    min_bound[1] = 0;
    max_bound[1] = 800;
    min_bound[2] = 0;
    max_bound[2] = 800;
	min_bound[3] = -0;
	max_bound[3] = 800;
	min_bound[4] = 0;
	max_bound[4] = 10;

    string search_type;
    if (!get_argument(arguments, "--search_type", false, search_type)) {
        fprintf(stderr, "Improperly specified search type: '%s'\n", search_type.c_str());
        fprintf(stderr, "Possibilities are:\n");
        fprintf(stderr, "    de     -       differential evolution\n");
        fprintf(stderr, "    ps     -       particle swarm optimization\n");
        fprintf(stderr, "    snm    -       synchronous newton method\n");
        fprintf(stderr, "    gd     -       gradient descent\n");
        fprintf(stderr, "    cgd    -       conjugate gradient descent\n");
		fprintf(stderr, "    sweep  -       parameter sweep\n");
		fprintf(stderr, "    check  -		check solution\n");
		exit(0);
	}

    if (search_type.compare("ps") == 0) {
        ParticleSwarm ps(min_bound, max_bound, arguments);
        ps.iterate(objective_function);

    } else if (search_type.compare("de") == 0) {
        DifferentialEvolution de(min_bound, max_bound, arguments);
        de.iterate(objective_function);

    } else if (search_type.compare("sweep") == 0) {
        vector<double> step_size(5, 0);
        step_size[0] = 50;
        step_size[1] = 50;
        step_size[2] = 10;
		step_size[3] = 10;
		step_size[4] = 0.05;

        parameter_sweep(min_bound, max_bound, step_size, objective_function);

    } else if (search_type.compare("snm") == 0 || search_type.compare("gd") == 0 || search_type.compare("cgd") == 0) {
		vector<double> starting_point(3, 0);

#ifdef _MSC_VER
		srand(time(NULL));
        starting_point[0] = min_bound[0] + ((max_bound[0] - min_bound[0]) * ((double)rand()/(double)RAND_MAX));
        starting_point[1] = min_bound[1] + ((max_bound[1] - min_bound[1]) * ((double)rand()/(double)RAND_MAX));
        starting_point[2] = min_bound[2] + ((max_bound[2] - min_bound[2]) * ((double)rand()/(double)RAND_MAX));
#else
        srand48(time(NULL));
		starting_point[0] = min_bound[0] + ((max_bound[0] - min_bound[0]) * drand48());
        starting_point[1] = min_bound[1] + ((max_bound[1] - min_bound[1]) * drand48());
        starting_point[2] = min_bound[2] + ((max_bound[2] - min_bound[2]) * drand48());
#endif

        vector<double> step_size(6, 0);
        step_size[0] = 0.005;
        step_size[1] = 0.005;
        step_size[2] = 0.005;

        if (search_type.compare("snm") == 0) {
            synchronous_newton_method(arguments, objective_function, starting_point, step_size);
        } else if (search_type.compare("gd") == 0) {
            synchronous_gradient_descent(arguments, objective_function, starting_point, step_size);
        } else if (search_type.compare("cgd") == 0) {
            synchronous_conjugate_gradient_descent(arguments, objective_function, starting_point, step_size);
        }

    } else if (search_type.compare("check") == 0) {
			double tot_inch;
			double tot_incl;
			double ag_exph;
			double ag_expl;
			double mu;

			cout << "Enter the following: Total Income (H), Total Income (L), Expenditures (H), Expenditures(L), mu: " << endl;
			cin >> tot_inch >> tot_incl >> ag_exph >> ag_expl >> mu;
			check_solution(tot_inch, tot_incl, ag_exph, ag_expl, mu);
	
	} else {
        fprintf(stderr, "Improperly specified search type: '%s'\n", search_type.c_str());
        fprintf(stderr, "Possibilities are:\n");
        fprintf(stderr, "    de     -       differential evolution\n");
        fprintf(stderr, "    ps     -       particle swarm optimization\n");
        fprintf(stderr, "    snm    -       synchronous newton method\n");
        fprintf(stderr, "    gd     -       gradient descent\n");
        fprintf(stderr, "    cgd    -       conjugate gradient descent\n");
		fprintf(stderr, "    sweep  -       parameter sweep\n");
		fprintf(stderr, "	 check	-		check solution\n");
        exit(0);
    }

    output_csv->close();
    delete output_csv;

    return 0;
}
