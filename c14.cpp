/*
Experiment 14 : There are flight paths between cities. If there is a flight between City A and City B then there is an edge between the cities. 
The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey. Represent this as a graph.
The node can be represented by the airport name or name of the city. Use adjacency list representation of the graph or use adjacency matrix representation of the graph.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    cin.ignore();

    vector<string> cities(n);
    vector<vector<int>> adj(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        cout << "Enter name of City " << i + 1 << ": ";
        getline(cin, cities[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Enter distance between " << cities[i] << " and " << cities[j] << ": ";
            cin >> adj[i][j];
            adj[j][i] = adj[i][j];
        }
    }

    cout << "\nAdjacency Matrix:\n\t";
    for (const auto& city : cities) {
        cout << city << "\t";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << cities[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << adj[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
