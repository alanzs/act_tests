// Descripción breve del programa:
// Este programa analiza transmisiones en busca de código malicioso y patrones específicos como palíndromos y substrings comunes.
//
// Autores:
// Juan Diego Susunaga Velásquez - A01764884
// Manuel Alejandro Cruz Valladares - A00836441
// Adrián Salazar Rodríguez - A00835314
// Alan Sanmiguel Garay - A00837404
//
// Fecha: 06/04/2025

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

// Función que lee un archivo y devuelve su contenido como un string
string leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary); // Se abre el archivo en modo binario
    if (!archivo) {
        cerr << "Error: Archivo no encontrado - " << nombreArchivo << endl;
        exit(EXIT_FAILURE); // Si el archivo no se encuentra, termina la ejecución del programa
    }

    string contenido; // Variable para almacenar el contenido del archivo
    archivo.seekg(0, ios::end); // Mueve el cursor al final del archivo
    contenido.resize(archivo.tellg()); // Redimensiona el string para ajustarse al tamaño del archivo
    archivo.seekg(0, ios::beg); // Vuelve al inicio del archivo
    archivo.read(&contenido[0], contenido.size()); // Lee el contenido del archivo al string
    return contenido;
}

// Función que busca una subcadena en un texto
int buscarSubcadena(const string& texto, const string& patron) {
    size_t pos = texto.find(patron); // Busca la subcadena en el texto
    return pos != string::npos ? static_cast<int>(pos) + 1 : -1; // Retorna la posición de la subcadena o -1 si no se encuentra
}

// Función que expande alrededor de un centro para encontrar palíndromos
void expandirCentro(const string& s, int izq, int der, int& inicio, int& maxLong) {
    while (izq >= 0 && der < s.length() && s[izq] == s[der]) {
        int longitudActual = der - izq + 1; // Calcula la longitud del palíndromo actual
        if (longitudActual > maxLong) { // Si es el palíndromo más largo encontrado hasta ahora
            inicio = izq; // Actualiza la posición de inicio
            maxLong = longitudActual; // Actualiza la longitud máxima
        }
        izq--; // Se mueve hacia la izquierda
        der++; // Se mueve hacia la derecha
    }
}

// Función que devuelve el palíndromo más largo en una cadena
tuple<int, int, string> palindromoMasLargo(const string& s) {
    if (s.empty()) return {0, 0, ""}; // Si la cadena está vacía, retorna valores por defecto

    int inicio = 0, maxLong = 1; // Inicializa las variables de inicio y longitud máxima

    // Se buscan palíndromos en todos los centros posibles
    for (int i = 0; i < s.length(); i++) {
        expandirCentro(s, i, i, inicio, maxLong); // Palíndromos de longitud impar
        expandirCentro(s, i, i + 1, inicio, maxLong); // Palíndromos de longitud par
    }

    string resultado = s.substr(inicio, maxLong); // Extrae el palíndromo más largo
    return {inicio + 1, inicio + maxLong, resultado}; // Devuelve las posiciones y el palíndromo
}

// Función que encuentra la subsecuencia común más larga (LCS) entre dos cadenas
tuple<int, int, int, int, string> lcs(const string& X, const string& Y) {
    int m = X.length(), n = Y.length();
    vector<vector<int>> dp(2, vector<int>(n + 1, 0)); // Matriz para almacenar las longitudes de las subsecuencias comunes
    int max_len = 0, end_X = 0, end_Y = 0; // Variables para almacenar la longitud máxima y las posiciones finales

    // Llenar la matriz dp con las longitudes de las subsecuencias comunes
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) { // Si los caracteres son iguales
                dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + 1; // Se actualiza la longitud de la subsecuencia
                if (dp[i % 2][j] > max_len) { // Si la subsecuencia encontrada es más larga
                    max_len = dp[i % 2][j]; // Actualiza la longitud máxima
                    end_X = i - 1; // Actualiza la posición final en X
                    end_Y = j - 1; // Actualiza la posición final en Y
                }
            } else {
                dp[i % 2][j] = 0; // Si no hay coincidencia, la longitud de la subsecuencia es 0
            }
        }
    }

    if (max_len == 0) return {0, 0, 0, 0, ""}; // Si no se encuentra ninguna subsecuencia común

    int start_X = end_X - max_len + 1; // Calcula la posición de inicio en X
    int start_Y = end_Y - max_len + 1; // Calcula la posición de inicio en Y
    string substr = X.substr(start_X, max_len); // Extrae la subsecuencia común
    return {start_X + 1, end_X + 1, start_Y + 1, end_Y + 1, substr}; // Devuelve las posiciones y la subsecuencia
}