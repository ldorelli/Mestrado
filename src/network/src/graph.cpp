#include "graph.hpp"


snet::Graph::Graph() {	
	n_nodes = 0;
}

void snet::Graph::addNode(std::string name) {
	if (nodes.count(name)) {
		throw "Already a node with this name.";
	}
	nodes[name] = n_nodes++;
	adj.push_back(std::vector<int>());
}

void snet::Graph::addNode() {
	adj.push_back(std::vector<int>() );
}