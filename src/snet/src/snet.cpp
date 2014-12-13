#include "snet.hpp"
	
snet::Graph::Graph() {	
	n_nodes = 0;
	inf = 1e9;
}

double snet::Graph::getInf() {
	return inf;
}

void snet::Graph::setInf(double inf) {
	this->inf = inf;
}

void snet::Graph::addNode(std::string name) {
	if (nodes.count(name)) {
		throw "Already a node with this name.";
	}
	nodes[name] = n_nodes++;
	E.push_back(std::vector<int>());
	W.push_back(std::vector<double>());
}

void snet::Graph::addNode() {
	E.push_back(std::vector<int>());
	W.push_back(std::vector<double>());
}

void snet::Graph::validateNode(int s) {
	if (s < 0 or s >= n_nodes) {
		throw "Node index doesn't exist";
	}
}

void snet::Graph::validateNode(std::string s) {
	if (nodes.count(s) == 0) {
		throw "Node " + s + " doesn't exist in the graph.";
	} 
}

void snet::Graph::addEdge(int s, int t, double w) {
	validateNode(s);
	E[s].push_back(t);
	W[s].push_back(t);
}


void snet::Graph::addEdge(std::string s, std::string t, double w) {
	validateNode(s);
	validateNode(t);
 	E[nodes[s]].push_back(nodes[t]);
 	W[nodes[s]].push_back(w);
}

void snet::Graph::loadRAW(std::string filename) {

} 

double snet::Graph::dijkstra(std::string s, std::string t) {
	validateNode(s);
	validateNode(t);
	return dijkstra(nodes[s], nodes[t]);
}	


double snet::Graph::dijkstra(int s, int t) {
	std::vector<double> dist(n_nodes, inf);
	std::priority_queue<std::pair<double, int> > q;
	q.push(std::make_pair(0.0, s));
	dist[s] = 0.0;
	while (!q.empty()) {
		int c = q.top().second;
		double w = -q.top().first;
		q.pop();
		if (dist[c] < w) continue;
		if (c == t) return w;
		
		for (int i = 0; i < E[c].size(); ++i) {
			double ww = W[c][i];
			int nn = E[c][i];
			if (dist[nn] > w + ww) {
				dist[nn] = w + ww;
				q.push(std::make_pair(-w - ww, nn));
			}
		}
	}
	return inf;
}