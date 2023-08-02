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
 * Test of Bidirectional graph with properties
 * satisfying MutablePropertyGraph concept
 */
#include <iomanip>
#include <iostream>
#include <string>

#include <graph/adjacency_list.hpp>
#include <graph/concepts.hpp>
#include <graph/tags.hpp>


using Graph = graph::AdjacencyList<graph::tags::Bidirectional, std::string, std::string>;

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
    static_assert(graph::BidirectionalGraph<Graph> && graph::MutablePropertyGraph<Graph>);
    static_assert(std::default_initializable<Graph>);
    static_assert(std::copy_constructible<Graph>);
    static_assert(std::copyable<Graph>);
    static_assert(std::move_constructible<Graph>);
    static_assert(std::movable<Graph>);

    auto G{Graph()};

    std::cout << std::setfill('=') << std::setw(80) << "" << '\n';
    std::cout << "DM852 Introduction to Generic Programming\n";
    std::cout << "Final Project - Spring 2022 - Dennis Andersen - deand17\n\n";
    std::cout << "Test: AdjacencyList<tags::Bidirectional, std::string, std::string> satisfies MutablePropertyGraph concept\n\n";

    std::cout << "G: |V| = " << numVertices(G) << ", Vertices: ";
    print_vertices(G);
    std::cout << "G: |E| = " << numEdges(G) << ", Edges: ";
    print_edges(G);

    std::vector<std::string> s{"Introduction", "to", "Generic", "Programming"};
    std::cout << "\nAdding 4 vertices and 6 edges to G\n";
    for (int i = 0; i < 4; ++i) {
        addVertex(std::move(s[i]), G);
    }
    addEdge(0, 1, std::move(std::to_string(42)), G);
    addEdge(0, 2, std::move(std::to_string(43)), G);
    addEdge(1, 3, std::move(std::to_string(44)), G);
    addEdge(2, 3, std::move(std::to_string(45)), G);
    addEdge(3, 1, std::move(std::to_string(46)), G);
    addEdge(3, 2, std::move(std::to_string(47)), G);

    std::cout << "G: |V| = " << numVertices(G) << ", Vertices: ";
    print_vertices(G);
    std::cout << "G: |E| = " << numEdges(G) << ", Edges: ";
    print_edges(G);

    std::cout << "\nOut and in degree and out edges and in edges for each vertex:\n";
    for (auto v : vertices(G)) {
        std::cout << v << ": '" << G[v] << "'\n   out degree:   "
                  << outDegree(v, G) << ", out edges: ";
        auto oe{outEdges(v, G)};
        for (auto e : oe) {
            std::cout << e.storedEdgeIdx << ": (" << e.src << ',' << e.tar << ") ";
        }
        std::cout << "\n   in degree :   " << inDegree(v, G) << ", in edges : ";
        auto ie{inEdges(v, G)};
        for (auto e : ie) {
            std::cout << e.storedEdgeIdx << ": (" << e.src << ',' << e.tar << ") ";
        }
        std::cout << '\n';
    }
    std::cout << std::setfill('=') << std::setw(80) << "" << '\n';

    return 0;
}