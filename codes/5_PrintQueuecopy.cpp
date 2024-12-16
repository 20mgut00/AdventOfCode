#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

vector<int> sortOrder(const vector<pair<int,int>> rules, const vector<int> order){
    unordered_map<int, vector<int>> graph;
    unordered_map<int, int> inDegree;

    // Build the graph and in-degree count
    for (const auto& rule : rules) {
        int u = rule.first;
        int v = rule.second;
        graph[u].push_back(v);
        inDegree[v]++;
        if (inDegree.find(u) == inDegree.end()) {
            inDegree[u] = 0; // Ensure all nodes are in the inDegree map
        }
    }

    // Print the graph and in-degrees for debugging
    cout << "Graph:" << endl;
    for (const auto& entry : graph) {
        cout << entry.first << " -> ";
        for (int neighbor : entry.second) {
            cout << neighbor << " ";
        }
        cout << endl;
    }

    cout << "In-degrees:" << endl;
    for (const auto& entry : inDegree) {
        cout << entry.first << ": " << entry.second << endl;
    }

    // Queue for nodes with no incoming edges
    queue<int> q;
    for (int num : order) {
        if (inDegree[num] == 0) {
            q.push(num);
        }
    }

    vector<int> sortedOrder;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        sortedOrder.push_back(current);

        for (int neighbor : graph[current]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Check if we have a valid topological sort
    if (sortedOrder.size() != order.size()) {
        return {}; // Cycle detected or not all nodes are included
    }

    return sortedOrder;
}

bool isValidOrder(const vector<pair<int, int>> rules, const vector<int> order) {
    // Create a mapping of each number to its position in the order
    unordered_map<int, int> positionMap;
    for (int i = 0; i < order.size(); ++i)
        positionMap[order[i]] = i;

    // Check each rule
    for (pair<int, int> rule : rules) {
        int first = rule.first;
        int second = rule.second;

        // Only check rules that involve numbers present in the order
        if (positionMap.find(first) != positionMap.end() && positionMap.find(second) != positionMap.end())
            // If first appears after second in the order, it's invalid
            if (positionMap[first] > positionMap[second])
                return false;
    }

    return true;
}

int main() {

    // Open file and error management
    ifstream fich("../inputs/PrintQueueTest.txt");
    if (!fich.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Define the rules as pairs (A|B) meaning A must come before B
    vector<pair<int, int>> rules;
    string text;
    while (getline(fich, text) && text != "") {
        int first = stoi(text.substr(0, text.find('|')));
        int second = stoi(text.substr(text.find('|') + 1, text.size()));
        rules.push_back({first, second});
    }

    int sum = 0;
    while (getline(fich, text)) {
        vector<int> order;
        stringstream ss(text);
        string temp;
        while (getline(ss, temp, ','))
            order.push_back(stoi(temp));
        // Check if the order is valid
        if (isValidOrder(rules, order)) {
            sum += order[order.size()/2];
            cout << "\nValid\t\t";
            for(int i : order)
                cout << i << " ";
        } else {
            vector<int> sortO = sortOrder(rules,order);
            cout << "\nNot Valid\t";
            cout << endl;
            for(int i : sortO)
                cout << i << " ";
            cout << endl;
            for(int i : order)
                cout << i << " ";
        }
    }

    cout << "\nSum: " << sum;
    return 0;
}