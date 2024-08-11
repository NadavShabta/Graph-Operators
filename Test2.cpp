// Nadav034@gmail.com

#include "doctest/doctest.h"
#include "Algorithms.hpp"
#include <vector>
#include "Graph.hpp"
#include <sstream>

using namespace std;


TEST_CASE("Test graph addition") {
    Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g1.loadGraph(graph);

    Graph g2;
    vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
    };
    g2.loadGraph(weightedGraph);

    Graph g3 = g1 + g2;

    vector<vector<int>> expectedGraph = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}
    };
    Graph expect;
    expect.loadGraph(expectedGraph);

    CHECK(g3.haveSameEdges(expect));
}

TEST_CASE("Test graph subtraction") {
    Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g1.loadGraph(graph);

    Graph g2;
    vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
    };
    g2.loadGraph(weightedGraph);

    Graph g3 = g2 - g1;

    vector<vector<int>> expectedGraph = {
            {0, 0, 1},
            {0, 0, 1},
            {1, 1, 0}
    };

    CHECK(g3.getGraph() == expectedGraph);
}

TEST_CASE("Test unary plus operator") {
    Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g1.loadGraph(graph);

    Graph g2 = +g1;

    CHECK(g1.getGraph() == g2.getGraph());
}

TEST_CASE("Test unary minus operator") {
    Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g1.loadGraph(graph);

    Graph g2 = -g1;

    vector<vector<int>> expectedGraph = {
            {0, -1, 0},
            {-1, 0, -1},
            {0, -1, 0}
    };

    CHECK(g2.getGraph() == expectedGraph);
}

TEST_CASE("Test comparison operators") {
    Graph g1;
    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
    };
    g2.loadGraph(graph2);

    Graph g3 = g1 + g1;  // g3 is equal to twice of g1

    CHECK(g1 != g2);
    CHECK(g1 == g1);
    CHECK(g2 > g1);
    CHECK(g1 < g2);
    CHECK(g1 <= g1);
    CHECK(g1 >= g1);
    CHECK(!(g3 > g1));
    CHECK(!(g1 < g3));
}
TEST_CASE("Test subgraph comparison") {
    Graph g1;
    vector<vector<int>> graph1 = {
            {0, 1},
            {1, 0}
    };
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g2.loadGraph(graph2);

    CHECK(g1 != g2);
    CHECK(g2 > g1);
    CHECK(g1 < g2);
    CHECK(g1 <= g2);
    CHECK(!(g1 >= g2));

    Graph g3;
    vector<vector<int>> graph3 = {
            {0, 0},
            {1, 0}
    };
    g3.loadGraph(graph3);

    Graph g4;
    vector<vector<int>> graph4 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g4.loadGraph(graph4);
    CHECK(g4 != g3);
    CHECK(g4 > g3);
    CHECK(g3 < g4);
    CHECK(g3 <= g4);
    CHECK(!(g3 >= g4));

    Graph g5;
    vector<vector<int>> graph5 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g5.loadGraph(graph5);

    Graph g6;
    vector<vector<int>> graph6 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g6.loadGraph(graph6);

    cout<<"g5"<<endl;
    g5.printGraph();
    cout<<"g6"<<endl;
    g6.printGraph();
    CHECK(g6 == g5);
    CHECK(!(g6 > g5));
    CHECK(!(g5 < g6));
    CHECK(g6 <= g5);
    CHECK(g5 >= g6);
}


TEST_CASE("Test increment and decrement operators") {
    Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g1.loadGraph(graph);

    Graph g2 = g1;
    ++g1;

    vector<vector<int>> expectedIncrementedGraph = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}
    };

    CHECK(g1.getGraph() == expectedIncrementedGraph);

    --g1;
    CHECK(g1.getGraph() == graph);

    g1--;
    vector<vector<int>> expectedDecrementedGraph = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
    };

    CHECK(g1.getGraph() == expectedDecrementedGraph);
}

TEST_CASE("Test scalar multiplication") {
    Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g1.loadGraph(graph);

    Graph g2 = g1 * 2;

    vector<vector<int>> expectedGraph = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}
    };

    CHECK(g2.getGraph() == expectedGraph);
}

