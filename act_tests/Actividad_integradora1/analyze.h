#ifndef analyze.h
#define analyze.h

#include <string>
#include <tuple>

using namespace std;

string leerArchivo(const string& nombreArchivo);
int buscarSubcadena(const string& texto, const string& patron);
tuple<int, int, string> palindromoMasLargo(const string& s);
tuple<int, int, int, int, string> lcs(const string& X, const string& Y);

#endif
