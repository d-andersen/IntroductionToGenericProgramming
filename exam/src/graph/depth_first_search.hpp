/**
 * depth_first_search.hpp
 *
 * DM852 Introduction to Generic Programming
 *
 * Final Project - Spring 2022
 *
 * Dennis Andersen - deand17
 * 2022-06-15
 *
 * This file was provided but has been changed to implement task 2a.
 */
#ifndef GRAPH_DEPTH_FIRST_SEARCH_HPP
#define GRAPH_DEPTH_FIRST_SEARCH_HPP

#include "traits.hpp"

#include <iostream>
#include <vector>

namespace graph {

struct DFSNullVisitor {
	template<typename G, typename V>
	void initVertex(const V& v, const G& g) { }

	template<typename G, typename V>
	void startVertex(const V& v, const G& g) { }

	template<typename G, typename V>
	void discoverVertex(const V& v, const G& g) { }

	template<typename G, typename V>
	void finishVertex(const V& v, const G& g) { }

	template<typename G, typename E>
	void examineEdge(const E& e, const G& g) { }

	template<typename G, typename E>
	void treeEdge(const E& e, const G& g) { }

	template<typename G, typename E>
	void backEdge(const E& e, const G& g) { }

	template<typename G, typename E>
	void forwardOrCrossEdge(const E& e, const G& g) { }

	template<typename G, typename E>
	void finishEdge(const E& e, const G& g) { }
};

namespace detail {

enum struct DFSColour {
	White, Grey, Black
};

template<typename Graph, typename Visitor>
void dfsVisit(const Graph &g, Visitor visitor, typename Traits<Graph>::VertexDescriptor u,
		      std::vector<DFSColour> &colour)
{
    visitor.discoverVertex(u, g);
    colour[getIndex(u, g)] = DFSColour::Grey;
    auto u_out_edges{outEdges(u, g)};
    for (const auto &e : u_out_edges) {
        auto v{target(e, g)};
        visitor.examineEdge(e, g);
        if (colour[getIndex(v, g)] == DFSColour::White) {
            visitor.treeEdge(e, g);
            dfsVisit(g, visitor, v, colour);
        } else if (colour[getIndex(v, g)] == DFSColour::Grey) {
            visitor.backEdge(e, g);
        } else if (colour[getIndex(v, g)] == DFSColour::Black) {
            visitor.forwardOrCrossEdge(e, g);
        }
        visitor.finishEdge(e, g);
    }
    colour[getIndex(u, g)] = DFSColour::Black;
    visitor.finishVertex(u, g);
}

} // namespace detail

// The following pre-conditions are required:
// - g is a directed acyclic graph
template<typename Graph, typename Visitor>
void dfs(const Graph &g, Visitor visitor)
{
    auto colour{std::vector<detail::DFSColour>(numVertices(g))};
    auto V{vertices(g)};
    for (const auto &u : V) {
        colour[getIndex(u, g)] = detail::DFSColour::White;
        visitor.initVertex(u, g);
    }
    for (const auto &u : V) {
        if (colour[getIndex(u, g)] == detail::DFSColour::White) {
            visitor.startVertex(u, g);
            detail::dfsVisit(g, visitor, u, colour);
        }
    }
}

} // namespace graph

#endif // GRAPH_DEPTH_FIRST_SEARCH_HPP
