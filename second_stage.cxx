#include <cfloat>
#include "stdint.h"
#include <time.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "tao/asynchronous_algorithms/particle_swarm.hxx"
#include "tao/asynchronous_algorithms/differential_evolution.hxx"

#include "tao/synchronous_algorithms/parameter_sweep.hxx"
#include "tao/synchronous_algorithms/synchronous_gradient_descent.hxx"
#include "tao/synchronous_algorithms/synchronous_newton_method.hxx"

//from undvc_common
#include "tao/undvc_common/arguments.hxx"
#include "tao/undvc_common/vector_io.hxx"

#include "government_problem/stdafx.h"

using namespace std;

/* The following parameters are constant. */
double A_1;
double A_2;
double A_3;
double B_1;
double B_2;
double B_3;
double eta;

/* Updated 07/29/2012 */
double cleanprice = 1;
double dirtyprice = 1;
double wage_h = 16.07;
double wage_l = 10.50;
double pop_h = 0.50;
double pop_l = 0.50;
double time_endowment = 80;

double a = 52.50;
double b = 5.00;
double c = 5.00;
double revenue = 0;
double penalty_value = 100;

ofstream *output_csv;

double objective_function(const vector<double> &A) {
    double f = 0;
    uint32_t success_count = 0;

	double tot_inch = A[0]; // total income (high type)
	double tot_incl = A[1]; // total income (low type)
	double ag_exph = A[2]; // aggregate expenditures (high type)
	double ag_expl = A[3]; // aggregate expenditures (low type)
	double mu = A[4]; // multiplier term

	/* Restrictions On Parameter Values
		-  tot_inch > tot_incl
		-  ag_exph > ag_expl
		-  tot_inch > ag_exph */
	
	/*Can rewrite total income constraint based on labor supply.
		total income = wage rate * labor hours ==>
		tot_inch = wage_h * labor_h ==> labor_h = tot_inch / wage_h.
	  Restriction is labor_h > labor_l (high type works more than low type) */
	double labor_h = tot_inch / wage_h;
	double labor_l = tot_incl / wage_l;
	
	bool success = true;

	/*if (tot_inch < tot_incl) {
		f -= (tot_incl - tot_inch);
		f -= 50.0;
		success = false;
	}*/
	
	if (labor_h < labor_l) {
        f -= (labor_l - labor_h); //subtract the difference between labor_l and labor_h
        f -= penalty_value;  //apply a penalty.
		success = false;
	} 

	if (ag_exph < ag_expl) {
        f -= (ag_expl - ag_exph); //subtract the difference between ag_expl and ag_exph
        f -= penalty_value;  //apply a penalty.
		success = false;
	}

	if (tot_inch < ag_exph) {
        f -= (ag_exph - tot_inch); //subtract the difference between ag_exph and tot_inch
        f -= penalty_value; //apply a penalty.
		success = false;
	}

	// cout << "Success: " << success << endl;

	if (success) {
		// First-Order Conditions -- Income (high type, low type)
		double focinchval = foc_inc(cleanprice, dirtyprice, wage_h, pop_h, time_endowment, tot_inch, ag_exph, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta) * foc_inc(cleanprice, dirtyprice, wage_h, pop_h, time_endowment, tot_inch, ag_exph, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta);
		double focinclval = foc_inc(cleanprice, dirtyprice, wage_l, pop_l, time_endowment, tot_incl, ag_expl, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta) * foc_inc(cleanprice, dirtyprice, wage_l, pop_l, time_endowment, tot_incl, ag_expl, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta);

		// First-Order Conditions -- Expenditures (high type, low type)
		double focexphval = foc_exp(cleanprice, dirtyprice, wage_h, pop_h, time_endowment, tot_inch, ag_exph, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta) * foc_exp(cleanprice, dirtyprice, wage_h, pop_h, time_endowment, tot_inch, ag_exph, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta);
		double focexplval = foc_exp(cleanprice, dirtyprice, wage_l, pop_l, time_endowment, tot_incl, ag_expl, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta) * foc_exp(cleanprice, dirtyprice, wage_l, pop_l, time_endowment, tot_incl, ag_expl, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta);

		// Bgt Constraint
		double bgtcnstval = bgtcnst(pop_h, pop_l, tot_inch, tot_incl, ag_exph, ag_expl, revenue) * bgtcnst(pop_h, pop_l, tot_inch, tot_incl, ag_exph, ag_expl, revenue);

		/* cout << "Point: " << vector_to_string(A) << endl;
		cout << "Revenue: " << revenue << endl;
		cout << "Bgt Cnst: " << bgtcnst(pop_h, pop_l, tot_inch, tot_incl, ag_exph, ag_expl, revenue) << endl;
		cout << focinchval << "; " << focinclval << "; " << focexphval << "; " << focexplval << "; " << bgtcnstval << endl; */

		// Minimize sum of squared differences
		f = - ( focinchval + focinclval + focexphval + focexplval + bgtcnstval );
		// cout << "Fitness function: " << f << endl;
    }
	return f;
}

