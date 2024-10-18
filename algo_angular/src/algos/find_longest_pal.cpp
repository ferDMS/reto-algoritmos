#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Preprocesa el string para manejar palíndromos pares
string preprocess(const string &s)
{
    string t = "^";
    for (char c : s)
        t += "#" + string(1, c);
    t += "#$";
    return t;
}

// Convierte todas las letras mayúsculas a minúsculas
string to_lowercase(const string &s)
{
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Implementación del algoritmo de Manacher
pair<int, int> manacher_algo(const string &s)
{
    string t = preprocess(s);
    int m = t.length();
    vector<int> p(m, 0);

    int center = 0, right = 0;
    int max_len = 0, start = 0;

    for (int i = 1; i < m - 1; ++i)
    {
        if (i < right)
        {
            int j = 2 * center - i;
            p[i] = min(right - i, p[j]);
        }

        // Expandir palíndromo en ambos lados
        while (t[i + p[i] + 1] == t[i - p[i] - 1])
        {
            p[i]++;
        }

        if (i + p[i] > right)
        {
            center = i;
            right = i + p[i];
        }

        if (p[i] > max_len)
        {
            max_len = p[i];
            start = (i - max_len) / 2;
        }
    }

    return {start, max_len};
}

// Función principal para ejecutar con archivo de texto
int main()
{
    string filename = "../testcases/text1.txt";
    string text;

    // Leer el archivo de texto
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return 1;
    }

    getline(file, text, '\0');
    file.close();

    // Convertir el texto a minúsculas
    text = to_lowercase(text);

    // Ejecutar el algoritmo de Manacher
    pair<int, int> result = manacher_algo(text);
    int start = result.first;
    int length = result.second;
    string palindrome = text.substr(start, length);

    // Mostrar el resultado en formato JSON
    cout << "{\n";
    cout << "    \"pal\": \"" << palindrome << "\",\n";
    cout << "    \"start\": " << start << ",\n";
    cout << "    \"end\": " << start + length - 1 << "\n";
    cout << "}" << endl;

    return 0;
}