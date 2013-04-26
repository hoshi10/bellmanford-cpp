/*
Bellman-Ford Algorithm (C++ STL)
Copyright (c) 2013 TKT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once
#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <cfloat>
#include <map>
#include <set>
#include <vector>
using namespace std;

// Interface for the node structure which BellmanFordSearch will require.
template <class T> class BellmanFordNode {
public:
	virtual ~BellmanFordNode() {};
	virtual float getCost(T &successor) const = 0; // Returns the cost from this node to the successor node. Used to compute edge weight.
	virtual vector<T> getSuccessors() const = 0; // Returns a list of successors linked to this node
	virtual bool operator<(const T& rhs) const = 0;
};

template <class Node> class BellmanFordSearch {

#if (defined(__cplusplus) && __cplusplus > 199711L) || (defined(_MSC_VER) && _MSC_VER >= 1600)
	static_assert(is_base_of<BellmanFordNode<Node>, Node>::value, "Node must be derived from BellmanFordNode!");
#endif

public: // data

	// A structure to represent a weighted edge in graph.
	// The user provided Node class defines the edge source and destination.
	class Edge	{
	public:
		Node src, dest;
		float weight;
	};

public: // methods

	BellmanFordSearch() : V(0), E(0) {}
	~BellmanFordSearch() {}

	/*
	Initialises the edge structures from a given list of nodes.
	*/
	void initGraph(const vector<Node> &nodes) {
		Edge edge;
		edges.clear();
		dist.clear();

		set<Node> closedNodes;
		for(typename vector<Node>::const_iterator n = nodes.begin(); n != nodes.end(); ++n) {
			const Node &src = *n;
			if(closedNodes.count(src) != 0) continue;
			closedNodes.insert(src);

			vector<Node> successors = src.getSuccessors();
			for(typename vector<Node>::const_iterator s = successors.begin(); s != successors.end(); ++s) {
				edge.src = src;
				edge.dest = *s;
				edge.weight = edge.src.getCost(edge.dest);
				edges.push_back(edge);
			}
		}

		V = closedNodes.size();
		E = edges.size();
	}

	/*
	Finds shortest distances from src to all other vertices using 
	Bellman-Ford algorithm. Requires initGraph to be called beforehand
	to prepare the necessary edge structures.
	
	Returns false if negative weight cycle exists.
	*/
	bool search(Node src) {
		if(edges.empty()) return true;

		// Step 1: Initialize distances from src to all other vertices as INFINITE
		for(typename std::vector<Edge>::const_iterator e = edges.begin(); e != edges.end(); ++e) {
			dist[e->src] = FLT_MAX;
			dist[e->dest] = FLT_MAX;
		}
		dist[src] = 0;

		// Step 2: Relax all edges |V| - 1 times. A simple shortest path from src
		// to any other vertex can have at-most |V| - 1 edges
		for (unsigned int i = 1; i <= V-1; i++) {
			for (unsigned int j = 0; j < E; j++) {
				Node u = edges[j].src;
				Node v = edges[j].dest;
				float weight = edges[j].weight;
				if (dist[u] + weight < dist[v])
					dist[v] = dist[u] + weight;
			}
		}

		// Step 3: check for negative-weight cycles.  The above step guarantees
		// shortest distances if graph doesn't contain negative weight cycle. 
		// If we get a shorter path, then there is a cycle.
		bool negativeCycle = false;
		for (unsigned int i = 0; i < E; i++) {
			Node u = edges[i].src;
			Node v = edges[i].dest;
			float weight = edges[i].weight;
			if (dist[u] + weight < dist[v]) {
				negativeCycle = true;
				break;
			}
		}

		edges.resize(0);
		return !negativeCycle;
	}

	const map<Node, float>& getDistanceMap() {
		return dist;
	}

private: // data
	unsigned int V, E;
	vector<Edge> edges;
	map<Node, float> dist;
};

#endif