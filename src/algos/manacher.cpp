#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Uso: " << argv[0] << "[filename]" << endl;
        return 1;
    }

    string filename = argv[1];
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

    // Ejecutar el algoritmo de Manacher
    pair<int, int> result = manacher_algo(text);

    // Mostrar el resultado
    cout << result.first << ", " << result.second << endl;

    return 0;
}
