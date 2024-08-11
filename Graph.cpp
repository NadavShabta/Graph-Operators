//  Nadav034@gmail.com

#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// Constructors

/**
 * Constructs a Graph with a specified adjacency matrix, direction, and weight status.
 *
 * @param newGraph The adjacency matrix.
 * @param directed True if the graph is directed.
 * @param weighted True if the graph has weighted edges.
 * @param vertex The number of vertices in the graph.
 */
Graph::Graph(std::vector<std::vector<int>> newGraph, bool directed, bool weighted, int vertex) {
    this->graph = newGraph;
    this->isDirected = directed;
    this->isWeighted = weighted;
    this->numVer = vertex;
}

/**
 * Default constructor for an empty graph.
 */
Graph::Graph() : numVer(0), isDirected(false), isWeighted(false) {}

/**
 * Loads a new adjacency matrix into the graph.
 *
 * @param newGraph The new adjacency matrix.
 * @throws std::invalid_argument if the matrix is not square.
 */
void Graph::loadGraph(const vector<vector<int>>& newGraph) {
    if (newGraph.empty()) {
        graph.clear();
        numVer = 0;
        isDirected = false;
        isWeighted = false;
        return;
    }

    std::size_t rows = newGraph.size();
    for (const auto& row : newGraph) {
        if (row.size() != rows) {
            throw std::invalid_argument("Invalid graph: The provided graph is not a square matrix.");
        }
    }

    graph = newGraph;
    numVer = static_cast<int>(rows);
    isDirected = isGraphDirected();
    isWeighted = isGraphWeighted();
}

/**
 * Prints the graph's adjacency matrix.
 */
void Graph::printGraph() {
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            cout << this->graph[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Checks if the graph is directed.
 *
 * @return True if the graph is directed.
 */
bool Graph::isGraphDirected() {
    for (int i = 0; i < this->getVertexNum(); ++i) {
        for (int j = 0; j < this->getVertexNum(); ++j) {
            if (this->getGraph()[i][j] != this->getGraph()[j][i]) {
                this->isDirected = true;
                return true;
            }
        }
    }
    this->isDirected = false;
    return false;
}

/**
 * Checks if the graph has weighted edges.
 *
 * @return True if the graph has weighted edges.
 */
bool Graph::isGraphWeighted() {
    for (int i = 0; i < this->getVertexNum(); ++i) {
        for (int j = 0; j < this->getVertexNum(); ++j) {
            if ((this->getGraph()[i][j] > 1) || (this->getGraph()[i][j] < 0)) {
                this->isWeighted = true;
                return true;
            }
        }
    }
    this->isWeighted = false;
    return false;
}

/**
 * Checks if the graph has negative weights.
 *
 * @return True if the graph has negative weights.
 */
bool Graph::isGraphNegWeighted() {
    for (int i = 0; i < this->getVertexNum(); ++i) {
        for (int j = 0; j < this->getVertexNum(); ++j) {
            if (this->getGraph()[i][j] < 0) {
                return true;
            }
        }
    }
    return false;
}

// Getters

/**
 * Gets the number of vertices.
 *
 * @return The number of vertices.
 */
int Graph::getVertexNum() const {
    return numVer;
}

/**
 * Checks if the graph is directed.
 *
 * @return True if the graph is directed.
 */
bool Graph::getIsDirected() const {
    return isDirected;
}

/**
 * Checks if the graph has weighted edges.
 *
 * @return True if the graph has weighted edges.
 */
bool Graph::getIsWeighted() const {
    return isWeighted;
}

/**
 * Checks if the graph is empty.
 *
 * @return True if the graph is empty.
 */
bool Graph::getIsEmpty() const {
    return numVer == 0;
}

/**
 * Gets the adjacency matrix of the graph.
 *
 * @return The adjacency matrix.
 */
const vector<vector<int>>& Graph::getGraph() const {
    return this->graph;
}

/**
 * Gets the number of edges in the graph.
 *
 * @return The number of edges.
 */
int Graph::getNumberOfEdges() const {
    int numEdges = 0;
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            if (graph[i][j] != 0) {
                numEdges++;
            }
        }
    }
    if (!isDirected) {
        numEdges /= 2;
    }
    return numEdges;
}

/**
 * Checks if two graphs have the same edges.
 *
 * @param graph1 The graph to compare.
 * @return True if the graphs have the same edges.
 */
