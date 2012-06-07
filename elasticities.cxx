#include <cfloat>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "particle_swarm.hxx"
#include "differential_evolution.hxx"

#include "parameter_sweep.hxx"

//from undvc_common
#include "arguments.hxx"
#include "vector_io.hxx"

#include "multi_objective/stdafx.h"

using namespace std;

/**
 *  The following parameters are constant.
 */
double a = 79.51798;
double b = 17.79808;
double c = 12.70294;

double cleanprice = 1.687396;
double dirtyprice = 1.073141;
double netwage = 9.596359;
double cleangood = 202.9236;
double dirtygood = 23.97178;
double leisuregood = 38.01983;
double time_endowment = 70;
double virtual_inc = 88.3237;
double total_income = 760.0689;

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

double fitness(const vector<double> &A) {
    double f = 0;
    uint32_t success_count = 0;

    /* mux_v > 0 */
    /* muy_v > 0 */
    /* mul_v > 0 */
    double mux_v = mux(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);
    double muy_v = muy(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);
    double mul_v = mul(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);

     if (mux_v > 0) success_count++; f -= penalty_leq(0, mux_v);
     if (muy_v > 0) success_count++; f -= penalty_leq(0, muy_v);
     if (mul_v > 0) success_count++; f -= penalty_leq(0, mul_v);

    double den_v = den(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c);
    double den_inc = deninc(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c);

    /* Elasticity Criteria: */
    double elastxp = ( dxdpnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( cleanprice / cleangood );        /* -1 < elastxp < 0; */
    double elastxq = ( dxdqnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( dirtyprice / cleangood );        /* abs val ( elastxq ) < 1; */
    double elastxw = ( dxdwnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( netwage / cleangood);            /* abs val ( elastxw ) < 1; */

     if (-2 < elastxp && elastxp < 0) success_count++; f -= penalty_out_inclusive(-1, 0, elastxp);
     if (-2 < elastxq && elastxq < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastxq);
     if (-2 < elastxw && elastxw < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastxw);

    double elastyp = ( dydpnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( cleanprice / dirtygood );        /* abs val ( elastyp ) < 1; */
    double elastyq = ( dydqnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( dirtyprice / dirtygood );        /* -1 < elastyq < 0; */
    double elastyw = ( dydwnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( netwage / dirtygood );           /* abs val ( elastyw ) < 1; */

     if (-2 < elastyp && elastyp < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastyp);
     if (-2 < elastyq && elastyq < 0) success_count++; f -= penalty_out_inclusive(-1, 0, elastyq);
     if (-2 < elastyw && elastyw < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastyw);

    double elastlp = ( dldpnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( cleanprice / leisuregood );      /* abs val ( elastlp ) < 1; */
    double elastlq = ( dldqnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( dirtyprice / leisuregood );      /* abs val ( elastlq ) < 1; */
    double elastlw = ( dldwnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( netwage / leisuregood );         /* abs val ( elastlw ) < 1; */

     if (-2 < elastlp && elastlp < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastlp);
     if (-2 < elastlq && elastlq < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastlq);
     if (-2 < elastlw && elastlw < 2) success_count++; f -= penalty_out_inclusive(-1, 1, elastlw);

    double etax = ( dxdMnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_inc ) * ( total_income / cleangood );       /* 0 < etax > 2; */
    double etay = ( dydMnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_inc ) * ( total_income / dirtygood );       /* 0 < etay > 2; */
    double etal = ( dldMnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_inc ) * ( total_income / leisuregood );     /* 0 < etal > 2; */

     if (0 < etax && etax < 2.5) success_count++; f -= penalty_out_inclusive(0, 2, etax);
     if (0 < etay && etay < 2.5) success_count++; f -= penalty_out_inclusive(0, 2, etay);
     if (0 < etal && etal < 2.5) success_count++; f -= penalty_out_inclusive(0, 2, etal);

    /* report minor 2, minor 3, minor 4 */
    double minor2_v = minor2(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);
    double minor3_v = minor3(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);
    double minor4_v = minor4(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);


    if (success_count >= 14 && f > -0.01) {
        (*output_csv) << A[0] << ", " << A[1] << ", " << A[2] << ", " << success_count << ", " << f << ", " << mux_v << ", " << muy_v << ", " << mul_v << ", " << elastxp << ", " << elastxq << ", " << elastxw << ", " << elastyp << ", " << elastyq << ", " << elastyw << ", " << elastlp << ", " << elastlq << ", " << elastlw << ", " << etax << ", " << etay << ", " << etal << ", " << minor2_v << ", " << minor3_v << ", " << minor4_v << endl;
    }

    return f;
}

double fitness_verbose(const vector<double> &A) {
    double f = 0;
    vector<bool> success;
    vector<double> penalties;

    /* mux_v > 0 */
    /* muy_v > 0 */
    /* mul_v > 0 */
    double mux_v = mux(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);
    double muy_v = muy(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);
    double mul_v = mul(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);

    success.push_back(mux_v > 0); penalties.push_back(penalty_leq(0, mux_v));
    success.push_back(muy_v > 0); penalties.push_back(penalty_leq(0, muy_v));
    success.push_back(mul_v > 0); penalties.push_back(penalty_leq(0, mul_v));

    double den_v = den(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c);
    double den_inc = deninc(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c);

    /* Elasticity Criteria: */
    double elastxp = ( dxdpnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( cleanprice / cleangood );        /* -1 < elastxp < 0; */
    double elastxq = ( dxdqnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( dirtyprice / cleangood );        /* abs val ( elastxq ) < 1; */
    double elastxw = ( dxdwnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( netwage / cleangood);            /* abs val ( elastxw ) < 1; */

    success.push_back(-1 < elastxp && elastxp < 0); penalties.push_back(penalty_out_inclusive(-1, 0, elastxp));
    success.push_back(-1 < elastxq && elastxq < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastxq));
    success.push_back(-1 < elastxw && elastxw < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastxw));

    double elastyp = ( dydpnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( cleanprice / dirtygood );        /* abs val ( elastyp ) < 1; */
    double elastyq = ( dydqnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( dirtyprice / dirtygood );        /* -1 < elastyq < 0; */
    double elastyw = ( dydwnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( netwage / dirtygood );           /* abs val ( elastyw ) < 1; */

    success.push_back(-1 < elastyp && elastyp < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastyp));
    success.push_back(-1 < elastyq && elastyq < 0); penalties.push_back(penalty_out_inclusive(-1, 0, elastyq));
    success.push_back(-1 < elastyw && elastyw < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastyw));

    double elastlp = ( dldpnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( cleanprice / leisuregood );      /* abs val ( elastlp ) < 1; */
    double elastlq = ( dldqnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( dirtyprice / leisuregood );      /* abs val ( elastlq ) < 1; */
    double elastlw = ( dldwnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_v ) * ( netwage / leisuregood );         /* abs val ( elastlw ) < 1; */

    success.push_back(-1 < elastlp && elastlp < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastlp));
    success.push_back(-1 < elastlq && elastlq < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastlq));
    success.push_back(-1 < elastlw && elastlw < 1); penalties.push_back(penalty_out_inclusive(-1, 1, elastlw));

    double etax = ( dxdMnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_inc ) * ( total_income / cleangood );       /* 0 < etax > 2; */
    double etay = ( dydMnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_inc ) * ( total_income / dirtygood );       /* 0 < etay > 2; */
    double etal = ( dldMnum(cleanprice, dirtyprice, netwage, time_endowment, virtual_inc, A[0], A[1], A[2], a, b, c) / den_inc ) * ( total_income / leisuregood );     /* 0 < etal > 2; */

    success.push_back(0 < etax && etax < 2); penalties.push_back(penalty_out_inclusive(0, 2, etax));
    success.push_back(0 < etay && etay < 2); penalties.push_back(penalty_out_inclusive(0, 2, etay));
    success.push_back(0 < etal && etal < 2); penalties.push_back(penalty_out_inclusive(0, 2, etal));

    /* report minor 2, minor 3, minor 4 */
    double minor2_v = minor2(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);
    double minor3_v = minor3(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);
    double minor4_v = minor4(cleangood, dirtygood, leisuregood, A[0], A[1], A[2], a, b, c);

    cout << "success:   " << vector_to_string(success) << endl;
    cout << "penalties: " << vector_to_string(penalties) << endl;

    cout << "fitness, mux, muy, mul, elastxp, elastxq, elastxw, elastyp, elastyq, elastyw, elastlp, elastlq, elastlw, etax, etay, etal, minor2, minor3, minor4, A_1, A_2, A_3" << endl;
    cout << f << ", " << mux_v << ", " << muy_v << ", " << mul_v << ", " << elastxp << ", " << elastxq << ", " << elastxw << ", " << elastyp << ", " << elastyq << ", " << elastyw << ", " << elastlp << ", " << elastlq << ", " << elastlw << ", " << etax << ", " << etay << ", " << etal << ", " << minor2_v << ", " << minor3_v << ", " << minor4_v << ", " << A[0] << ", " << A[1] << ", " << A[2] << endl;

    return f;
}



int main(int number_arguments, char **argv) {
    vector<string> arguments(argv, argv + number_arguments);

    output_csv = new ofstream("elasticities_sweep.txt");
    (*output_csv) << "A_1, A_2, A_3, passed_constraints, fitness, mux, muy, mul, elastxp, elastxq, elastxw, elastyp, elastyq, elastyw, elastlp, elastlq, elastlw, etax, etay, etal, minor2, minor3, minor4" << endl;

    int number_parameters = 3;
    vector<double> min_bound(number_parameters, 0);
    vector<double> max_bound(number_parameters, 0);

    min_bound[0] = -3.0;
    max_bound[0] = 3.0;
    min_bound[1] = -3.0;
    max_bound[1] = 3.0;
    min_bound[2] = -3.0;
    max_bound[2] = 3.0;

    string search_type;
    get_argument(arguments, "--search_type", true, search_type);

    if (search_type.compare("ps") == 0) {
        ParticleSwarm ps(min_bound, max_bound, arguments);
        ps.iterate(fitness);

    } else if (search_type.compare("de") == 0) {
        DifferentialEvolution de(min_bound, max_bound, arguments);
        de.iterate(fitness);

    } else if (search_type.compare("sweep") == 0) {
        vector<double> step_size(6, 0);
        step_size[0] = 0.005;
        step_size[1] = 0.005;
        step_size[2] = 0.005;

        parameter_sweep(min_bound, max_bound, step_size, fitness);

    } else {
        fprintf(stderr, "Improperly specified search type: '%s'\n", search_type.c_str());
        fprintf(stderr, "Possibilities are:\n");
        fprintf(stderr, "    de     -       differential evolution\n");
        fprintf(stderr, "    ps     -       particle swarm optimization\n");
        exit(0);
    }

    output_csv->close();
    delete output_csv;

    return 0;
}
