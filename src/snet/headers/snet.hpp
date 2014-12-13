// This is a simple graph class because I'm sick of all the slow and ugly ass libraries out there
#include <map>
#include <vector>
#include <set>
#include <string>
#include <queue> 

namespace snet {

class Graph {

public:
	/*
	 * 	Empty constructor. Creates an empty graph.
	 */
	Graph();

	/*
	 *	Sets the number to use as infinity in the algorithms.
	 */
	void setInf(double inf);

	/*
	 *	Gets the current infinity value.
	 */
	double getInf();

	/*
	 * Add a node to the graph. This node is named and can be acessed later by its name.  
	 * @param name The name of the node.
	 */
	void addNode(std::string name);

	/*
	 * Add an unnamed node to the graph.
	 */
	void addNode();

	/*
	 *	Adds a directed edge between nodes s and t.
	 *	@param s Source of the edge.
	 *	@param t Endpoint of the edge.
	 *	@param w Weight of the edge.
	 */
	void addEdge(int s, int t, double w = 0.0);

	/*
	 *	Adds a directed edge between named nodes s and t.
	 * 	@param s Name of the source node.
	 *  @param t Name of the endpoint.
	 *	@param w Weight of the edge. 
	 */
	void addEdge(std::string s, std::string t, double w = 0.0);

	/* 
	 *	Loads a graph in RAWgraph format.
	 *	@param filepath Path to the RAWgraph file. 
	 */
	void loadRAW(std::string filepath);

	/*
	 *	Calculates the shortest path between nodes s and t.
	 *	@param s Name of the source node.
	 * 	@param t Name of the goal node.
	 * 	@return The shortest path lenght or Graph.INF if not recheable.
	 */
	double dijkstra(std::string s, std::string t);

	/*
	 *	Calculates the shortest path between nodes s and t.
	 *	@param s Index of the source node.
	 * 	@param t Index of the goal node.
	 * 	@return The shortest path lenght or Graph.INF if not recheable.
	 */	
	double dijkstra(int s, int t);

private:
	std::map<std::string, int> nodes;
	std::vector< std::vector<int> > E;
	std::vector< std::vector<double> >	W; 
	int n_nodes; 

	double inf;

	void validateNode(std::string s);
	void validateNode(int s);

};
}