bool Graph::haveSameEdges(const Graph& graph1) const {
    if (graph1.getVertexNum() != numVer) {
        return false;
    }
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            if (graph[i][j] != graph1.getGraph()[i][j]) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Checks if a submatrix matches the current graph.
 *
 * @param largerGraph The larger graph.
 * @param subGraph The subgraph to match.
 * @param startRow The starting row.
 * @param startCol The starting column.
 * @return True if the subgraph matches.
 */
bool Graph::isSubmatrixMatch(const std::vector<std::vector<int>>& largerGraph, const std::vector<std::vector<int>>& subGraph, int startRow, int startCol) const {
    size_t subRows = subGraph.size();
    size_t subCols = subGraph[0].size();

    for (size_t i = 0; i < subRows; ++i) {
        for (size_t j = 0; j < subCols; ++j) {
            if (largerGraph[startRow + i][startCol + j] != subGraph[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Function to check if the current graph is contained in another graph
/**
 * Checks if the current graph is contained within another graph.
 *
 * @param other The other graph to check against.
 * @return True if the current graph is contained within the other graph.
 */
bool Graph::isContainedIn(const Graph& other) const {
    if (numVer > other.numVer) {
        return false;
    }
    int a = 0;
    if (numVer == other.numVer) {
        for (int i = 0; i < numVer; ++i) {
            for (int j = 0; j < numVer; ++j) {
                if (graph[i][j] != other.graph[i][j]) {
                    ++a;
                }
            }
        }
        if (a == 0) return false;
    }

    int subRows = numVer;
    int subCols = numVer;
    const auto& otherGraph = other.getGraph();

    for (int i = 0; i <= other.numVer - subRows; ++i) {
        for (int j = 0; j <= other.numVer - subCols; ++j) {
            if (isSubmatrixMatch(otherGraph, graph, i, j)) {
                return true;
            }
        }
    }
    return false;
}

// Arithmetic operators

/**
 * Unary plus operator, returns a copy of the graph.
 *
 * @return A copy of the current graph.
 */
Graph Graph::operator+() const {
    return *this;
}

/**
 * Adds two graphs together.
 *
 * @param other The graph to add.
 * @return The resulting graph.
 * @throws invalid_argument if the graphs are not the same size.
 */
Graph Graph::operator+(const Graph& other) const {
    if (numVer != other.numVer) {
        throw invalid_argument("Graphs must be of the same size to add.");
    }
    Graph result(graph, isDirected, isWeighted, numVer);
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            result.graph[i][j] = graph[i][j] + other.graph[i][j];
        }
    }
    return result;
}

/**
 * Adds another graph to the current graph.
 *
 * @param other The graph to add.
 * @return The current graph after addition.
 */
Graph& Graph::operator+=(const Graph& other) {
    *this = *this + other;
    return *this;
}

/**
 * Unary minus operator, negates the weights of the graph.
 *
 * @return The resulting graph with negated weights.
 */
Graph Graph::operator-() const {
    Graph result(graph, isDirected, isWeighted, numVer);
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            result.graph[i][j] = -graph[i][j];
        }
    }
    return result;
}

/**
 * Subtracts another graph from the current graph.
 *
 * @param other The graph to subtract.
 * @return The resulting graph after subtraction.
 * @throws invalid_argument if the graphs are not the same size.
 */
Graph Graph::operator-(const Graph& other) const {
    if (numVer != other.numVer) {
        throw invalid_argument("Graphs must be of the same size to subtract.");
    }
    Graph result(graph, isDirected, isWeighted, numVer);
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            result.graph[i][j] = graph[i][j] - other.graph[i][j];
        }
    }
    return result;
}

/**
 * Subtracts another graph from the current graph.
 *
 * @param other The graph to subtract.
 * @return The current graph after subtraction.
 */
Graph& Graph::operator-=(const Graph& other) {
    *this = *this - other;
    return *this;
}

// Comparison operators

/**
 * Checks if the current graph is greater than another graph.
 *
 * @param other The graph to compare against.
 * @return True if the current graph is greater.
 */
bool Graph::operator>(const Graph& other) const {
    if (isContainedIn(other)) {
        return false;
    }
    if (other.isContainedIn(*this)) {
        return true;
    }
    if (this->getNumberOfEdges() > other.getNumberOfEdges()) {
        return true;
    } else if (numVer > other.numVer) {
        return true;
    }

    return false;
}

