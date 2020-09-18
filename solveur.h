#ifndef SOLVEUR_H
#define SOLVEUR_H

#include <iostream>
#include <string>
#include <vector>

#include "./maillage.h"

using namespace std;

class Solveur
{
private:
    string *_schema;
    double *_deltaT;
    Maillage *_maillage;
    vector<double> *_solution;
    double *_c;
    string *_frontiere;

public:
    Solveur(double *cfl, double *c, string *schema, vector<double> *condition_init, Maillage *maillage, string *frontiere);
    ~Solveur();

    Maillage *getMaillage();
    double *getDeltaT();
    vector<double> *getSolution();
    vector<double> *getNextSolution();
};
#endif