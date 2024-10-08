// Nadav034@gmail.com

#include "Algorithms.hpp"
#include <queue>
#include <limits>
#include <algorithm>
#include <string>
#include <set>
#include <sstream>
#include <stack>

using namespace std;
// Depth-First Search utility for connectivity check
/**
 * Performs DFS to mark visited vertices for connectivity check.
 *
 * @param graph The graph to traverse.
 * @param v The starting vertex.
 * @param visited A vector to track visited vertices.
 */
void Algorithms::DFSUtil(const Graph& graph, int v, std::vector<bool>& visited) {
    visited[v] = true;
    const auto& matrix = graph.getGraph();
    for (int i = 0; i < graph.getVertexNum(); ++i) {
        if (matrix[v][i] != 0 && !visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }
}

// Function to check if the graph is connected
/**
 * Checks if the graph is connected.
 *
 * @param graph The graph to check.
 * @return 1 if connected, 0 otherwise.
 */
int Algorithms::isConnected( Graph& graph) {
    if(graph.getIsEmpty()){
        cout<<"graph is empty"<<endl;
        return 0;
    }
    int numVer = graph.getVertexNum();
    std::vector<bool> visited(numVer, false);
    // Perform DFS starting from the first vertex
    DFSUtil(graph, 0, visited);
    // Check if all vertices are visited
    for (int i = 0; i < numVer; ++i) {
        if (!visited[i]) {
            return 0; // Not connected
        }
    }
    // For directed graphs, check reverse reachability
    if (graph.isGraphDirected()) {
        // Create a transpose of the graph
        std::vector<std::vector<int>> transpose(numVer, std::vector<int>(numVer, 0));
        const auto& matrix = graph.getGraph();
        for (int i = 0; i < numVer; ++i) {
            for (int j = 0; j < numVer; ++j) {
                transpose[j][i] = matrix[i][j];
            }
        }
        // Create a new Graph object for the transposed graph
        Graph transposedGraph(transpose, graph.isGraphDirected(), graph.isGraphWeighted(), numVer);
        // Reset visited and perform DFS on the transpose
        std::fill(visited.begin(), visited.end(), false);
        DFSUtil(transposedGraph, 0, visited);
        for (int i = 0; i < numVer; ++i) {
            if (!visited[i]) {
                return 0; // Not strongly connected
            }
        }
    }
    return 1; // Connected
}

// Function to relax edges in the graph
/**
 * Relaxes the edges of the graph to update distances and parents.
 *
 * @param g The graph.
 * @param dist Distance vector.
 * @param parent Parent vector.
 */
void Algorithms::relaxEdges(const Graph &g, std::vector<int> &dist, std::vector<int> &parent) {
    int V = g.getVertexNum();
    std::vector<std::vector<int>> matrix = g.getGraph();
    const int INF = std::numeric_limits<int>::max();

    for (int i = 1; i <= V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (matrix[u][v] != 0 && dist[u] != INF && dist[u] + matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + matrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }
}



// Function to find the shortest path in an unweighted graph using BFS
/**
 * Finds the shortest path in an unweighted graph using BFS.
 *
 * @param graph The graph.
 * @param start The start vertex.
 * @param end The end vertex.
 * @return A pair containing the shortest path length and the path itself.
 */
std::pair<int, std::vector<int>> Algorithms::bfsShortestPath(const Graph& graph, int start, int end) {
    int numVer = graph.getVertexNum();
    std::vector<int> distance(numVer, -1);
    std::vector<int> parent(numVer, -1);
    std::queue<int> q;

    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < numVer; ++i) {
            if (graph.getGraph()[v][i] != 0 && distance[i] == -1) {
                distance[i] = distance[v] + 1;
                parent[i] = v;
                q.push(i);
            }
        }
    }

    if (distance[end] == -1) {
        return {-1, {}}; // No path found
    }

    // Reconstruct the path
    std::vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());

    return {distance[end], path}; // Shortest path length and path
}

// Function to find the shortest path in a weighted graph using Dijkstra's algorithm
/**
 * Finds the shortest path in a weighted graph using Dijkstra's algorithm.
 *
 * @param graph The graph.
 * @param start The start vertex.
 * @param end The end vertex.
 * @return A pair containing the shortest path length and the path itself.
 */
