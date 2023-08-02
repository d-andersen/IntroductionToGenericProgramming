/**
 * adjacency_list.hpp
 *
 * DM852 Introduction to Generic Programming
 *
 * Final Project - Spring 2022
 *
 * Dennis Andersen - deand17
 * 2022-06-15
 *
 * This file was provided but has been changed to implement task 1.
 */
#ifndef GRAPH_ADJACENCY_LIST_HPP
#define GRAPH_ADJACENCY_LIST_HPP

#include "tags.hpp"
#include "traits.hpp"
#include "properties.hpp"

#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <algorithm>
#include <cassert>
#include <list>
#include <type_traits>
#include <vector>

#include <iostream>

namespace graph {

template<typename DirectedCategoryT,
         typename VertexPropT = NoProp,
         typename EdgePropT = NoProp>
requires std::derived_from<DirectedCategoryT, tags::Undirected> ||
         std::derived_from<DirectedCategoryT, tags::Directed>
struct AdjacencyList
{
private:
	struct OutEdge
    {
        std::size_t tar;
	};

    struct InEdge
    {
        std::size_t src;
    };

	using OutEdgeList = std::vector<OutEdge>;
    using InEdgeList = std::vector<InEdge>;

    // primary template of partial specialization
    // https://en.cppreference.com/w/cpp/language/partial_specialization
    //
    template <typename DirectedCategoryT1, typename VertexPropT1, typename Dummy = void>
	struct StoredVertexSimple
    {
        StoredVertexSimple() = default;

        explicit
        StoredVertexSimple(VertexPropT1 &&vp) : prop(std::move(vp)) { }

		OutEdgeList eOut;
        VertexPropT1 prop;
	};

    // partial specialization
    template <typename Dummy>
    struct StoredVertexSimple<tags::Directed, NoProp, Dummy>
    {
        OutEdgeList eOut;
    };

    // partial specialization
    template <typename Dummy>
    struct StoredVertexSimple<tags::Bidirectional, NoProp, Dummy>
    {
        OutEdgeList eOut;
        InEdgeList eIn;
    };

    // partial specialization
    template <typename VertexPropT1, typename Dummy>
    struct StoredVertexSimple<tags::Bidirectional, VertexPropT1, Dummy>
    {
        StoredVertexSimple() = default;

        explicit
        StoredVertexSimple(VertexPropT1 &&vp) : prop(std::move(vp)) { }

        OutEdgeList eOut;
        InEdgeList eIn;
        VertexPropT1 prop;
    };

	using StoredVertex = StoredVertexSimple<DirectedCategoryT, VertexPropT>;

    // primary template of partial specialization
    template <typename EdgePropT1, typename Dummy = void>
	struct StoredEdgeSimple
    {
        StoredEdgeSimple(std::size_t src, std::size_t tar) : src(src), tar(tar) { }

        StoredEdgeSimple(std::size_t src, std::size_t tar, EdgePropT1 &&ep)
            : src(src), tar(tar), prop(std::move(ep)) { }

		std::size_t src, tar;
        EdgePropT1 prop;
	};

    // partial specialization
    template <typename Dummy>
    struct StoredEdgeSimple<NoProp, Dummy>
    {
        StoredEdgeSimple(std::size_t src, std::size_t tar) : src(src), tar(tar) { }

        std::size_t src, tar;
    };

    using StoredEdge = StoredEdgeSimple<EdgePropT>;

	using VList = std::vector<StoredVertex>;
	using EList = std::vector<StoredEdge>;

public: // Graph
	using DirectedCategory = DirectedCategoryT;
	using VertexDescriptor = std::size_t;

	struct EdgeDescriptor
    {
		EdgeDescriptor() = default;
		EdgeDescriptor(std::size_t src, std::size_t tar,
		               std::size_t storedEdgeIdx)
			: src(src), tar(tar), storedEdgeIdx(storedEdgeIdx) {}

	public:
		std::size_t src, tar;
		std::size_t storedEdgeIdx;

