#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    // Open file and error management
    ifstream fich("../inputs/PrintQueueTest.txt");
    if (!fich.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string text;
    multimap<int, int> rules;
    //Initialize rules map with the first section
    while (getline(fich, text) && text != "") {
        int first = stoi(text.substr(0, text.find('|')));
        int second = stoi(text.substr(text.find('|') + 1, text.size()));
        rules.insert({first, second});
    }

    int sum = 0;
    //Read each update
    while (getline(fich, text)) {
        vector<int> line;
        stringstream ss(text);
        string temp;
        //Store the numbers in the vector without the ','
        while (getline(ss, temp, ',')) {
            line.push_back(stoi(temp));
        }

        bool valido = true;
        //Loop trought the line inverse checking if the rules are broken with
        //the remaining elements
        for (int i = line.size() - 1; i > 0 && valido; i--) {
            auto range = rules.equal_range(line[i]);
            for (auto it = range.first; it != range.second && valido; ++it) {
                for (int j = 0; j < i && valido; j++) {
                    if (line[j] == it->second)
                        valido = false;
                }
            }
        }

        if (valido) {
            sum += line[line.size() / 2];
            cout << text << "\tCorrect" << endl;
        }
    }

    cout << "Suma total: " << sum;
    fich.close();
    return 0;
}