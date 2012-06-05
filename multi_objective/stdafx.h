#ifndef MULTI_OBJECTIVE_STDAFK_H
#define MULTI_OBJECTIVE_STDAFK_H

double den(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);

double deninc(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);

double dldMnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dldpnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dldqnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dldwnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dxdMnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dxdpnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dxdqnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dxdwnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dydMnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dydpnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dydqnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);
double dydwnum(double cleanprice, double dirtyprice, double netwage, double time_endowment, double virtual_inc, double A_1, double A_2, double A_3, double a, double b, double c);

double minor2(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c);
double minor3(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c);
double minor4(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c);

double mul(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c);
double mux(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c);
double muy(double cleangood, double dirtygood, double leisuregood, double A_1, double A_2, double A_3, double a, double b, double c);

#endif