void check_solution(double tot_inch, double tot_incl, double ag_exph, double ag_expl, double mu) {
	double focinchval = foc_inc(cleanprice, dirtyprice, wage_h, pop_h, time_endowment, tot_inch, ag_exph, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta); 
	double focinclval = foc_inc(cleanprice, dirtyprice, wage_l, pop_l, time_endowment, tot_incl, ag_expl, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta); 
	
	double focexphval = foc_exp(cleanprice, dirtyprice, wage_h, pop_h, time_endowment, tot_inch, ag_exph, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta);
	double focexplval = foc_exp(cleanprice, dirtyprice, wage_l, pop_l, time_endowment, tot_incl, ag_expl, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta);

	double bgtcnstval = bgtcnst(pop_h, pop_l, tot_inch, tot_incl, ag_exph, ag_expl, revenue);

	double tot_inch2 = tot_inch - 1;
	double tot_incl2 = tot_incl + 1;
	double ag_exph2 = ag_exph - 1;
	double ag_expl2 = ag_expl + 1;

	double welfare = swf_fb(cleanprice, dirtyprice, wage_h, wage_l, pop_h, pop_l, time_endowment, tot_inch, tot_incl, ag_exph, ag_expl, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta, revenue);
	double checkwelfare = swf_fb(cleanprice, dirtyprice, wage_h, wage_l, pop_h, pop_l, time_endowment, tot_inch2, tot_incl2, ag_exph2, ag_expl2, mu, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c, eta, revenue);

	(*output_csv) << "FOC Income (H): " << focinchval << " Foc Income (L): " << focinclval << endl;
	(*output_csv) << "FOC Expenditures (H): " << focexphval << " FOC Expenditures (L): " << focexplval << endl;
	(*output_csv) << "Budget Constraint: " << bgtcnstval << " Original Welfare: " << welfare << " Adjusted Welfare: " << checkwelfare << endl;
}

