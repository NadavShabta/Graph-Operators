//
// Created by nadav on 6/20/2024.
//

#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

//Constructors

Graph::Graph(std::vector<std::vector<int>> newGraph, bool directed, bool weighted, int vertex) {
    this->graph=newGraph;
    this->isDirected=directed;
    this->isWeighted = weighted;
    this->numVer = vertex;
}
Graph::Graph() : numVer(0), isDirected(false), isWeighted(false) {}

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
void Graph::printGraph() {
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            cout<< this->graph[i][j] << " ";
        }
        cout<<endl;
    }
}

 bool Graph:: isGraphDirected() {
     for (int i = 0; i < this->getVertexNum(); ++i) {
         for (int j = 0; j < this->getVertexNum(); ++j) {
             if (this->getGraph()[i][j]!= this->getGraph()[j][i]){
                 this->isDirected= true;
                 return true;
             }
         }
     }
     this->isDirected = false;
     return false;
}

bool Graph :: isGraphWeighted() {
    for (int i = 0; i < this->getVertexNum(); ++i) {
        for (int j = 0; j < this->getVertexNum(); ++j) {
            if ((this->getGraph()[i][j]>1) || (this->getGraph()[i][j]<0 )){
                this->isWeighted = true;
                return true;
            }
        }
    }
    this->isWeighted= false;
    return false;
}
//Getters

int Graph:: getVertexNum() const{
    return numVer;
}
bool Graph :: getIsDirected() const{
    return isDirected;
}
bool Graph :: getIsWeighted() const{
    return isWeighted;
}
bool Graph :: getIsEmpty() const{
    return numVer == 0;
}
const vector<vector<int>>& Graph :: getGraph() const {
    return this->graph;
}
int Graph::getNumberOfEdges() const {
    int numEdges = 0;
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            if (graph[i][j] != 0) {
                numEdges++;
            }
        }
    }
    // For undirected graphs, each edge is counted twice
    if (!isDirected) {
        numEdges /= 2;
    }
    return numEdges;
}
bool Graph:: haveSameEdges(const Graph& graph1)const{
    if(graph1.getVertexNum()!=numVer){
        return false;
    }
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            if (graph[i][j]!=graph1.getGraph()[i][j]){
                return false;
            }
        }
    }
    return true;
}

//bool Graph:: isContain(const Graph& graph1) const{
//    if (this->numVer < graph1.numVer){
//        return false;
//    }
//    for (int i = 0; i < graph1.numVer; ++i) {
//        for (int j = 0; j < graph1.numVer; ++j) {
//            if (graph1.graph[i][j]!=0) {
//                if (graph[i][j] == 0) {
//                    return false;
//                }
//            }
//        }
//    }
//    return true;
//}
// Helper function to check if a submatrix matches the graph
bool Graph:: isSubmatrixMatch(const std::vector<std::vector<int>>& largerGraph, const std::vector<std::vector<int>>& subGraph, int startRow, int startCol)const {
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
bool Graph::isContainedIn(const Graph& other) const {
    if (numVer > other.numVer) {
        return false;
    }
    int a = 0;
    if (numVer == other.numVer){
        for (int i = 0; i < numVer; ++i) {
            for (int j = 0; j < numVer; ++j) {
                if (graph[i][j]!=other.graph[i][j]){
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

Graph Graph::operator+() const {
    return *this;
}
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

Graph& Graph::operator+=(const Graph& other) {
    *this = *this + other;
    return *this;
}

Graph Graph::operator-() const {
    Graph result(graph, isDirected, isWeighted, numVer);
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            result.graph[i][j] = -graph[i][j];
        }
    }
    return result;
}

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

Graph& Graph::operator-=(const Graph& other) {
    *this = *this - other;
    return *this;
}

// Comparison operators
bool Graph::operator>(const Graph& other) const {
    if (isContainedIn(other)) {
        return false;
    }
    if (other.isContainedIn(*this)){
        return true;
    }
    if (this->getNumberOfEdges()>other.getNumberOfEdges()){
        return true;
    } else if(numVer>other.numVer){
        return true;
    }

    return false;
}
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
bool Graph::operator==(const Graph& other) const {
    if (haveSameEdges(other)){
        return true;
    }
    if (!(*this>other) && !(*this<other)){
        return true;
    }
    return false;
}


bool Graph::operator!=(const Graph& other) const {
    return !(*this == other);
}


bool Graph::operator>=(const Graph& other) const {
    return *this > other || *this == other;
}

bool Graph::operator<=(const Graph& other) const {
    return *this < other || *this == other;
}





// Increment and decrement operators
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

const Graph Graph::operator++(int) {
    Graph temp = *this;
    ++(*this);
    return temp;
}

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

const Graph Graph::operator--(int) {
    Graph temp = *this;
    --(*this);
    return temp;
}

// Scalar multiplication
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
ostream& operator<<(ostream& os, const Graph& g) {
    for (int i = 0; i < g.numVer; ++i) {
        for (int j = 0; j < g.numVer; ++j) {
            os << g.graph[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

