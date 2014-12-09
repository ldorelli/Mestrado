// This is a simple graph class because I'm sick of all the slow and ugly ass libraries out there
#include <map>
#include <vector>
#include <set>
#include <string>

namespace snet {

class Graph {
public:
	/*
	 * 	Empty constructor. Creates an empty graph.
	 */
	Graph();

	/*
	 * Add a node to the graph. This node is named and can be acessed later by its name.  
	 * @param name The name of the node.
	 */
	void addNode(std::string name);

	/*
	 * Add an unnamed node to the graph.
	 */
	void addNode();

private:
	std::map<std::string, int> nodes;
	std::vector< std::vector<int> > adj;
	int n_nodes; 
};

}
