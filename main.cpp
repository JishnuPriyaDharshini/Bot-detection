#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#include <unordered_set> 
#include <random> 
#include <ctime>  
using namespace std;

class Graph {
public:
    int rows, cols; // 2D maze is considered.
    vector<list<int>> adj; // adjacency list
    unordered_set<int> traps; // to store traps as node indices.
    //initializing 
    Graph(int rows, int cols) : rows(rows), cols(cols) {
        adj.resize(rows * cols);
    }

    // 2D to 1D conversion to represent the position.
    int to1D(int row, int col) {
        return row * cols + col;
    }
    //assuming undirectional.
    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }

    // randomly placing traps, ensuring start and end nodes are not traps.
    void generateRandomTraps(int trapCount) {
        srand(time(0)); // seed,producing different sequences of random numbers on each execution.
        int totalNodes = rows * cols;

        while (trapCount > 0) {
            int trapNode = rand() % totalNodes;

            // Ensuring traps are not placed at the start or end.
            if (traps.find(trapNode) == traps.end() && trapNode != 0 && trapNode != totalNodes - 1) {
                traps.insert(trapNode);
                trapCount--;
            }
        }
    }
    //boolean for trap node detection.
    bool isTrap(int node) {
        return traps.find(node) != traps.end();
    }
    //display function for the maze along with traps.
    void displayMaze() {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                int node = to1D(row, col);
                if (isTrap(node)) {
                    cout << " 🟥 "; // trap is shown as a red block.
                } else {
                    cout << " 🟩 "; // normal node is a green block.
                }
            }
            cout << endl;
        }
    }
};
 //creating the graph accordingly.
void create2DMaze(Graph &graph) {
    for (int row = 0; row < graph.rows; ++row) {
        for (int col = 0; col < graph.cols; ++col) {
            int node = graph.to1D(row, col);

            // connecting to up, down, left, right nodes
            if (row > 0) graph.addEdge(node, graph.to1D(row - 1, col)); // Up
            if (row < graph.rows - 1) graph.addEdge(node, graph.to1D(row + 1, col)); // Down
            if (col > 0) graph.addEdge(node, graph.to1D(row, col - 1)); // Left
            if (col < graph.cols - 1) graph.addEdge(node, graph.to1D(row, col + 1)); // Right
        }
    }
}
class Bot {
public:
    int currentNode;
    Graph &graph;

    Bot(Graph &g) : graph(g), currentNode(0) {}

    // Bot moves using BFS to avoid traps
    vector<int> findSmartPath(int start, int end) {
        queue<int> q;
        vector<bool> visited(graph.rows * graph.cols, false);
        vector<int> parent(graph.rows * graph.cols, -1);

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            if (node == end) break;

            for (int neighbor : graph.adj[node]) {
                if (!visited[neighbor] && !graph.isTrap(neighbor)) { // Avoid traps
                    visited[neighbor] = true;
                    parent[neighbor] = node;
                    q.push(neighbor);
                }
            }
        }

        // Backtracking to find the path
        vector<int> path;
        int current = end;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());
        return path;
    }
    //simulation of bot movement and printing the path.
    void simulateBotPath(const vector<int>& path) {
        for (int node : path) {
            currentNode = node;
            //if (graph.isTrap(currentNode)) {
            //    cout << "🚨 Bot fell into a trap at node: " << currentNode << endl;}
            
           // else {
                cout << "🤖 Bot moved to node: " << currentNode << endl;
           // }
        }
    }
};
class Human {
public:
int currentNode;
Graph &graph;

Human(Graph &g) : graph(g), currentNode(0) {}

//BFS to find the shortest path avoing the hurdles.
vector<int> findShortPath(int start, int end) {
        queue<int> q;
        vector<bool> visited(graph.rows * graph.cols, false);
        vector<int> parent(graph.rows * graph.cols, -1);

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            if (node == end) break;

            for (int neighbor : graph.adj[node]) {
                if (!visited[neighbor] ) { 
                    visited[neighbor] = true;
                    parent[neighbor] = node;
                    q.push(neighbor);
                }
            }
        }

        // Backtracking to find the path
        vector<int> path;
        int current = end;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());
        return path;
    }
    //printing the human path
    void followShortestPath(vector<int> &path) {
        for (int node : path) {
            cout << "🧑 Human moved to node: " << node << endl;
        }
    }
};

int main() {
    cout << "Starting Trap Bot Detection System" << endl;

    // Create 2D maze of size 6x6
    Graph graph(6, 6);
    create2DMaze(graph);

    // Randomly generate traps
    graph.generateRandomTraps(5);

    // Display the maze with traps
    cout << "\nMaze Layout (Red = Trap, Green = Safe)\n";
    graph.displayMaze();

    // Get the human's path (does not avoid traps)
    cout << "\n🧑 Human's path from start to end:" << endl;
    Human human(graph);
    Bot bot(graph);

    // Get paths of human and bot.
    vector<int> humanPath = human.findShortPath(0, graph.to1D(graph.rows - 1, graph.cols - 1));
    human.followShortestPath(humanPath);

    // Bot avoids traps
    cout << "\n🤖 Bot's path (avoiding traps):" << endl;
    vector<int> botPath = bot.findSmartPath(0, graph.to1D(graph.rows - 1, graph.cols - 1));
    bot.simulateBotPath(botPath);

    // Check for difference in path
    if (humanPath != botPath) {
        cout << "\n Bot Detected! Bot path is different from human path.\n " << endl;
    } else {
        cout << "\n No Bot Detected! Paths are similar.\n" << endl;
    }

    return 0;
}
