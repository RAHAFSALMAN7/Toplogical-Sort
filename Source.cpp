#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> graph; // Adjacency list representation of the graph
    vector<int> indegree; // Stores the indegree of each vertex
    vector<int> currentOrder; // Current topological ordering being explored
    vector<vector<int>> allOrders; // Stores all possible topological orderings

public:
    Graph() {} // Constructor

    void addEdge(int u, int v) {
        if (u < 0 || v < 0) { // Check if vertices are non-negative
            cout << "Error: Invalid edge, vertices must be non-negative." << endl;
            return;
        }
        if (u >= indegree.size()) { // Resize indegree vector if necessary
            indegree.resize(u + 1);
        }
        if (v >= indegree.size()) {
            indegree.resize(v + 1);
        }
        graph[u].push_back(v); // Add v to u's adjacency list
        indegree[v]++; // Increment indegree of vertex v
    }

    void backtrack() {
        bool allVisited = true;
        for (int i = 0; i < indegree.size(); ++i) {
            if (indegree[i] == 0) { // Check if vertex has indegree 0
                allVisited = false; // Mark that not all vertices have been visited
                indegree[i]--; // Mark vertex as visited
                currentOrder.push_back(i); // Add vertex to current ordering
                for (int v : graph[i]) { // Update indegrees of adjacent vertices
                    indegree[v]--;
                }
                backtrack(); // Recursively explore next vertex
                for (int v : graph[i]) { // Backtrack by restoring indegrees
                    indegree[v]++;
                }
                currentOrder.pop_back(); // Remove current vertex from ordering
                indegree[i]++; // Backtrack by restoring indegree of current vertex
            }
        }
        // If all vertices visited and current order size matches number of vertices, add order to allOrders
        if (allVisited && currentOrder.size() == indegree.size()) {
            allOrders.push_back(currentOrder);
        }
    }

    void printAllOrders() {
        backtrack(); // Find all possible topological orderings
        for (const auto& order : allOrders) { // Print each ordering stored in allOrders
            for (int vertex : order) {
                cout << vertex << " "; // Print vertices in the order
            }
            cout << endl; // Move to the next line for the next ordering
        }
    }
};

int main() {
    Graph g;
    // Add edges to construct the directed acyclic graph (DAG)
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "All possible ordering solutions:" << endl;
    g.printAllOrders(); // Print all possible topological orderings

    return 0;
}
