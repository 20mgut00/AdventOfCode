#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    // Open file and error management
    // ifstream fich("../inputs/MullItOver.txt");
    ifstream fich("../inputs/MullItOver.txt");
    if (!fich.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // mul\( == mul(
    // (\d{1,3}) == 1 <= n <= 999
    // ,
    // (\d{1,3}) == 1 <= n <= 999
    // \) == )
    regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
    // Vector to hold the matched substrings
    string text;
    int sum = 0;
    bool dont = false;
    vector<string> matchVec;
    while (getline(fich, text)) {
        sregex_token_iterator it(text.begin(), text.end(), pattern);
        sregex_token_iterator end;

        // Use regex_iterator to find all matches
        while (it != end) {
            string match = *it;
            matchVec.push_back(match);
            ++it;
        }
    }
    for (int i = 0; i < matchVec.size(); i++) {
        
        if (matchVec[i] == "don't()" && !dont){
            cout << i+1 << "\t" << matchVec[i] << endl;
            dont = true;
        }
        else if (matchVec[i] == "do()" && dont){
            cout << i+1 << "\t" << matchVec[i] << endl;
            dont = false;
        }
        else if (matchVec[i].front() == 'm' && !dont) {
            cout << i+1 << "\t" << matchVec[i] << "\t-> ";
            matchVec[i].erase(matchVec[i].begin(), matchVec[i].begin() + 4);
            matchVec[i].erase(matchVec[i].end() - 1, matchVec[i].end());
            stringstream ss(matchVec[i]);
            string n1, n2;
            getline(ss, n1, ',');
            getline(ss, n2, ',');
            int mul = stoi(n1) * stoi(n2);
            cout << n1 << " * " << n2 << "\t= " << mul << endl;
            sum += mul;
        }
    }
    cout << "Add of all the multiplications: " << sum;

    fich.close();
    return 0;
}