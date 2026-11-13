// Keshav Yanamandra
// COMSC-210-5293, Fall 2026
// Lab 34
// the graph is a flight network out of SFO
// nodes are airports, weights are nonstop flight time in minutes
// the airports are the ones that came up most in my lab 30 flight data


#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;

const int SIZE = 11;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

const string AIRPORTS[SIZE] = {"SFO", "LAX", "SEA", "DEN", "PHX", "LAS",
                               "SLC", "DFW", "ORD", "JFK", "BOS"};
const string ROLES[SIZE] = {"Hub", "Hub", "Spoke", "Hub", "Spoke", "Spoke",
                            "Spoke", "Hub", "Hub", "Hub", "Spoke"};

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }


    // Print the whole route network, one airport at a time
    void printGraph() {
        cout << "Flight Network Topology:" << endl;
        cout << "========================" << endl;

        for (int i = 0; i < (int)adjList.size(); i++) {
            cout << AIRPORTS[i] << " (" << ROLES[i] << ") connects to:" << endl;

            for (Pair v : adjList[i])
                cout << "  -> " << AIRPORTS[v.first]
                     << " (Flight time: " << v.second << " min)" << endl;
        }
        cout << endl;
    }

    // Depth-first search, uses a stack so it goes deep before wide
    // this follows one routing path as far as it goes before backing up
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        visited[start] = true;
        s.push(start);

        cout << "Route Trace (DFS) from " << AIRPORTS[start]
             << " (" << ROLES[start] << "):" << endl;
        cout << "Purpose: Following one routing path as deep as it goes" << endl;
        cout << "=======================================" << endl;

        while (!s.empty()) {
            int node = s.top();
            s.pop();

            cout << "Inspecting " << AIRPORTS[node]
                 << " (" << ROLES[node] << ")" << endl;

            // push unvisited neighbors, LIFO makes the backtracking happen
            for (Pair v : adjList[node])
                if (!visited[v.first]) {
                    visited[v.first] = true;
                    s.push(v.first);

                    cout << "  -> Can route on to " << AIRPORTS[v.first]
                         << " (" << ROLES[v.first] << ") - Flight time: "
                         << v.second << " min" << endl;
                }
        }
        cout << endl;
    }

    // Breadth-first search, uses a queue so it goes level by level
    // each level is one more connection away from the starting airport
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "Connection Reach (BFS) from " << AIRPORTS[start]
             << " (" << ROLES[start] << "):" << endl;
        cout << "Purpose: Finding what is reachable in the fewest connections" << endl;
        cout << "=================================================" << endl;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            cout << "Checking " << AIRPORTS[node]
                 << " (" << ROLES[node] << ")" << endl;

            // mark each neighbor visited as it is enqueued
            for (Pair v : adjList[node])
                if (!visited[v.first]) {
                    visited[v.first] = true;
                    q.push(v.first);

                    cout << "  -> Next reachable: " << AIRPORTS[v.first]
                         << " (" << ROLES[v.first] << ") - Flight time: "
                         << v.second << " min" << endl;
                }
        }
        cout << endl;
    }

};

int main() {
    // Creates a vector of graph edges/weights
    // vector<Edge> edges = {
    //     // (x, y, w) —> edge from x to y having weight w
    //     {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    // };

    // deleted nodes 5 and 6 from the lesson graph, added 6 new nodes (5 through 10),
    // and changed weights 7 - 2 + 6 = 11 nodes
    // 0 SFO  1 LAX  2 SEA  3 DEN  4 PHX  5 LAS
    // 6 SLC  7 DFW  8 ORD  9 JFK  10 BOS
    // (x, y, w) -> edge from x to y, w is nonstop flight time in minutes
    vector<Edge> edges = {
        {0,1,75},{0,2,115},{0,3,140},{0,5,85},{1,4,70},{1,5,60},
        {2,3,155},{2,6,110},{3,4,105},{3,6,75},{3,8,145},{4,7,120},
        {5,6,80},{6,8,175},{7,8,135},{7,9,215},{8,9,130},{8,10,165},
        {9,10,70}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
