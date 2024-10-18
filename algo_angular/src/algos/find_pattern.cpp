#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Implementación del algoritmo Z
vector<pair<int, int>> z_algo(const string &text, const string &pattern)
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

    vector<pair<int, int>> intervals;
    int last_end = -1;
    for (int i = pattern.length() + 1; i < len; ++i)
    {
        if (Z[i] == pattern.length())
        {
            int start = i - pattern.length() - 1;
            int end = start + pattern.length() - 1;
            if (start > last_end)
            {
                intervals.push_back({start, end});
                last_end = end;
            }
        }
    }

    return intervals;
}

// Función para mostrar los resultados
void print_intervals(const vector<pair<int, int>>& intervals) {
    for (const auto& interval : intervals) {
        cout << "(" << interval.first << ", " << interval.second << ") ";
    }
    cout << endl;
}

int main() {
    // Leer el patrón desde ../testcases/input.txt
    ifstream patternFile("../testcases/input.txt");
    if (!patternFile.is_open()) {
        cerr << "Error al abrir el archivo de entrada: ../testcases/input.txt" << endl;
        return 1;
    }

    string pattern;
    getline(patternFile, pattern);
    patternFile.close();

    // Leer el texto desde ../testcases/text1.txt
    ifstream textFile("../testcases/text1.txt");
    if (!textFile.is_open()) {
        cerr << "Error al abrir el archivo: ../testcases/text1.txt" << endl;
        return 1;
    }

    string text;
    getline(textFile, text, '\0'); // leer todo el archivo como un string
    textFile.close();

    // Ejecutar el algoritmo Z y obtener las posiciones encontradas
    vector<pair<int, int>> result = z_algo(text, pattern);

    // Construir la cadena JSON manualmente
    string jsonOutput = "[\n";
    for (size_t i = 0; i < result.size(); ++i) {
        jsonOutput += "    {\"start\": " + to_string(result[i].first) + ", \"end\": " + to_string(result[i].second) + "}";
        if (i < result.size() - 1) {
            jsonOutput += ",";
        }
        jsonOutput += "\n";
    }
    jsonOutput += "]";

    // Escribir la cadena JSON en un archivo
    ofstream outputFile("../testcases/output.json");
    if (outputFile.is_open()) {
        outputFile << jsonOutput;
        outputFile.close();
    } else {
        cerr << "Error al abrir el archivo de salida: ../testcases/output.json" << endl;
        return 1;
    }

    return 0;
}