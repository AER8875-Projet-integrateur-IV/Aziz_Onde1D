#include "./onde1D.h"

int main(int argc, char *argv[])
{
	Onde1D *onde = new Onde1D();
	onde->startOnde1D(argc, argv);
	delete onde;
	return 0;
}