std::pair<int, std::vector<int>> Algorithms::dijkstraShortestPath(const Graph& graph, int start, int end) {
    int numVer = graph.getVertexNum();
    std::vector<int> distance(numVer, std::numeric_limits<int>::max());
    std::vector<int> parent(numVer, -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int v = pq.top().second;
        pq.pop();

        if (dist > distance[v]) continue;

        for (int i = 0; i < numVer; ++i) {
            if (graph.getGraph()[v][i] != 0) {
                int weight = graph.getGraph()[v][i];
                if (distance[v] + weight < distance[i]) {
                    distance[i] = distance[v] + weight;
                    parent[i] = v;
                    pq.push({distance[i], i});
                }
            }
        }
    }

    if (distance[end] == std::numeric_limits<int>::max()) {
        return {-1, {}}; // No path found
    }

    // Reconstruct the path
    std::vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());

    return {distance[end], path}; // Shortest path length and path
}

// Function to find the shortest path using Bellman-Ford algorithm
/**
 * Finds the shortest path using the Bellman-Ford algorithm.
 *
 * @param g The graph.
 * @param start The start vertex.
 * @param end The end vertex.
 * @return A string representing the path or a negative cycle message.
 */
string Algorithms::bellmanFordShortestPath(const Graph &g, int start, int end) {
    std::stringstream ss;
    int vertexNum = g.getVertexNum();
    const int INF = std::numeric_limits<int>::max();

    if (vertexNum == 0 || start >= vertexNum || end >= vertexNum) {
        return "-1";
    }

    std::vector<int> dist(vertexNum, INF);
    std::vector<int> parent(vertexNum, -1);
    dist[start] = 0;

    // Relax all edges
    relaxEdges(g, dist, parent);

    // Check for negative weight cycles
    for (int u = 0; u < vertexNum; ++u) {
        for (int v = 0; v < vertexNum; ++v) {
            int weight = g.getGraph()[u][v];
            if (weight != 0 && dist[u] != INF && dist[u] + weight < dist[v]) {
                // Negative weight cycle found
                return "Negative cycle detected";
            }
        }
    }

    if (dist[end] == INF) {
        return "-1"; // No path found
    }

    // Reconstruct the path
    std::stack<int> path;
    int currVertex = end;
    while (currVertex != -1) {
        path.push(currVertex);
        currVertex = parent[currVertex];
    }

    // Print the path
    while (!path.empty()) {
        ss << path.top();
        path.pop();
        if (!path.empty()) {
            ss << "->";
        }
    }
    return ss.str();
}

// Function to find the shortest path based on graph type
/**
 * Finds the shortest path based on the graph type (unweighted, weighted, or negative weighted).
 *
 * @param graph The graph.
 * @param start The start vertex.
 * @param end The end vertex.
 * @return A string representing the path or "-1" if no path is found.
 */
std::string Algorithms::shortestPath(Graph& graph, int start, int end) {
    std::pair<int, std::vector<int>> result;
    if (graph.isGraphNegWeighted()){
        return bellmanFordShortestPath(graph,start,end);
    }
    if (graph.isGraphWeighted()) {
        result = dijkstraShortestPath(graph, start, end);
    } else {
        result = bfsShortestPath(graph, start, end);
    }

    if (result.first == -1) {
        return "-1";
    }

    return formatPath(result.second);
}

// Helper function to format the path
/**
 * Formats the path as a string with "->" separators.
 *
 * @param path The path to format.
 * @return The formatted path string.
 */
std::string Algorithms::formatPath(const std::vector<int>& path) {
    std::string formattedPath;
    for (size_t i = 0; i < path.size(); ++i) {
        formattedPath += std::to_string(path[i]);
        if (i < path.size() - 1) {
            formattedPath += "->";
        }
    }
    return formattedPath;
}

