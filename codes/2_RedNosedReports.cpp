#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool isSafe(vector<int> numbers) {
    // Increassing Vector
    if (numbers[1] > numbers[0]) {
        for (int i = 1; i < numbers.size(); i++) {
            int diff = numbers[i] - numbers[i - 1];
            // Increassing Diff
            if (!(1 <= diff && diff <= 3))
                return false;
        }
        return true;
    // Decreasing Vector
    } else {
        for (int i = 1; i < numbers.size(); i++) {
            int diff = numbers[i] - numbers[i - 1];
            // Decreassing Diff
            if (!(-3 <= diff && diff <= -1))
                return false;
        }
        return true;
    }
}

bool isSuperSafe(vector<int> numbers) {
    if (isSafe(numbers))
        return true;
    // If !isSafe()
    for (int i = 0; i < numbers.size(); i++) {
        vector<int> subNumbers;
        // Subvector without i element
        for (int j = 0; j < i; j++)
            subNumbers.push_back(numbers[j]);
        for (int j = i + 1; j < numbers.size(); j++)
            subNumbers.push_back(numbers[j]);
        // Check every subvector
        if (isSafe(subNumbers))
            return true;
    }
    return false;
}

int main() {
    // Open file and error management
    // ifstream fich("../inputs/RedNosedReports.txt");
    ifstream fich("../inputs/RedNosedReports.txt");
    if (!fich.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Result 1
    int safeReports = 0;

    // Process each line in the file
    string line;
    int i = 1;
    while (getline(fich, line)) {
        // Initialize vector to store the numbers of the file
        vector<int> numbers;
        stringstream ss(line);
        int num;
        while (ss >> num)
            numbers.push_back(num);

        bool safe = isSuperSafe(numbers);
        safeReports += safe;

        cout << i << "\t";
        i++;
        for (int j : numbers) {
            cout << j << " ";
        }
        cout << (safe ? "Safe" : "Not Safe") << endl;
    }

    cout << "Number of Safe Reports: " << safeReports << endl;

    fich.close();
    return 0;
}