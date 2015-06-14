#include <Network.hpp>
#include <DisjointSet.hpp>
#include <iostream>

using namespace snet;
using namespace std;

int main (void) {
	snet::Network g;
	g.addNode("a");
	g.addNode("b");
	g.addNode("c");

	g.addEdge("a", "b", 10.0);
	g.addEdge("a", "c", 1.0);
	g.addEdge("c", "b", 2.0);
	

	std::cout << g.dijkstra("a", "b") << std::endl;

	DisjointSet d(10);
	d.join(0, 1);
	d.join(1, 2);

	cout << d.find(0) << " " << d.find(1) << endl;
	cout << d.countSet(1) << " " << d.countSet(7) << endl;
	

	return 0;
}