/**
 * Checks if the current graph is less than another graph.
 *
 * @param other The graph to compare against.
 * @return True if the current graph is less.
 */
bool Graph::operator<(const Graph& other) const {
    if (isContainedIn(other)) {
        return true;
    }
    if (other.isContainedIn(*this)) {
        return false;
    }
    if (this->getNumberOfEdges() < other.getNumberOfEdges()) {
        return true;
    } else if (this->getNumberOfEdges() == other.getNumberOfEdges() && numVer < other.numVer) {
        return true;
    }
    return false;
}

/**
 * Checks if the current graph is equal to another graph.
 *
 * @param other The graph to compare against.
 * @return True if the graphs are equal.
 */
bool Graph::operator==(const Graph& other) const {
    if (haveSameEdges(other)) {
        return true;
    }
    if (!(*this > other) && !(*this < other)) {
        return true;
    }
    return false;
}

/**
 * Checks if the current graph is not equal to another graph.
 *
 * @param other The graph to compare against.
 * @return True if the graphs are not equal.
 */
bool Graph::operator!=(const Graph& other) const {
    return !(*this == other);
}

/**
 * Checks if the current graph is greater than or equal to another graph.
 *
 * @param other The graph to compare against.
 * @return True if the current graph is greater than or equal.
 */
bool Graph::operator>=(const Graph& other) const {
    return *this > other || *this == other;
}

/**
 * Checks if the current graph is less than or equal to another graph.
 *
 * @param other The graph to compare against.
 * @return True if the current graph is less than or equal.
 */
bool Graph::operator<=(const Graph& other) const {
    return *this < other || *this == other;
}

// Increment and decrement operators

/**
 * Prefix increment operator, increases all edge weights by 1.
 *
 * @return The incremented graph.
 */
Graph& Graph::operator++() {
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            if (graph[i][j] != 0) {
                ++graph[i][j];
            }
        }
    }
    return *this;
}

/**
 * Postfix increment operator, increases all edge weights by 1.
 *
 * @return A copy of the graph before incrementing.
 */
const Graph Graph::operator++(int) {
    Graph temp = *this;
    ++(*this);
    return temp;
}

/**
 * Prefix decrement operator, decreases all edge weights by 1.
 *
 * @return The decremented graph.
 */
Graph& Graph::operator--() {
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            if (graph[i][j] != 0) {
                --graph[i][j];
            }
        }
    }
    return *this;
}

/**
 * Postfix decrement operator, decreases all edge weights by 1.
 *
 * @return A copy of the graph before decrementing.
 */
const Graph Graph::operator--(int) {
    Graph temp = *this;
    --(*this);
    return temp;
}

// Scalar multiplication

/**
 * Multiplies all edge weights by a scalar value.
 *
 * @param scalar The scalar to multiply by.
 * @return The resulting graph.
 */
Graph Graph::operator*(int scalar) const {
    Graph result(graph, isDirected, isWeighted, numVer);
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            result.graph[i][j] = graph[i][j] * scalar;
        }
    }
    return result;
}

// Graph multiplication

/**
 * Multiplies two graphs using matrix multiplication.
 *
 * @param other The graph to multiply with.
 * @return The resulting graph.
 * @throws invalid_argument if the graphs are not the same size.
 */
Graph Graph::operator*(const Graph& other) const {
    if (numVer != other.numVer) {
        throw invalid_argument("Graphs must be of the same size to multiply.");
    }
    Graph result(vector<vector<int>>(numVer, vector<int>(numVer, 0)), isDirected, isWeighted, numVer);
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            for (int k = 0; k < numVer; ++k) {
                result.graph[i][j] += graph[i][k] * other.graph[k][j];
            }
        }
    }
    return result;
}

// Output operator

/**
 * Overloads the << operator for easy printing of the graph.
 *
 * @param os The output stream.
 * @param g The graph to print.
 * @return The output stream.
 */
ostream& operator<<(ostream& os, const Graph& g) {
    for (int i = 0; i < g.numVer; ++i) {
        for (int j = 0; j < g.numVer; ++j) {
            os << g.graph[i][j] << " ";
        }
        os << endl;
    }
    return os;
}
