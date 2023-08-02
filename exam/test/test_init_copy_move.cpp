/**
 * main.cpp
 *
 * DM852 Introduction to Generic Programming
 *
 * Final Project - Spring 2022
 *
 * Dennis Andersen - deand17
 * 2022-06-15
 *
 * Test file
 */
#include <concepts>
#include <iomanip>
#include <iostream>

#include <graph/adjacency_list.hpp>
#include <graph/concepts.hpp>
#include <graph/tags.hpp>


using Graph = graph::AdjacencyList<graph::tags::Directed, std::string, std::string>;

void print_vertices(const Graph &g)
{
    for (auto v : vertices(g)) {
        std::cout << v << ": '" << g[v] << "'";
        if (v != numVertices(g) - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

void print_edges(const Graph &g)
{
    for (auto e : edges(g)) {
        std::cout << e.storedEdgeIdx << ": (" << e.src << ',' << e.tar << ") '" << g[e] << "'";
        if (e.storedEdgeIdx != numEdges(g) - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

int main()
{
    static_assert(graph::IncidenceGraph<Graph> && graph::MutableGraph<Graph>);
    static_assert(std::default_initializable<Graph>);
    static_assert(std::copy_constructible<Graph>);
    static_assert(std::move_constructible<Graph>);
    static_assert(std::copyable<Graph>);
    static_assert(std::movable<Graph>);

    std::cout << std::setfill('=') << std::setw(80) << "" << '\n';
    std::cout << "DM852 Introduction to Generic Programming\n";
    std::cout << "Final Project - Spring 2022 - Dennis Andersen - deand17\n\n";
    std::cout << "Test: AdjacencyList<tags::Directed, std::string, std::string> satisfies\n";
    std::cout << "      - std::default_initializable\n";
    std::cout << "      - std::copy_constructible\n";
    std::cout << "      - std::move_constructible\n";
    std::cout << "      - std::copyable\n";
    std::cout << "      - std::movable\n\n";

    // --------------------------------------------------------------------------------

    std::cout << std::setfill('-') << std::setw(80) << "" << '\n';
    std::cout << "Testing std::default_initializable: G\n\n";
    auto G{Graph()};

    std::cout << "G: |V| = " << numVertices(G) << ", Vertices: ";
    print_vertices(G);
    std::cout << "G: |E| = " << numEdges(G) << ", Edges: ";
    print_edges(G);

    std::cout << "\nTest std::default_initializable ... OK\n";
    std::cout << std::setfill('-') << std::setw(80) << "" << '\n';

    // --------------------------------------------------------------------------------

    std::vector<std::string> s{"Introduction", "to", "Generic", "Programming"};
    std::cout << "\nAdding 4 vertices and 4 edges to G\n";
    for (int i = 0; i < 4; ++i) {
        addVertex(std::move(s[i]), G);
    }
    addEdge(0, 1, std::move(std::string{"e0"}), G);
    addEdge(0, 2, std::move(std::string{"e1"}), G);
    addEdge(1, 3, std::move(std::string{"e2"}), G);
    addEdge(2, 3, std::move(std::string{"e3"}), G);

    std::cout << "G: |V| = " << numVertices(G) << ", Vertices: ";
    print_vertices(G);
    std::cout << "G: |E| = " << numEdges(G) << ", Edges: ";
    print_edges(G);
    std::cout << '\n';

    // --------------------------------------------------------------------------------

    std::cout << std::setfill('-') << std::setw(80) << "" << '\n';
    std::cout << "Testing std::copy_constructible: G2 = G\n\n";

    auto G2 = G;
    std::cout << "Adding additional vertex 4: 'DM852' and edge (3,4) 'e4' to G2\n";
    addVertex(std::move(std::string{"DM852"}), G2);
    addEdge(3, 4, std::move(std::string{"e4"}), G2);

    std::cout << "G: |V| = " << numVertices(G) << ", Vertices: ";
    print_vertices(G);
    std::cout << "G: |E| = " << numEdges(G) << ", Edges: ";
    print_edges(G);
    std::cout << "G2: |V| = " << numVertices(G2) << ", Vertices: ";
    print_vertices(G2);
    std::cout << "G2: |E| = " << numEdges(G2) << ", Edges: ";
    print_edges(G2);

    std::cout << "\nTest std::copy_constructible: G2 = G ... OK\n";
    std::cout << std::setfill('-') << std::setw(80) << "" << '\n';

    // --------------------------------------------------------------------------------

    std::cout << "Testing std::move_constructible: G3 = std::move(G2)\n\n";

    auto G3 = std::move(G2);
    std::cout << "G2: |V| = " << numVertices(G2) << ", Vertices: ";
    print_vertices(G2);
    std::cout << "G2: |E| = " << numEdges(G2) << ", Edges: ";
    print_edges(G2);
    std::cout << "G3: |V| = " << numVertices(G3) << ", Vertices: ";
    print_vertices(G3);
    std::cout << "G3: |E| = " << numEdges(G3) << ", Edges: ";
    print_edges(G3);

    std::cout << "\nTest std::move_constructible: G3 = std::move(G2) ... OK\n";
    std::cout << std::setfill('-') << std::setw(80) << "" << '\n';

    // --------------------------------------------------------------------------------

    std::cout << "Testing std::copyable: G2 = G\n";
    G2 = G;
    std::cout << "G: |V| = " << numVertices(G) << ", Vertices: ";
    print_vertices(G);
    std::cout << "G: |E| = " << numEdges(G) << ", Edges: ";
    print_edges(G);
    std::cout << "G2: |V| = " << numVertices(G2) << ", Vertices: ";
    print_vertices(G2);
    std::cout << "G2: |E| = " << numEdges(G2) << ", Edges: ";
    print_edges(G2);

    std::cout << "\nTest std::copyable: G2 = G ... OK\n";
    std::cout << std::setfill('=') << std::setw(80) << "" << '\n';

    // --------------------------------------------------------------------------------

    std::cout << "Testing std::movable: G = std::move(G3)\n";
    G = std::move(G3);
    std::cout << "G: |V| = " << numVertices(G) << ", Vertices: ";
    print_vertices(G);
    std::cout << "G: |E| = " << numEdges(G) << ", Edges: ";
    print_edges(G);
    std::cout << "G3: |V| = " << numVertices(G3) << ", Vertices: ";
    print_vertices(G3);
    std::cout << "G3: |E| = " << numEdges(G3) << ", Edges: ";
    print_edges(G3);

    std::cout << "\nTest std::movable: G = std::move(G3) ... OK\n";
    std::cout << std::setfill('=') << std::setw(80) << "" << '\n';

    return 0;
}