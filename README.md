# Nadav034@gmail.com

# Graph Operations Project

## Introduction

This project implements a `Graph` class that supports various operations on graphs represented by adjacency matrices. The `Graph` class includes arithmetic, comparison, increment, and decrement operators. This project also includes tests for each operator to ensure their correct functionality.

## Setup Instructions

### Prerequisites

- C++ compiler (e.g., `g++`)
- [doctest](https://github.com/onqtam/doctest) library for testing

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/graph-operations.git
    cd graph-operations
    ```

2. Install the `doctest` library if not already installed:
    ```sh
    sudo apt-get install doctest-dev
    ```

3. Build and run the tests:
    ```sh
    g++ -o test TestGraphOperators.cpp Graph.cpp -I/path/to/doctest
    ./test
    ```

## Graph Class

### Overview

The `Graph` class provides the following operators:

1. **Arithmetic Operators**
   - **Addition (`+`)**: Adds the adjacency matrices of two graphs.
   - **Subtraction (`-`)**: Subtracts the adjacency matrix of one graph from another.
   - **Unary Plus (`+`)**: Returns a copy of the graph.
   - **Unary Minus (`-`)**: Negates the weights of all edges in the graph.
   - **Addition Assignment (`+=`)**: Adds another graph to the current graph.
   - **Subtraction Assignment (`-=`)**: Subtracts another graph from the current graph.

2. **Comparison Operators**
   - **Equal to (`==`)**: Checks if two graphs are equal.
   - **Not Equal to (`!=`)**: Checks if two graphs are not equal.
   - **Greater than (`>`)**: Checks if one graph is greater than another.
   - **Greater than or Equal to (`>=`)**: Checks if one graph is greater than or equal to another.
   - **Less than (`<`)**: Checks if one graph is less than another.
   - **Less than or Equal to (`<=`)**: Checks if one graph is less than or equal to another.

3. **Increment and Decrement Operators**
   - **Prefix Increment (`++`)**: Increases the weights of all edges by 1.
   - **Postfix Increment (`++(int)`)**: Increases the weights of all edges by 1 and returns the original graph.
   - **Prefix Decrement (`--`)**: Decreases the weights of all edges by 1.
   - **Postfix Decrement (`--(int)`)**: Decreases the weights of all edges by 1 and returns the original graph.

4. **Scalar Multiplication**
   - **Multiplication (`*`)**: Multiplies the weights of all edges by a scalar.

5. **Graph Multiplication**
   - **Multiplication (`*`)**: Multiplies the adjacency matrices of two graphs.
   - Multiplication Assignment (`*=`): Multiplies the weights of all edges by a scalar, modifying the graph in place.
   - Division Assignment (`/=`): Divides the weights of all edges by a scalar, modifying the graph in place. Note: Division by zero is not allowed and will throw an exception.

6. **Output Operator**
   - **Output (`<<`)**: Outputs the adjacency matrix of the graph to the stream.

### Example Usage

```cpp
#include "Graph.h"
#include <iostream>

int main() {
    Graph g1({
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    }, false, true, 3);

    Graph g2({
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    }, false, true, 3);

    // Addition
    Graph g3 = g1 + g2;
    std::cout << "Addition of g1 and g2:\n" << g3 << std::endl;

    // Subtraction
    Graph g4 = g2 - g1;
    std::cout << "Subtraction of g1 from g2:\n" << g4 << std::endl;

    // Unary Plus
    Graph g5 = +g1;
    std::cout << "Unary plus of g1:\n" << g5 << std::endl;

    // Unary Minus
    Graph g6 = -g1;
    std::cout << "Unary minus of g1:\n" << g6 << std::endl;

    // Scalar Multiplication
    Graph g7 = g1 * 2;
    std::cout << "Scalar multiplication of g1 by 2:\n" << g7 << std::endl;

    // Graph Multiplication
    Graph g8 = g1 * g2;
    std::cout << "Graph multiplication of g1 and g2:\n" << g8 << std::endl;

    return 0;
}
