#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    // Open file and error management
    //ifstream fich("../inputs/RedNosedReports.txt");
    ifstream fich("../inputs/RedNosedReportsTest.txt");
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

        // Flags to check if the report is safe
        bool increasing = false;
        bool decreasing = false;
        bool same = false;
        bool error = false;
        
        // Check if the report is increasing, decreasing
        // and possible errors
        for (int i = 0; i < numbers.size() - 1; i++) {
            if (numbers[i] < numbers[i + 1]) {
                if (abs(numbers[i] - numbers[i + 1]) > 3)
                    error = true;
                increasing = true;
            } else if (numbers[i] > numbers[i + 1]) {
                if (abs(numbers[i + 1] - numbers[i]) > 3)
                    error = true;
                decreasing = true;
            } else {
                same = true;
            }
        }
        cout << i << "\t";
        i++;
        for (int j : numbers) {
            cout << j << " ";
        }

        // Check is report is safe or unsafe
        if (same || error || increasing && decreasing)
            cout << "Unsafe" << endl;
        else {
            safeReports++;
            cout << "Safe" << endl;
        }
    }

    cout << "Number of Safe Reports: " << safeReports << endl;

    fich.close();
    return 0;
}