	public:
		friend bool operator==(const EdgeDescriptor &a,
		                       const EdgeDescriptor &b)
        {
			return a.storedEdgeIdx == b.storedEdgeIdx;
		}
	};

public: // PropertyGraph
	using VertexProp = VertexPropT;
	using EdgeProp = EdgePropT;

public: // VertexListGraph
	struct VertexRange
    {
		// the iterator is simply a counter that returns its value when
		// dereferenced
		using iterator = boost::counting_iterator<VertexDescriptor>;

	public:
		VertexRange(std::size_t n) : n(n) {}
		iterator begin() const { return iterator(0); }
		iterator end()   const { return iterator(n); }

	private:
		std::size_t n;
	};

public: // EdgeListGraph
	struct EdgeRange
    {
		// We want to adapt the edge list,
		// so it dereferences to EdgeDescriptor instead of StoredEdge
		using EListIterator = typename EList::const_iterator;

		struct iterator : boost::iterator_adaptor<
				iterator, // because we use CRTP (Derived arg)
				EListIterator, // the iterator we adapt (Base arg)
				// we want to convert the StoredEdge into an EdgeDescriptor:
				EdgeDescriptor, // (Value arg)
				// we can use RA as the underlying iterator supports it:
				std::random_access_iterator_tag, // (Category arg)
				// when we dereference we return by value, not by reference
				EdgeDescriptor> // (Reference arg)
        {
			using Base = boost::iterator_adaptor<
				iterator, EListIterator, EdgeDescriptor,
				std::random_access_iterator_tag, EdgeDescriptor>;
		public:
			iterator() = default;
			iterator(EListIterator i, EListIterator first) : Base(i), first(first) {}

		private:
			// let the Boost machinery use our methods:
			friend class boost::iterator_core_access;

			EdgeDescriptor dereference() const
            {
				// get our current position stored in the
				// boost::iterator_adaptor base class
				const EListIterator &i = this->base_reference();
				return EdgeDescriptor{i->src, i->tar,
					static_cast<std::size_t>(i - first)};
			}

		private:
			EListIterator first;
		};

	public:
		EdgeRange(const AdjacencyList &g) : g(&g) {}

		iterator begin() const
        {
			return iterator(g->eList.begin(), g->eList.begin());
		}

		iterator end() const
        {
			return iterator(g->eList.end(), g->eList.begin());
		}

	private:
		const AdjacencyList *g;
	};

public: // IncidenceGraph
    struct OutEdgeRange
    {
        // We want to adapt the edge list,
        // so it dereferences to EdgeDescriptor instead of StoredEdge
        using OutEdgeListIterator = typename OutEdgeList::const_iterator;

        struct iterator : boost::iterator_adaptor<
                iterator, // because we use CRTP (Derived arg)
                OutEdgeListIterator, // the iterator we adapt (Base arg)
                // we want to convert the StoredEdge into an EdgeDescriptor:
                EdgeDescriptor, // (Value arg)
                // we can use RA as the underlying iterator supports it:
                std::random_access_iterator_tag, // (Category arg)
                // when we dereference we return by value, not by reference
                EdgeDescriptor> // (Reference arg)
        {
            using Base = boost::iterator_adaptor<
                    iterator, OutEdgeListIterator, EdgeDescriptor,
                    std::random_access_iterator_tag, EdgeDescriptor>;
        public:
            iterator() = default;
            iterator(OutEdgeListIterator i, OutEdgeListIterator first, VertexDescriptor src)
                : Base(i), first(first), src(src) { }

        private:
            // let the Boost machinery use our methods:
            friend class boost::iterator_core_access;

            EdgeDescriptor dereference() const
            {
                // get our current position stored in the
                // boost::iterator_adaptor base class
                const OutEdgeListIterator &i = this->base_reference();
                return EdgeDescriptor{src, i->tar,
                                      static_cast<std::size_t>(i - first)};
            }

        private:
            OutEdgeListIterator first;
            std::size_t src;
        };

    public:
        OutEdgeRange(VertexDescriptor v, const AdjacencyList &g) : src(v), g(&g) { }

        iterator begin() const
        {
            return iterator(g->vList[src].eOut.begin(), g->vList[src].eOut.begin(), src);
        }

        iterator end() const
        {
            return iterator(g->vList[src].eOut.end(), g->vList[src].eOut.begin(), src);
        }

