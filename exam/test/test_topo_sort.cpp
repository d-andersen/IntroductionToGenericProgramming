/**
 * test_topo_sort.cpp
 *
 * DM852 Introduction to Generic Programming
 *
 * Final Project - Spring 2022
 *
 * Dennis Andersen - deand17
 * 2022-06-15
 *
 * Test of topological sorting using the example in
 * Figure 22.7 from CLRS p. 613
 */
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

#include <graph/adjacency_list.hpp>
#include <graph/concepts.hpp>
#include <graph/tags.hpp>
#include <graph/topological_sort.hpp>
#include <graph/traits.hpp>

int main()
{
    using Graph = graph::AdjacencyList<graph::tags::Directed, std::string>;
    static_assert(graph::IncidenceGraph<Graph> && graph::MutableGraph<Graph>);
    auto g{Graph()};

    addVertex(std::move(std::string{"shirt"}), g);         // 0
    addVertex(std::move(std::string{"tie"}), g);         // 1
    addVertex(std::move(std::string{"jacket"}), g);      // 2
    addVertex(std::move(std::string{"belt"}), g);        // 3
    addVertex(std::move(std::string{"watch"}), g);       // 4
    addVertex(std::move(std::string{"pants"}), g);       // 5
    addVertex(std::move(std::string{"undershorts"}), g); // 6
    addVertex(std::move(std::string{"socks"}), g);       // 7
    addVertex(std::move(std::string{"shoes"}), g);       // 8

    addEdge(0, 1, g);
    addEdge(0, 3, g);
    addEdge(1, 2, g);
    addEdge(3, 2, g);
    addEdge(5, 3, g);
    addEdge(5, 8, g);
    addEdge(6, 5, g);
    addEdge(6, 8, g);
    addEdge(7, 8, g);

    std::cout << std::setfill('=') << std::setw(80) << "" << '\n';
    std::cout << "DM852 Introduction to Generic Programming\n";
    std::cout << "Final Project - Spring 2022 - Dennis Andersen - deand17\n\n";
    std::cout << "Test of topological sorting from task 2b\n";
    std::cout << "using Figure 22.7 from CLRS p. 613 as an example\n\n";
    std::cout << "Vertices: " << numVertices(g) << '\n';
    for (auto v : vertices(g)) {
        std::cout << v << ": " << g[v] << "  ";
    }
    std::cout << '\n';

    std::cout << "\nExpected order:\n";
    std::cout << "7: socks  6: undershorts  5: pants  8: shoes  4: watch  0: shirt  3: belt  1: tie  2: jacket\n";

    std::cout << "\nRunning topological search. Result after reversing:\n";
    std::vector<graph::Traits<Graph>::VertexDescriptor> vs;
    vs.reserve(numVertices(g));

    graph::dfs(g, graph::DFSNullVisitor{});

    graph::topoSort(g, std::back_inserter(vs));
    std::reverse(vs.begin(), vs.end());
    for (auto v : vs) {
        std::cout << v << ": " << g[v] << "  ";
    }
    std::cout << '\n';
    std::cout << std::setfill('=') << std::setw(80) << "" << '\n';

    return 0;
}