TEST_CASE("Test graph multiplication") {
    Graph g1;
    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
    };
    g2.loadGraph(graph2);

    Graph g3 = g1 * g2;

    vector<vector<int>> expectedGraph = {
            {1, 0, 2},
            {1, 3, 1},
            {1, 0, 2}
    };

    CHECK(g3.getGraph() == expectedGraph);
}

TEST_CASE("Test graph output") {
    Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g1.loadGraph(graph);

    ostringstream os;
    os << g1;

    string expectedOutput = "0 1 0 \n1 0 1 \n0 1 0 \n";
    CHECK(os.str() == expectedOutput);
}

TEST_CASE("Test operations with graphs having negative weights") {
    Graph g1;
    vector<vector<int>> graph1 = {
            {0, -1, 0},
            {-1, 0, -2},
            {0, -2, 0}
    };
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
            {0, -1, -1},
            {-1, 0, -2},
            {-1, -2, 0}
    };
    g2.loadGraph(graph2);

    // Test addition
    Graph result = g1 + g2;
    vector<vector<int>> expectedAddition = {
            {0, -2, -1},
            {-2, 0, -4},
            {-1, -4, 0}
    };
    CHECK(result.getGraph() == expectedAddition);

    // Test subtraction
    result = g2 - g1;
    vector<vector<int>> expectedSubtraction = {
            {0, 0, -1},
            {0, 0, 0},
            {-1, 0, 0}
    };
    CHECK(result.getGraph() == expectedSubtraction);

    // Test unary minus
    result = -g1;
    vector<vector<int>> expectedUnaryMinus = {
            {0, 1, 0},
            {1, 0, 2},
            {0, 2, 0}
    };
    CHECK(result.getGraph() == expectedUnaryMinus);

    // Test scalar multiplication
    result = g1 * 2;
    vector<vector<int>> expectedScalarMultiplication = {
            {0, -2, 0},
            {-2, 0, -4},
            {0, -4, 0}
    };
    CHECK(result.getGraph() == expectedScalarMultiplication);
}

TEST_CASE("Test operations with self-loops") {
    Graph g1;
    vector<vector<int>> graph1 = {
            {1, 1, 0},
            {1, 1, 1},
            {0, 1, 1}
    };
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}
    };
    g2.loadGraph(graph2);

    // Test addition
    Graph result = g1 + g2;
    vector<vector<int>> expectedAddition = {
            {1, 2, 1},
            {2, 1, 2},
            {1, 2, 1}
    };
    CHECK(result.getGraph() == expectedAddition);

    // Test subtraction
    result = g1 - g2;
    vector<vector<int>> expectedSubtraction = {
            {1, 0, -1},
            {0, 1, 0},
            {-1, 0, 1}
    };
    CHECK(result.getGraph() == expectedSubtraction);

    // Test unary minus
    result = -g1;
    vector<vector<int>> expectedUnaryMinus = {
            {-1, -1, 0},
            {-1, -1, -1},
            {0, -1, -1}
    };
    CHECK(result.getGraph() == expectedUnaryMinus);

    // Test scalar multiplication
    result = g1 * 3;
    vector<vector<int>> expectedScalarMultiplication = {
            {3, 3, 0},
            {3, 3, 3},
            {0, 3, 3}
    };
    CHECK(result.getGraph() == expectedScalarMultiplication);
}

TEST_CASE("Test operations on large graphs") {
    const int size = 100;
    vector<vector<int>> largeGraph1(size, vector<int>(size, 1));
    vector<vector<int>> largeGraph2(size, vector<int>(size, 2));

    Graph g1;
    g1.loadGraph(largeGraph1);

    Graph g2;
    g2.loadGraph(largeGraph2);

    // Test addition
    Graph result = g1 + g2;
    vector<vector<int>> expectedAddition(size, vector<int>(size, 3));
    CHECK(result.getGraph() == expectedAddition);

    // Test subtraction
    result = g2 - g1;
    vector<vector<int>> expectedSubtraction(size, vector<int>(size, 1));
    CHECK(result.getGraph() == expectedSubtraction);

    // Test scalar multiplication
    result = g1 * 2;
    vector<vector<int>> expectedScalarMultiplication(size, vector<int>(size, 2));
    CHECK(result.getGraph() == expectedScalarMultiplication);
}




