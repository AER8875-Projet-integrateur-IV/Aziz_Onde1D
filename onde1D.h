#ifndef ONDE1D_H
#define ONDE1D_H

#include <iostream>
#include <string>
#include <vector>
#include "./maillage.h"
#include "./solveur.h"

using namespace std;

class Onde1D
{
private:
    double *_cfl;
    int *_nPts;
    string *_schema;
    double *_l;
    double *_c;
    string *_frontiere;
    Maillage *_maillage;
    Solveur *_solveur;
    bool _error;

    void displayHelp(string name);
    void setInput(int argc, char *argv[]);
    void saveSolution(string path, int nbDeltaT, int type_);

public:
    Onde1D();
    ~Onde1D();

    void startOnde1D(int argc, char *argv[]);
};
#endif