#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int main() {
    //Open file and error management
    ifstream fich("../inputs/HistorianHysteria.txt");
    if (!fich.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    //Sets to store each column
    multiset<int> list1, list2;
    int n1,n2;
    //Read file and store in sets until end of file
    while(fich >> n1 && fich >> n2){
        list1.insert(n1);
        list2.insert(n2);
    }

    //Result 1 and Result 2
    int totalDistance = 0;
    int similarityScore = 0;

    //Iterators to traverse the sets
    auto it1 = list1.begin();
    auto it2 = list2.begin();
    while(it1 != list1.end() || it2 != list2.end()){
        //Distance = |a-b|
        totalDistance += abs(*it1 - *it2);
        //Similarity = b.count(a)
        similarityScore += *it1 * list2.count(*it1);

        cout << *it1 << " " << *it2 << "\t-Distance between: " << abs(*it1-*it2) << "\t-Similarity: " << list2.count(*it1) << endl;

        ++it1;
        ++it2;
    }

    cout << "Total distance: " << totalDistance << endl;
    cout << "Similarity score: " << similarityScore << endl;

    //Close the file
    fich.close();
    return 0;
}