int main(int number_arguments, char **argv) {
    vector<string> arguments(argv, argv + number_arguments);

    // Code to create an output file
	string output_filename;
    get_argument(arguments, "--output_filename", true, output_filename);

	output_csv = new ofstream(output_filename.c_str());

	// Code to enter parameter values
	vector<double> utility_parameters;
    get_argument_vector(arguments, "--utility_parameters", true, utility_parameters);
    A_1 = utility_parameters[0];
    A_2 = utility_parameters[1];
    A_3 = utility_parameters[2];
    B_1 = utility_parameters[3];
    B_2 = utility_parameters[4];
    B_3 = utility_parameters[5];
    eta = utility_parameters[6];

	(*output_csv) << "Parameters: A_1, A_2, A_3, B_1, B_2, B_3, eta" << endl;
	(*output_csv) << "Values: " << vector_to_string(utility_parameters) << endl;

	// Code to set up parameter bounds
	int number_parameters = 5;
    vector<double> min_bound(number_parameters, 0);
    vector<double> max_bound(number_parameters, 0);

	// Variable Order: tot_inch = A[0], tot_incl = A[1]; ag_exph = A[2]; ag_expl = A[3]; mu = A[4] 
	// Wage rates: w^h = 16.07; w^l = 10.50
    min_bound[0] = 562.45;
    max_bound[0] = 883.85;
    min_bound[1] = 315.00;
    max_bound[1] = 525.00;
    min_bound[2] = 401.75;
    max_bound[2] = 883.85;
	min_bound[3] = 262.50;
	max_bound[3] = 525.00;
	min_bound[4] = 0.01;
	max_bound[4] = 100.00;

	(*output_csv) << "Bounds: I^h, I^l, e^h, e^l, mu" << endl;
	(*output_csv) << "Min Bound: " << vector_to_string(min_bound) << endl;
	(*output_csv) << "Max Bound: " << vector_to_string(max_bound) << endl;
	(*output_csv) << "Penalty Value: " << penalty_value << endl;

	// Search type code
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
        for (int i = 0; i < 50; i++) {
            (*output_csv) << endl << "Running particle swarm: " << i << endl;

            ParticleSwarm ps(min_bound, max_bound, arguments);
            ps.iterate(objective_function);

            double global_best_fitness = ps.get_global_best_fitness();
            vector<double> global_best = ps.get_global_best();

            (*output_csv) << global_best_fitness << " -- " << vector_to_string(global_best) << endl;
            check_solution(global_best[0], global_best[1], global_best[2], global_best[3], global_best[4]);
        }

    } else if (search_type.compare("de") == 0) {
        for (int i = 0; i < 50; i++) {
            (*output_csv) << endl << "Running differential evolution: " << i << endl;

            DifferentialEvolution de(min_bound, max_bound, arguments);
            de.iterate(objective_function);

            double global_best_fitness = de.get_global_best_fitness();
            vector<double> global_best = de.get_global_best();

            (*output_csv) << global_best_fitness << " -- " << vector_to_string(global_best) << endl;
            check_solution(global_best[0], global_best[1], global_best[2], global_best[3], global_best[4]);
        }

    } else if (search_type.compare("sweep") == 0) {
        vector<double> step_size(5, 0);
        step_size[0] = 50;
        step_size[1] = 50;
        step_size[2] = 10;
		step_size[3] = 10;
		step_size[4] = 0.05;

        parameter_sweep(min_bound, max_bound, step_size, objective_function);

    } else if (search_type.compare("snm") == 0 || search_type.compare("gd") == 0 || search_type.compare("cgd") == 0) {
		vector<double> starting_point(5, 0);

#ifdef _MSC_VER
		srand(time(NULL));
        starting_point[0] = min_bound[0] + ((max_bound[0] - min_bound[0]) * ((double)rand()/(double)RAND_MAX));
        starting_point[1] = min_bound[1] + ((max_bound[1] - min_bound[1]) * ((double)rand()/(double)RAND_MAX));
        starting_point[2] = min_bound[2] + ((max_bound[2] - min_bound[2]) * ((double)rand()/(double)RAND_MAX));
        starting_point[3] = min_bound[3] + ((max_bound[3] - min_bound[3]) * ((double)rand()/(double)RAND_MAX));
        starting_point[4] = min_bound[4] + ((max_bound[4] - min_bound[4]) * ((double)rand()/(double)RAND_MAX));
#else
        srand48(time(NULL));
		starting_point[0] = min_bound[0] + ((max_bound[0] - min_bound[0]) * drand48());
        starting_point[1] = min_bound[1] + ((max_bound[1] - min_bound[1]) * drand48());
        starting_point[2] = min_bound[2] + ((max_bound[2] - min_bound[2]) * drand48());
        starting_point[3] = min_bound[3] + ((max_bound[3] - min_bound[3]) * drand48());
        starting_point[4] = min_bound[4] + ((max_bound[4] - min_bound[4]) * drand48());
#endif

        vector<double> step_size(5, 0);
        step_size[0] = 0.005;
        step_size[1] = 0.005;
        step_size[2] = 0.005;
        step_size[3] = 0.005;
        step_size[4] = 0.005;

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

            /*
            vector<double> values;
            values.push_back(554.493678067659);
            values.push_back(351.801407573766);
            values.push_back(490.04465848113);
            values.push_back(351.547612048929);
            values.push_back(17.3739636182224);

            cout << "Objective function returns: " << objective_function(values) << endl;
            */

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