void Algorithms::printCycle(const std::vector<int>& parent, int start, int end) {
    std::vector<int> cycle;
    cycle.push_back(end);
    for (int v = start; v != end; v = parent[v]) {
        cycle.push_back(v);
    }
    cycle.push_back(end);

    std::reverse(cycle.begin(), cycle.end());
    cout << "The cycle is: ";
    for (int v : cycle) {
        cout << v << " ";
    }
    cout << endl;
}

// DFS helper function for undirected graph
/**
 * DFS utility to detect a cycle in an undirected graph.
 *
 * @param v The current vertex.
 * @param parent The parent vertex.
 * @param graph The graph.
 * @param visited The visited vector.
 * @param parentVec The parent vector.
 * @return True if a cycle is detected, false otherwise.
 */
bool Algorithms::DFSUtilUndirected(int v, int parent, const Graph& graph, std::vector<bool>& visited, std::vector<int>& parentVec) {
    visited[v] = true;
    parentVec[v] = parent; // Set the parent of the current node

    for (int u = 0; u < graph.getVertexNum(); ++u) {
        if (graph.getGraph()[v][u] != 0) {
            if (!visited[u]) {
                if (DFSUtilUndirected(u, v, graph, visited, parentVec)) {
                    return true;
                }
            } else if (u != parent) {
                printCycle(parentVec, v, u);
                return true;
            }
        }
    }
    return false;
}


// DFS helper function for directed graph
/**
 * DFS utility to detect a cycle in a directed graph.
 *
 * @param v The current vertex.
 * @param graph The graph.
 * @param visited The visited vector.
 * @param recStack The recursion stack vector.
 * @param parentVec The parent vector.
 * @return True if a cycle is detected, false otherwise.
 */
bool Algorithms::DFSUtilDirected(int v, const Graph& graph, std::vector<bool>& visited, std::vector<bool>& recStack, std::vector<int>& parentVec) {
    visited[v] = true;
    recStack[v] = true;

    for (int u = 0; u < graph.getVertexNum(); ++u) {
        if (graph.getGraph()[v][u] != 0) {
            if (!visited[u]) {
                parentVec[u] = v;
                if (DFSUtilDirected(u, graph, visited, recStack, parentVec)) {
                    return true;
                }
            } else if (recStack[u]) {
                parentVec[v] = u; // Update the parent to reflect the cycle
                printCycle(parentVec, v, u);
                return true;
            }
        }
    }
    recStack[v] = false;
    return false;
}

// Main function to detect and print a cycle
string Algorithms::isContainsCycle(const Graph& graph) {
    int numVer = graph.getVertexNum();
    std::vector<bool> visited(numVer, false);
    std::vector<int> parentVec(numVer, -1);
    Graph g1;
    g1.loadGraph(graph.getGraph());
    if (g1.isGraphDirected()) {
        std::vector<bool> recStack(numVer, false);
        for (int v = 0; v < numVer; ++v) {
            if (!visited[v]) {
                if (Algorithms::DFSUtilDirected(v, graph, visited, recStack, parentVec)) {
                    return "";
                }
            }
        }
    } else {
        for (int v = 0; v < numVer; ++v) {
            if (!visited[v]) {
                if (Algorithms::DFSUtilUndirected(v, -1, graph, visited, parentVec)) {
                    return "";
                }
            }
        }
    }
    return "0";
}

// Function to partition the graph into two sets based on colors
/**
 * Partitions the graph into two sets based on vertex colors.
 *
 * @param colors The color vector.
 * @param partition1 Set 1 of vertices.
 * @param partition2 Set 2 of vertices.
 */
void Algorithms::partitionGraph(const std::vector<int>& colors, std::vector<int>& partition1, std::vector<int>& partition2)  {
    for (size_t v = 0; v < colors.size(); ++v) {
        if (colors[v] == 0) {
            partition1.push_back(v);
        } else if (colors[v] == 1) {
            partition2.push_back(v);
        }
    }
}

// Function to check if the graph is bipartite
/**
 * Checks if the graph is bipartite.
 *
 * @param graph The graph to check.
 * @return A string indicating whether the graph is bipartite.
 */

