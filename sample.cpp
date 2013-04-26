// Sample program to illustrate usage of the Bellman-Ford classes
#include "bellmanford.h"
#include <cfloat>
#include <climits>
#include <cstdio>

// Sample node class that implements BellmanFordNode
class GraphNode : public BellmanFordNode<GraphNode> {
public:
	int id;
	set<GraphNode*> neighbours;
	map<int, float> weights;

	GraphNode() : id(INT_MAX) {}
	GraphNode(int ID) : id(ID) {}

	float getCost(GraphNode &successor) const {
		map<int, float>::const_iterator i = weights.find(successor.id);
		if(i != weights.end()) {
			return i->second;
		} else return FLT_MAX;
	}

	vector<GraphNode> getSuccessors() const {
		vector<GraphNode> successors(neighbours.size());
		unsigned int i = 0;
		for(set<GraphNode*>::const_iterator n = neighbours.begin(); n != neighbours.end(); ++n, ++i)
			successors[i] = (*(*n));
		return successors;
	}

	bool operator<(const GraphNode& rhs) const { return id < rhs.id; }
};

// A utility function used to print the solution
template <typename Node>
void printTable(const map<Node, float> &dist) {
	printf("Vertex   Distance from Source\n");

	unsigned int i = 0;
	for (typename map<Node, float>::const_iterator d = dist.begin(); d != dist.end(); ++d, ++i)
		printf("%d \t\t %f\n", d->first.id, d->second);
}

int main1(int argc, char *argv[]) {
	BellmanFordSearch<GraphNode> bellmanfordsearch;
	
	vector<GraphNode*> nodePtrs(5);
	for(int i = 0; i < 5; i++) {
		nodePtrs[i] = new GraphNode(i);
	}
	nodePtrs[0]->neighbours.insert(nodePtrs[1]); nodePtrs[0]->weights[nodePtrs[1]->id] = -1;
	nodePtrs[0]->neighbours.insert(nodePtrs[2]); nodePtrs[0]->weights[nodePtrs[2]->id] = 4;
	nodePtrs[1]->neighbours.insert(nodePtrs[2]); nodePtrs[1]->weights[nodePtrs[2]->id] = 3;
	nodePtrs[1]->neighbours.insert(nodePtrs[3]); nodePtrs[1]->weights[nodePtrs[3]->id] = 2;
	nodePtrs[1]->neighbours.insert(nodePtrs[4]); nodePtrs[1]->weights[nodePtrs[4]->id] = 2;
	nodePtrs[3]->neighbours.insert(nodePtrs[1]); nodePtrs[3]->weights[nodePtrs[1]->id] = 1;
	nodePtrs[3]->neighbours.insert(nodePtrs[2]); nodePtrs[3]->weights[nodePtrs[2]->id] = 5;
	nodePtrs[4]->neighbours.insert(nodePtrs[3]); nodePtrs[4]->weights[nodePtrs[3]->id] = -3;

	vector<GraphNode> nodes(5);
	for(int i = 0; i < 5; i++) {
		nodes[i] = *nodePtrs[i];
	}

	bellmanfordsearch.initGraph(nodes);
	bool result = bellmanfordsearch.search(nodes[0]);
	if(result)
		printTable(bellmanfordsearch.getDistanceMap());
	else
		printf("Graph contains negative weight cycle\n");

	for(int i = 0; i < 5; i++)
		delete nodePtrs[i];
	nodePtrs.clear();

	return 0;
}
