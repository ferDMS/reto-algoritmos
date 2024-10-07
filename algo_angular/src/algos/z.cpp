#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Implementación del algoritmo Z
vector<int> z_algo(const string &text, const string &pattern)
{
    string combined = pattern + "$" + text;
    int len = combined.length();
    vector<int> Z(len, 0);

    int L = 0, R = 0;
    for (int i = 1; i < len; ++i)
    {
        if (i <= R)
        {
            Z[i] = min(R - i + 1, Z[i - L]);
        }

        while (i + Z[i] < len && combined[Z[i]] == combined[i + Z[i]])
        {
            Z[i]++;
        }

        if (i + Z[i] - 1 > R)
        {
            L = i;
            R = i + Z[i] - 1;
        }
    }

    vector<int> positions;
    for (int i = pattern.length() + 1; i < len; ++i)
    {
        if (Z[i] == pattern.length())
        {
            positions.push_back(i - pattern.length() - 1);
        }
    }

    return positions;
}

// Función para mostrar los resultados
void print_positions(const vector<int>& positions) {
        for (int pos : positions) {
            cout << pos << " ";
        }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << "[filename] [pattern]" << endl;
        return 1;
    }

    string filename = argv[1];
    string pattern = argv[2];
    string text;

    // Leer el archivo de texto
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return 1;
    }

    // Leer el contenido del archivo completo
    getline(file, text, '\0'); // leer todo el archivo como un string
    file.close();

    // Ejecutar el algoritmo Z y mostrar las posiciones encontradas
    vector<int> result = z_algo(text, pattern);
    print_positions(result);

    return 0;
}
