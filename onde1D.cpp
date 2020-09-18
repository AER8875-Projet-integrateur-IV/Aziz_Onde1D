#include "./onde1D.h"

Onde1D::Onde1D()
{
    _cfl = new double();
    _nPts = new int();
    _schema = new string("Centre");        // Autres options: Forward, Backward
    _l = new double(100.0);                // Longueur du domaine
    _c = new double(300.0);                // Vitesse de l'onde
    _frontiere = new string("periodique"); // Autre option symmetrique
    return;
}

Onde1D::~Onde1D()
{

    delete _nPts;
    delete _frontiere;
    delete _schema;
    delete _cfl;
    delete _c;
    delete _l;
    if (!_error)
    {
        delete _maillage;
        delete _solveur;
    }
    return;
}
void Onde1D::displayHelp(string name)
{
    cerr << "Utilisation de " << name << ":\n"
         << "Liste des Options:\n"
         << "\t-h,--help\t\tAfficher l'aide\n"
         << "\t-c,--cfl CFL\t\tDonner la valeur du CFL ***\n"
         << "\t-n,--nPts NOMBRE_DE_POINTS\t\tDonner le nombre "
         << "de points du maillage ***\n"
         << "\t-s,--schema SCHEMA\t\tDonner le schema à utiliser\n"
         << "\t--Longueur LONGUEUR\t\tDonner la longueur du domaine\n"
         << "\t--Vitesse VITESSE\t\tDonner la vitesse de l'onde\n"
         << "\t--Frontiere FRONTIERE\t\tDonner la condition au frontiere\n"
         << "\n\tLes options *** sont obligatoires"
         << endl;
}
void Onde1D::setInput(int argc, char *argv[])
{
    _error = false;
    int verif_input = 2;
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];
        if ((arg == "-h") || (arg == "--help"))
        {
            displayHelp(argv[0]);
            return;
        }
        else if ((arg == "-c") || (arg == "--cfl"))
        {
            if (i + 1 < argc)
            { // Make sure we aren't at the end of argv!
                *_cfl = stod(argv[++i]);
                --verif_input;
            }
            else
            {
                cerr << "La valeur du CFL n'est pas fournie." << endl;
                return;
            }
        }
        else if ((arg == "-n") || (arg == "--nPts"))
        {
            if (i + 1 < argc)
            {
                *_nPts = stoi(argv[++i]);
                --verif_input;
            }
            else
            {
                cerr << "Le nombre de points n'est pas fournie." << endl;
                return;
            }
        }
        else if ((arg == "-s") || (arg == "--schema"))
        {
            if (i + 1 < argc)
            {
                *_schema = argv[++i];
            }
        }
        else if (arg == "--Longueur")
        {
            if (i + 1 < argc)
            {
                *_l = stod(argv[++i]);
            }
        }
        else if (arg == "--Vitesse")
        {
            if (i + 1 < argc)
            {
                *_c = stod(argv[++i]);
            }
        }
    }
    if (verif_input)
    {
        cout << "Entrées incorrectes.\n";
        _error = true;
    }
    /**
    cout <<"Input:\n"
         << " CFL : " << *_cfl << endl
         << "nPTS: " << *_nPts << endl
         << "schema: " << *_schema << endl
         << "longueur: " << *_l << endl
         << "Vitesse: " << *_c << endl;
    return;
    **/
}

void Onde1D::startOnde1D(int argc, char *argv[])
{
    setInput(argc, argv);
    if (!_error)
    {
        _maillage = new Maillage(_nPts, _l);
        vector<vector<double>> *Cells = _maillage->getCells();
        vector<double> *condInit = new vector<double>();
        for (size_t i = 0; i < Cells->size(); i++)
        {
            if (Cells->at(i)[2] <= 60.0 && Cells->at(i)[2] >= 40)
            {
                condInit->push_back(100.0);
            }
            else
            {
                condInit->push_back(0.0);
            }
        }
        _solveur = new Solveur(_cfl, _c, _schema, condInit, _maillage, _frontiere);
        saveSolution("../resultats.dat", 51, 0);
    }
    return;
}

void Onde1D::saveSolution(string path, int nbDeltaT, int type_)
{
    FILE *_file = fopen(path.c_str(), "w");
    if (_file == NULL)
    {
        printf("could not open %s.\n", path.c_str());
        system("pause");
        exit(1);
    }
    if (type_ == 1)
    {

        for (int i = 0; i < nbDeltaT; i++)
        {
            fprintf(_file, "### Temps (s): %d  %f\n", i, *_solveur->getDeltaT() * i);
            vector<double> *solution;
            if (i == 0)
            {
                solution = _solveur->getSolution();
            }
            else
            {
                solution = _solveur->getNextSolution();
            }
            vector<vector<double>> *cellules = _maillage->getCells();
            for (size_t j = 0; j < solution->size(); j++)
            {
                fprintf(_file, "%f\t\t%f\n", cellules->at(j)[2], solution->at(j));
            }
            fprintf(_file, "\n");
        }
    }
    else
    {

        for (int i = 0; i < nbDeltaT; i++)
        {
            vector<double> *solution;
            if (i == 0)
            {
                solution = _solveur->getSolution();
            }
            else
            {
                solution = _solveur->getNextSolution();
            }
            if (i == nbDeltaT - 1)
            {
                fprintf(_file, "### Temps t = %f(s)\n", *_solveur->getDeltaT() * i);
                vector<vector<double>> *cellules = _maillage->getCells();
                for (size_t j = 0; j < solution->size(); j++)
                {
                    fprintf(_file, "%f\t\t%f\n", cellules->at(j)[2], solution->at(j));
                }
                fprintf(_file, "\n");
            }
        }
    }

    fclose(_file);
}
