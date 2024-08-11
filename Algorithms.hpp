// Nadav034@gmail.com

#include "Graph.hpp"
#include <utility> // for std::pair
#include <queue>


namespace Algorithms {
    int isConnected(Graph &graph);
    void DFSUtil(const Graph& graph, int v, std::vector<bool>& visited);
    std::string shortestPath(Graph& graph, int start, int end);
    std::string formatPath(const std::vector<int>& path);
    std::string bellmanFordShortestPath(const Graph &g, int start, int end);
    std::pair<int, std::vector<int>> dijkstraShortestPath(const Graph &graph, int start, int end);
    std::pair<int, std::vector<int>> bfsShortestPath(const Graph &graph, int start, int end);
    std::string isContainsCycle(const Graph& graph);
    void printCycle(const std::vector<int> &parent, int start, int end);
    bool DFSUtilUndirected(int v, int parent, const Graph &graph, std::vector<bool> &visited, std::vector<int> &parentVec);
    bool DFSUtilDirected(int v, const Graph &graph, std::vector<bool> &visited, std::vector<bool> &recStack,std::vector<int> &parentVec);
    std::string isBipartite(const Graph& graph);
    void partitionGraph(const std::vector<int>& colors, std::vector<int>& partition1, std::vector<int>& partition2);
    void relaxEdges(const Graph &g, std::vector<int> &dist, std::vector<int> &parent);
    void printNegativeCycle(const std::vector<int> &parent, int start);
    bool isValidCycle(const vector<int>& parent, int start, const Graph& graph);
    void negativeCycle(const Graph& graph);

}
