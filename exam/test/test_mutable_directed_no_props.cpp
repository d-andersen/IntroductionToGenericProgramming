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
 * Test of Directed graph with no properties
 * satisfying MutableGraph concept
 */
#include <iomanip>
#include <iostream>

#include <graph/adjacency_list.hpp>
#include <graph/concepts.hpp>
#include <graph/tags.hpp>


using Graph = graph::AdjacencyList<graph::tags::Directed>;

void print_vertices(const Graph &g)
{
    for (auto v : vertices(g)) {
        std::cout << v;
        if (v != numVertices(g) - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

void print_edges(const Graph &g)
{
    for (auto e : edges(g)) {
        std::cout << e.storedEdgeIdx << ": (" << e.src << ',' << e.tar << ')';
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
    static_assert(std::copyable<Graph>);
    static_assert(std::move_constructible<Graph>);
    static_assert(std::movable<Graph>);

    auto G{Graph()};

    std::cout << std::setfill('=') << std::setw(80) << "" << '\n';
    std::cout << "DM852 Introduction to Generic Programming\n";
    std::cout << "Final Project - Spring 2022 - Dennis Andersen - deand17\n\n";
    std::cout << "Test: AdjacencyList<tags::Directed> satisfies MutableGraph concept\n\n";

    std::cout << "G: |V| = " << numVertices(G) << ", Vertices: ";
    print_vertices(G);
    std::cout << "G: |E| = " << numEdges(G) << ", Edges: ";
    print_edges(G);

    std::cout << "\nAdding 4 vertices and 4 edges to G\n";
    for (int i = 0; i < 4; ++i) {
        addVertex(G);
    }
    addEdge(0, 1, G);
    addEdge(0, 2, G);
    addEdge(1, 3, G);
    addEdge(2, 3, G);

    std::cout << "G: |V| = " << numVertices(G) << ", Vertices: ";
    print_vertices(G);
    std::cout << "G: |E| = " << numEdges(G) << ", Edges: ";
    print_edges(G);

    std::cout << "\nOut degree and out edges for each vertex:\n";
    for (auto v : vertices(G)) {
        std::cout << v << ", out degree:   "
                  << outDegree(v, G) << ", out edges: ";
        auto oe{outEdges(v, G)};
        for (auto e : oe) {
            std::cout << e.storedEdgeIdx << ": (" << e.src << ',' << e.tar << ") ";
        }
        std::cout << '\n';
    }
    std::cout << std::setfill('=') << std::setw(80) << "" << '\n';

    return 0;
}