#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const string TARGET = "MAS";

bool isInBounds(int x, int y, int height, int width) {
    return y >= 0 && y < height && x >= 0 && x < width;
}

int countXmas(const vector<string> matrix, int i, int j, int height, int width) {
    int count = 0;
    int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, 1}, {0, -1}, // up, down, right, left
        {-1, -1},
        {1, 1},
        {-1, 1},
        {1, -1} // up-left, down-right, up-right, down-left
    };

    for (auto dir : directions) {
        int dx = dir[0], dy = dir[1];
        bool valid = true;
        int k = 1;
        do {
            int x = j + k * dx, y = i + k * dy;
            if (!isInBounds(x, y, height, width) || matrix[y][x] != TARGET[k - 1])
                valid = false;
            
            k++;
        } while (k <= 3 && valid);
        if (valid)
            count++;
    }
        return count;
}

int main() {
    ifstream fich("../inputs/CeresSearch.txt");
    if (!fich.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    vector<string> matrix;
    string line;
    while (getline(fich, line))
        matrix.push_back(line);

    int height = matrix.size();
    int width = matrix[0].size();

    int xmas = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            bool up = true, right = true, down = true, left = true;
            if (matrix[i][j] == 'X')
                xmas += countXmas(matrix, i, j, height, width);
            cout << matrix[i][j];
        }
        cout << endl;
    }

    cout << "XMAS:\t" << xmas << endl;
    fich.close();
    return 0;
}