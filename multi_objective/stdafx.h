#ifndef MULTI_OBJECTIVE_STDAFK_H
#define MULTI_OBJECTIVE_STDAFK_H

double dldI(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dldp(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dldq(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dldw(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dxdI(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dxdp(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dxdq(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dxdw(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dydI(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dydp(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dydq(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double dydw(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);

double minor2(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double minor3(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double minor4(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);

double mul(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double mux(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);
double muy(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double B_1, double B_2, double B_3, double a, double b, double c);

#endif
