#ifndef MAILLAGE_H
#define MAILLAGE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Maillage
{
private:
    double *_deltaX;
    vector<double> *_nodes;
    vector<vector<double>> *_cells;

public:
    Maillage(int *nbPts, double *l);
    ~Maillage();

    vector<double> *getNodes();
    vector<vector<double>> *getCells();
    double *getDeltaX();
};
#endif