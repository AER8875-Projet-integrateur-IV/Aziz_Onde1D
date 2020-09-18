#include "maillage.h"

Maillage::Maillage(int *nbPts, double *l)
{
    _deltaX = new double(*l / (*nbPts - 1));
    _nodes = new vector<double>();
    for (int i = 0; i < *nbPts + 2; i++)
    {
        _nodes->push_back(i * (*_deltaX) - (*_deltaX));
    }
    _cells = new vector<vector<double>>();
    for (int i = 0; i < *nbPts + 1; i++)
    {
        _cells->push_back(vector<double>());
        _cells->at(i).push_back(i);
        _cells->at(i).push_back(i + 1);
        _cells->at(i).push_back(0.5 * (_nodes->at(i) + _nodes->at(i + 1)));
        if (i == 0 || i == *nbPts)
        {
            _cells->at(i).push_back(0); //cellule fantome
        }
        else
        {
            _cells->at(i).push_back(1);
        }
    }
    return;
}

Maillage::~Maillage()
{
    delete _deltaX;
    delete _nodes;
    delete _cells;
    return;
}

vector<double> *Maillage::getNodes()
{
    return _nodes;
}
vector<vector<double>> *Maillage::getCells()
{
    return _cells;
}
double *Maillage::getDeltaX()
{
    return _deltaX;
}