std::string Algorithms::isBipartite(const Graph& graph)  {
    int numVer = graph.getVertexNum();
    vector<int> colors(numVer, -1); // Initialize all vertices as uncolored
    queue<int> q;

    for (int start = 0; start < numVer; ++start) {
        if (colors[start] == -1) { // Not colored yet
            colors[start] = 0; // Start coloring with 0
            q.push(start);

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int u = 0; u < numVer; ++u) {
                    if (graph.getGraph()[v][u] != 0) {
                        if (colors[u] == -1) { // If the vertex u is not colored
                            colors[u] = 1 - colors[v]; // Color with the opposite color
                            q.push(u);
                        } else if (colors[u] == colors[v]) {
                            // If adjacent vertices have the same color, the graph is not bipartite
                            return "0";
                        }
                    }
                }
            }
        }
    }

    vector<int> partition1, partition2;
    partitionGraph(colors, partition1, partition2);

    ostringstream result;
    result << "The graph is bipartite.\n";
    result << "Partition 1: { ";
    for (int v : partition1) {
        result << v << " ";
    }
    result << "}\n";
    result << "Partition 2: { ";
    for (int v : partition2) {
        result << v << " ";
    }
    result << "}";

    return result.str();
}

void Algorithms::printNegativeCycle(const std::vector<int>& parent, int start) {
    int current = start;
    std::vector<int> cycle;
    do {
        cycle.push_back(current);
        current = parent[current];
    } while (current != start);
    cycle.push_back(start);
    std::reverse(cycle.begin(), cycle.end());

    cout << "Negative cycle found: ";
    for (int v : cycle) {
        cout << v << " ";
    }
    cout << endl;
}

// Function to detect and print negative cycles
/**
 * Detects and prints negative cycles using the Bellman-Ford algorithm.
 *
 * @param graph The graph to check.
 */
void Algorithms::negativeCycle(const Graph& graph) {
    int numVer = graph.getVertexNum();
    vector<int> dist(numVer, numeric_limits<int>::max());
    vector<int> parent(numVer, -1);
    dist[0] = 0; // Start from vertex 0 (or you can loop through all vertices as start points)

    // Relax edges |V| - 1 times
    for (int i = 0; i < numVer - 1; ++i) {
        for (int u = 0; u < numVer; ++u) {
            for (int v = 0; v < numVer; ++v) {
                if (graph.getGraph()[u][v] != numeric_limits<int>::max() && dist[u] != numeric_limits<int>::max() && dist[u] + graph.getGraph()[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph.getGraph()[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < numVer; ++u) {
        for (int v = 0; v < numVer; ++v) {
            if (graph.getGraph()[u][v] != numeric_limits<int>::max() && dist[u] != numeric_limits<int>::max() && dist[u] + graph.getGraph()[u][v] < dist[v]) {
                // Negative cycle detected, reconstruct the cycle
                vector<bool> visited(numVer, false);
                int current = v;
                while (!visited[current]) {
                    visited[current] = true;
                    current = parent[current];
                }

                if (isValidCycle(parent, current, graph)) {
                    printNegativeCycle(parent, current);
                } else {
                    cout << "False positive detected, not a real negative cycle in a undirected graph." << endl;
                }
                return;
            }
        }
    }

    cout << "No negative cycle found." << endl;
}

// Helper function to validate a cycle
/**
 * Validates if the detected cycle is a true negative cycle.
 *
 * @param parent The parent vector.
 * @param start The starting vertex of the cycle.
 * @param graph The graph.
 * @return True if the cycle is valid, false otherwise.
 */
bool Algorithms::isValidCycle(const vector<int>& parent, int start, const Graph& graph) {
    vector<int> cycle;
    int current = start;
    do {
        cycle.push_back(current);
        current = parent[current];
    } while (current != start);
    cycle.push_back(start);
    reverse(cycle.begin(), cycle.end());

    // Check for cycle length of 3 vertices (2 edges)
    if (cycle.size() == 3) {
        int u = cycle[0];
        int v = cycle[1];
        if (!graph.getIsDirected() && graph.getGraph()[u][v] != numeric_limits<int>::max() && graph.getGraph()[v][u] != numeric_limits<int>::max()) {
            return false;  // Not a valid negative cycle in a directed graph
        }
    }
    return true;
}
