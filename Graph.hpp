#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Graph {
private:
    int numVer;
    bool isDirected;
    bool isWeighted;
    vector<vector<int>> graph;

public:
    //Constructor
    Graph(vector<vector<int>> newGraph, bool directed, bool weighted, int vertex);

    //default constructor
    Graph();

    void loadGraph(const vector<vector<int>>& newGraph);
    void printGraph();

    //Getters

    int getVertexNum() const;
    bool getIsDirected() const;
    bool getIsWeighted() const;
    bool getIsEmpty() const;
    const std::vector<std::vector<int>>& getGraph() const;
    bool isGraphDirected();
    bool isGraphWeighted();
    int getNumberOfEdges() const;
    bool haveSameEdges(const Graph& graph1)const;
    bool isContainedIn(const Graph& other) const;
    bool isSubmatrixMatch(const std::vector<std::vector<int>>& largerGraph, const std::vector<std::vector<int>>& subGraph, int startRow, int startCol)const;


    // Arithmetic operators
    Graph operator+() const;
    Graph operator+(const Graph& other) const;
    Graph& operator+=(const Graph& other);
    Graph operator-() const;
    Graph operator-(const Graph& other) const;
    Graph& operator-=(const Graph& other);

    // Comparison operators
    bool operator==(const Graph& other) const;
    bool operator!=(const Graph& other) const;
    bool operator<(const Graph& other) const;
    bool operator<=(const Graph& other) const;
    bool operator>(const Graph& other) const;
    bool operator>=(const Graph& other) const;

    // Increment and decrement operators
    Graph& operator++();    // Prefix increment
    const Graph operator++(int);  // Postfix increment
    Graph& operator--();    // Prefix decrement
    const Graph operator--(int);  // Postfix decrement

    // Scalar multiplication
    Graph operator*(int scalar) const;

    // Graph multiplication
    Graph operator*(const Graph& other) const;

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
};




