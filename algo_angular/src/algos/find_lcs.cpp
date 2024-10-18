#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

// Struct to hold the result
struct LCSResult {
    string lcs;
    int start1;
    int end1;
    int start2;
    int end2;
};

// Función para leer el contenido de un archivo
string read_file(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }

    string content;
    getline(file, content, '\0');
    file.close();
    return content;
}

// Función para encontrar la subcadena común más larga usando programación dinámica
LCSResult longest_common_substring(const string &text1, const string &text2)
{
    int n = text1.size();
    int m = text2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    int max_len = 0;
    int end_index1 = 0;
    int end_index2 = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (text1[i - 1] == text2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max_len)
                {
                    max_len = dp[i][j];
                    end_index1 = i - 1;
                    end_index2 = j - 1;
                }
            }
        }
    }

    int start_index1 = end_index1 - max_len + 1;
    int start_index2 = end_index2 - max_len + 1;
    string lcs = text1.substr(start_index1, max_len);

    return {lcs, start_index1, end_index1, start_index2, end_index2};
}

// Función principal
int main()
{
    string filename1 = "../testcases/text1.txt";
    string filename2 = "../testcases/text2.txt";
    string output_filename = "../testcases/output.json";

    // Leer los archivos de texto
    string text1 = read_file(filename1);
    string text2 = read_file(filename2);

    // Encontrar la subcadena común más larga
    LCSResult result = longest_common_substring(text1, text2);

    // Escribir el resultado en formato JSON en un archivo
    ofstream output_file(output_filename);
    if (!output_file.is_open())
    {
        cerr << "Error al abrir el archivo de salida: " << output_filename << endl;
        return 1;
    }

    output_file << "[\n";
    output_file << "    {\"text1\": {\"start\": " << result.start1 << ", \"end\": " << result.end1 << "}},\n";
    output_file << "    {\"text2\": {\"start\": " << result.start2 << ", \"end\": " << result.end2 << "}}\n";
    output_file << "]";

    output_file.close();

    return 0;
}