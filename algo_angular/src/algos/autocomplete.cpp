#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <cctype>

using namespace std;

// TrieNode class
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// Trie class
class Trie {
private:
    TrieNode* root;

    // Helper function to collect all words from a given node
    void collectWords(TrieNode* node, string prefix, vector<string>& result) {
        if (node->isEndOfWord) {
            result.push_back(prefix);
        }
        for (auto& pair : node->children) {
            collectWords(pair.second, prefix + pair.first, result);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(const string &word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    // Search for a word in the Trie
    bool search(const string &word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->isEndOfWord;
    }

    // Get all words with the given prefix
    vector<string> getWordsWithPrefix(const string &prefix) {
        vector<string> result;
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return result; // No words with the given prefix
            }
            node = node->children[c];
        }
        collectWords(node, prefix, result);
        return result;
    }
};

int main() {
    Trie trie;
    ifstream inputFile("../testcases/text1.txt");
    string content;

    if (!inputFile) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    // Read the entire file content
    stringstream buffer;
    buffer << inputFile.rdbuf();
    content = buffer.str();

    inputFile.close();

    // Use a set to handle duplicated words
    unordered_set<string> uniqueWords;
    stringstream ss(content);
    string word;

    // Split the content into words using whitespaces as separators
    while (ss >> word) {
        // Remove quotation marks and punctuation
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalnum(c); }), word.end());
        // Convert to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (!word.empty()) {
            uniqueWords.insert(word);
        }
    }

    // Insert each unique word into the Trie
    for (const string& uniqueWord : uniqueWords) {
        trie.insert(uniqueWord);
    }

    // Read the prefix from the input file
    ifstream prefixFile("../testcases/input.txt");
    string prefix;
    if (prefixFile.is_open()) {
        getline(prefixFile, prefix);
        prefixFile.close();
    } else {
        cerr << "Error opening prefix file" << endl;
        return 1;
    }

    vector<string> words = trie.getWordsWithPrefix(prefix);

    // Manually construct the JSON string for the list of words
    string jsonOutput = "[\n";
    for (size_t i = 0; i < words.size(); ++i) {
        jsonOutput += "  \"" + words[i] + "\"";
        if (i < words.size() - 1) {
            jsonOutput += ",";
        }
        jsonOutput += "\n";
    }
    jsonOutput += "]";

    // Write the JSON string to a file
    ofstream outputFile("../testcases/output.json");
    if (outputFile.is_open()) {
        outputFile << jsonOutput;
        outputFile.close();
    } else {
        cerr << "Error opening output file" << endl;
        return 1;
    }

    return 0;
}