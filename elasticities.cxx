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

#include "multi_objective/stdafx.h"

using namespace std;

/**
 *  The following parameters are constant.
 */
double a = 67.98208;
double b = 7.113661;
double c = 30;

double cleanprice = 1.687429;
double dirtyprice = 1.072984;
double netwage = 7.478338;
double cleangood = 202.8819;
double dirtygood = 23.98821;
double leisuregood = 47.05382;
double time_endowment = 80;
double virtual_inc = 111.5087;
double total_income = 709.7757;

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

	double A_1 = A[0];
	double A_2 = A[1];
	double A_3 = A[2];
	double B_1 = A[3];
	double B_2 = A[4];
	double B_3 = A[5];

    /* mux_v > 0 */
    /* muy_v > 0 */
    /* mul_v > 0 */
    double mux_v = mux(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
    double muy_v = muy(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
    double mul_v = mul(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

     if (mux_v > 0) success_count++; f -= penalty_leq(0, mux_v);
     if (muy_v > 0) success_count++; f -= penalty_leq(0, muy_v);
     if (mul_v > 0) success_count++; f -= penalty_leq(0, mul_v);

    /* Elasticity Criteria: */
    double elastxp = dxdp(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( cleanprice / cleangood );        /* -1 < elastxp < 0; */
    double elastxq = dxdq(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( dirtyprice / cleangood );        /* abs val ( elastxq ) < 1; */
    double elastxw = dxdw(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( netwage / cleangood);            /* abs val ( elastxw ) < 1; */

     if (-2 < elastxp && elastxp < 0) success_count++; f -= penalty_out_inclusive(-1, 0, elastxp);
     if (-2 < elastxq && elastxq < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastxq);
     if (-2 < elastxw && elastxw < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastxw);

    double elastyp = dydp(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( cleanprice / dirtygood );        /* abs val ( elastyp ) < 1; */
    double elastyq = dydq(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( dirtyprice / dirtygood );        /* -1 < elastyq < 0; */
    double elastyw = dydw(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( netwage / dirtygood );           /* abs val ( elastyw ) < 1; */

     if (-2 < elastyp && elastyp < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastyp);
     if (-2 < elastyq && elastyq < 0) success_count++; f -= penalty_out_inclusive(-1, 0, elastyq);
     if (-2 < elastyw && elastyw < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastyw);

    double elastlp = dldp(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( cleanprice / leisuregood );      /* abs val ( elastlp ) < 1; */
    double elastlq = dldq(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( dirtyprice / leisuregood );      /* abs val ( elastlq ) < 1; */
    double elastlw = dldw(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( netwage / leisuregood );         /* abs val ( elastlw ) < 1; */

     if (-2 < elastlp && elastlp < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastlp);
     if (-2 < elastlq && elastlq < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastlq);
     if (-2 < elastlw && elastlw < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastlw);

    double etax = dxdI(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( total_income / cleangood );       /* 0 < etax > 2; */
    double etay = dydI(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( total_income / dirtygood );       /* 0 < etay > 2; */
    double etal = dldI(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( total_income / leisuregood );     /* 0 < etal > 2; */

     if (0 < etax && etax < 2.5) success_count++; f -= penalty_out_inclusive(0, 2, etax);
     if (0 < etay && etay < 2.5) success_count++; f -= penalty_out_inclusive(0, 2, etay);
     if (0 < etal && etal < 2.5) success_count++; f -= penalty_out_inclusive(0, 2, etal);

    /* report minor 2, minor 3, minor 4 */
    double minor2_v = minor2(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
    double minor3_v = minor3(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
    double minor4_v = minor4(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);


    if (success_count >= 14 && f > -0.01) {
        (*output_csv) << A[0] << ", " << A[1] << ", " << A[2] << ", " << A[3] << ", " << A[4] << ", " << A[5] << ", " << success_count << ", " << f << ", " << mux_v << ", " << muy_v << ", " << mul_v << ", " << elastxp << ", " << elastxq << ", " << elastxw << ", " << elastyp << ", " << elastyq << ", " << elastyw << ", " << elastlp << ", " << elastlq << ", " << elastlw << ", " << etax << ", " << etay << ", " << etal << ", " << minor2_v << ", " << minor3_v << ", " << minor4_v << endl;
    }

    return f;
}

double objective_function_verbose(const vector<double> &A) {
    double f = 0;
    vector<bool> success;
    vector<double> penalties;

	double A_1 = A[0];
	double A_2 = A[1];
	double A_3 = A[2];
	double B_1 = A[3];
	double B_2 = A[4];
	double B_3 = A[5];

    /* mux_v > 0 */
    /* muy_v > 0 */
    /* mul_v > 0 */
    double mux_v = mux(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
    double muy_v = muy(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
    double mul_v = mul(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

    success.push_back(mux_v > 0); penalties.push_back(penalty_leq(0, mux_v));
    success.push_back(muy_v > 0); penalties.push_back(penalty_leq(0, muy_v));
    success.push_back(mul_v > 0); penalties.push_back(penalty_leq(0, mul_v));

    /* Elasticity Criteria: */
    double elastxp = dxdp(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( cleanprice / cleangood );        /* -1 < elastxp < 0; */
    double elastxq = dxdq(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( dirtyprice / cleangood );        /* abs val ( elastxq ) < 1; */
    double elastxw = dxdw(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( netwage / cleangood);            /* abs val ( elastxw ) < 1; */

    success.push_back(-1 < elastxp && elastxp < 0); penalties.push_back(penalty_out_inclusive(-1, 0, elastxp));
    success.push_back(-1 < elastxq && elastxq < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastxq));
    success.push_back(-1 < elastxw && elastxw < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastxw));

    double elastyp = dydp(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( cleanprice / dirtygood );        /* abs val ( elastyp ) < 1; */
    double elastyq = dydq(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( dirtyprice / dirtygood );        /* -1 < elastyq < 0; */
    double elastyw = dydw(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( netwage / dirtygood );           /* abs val ( elastyw ) < 1; */

    success.push_back(-1 < elastyp && elastyp < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastyp));
    success.push_back(-1 < elastyq && elastyq < 0); penalties.push_back(penalty_out_inclusive(-1, 0, elastyq));
    success.push_back(-1 < elastyw && elastyw < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastyw));

    double elastlp = dldp(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( cleanprice / leisuregood );      /* abs val ( elastlp ) < 1; */
    double elastlq = dldq(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( dirtyprice / leisuregood );      /* abs val ( elastlq ) < 1; */
    double elastlw = dldw(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( netwage / leisuregood );         /* abs val ( elastlw ) < 1; */

    success.push_back(-1 < elastlp && elastlp < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastlp));
    success.push_back(-1 < elastlq && elastlq < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastlq));
    success.push_back(-1 < elastlw && elastlw < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastlw));

    double etax = dxdI(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( total_income / cleangood );       /* 0 < etax > 2; */
    double etay = dydI(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( total_income / dirtygood );       /* 0 < etay > 2; */
    double etal = dldI(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c) * ( total_income / leisuregood );     /* 0 < etal > 2; */

    success.push_back(0 < etax && etax < 2); penalties.push_back(penalty_out_inclusive(0, 2, etax));
    success.push_back(0 < etay && etay < 2); penalties.push_back(penalty_out_inclusive(0, 2, etay));
    success.push_back(0 < etal && etal < 2); penalties.push_back(penalty_out_inclusive(0, 2, etal));

    /* report minor 2, minor 3, minor 4 */
    double minor2_v = minor2(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
    double minor3_v = minor3(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);
    double minor4_v = minor4(cleangood, dirtygood, leisuregood, A_1, A_2, A_3, B_1, B_2, B_3, a, b, c);

    cout << "success:   " << vector_to_string(success) << endl;
    cout << "penalties: " << vector_to_string(penalties) << endl;

    cout << "fitness, mux, muy, mul, elastxp, elastxq, elastxw, elastyp, elastyq, elastyw, elastlp, elastlq, elastlw, etax, etay, etal, minor2, minor3, minor4, A_1, A_2, A_3, B_1, B_2, B_3" << endl;
    cout << f << ", " << mux_v << ", " << muy_v << ", " << mul_v << ", " << elastxp << ", " << elastxq << ", " << elastxw << ", " << elastyp << ", " << elastyq << ", " << elastyw << ", " << elastlp << ", " << elastlq << ", " << elastlw << ", " << etax << ", " << etay << ", " << etal << ", " << minor2_v << ", " << minor3_v << ", " << minor4_v << ", " << A[0] << ", " << A[1] << ", " << A[2] << A[3] << ", " << A[4] << ", " << A[5] << ", " << endl;

    return f;
}



int main(int number_arguments, char **argv) {
    vector<string> arguments(argv, argv + number_arguments);

    output_csv = new ofstream("elasticities_sweep.txt");
    (*output_csv) << "A_1, A_2, A_3, B_1, B_2, B_3, passed_constraints, fitness, mux, muy, mul, elastxp, elastxq, elastxw, elastyp, elastyq, elastyw, elastlp, elastlq, elastlw, etax, etay, etal, minor2, minor3, minor4" << endl;

    int number_parameters = 6;
    vector<double> min_bound(number_parameters, 0);
    vector<double> max_bound(number_parameters, 0);

    min_bound[0] = -3.0;
    max_bound[0] = 3.0;
    min_bound[1] = -3.0;
    max_bound[1] = 3.0;
    min_bound[2] = -3.0;
    max_bound[2] = 3.0;
	min_bound[3] = -3.0;
	max_bound[3] = 3.0;
	min_bound[4] = -3.0;
	max_bound[4] = 3.0;
	min_bound[5] = -3.0;
	max_bound[5] = 3.0;

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
		exit(0);
	}

    if (search_type.compare("ps") == 0) {
        ParticleSwarm ps(min_bound, max_bound, arguments);
        ps.iterate(objective_function);

    } else if (search_type.compare("de") == 0) {
        DifferentialEvolution de(min_bound, max_bound, arguments);
        de.iterate(objective_function);

    } else if (search_type.compare("sweep") == 0) {
        vector<double> step_size(6, 0);
        step_size[0] = 1.00;
        step_size[1] = 1.00;
        step_size[2] = 1.00;
		step_size[3] = 1.00;
		step_size[4] = 1.00;
		step_size[5] = 1.00;

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

    } else {
        fprintf(stderr, "Improperly specified search type: '%s'\n", search_type.c_str());
        fprintf(stderr, "Possibilities are:\n");
        fprintf(stderr, "    de     -       differential evolution\n");
        fprintf(stderr, "    ps     -       particle swarm optimization\n");
        fprintf(stderr, "    snm    -       synchronous newton method\n");
        fprintf(stderr, "    gd     -       gradient descent\n");
        fprintf(stderr, "    cgd    -       conjugate gradient descent\n");
		fprintf(stderr, "    sweep  -       parameter sweep\n");
        exit(0);
    }

    output_csv->close();
    delete output_csv;

    return 0;
}