    private:
        std::size_t src;
        const AdjacencyList *g;
    };

public: // BidirectionalGraph
    struct InEdgeRange
    {
        // We want to adapt the edge list,
        // so it dereferences to EdgeDescriptor instead of StoredEdge
        using InEdgeListIterator = typename InEdgeList::const_iterator;

        struct iterator : boost::iterator_adaptor<
                iterator, // because we use CRTP (Derived arg)
                InEdgeListIterator, // the iterator we adapt (Base arg)
                // we want to convert the StoredEdge into an EdgeDescriptor:
                EdgeDescriptor, // (Value arg)
                // we can use RA as the underlying iterator supports it:
                std::random_access_iterator_tag, // (Category arg)
                // when we dereference we return by value, not by reference
                EdgeDescriptor> // (Reference arg)
        {
            using Base = boost::iterator_adaptor<
                    iterator, InEdgeListIterator, EdgeDescriptor,
                    std::random_access_iterator_tag, EdgeDescriptor>;
        public:
            iterator() = default;
            iterator(InEdgeListIterator i, InEdgeListIterator first, VertexDescriptor tar)
                : Base(i), first(first), tar(tar) { }

        private:
            // let the Boost machinery use our methods:
            friend class boost::iterator_core_access;

            EdgeDescriptor dereference() const
            {
                // get our current position stored in the
                // boost::iterator_adaptor base class
                const InEdgeListIterator &i = this->base_reference();
                return EdgeDescriptor{i->src, tar,
                                      static_cast<std::size_t>(i - first)};
            }

        private:
            InEdgeListIterator first;
            std::size_t tar;
        };

    public:
        InEdgeRange(VertexDescriptor v, const AdjacencyList &g) : tar(v), g(&g) { }

        iterator begin() const
        {
            return iterator(g->vList[tar].eIn.begin(), g->vList[tar].eIn.begin(), tar);
        }

        iterator end() const
        {
            return iterator(g->vList[tar].eIn.end(), g->vList[tar].eIn.begin(), tar);
        }

    private:
        std::size_t tar;
        const AdjacencyList *g;
    };

public:
	AdjacencyList() = default;
	AdjacencyList(std::size_t n) : vList(n) {}

private:
	VList vList;
	EList eList;

public: // Graph
	friend VertexDescriptor source(EdgeDescriptor e, const AdjacencyList &g)
    {
		return e.src;
	}

	friend VertexDescriptor target(EdgeDescriptor e, const AdjacencyList &g)
    {
		return e.tar;
	}

public: // VertexListGraph
	friend std::size_t numVertices(const AdjacencyList &g)
    {
		return g.vList.size();
	}

	friend VertexRange vertices(const AdjacencyList &g)
    {
		return VertexRange(numVertices(g));
	}

public: // EdgeListGraph
	friend std::size_t numEdges(const AdjacencyList &g)
    {
		return g.eList.size();
	}

	friend EdgeRange edges(const AdjacencyList &g)
    {
		return EdgeRange(g);
	}

public: // Other
	friend std::size_t getIndex(VertexDescriptor v, const AdjacencyList &g)
    {
		return v;
	}

public: // IncidenceGraph
    friend OutEdgeRange outEdges(VertexDescriptor v, const AdjacencyList &g)
    {
        return OutEdgeRange(v, g);
    }

    friend std::size_t outDegree(VertexDescriptor v, const AdjacencyList &g)
    {
        return g.vList[v].eOut.size();
    }

public: // BidirectionalGraph
    friend InEdgeRange inEdges(VertexDescriptor v, const AdjacencyList &g)
    requires std::same_as<DirectedCategory, tags::Bidirectional>
    {
        return InEdgeRange(v, g);
    }

