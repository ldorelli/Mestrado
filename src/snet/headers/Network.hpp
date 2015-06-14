// This is a simple netowork class because I'm sick of all the slow and ugly ass libraries out there
#include <map>
#include <vector>
#include <set>
#include <string>
#include <queue> 
#include <deque>
#include <functional>
#include <Json.hpp>

namespace snet {

/**
 * Simple class that represents a simple edge. Returned by some algorithms.
 * All members are public. For directed edges, the direction is s->t.
 */
class Edge {
public:
	int s;
	int t;
	Edge();
};

/*
 * This class represents a simple network.
 */
class Network {

public:
	/**
	 * 	Empty constructor. Creates an empty network.
	 */
	Network();

	/**
 	 * Returns the size of the network 
	 */ 
	int size ();

	/**
	 *	Sets the number to use as infinity in the algorithms.
	 *	@param The double value that should be treated as infinity.
	 */
	void setInf(double inf);

	/**
	 *	Gets the current infinity value.
	 *  @return The value of infinity.
	 */
	double getInf();

	/**
	 * Checks if parameter is infinity.
	 *	@param val Query parameter.
	 *	@return true if value is infinity with 1e-7 precision.
	 */
	 bool isInf(double val);

	/**
	 * Add a node to the network. This node is named and can be acessed later by its name.  
	 * @param name The name of the node.
	 */
	void addNode(std::string name);

	/**
	 * Tests if a node exists in the network.
	 * @param name The identifier of the node.
	 * @return True if the node with the given name is already in the network.
	 */
	bool hasNode(std::string name);

	/**
	 * Add an unnamed node to the network.
	 */
	void addNode();

	/**
	 *	Adds a directed edge between nodes s and t.
	 *	@param s Source of the edge.
	 *	@param t Endpoint of the edge.
	 *	@param w Weight of the edge.
	 */
	void addEdge(int s, int t, double w = 0.0);

	/**
	 *	Adds a directed edge between nodes s and t. 
	 *	This edge can be acessed later on, and changed.
	 *  Not accepting multigraphs.
	 *	@param s Source of the edge.
	 *	@param t Endpoint of the edge.
	 *	@param w Weight of the edge.
	 */
	void addIEdge (int s, int t, double w = 0.0);

	/**
	 *	Adds a directed edge between named nodes s and t.
	 *	This edge can be acessed later on, and changed.
	 *  Not accepting multigraphs.
	 * 	@param s Name of the source node.
	 *  @param t Name of the endpoint.
	 *	@param w Weight of the edge. 
	 */
	void addIEdge(std::string s, std::string t, double w = 0.0);

	/**
	 *	Adds a directed edge between named nodes s and t.
	 * 	@param s Name of the source node.
	 *  @param t Name of the endpoint.
	 *	@param w Weight of the edge. 
	 */
	void addEdge(std::string s, std::string t, double w = 0.0);

	/**
	 *	Loads a network in RAWnetwork format. Assumes nodes are given 
	 *	with their names.
	 *	@param filepath Path to the RAWnetwork file. 
	 */
	void loadRAW(std::string filepath);

	/**
	 *	Reads a network in RAWnetwork format from stdio 
	 *	with their names.
	 */
	void readRAW();	

	/**
	 *	Calculates the shortest path between nodes s and t.
	 *	@param s Name of the source node.
	 * 	@param t Name of the goal node.
	 * 	@return The shortest path lenght or Inf if not recheable.
	 */
	double dijkstra(std::string s, std::string t);

	/**
	 *	Calculates the shortest path between nodes s and t.
	 *	@param s Index of the source node.
	 * 	@param t Index of the goal node.
	 * 	@return The shortest path lenght or network.INF if not recheable.
	 */	
	double dijkstra(int s, int t);

	/**
	 * 	Implementation of my algorithm to measure attention in a weighted
	 *	network, given an ordered list representing observations (node appeareances).
	 *	Each entry in the list means that a node has received some attention. All entries
	 *	are treated as equal. All entries in the same position are considered to happen at
	 *  the same time. For example, if the observations are [ [0, 1], [3] ], then  
	 *	observations 0 and 1 ocurred simultaneously.
	 *	@param O A vector<vector<int>> containing node observations.
	 *  @param inf Value to be returned case there's no path between two nodes.
	 *	@return Returns the mean attention-distance of the list, that is, the sum of the 
	 *	shortest paths between consecutive observations. If there's no path between two 
	 *	observations, inf value is returned.
	 */
	 double attentionIndex(std::vector<std::vector<int> > O, double inf);


	/**
	 *	Karger min/max cut algorithm. Parallel implementation. 
	 *  
	 */
	template <typename Compare> std::vector<Edge> karger();

	/**
	 * Calculates communities based on a min-cut algorithm. 
	 * @param nIter Number of iterations for the Stoer-Wagner algorithm. Optional.
	 */
	std::vector<int> minCutCommunities();

	/**
	 * Apply a function to the weights of the graph.
	 */
	void changeWeights(std::function<double(double)>);

	/**
	 * Apply a function to the weights of the graph.
	 */
	void changeIWeights(std::function<double(double)>);

	/********************************************************************************************
	 * 										Twitter Module
	 ********************************************************************************************/

	/**
	 * Loads the Hashtags from a Tweet in Json Format into the graph. 
	 * @param json The json string containing a Tweet.
	 */
	 void addHashtags(Json::Value tweet);
	 
	 /**
	  * Loads the user from a Tweet and all the mentions 
	  * @param json The json string cointaining a Tweet.
	  */
	  void loadMentions(Json::Value tweet);

public: 
	// A subset vector, indicating the current set a node belongs to. 
	std::vector<int> subs; 
	// Node names
	std::map<std::string, int> nodes;

	// Special list of edges of the network, indexable
	std::map <int, std::map<int, double> > EE;
	// Edges of the network
	std::deque< std::vector<int> > E;
	// Edge weights of the network
	std::deque< std::vector<double> >	W; 
	// Number of nodes (E.size() should be equal to this)
	int n_nodes; 
	// Infinity
	double inf;

	const double EPS = 1e-7;

	void validateNode(std::string s);
	void validateNode(int s);
};
}
