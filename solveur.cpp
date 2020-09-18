#include "solveur.h"

Solveur::Solveur(double *cfl, double *c, string *schema, vector<double> *condition_init, Maillage *maillage, string *frontiere)
{
    _maillage = maillage;
    _solution = condition_init; //A revoir
    _schema = schema;
    _c = c;
    _frontiere = frontiere;
    _deltaT = new double((*cfl) * (*(_maillage->getDeltaX())) / (*_c));
    return;
}

Solveur::~Solveur()
{
    delete _deltaT;
    delete _solution;
    return;
}

Maillage *Solveur::getMaillage()
{
    return _maillage;
}

vector<double> *Solveur::getSolution()
{
    return _solution;
}

vector<double> *Solveur::getNextSolution()
{
    vector<double> temp = vector<double>();
    double cfl = (*_c) * (*_deltaT) / (*(_maillage->getDeltaX()));
    if (*_schema == "Centre")
    {
        for (size_t i = 1; i < _solution->size() - 1; i++)
        {
            temp.push_back(_solution->at(i) - 0.5 * cfl * (_solution->at(i + 1) - _solution->at(i - 1)));
        }
    }
    else if (*_schema == "Backward")
    {
        for (size_t i = 1; i < _solution->size() - 1; i++)
        {
            temp.push_back(_solution->at(i) - cfl * (_solution->at(i) - _solution->at(i - 1)));
        }
    }
    else if (*_schema == "Forward")
    {
        for (size_t i = 1; i < _solution->size() - 1; i++)
        {
            temp.push_back(_solution->at(i) - cfl * (_solution->at(i + 1) - _solution->at(i)));
        }
    }
    else
    {
        cout << "Le schema entré est incorrect\n";
        system("pause");
        exit(1);
    }
    for (size_t i = 1; i < _solution->size(); i++)
    {
        if (i == _solution->size() - 1)
        {
            // Applicaton des conditions aux frontières
            if (*_frontiere == "periodique")
            {
                _solution->at(0) = _solution->at(i - 1);
                _solution->at(i) = _solution->at(1);
            }
            else if (*_frontiere == "symmetrique")
            {
                _solution->at(0) = -_solution->at(1);
                _solution->at(i) = -_solution->at(i - 1);
            }
            else
            {
                cout << "Conditions aux frontières '"
                     << *_frontiere << "' non implémentées.\n";
                system("pause");
                exit(1);
            }
        }
        else
        {
            _solution->at(i) = temp[i - 1];
        }
    }
    return _solution;
}

double *Solveur::getDeltaT()
{
    return _deltaT;
}