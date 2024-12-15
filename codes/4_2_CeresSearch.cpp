#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const string TARGET = "AS";

bool isInBounds(int x, int y, int height, int width) {
    return y >= 0 && y < height && x >= 0 && x < width;
}

int countXmas(const vector<string> matrix, int i, int j, int height, int width) {
    int count = 0;
    int directions[4][2] = {
        {-1, -1},
        {1, 1},
        {-1, 1},
        {1, -1} // up-left, down-right, up-right, down-left
    };
    
    if (isInBounds(j + 2, i, height, width) && matrix[i][j + 2] == 'M') {                                                                     // M a la derecha
        if (isInBounds(j + 2, i + 2, height, width) && matrix[i + 1][j + 1] == 'A' && matrix[i + 2][j + 2] == 'S' && matrix[i + 2][j] == 'S') // xmas Down
            count++;
        if (isInBounds(j + 2, i - 2, height, width) && matrix[i - 1][j + 1] == 'A' && matrix[i - 2][j + 2] == 'S' && matrix[i - 2][j] == 'S') // xmas Up
            count++;
    }
    if (isInBounds(j, i + 2, height, width) && matrix[i + 2][j] == 'M') {                                                                     // M abajo
        if (isInBounds(j + 2, i + 2, height, width) && matrix[i + 1][j + 1] == 'A' && matrix[i + 2][j + 2] == 'S' && matrix[i][j + 2] == 'S') // xmas Right
            count++;
        if (isInBounds(j - 2, i + 2, height, width) && matrix[i + 1][j - 1] == 'A' && matrix[i + 2][j - 2] == 'S' && matrix[i][j - 2] == 'S') // xmas Left
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
            if (matrix[i][j] == 'M')
                xmas += countXmas(matrix, i, j, height, width);
            cout << matrix[i][j];
        }
        cout << endl;
    }

    cout << "XMAS:\t" << xmas << endl;
    fich.close();
    return 0;
}