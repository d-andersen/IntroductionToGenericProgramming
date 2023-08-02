/**
 * topological_sort.hpp
 *
 * DM852 Introduction to Generic Programming
 *
 * Final Project - Spring 2022
 *
 * Dennis Andersen - deand17
 * 2022-06-15
 *
 * This file was provided but has been changed to implement task 2b.
 */
#ifndef GRAPH_TOPOLOGICAL_SORT_HPP
#define GRAPH_TOPOLOGICAL_SORT_HPP

#include "depth_first_search.hpp"

namespace graph {
namespace detail {

template<typename OIter>
struct TopoVisitor : DFSNullVisitor
{
	TopoVisitor(OIter iter) : iter(iter) { }

    template<typename G, typename V>
    void finishVertex(const V& v, const G& g)
    {
        *iter = v;
        ++iter;
    }

private:
	OIter iter;
};

} // namespace detail

template<typename Graph, typename OutputIterator>
void topoSort(const Graph &g, OutputIterator oIter) {
    dfs(g, detail::TopoVisitor<OutputIterator>{oIter});
}

} // namespace graph

#endif // GRAPH_TOPOLOGICAL_SORT_HPP