    friend std::size_t inDegree(VertexDescriptor v, const AdjacencyList &g)
    requires std::same_as<DirectedCategory, tags::Bidirectional>
    {
        return g.vList[v].eIn.size();
    }

public: // MutableGraph
    friend std::size_t addVertex(AdjacencyList &g)
    requires std::default_initializable<VertexProp>
    {
        g.vList.push_back(StoredVertex{});
        return g.vList.size() - 1;
    }

private:
    friend EdgeDescriptor addEdgeImpl(VertexDescriptor u, VertexDescriptor v,
                                      AdjacencyList &g, tags::Directed)
    {
        g.vList[u].eOut.push_back(OutEdge{v});
        g.eList.push_back(StoredEdge{u, v});
        return EdgeDescriptor{u, v, g.eList.size() - 1};
    }

private:
    friend EdgeDescriptor addEdgeImpl(VertexDescriptor u, VertexDescriptor v,
                                      AdjacencyList &g, tags::Bidirectional)
    {
        g.vList[u].eOut.push_back(OutEdge{v});
        g.vList[v].eIn.push_back(InEdge{u});
        g.eList.push_back(StoredEdge{u, v});
        return EdgeDescriptor{u, v, g.eList.size() - 1};
    }

public:
    // Adds an edge to g between vertices u (src) and v (tar).
    // The following pre-conditions are required:
    // - Both u and v are valid vertex descriptors for g
    // - u and v are different
    // - No edge (u, v) exist already in g
    friend EdgeDescriptor addEdge(VertexDescriptor u, VertexDescriptor v,
                                  AdjacencyList &g)
    requires std::default_initializable<EdgeProp>
    {
        return addEdgeImpl(u, v, g, DirectedCategory{});
    }

public: // MutablePropertyGraph
    friend std::size_t addVertex(VertexProp &&vp, AdjacencyList &g)
    requires std::movable<VertexProp>
    {
        g.vList.push_back(StoredVertex{std::move(vp)});
        return g.vList.size() - 1;
    }

private:
    friend EdgeDescriptor addEdgeImpl(VertexDescriptor u, VertexDescriptor v,
                                      EdgeProp &&ep, AdjacencyList &g, tags::Directed)
    {
        g.vList[u].eOut.push_back(OutEdge{v});
        g.eList.push_back(StoredEdge{u, v, std::move(ep)});
        return EdgeDescriptor{u, v, g.eList.size() - 1};
    }

private:
    friend EdgeDescriptor addEdgeImpl(VertexDescriptor u, VertexDescriptor v,
                                      EdgeProp &&ep, AdjacencyList &g, tags::Bidirectional)
    {
        g.vList[u].eOut.push_back(OutEdge{v});
        g.vList[v].eIn.push_back(InEdge{u});
        g.eList.push_back(StoredEdge{u, v, std::move(ep)});
        return EdgeDescriptor{u, v, g.eList.size() - 1};
    }

public:
    // Adds an edge to g between vertices u (src) and v (tar).
    // The following pre-conditions are required:
    // - Both u and v are valid vertex descriptors for g
    // - u and v are different
    // - No edge (u, v) exist already in g
    friend EdgeDescriptor addEdge(VertexDescriptor u, VertexDescriptor v,
                                  EdgeProp &&ep, AdjacencyList &g)
    requires std::movable<EdgeProp>
    {
        return addEdgeImpl(u, v, std::move(ep), g, DirectedCategory{});
    }

public: // PropertyGraph
    // Returns a reference to the property of the stored vertex with the index given
    // by idx. No bounds checking is performed.
    // The following pre-conditions are required:
    // - vd is a valid vertex descriptor for g
    VertexProp &operator[] (VertexDescriptor vd)
    {
        return vList[vd].prop;
    }

public:
    // Returns a reference to the property of the stored vertex with the index given
    // by idx. No bounds checking is performed.
    // The following pre-conditions are required:
    // - vd is a valid vertex descriptor for g
    const VertexProp &operator[] (VertexDescriptor vd) const
    {
        return vList[vd].prop;
    }

public:
    // Returns a reference to the property of the stored edge with the index given
    // by idx. No bounds checking is performed.
    // The following pre-conditions are required:
    // - ed is a valid edge descriptor for g
    EdgeProp &operator[] (EdgeDescriptor ed)
    {
        return eList[ed.storedEdgeIdx].prop;
    }

public:
    // Returns a reference to the property of the stored edge with the index given
    // by idx. No bounds checking is performed.
    // The following pre-conditions are required:
    // - ed is a valid edge descriptor for g
    const EdgeProp &operator[] (EdgeDescriptor ed) const
    {
        return eList[ed.storedEdgeIdx].prop;
    }
};

} // namespace graph

#endif // GRAPH_ADJACENCY_LIST_HPP
