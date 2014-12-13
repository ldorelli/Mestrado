#include <snet.hpp>
#include <iostream>

int main (void) {
	snet::Graph g;
	g.addNode("a");
	g.addNode("b");
	g.addNode("c");

	g.addEdge("a", "b", 10.0);
	g.addEdge("a", "c", 1.0);
	g.addEdge("c", "b", 2.0);
	

	std::cout << g.dijkstra("a", "b") << std::endl;

	return 0;
}