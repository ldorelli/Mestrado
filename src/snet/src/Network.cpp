#include <Network.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdlib>

snet::Network::Network() {	
	n_nodes = 0;
	inf = 1e9;
}

int snet::Network::size () {
	return nodes.size();
}

double snet::Network::getInf() {
	return inf;
}

void snet::Network::setInf(double inf) {
	this->inf = inf;
}

void snet::Network::addNode(std::string name) {
	if (nodes.count(name)) {
		return;
	}
	nodes[name] = n_nodes++;
	E.push_back(std::vector<int>());
	W.push_back(std::vector<double>());
}

void snet::Network::addNode() {
	E.push_back(std::vector<int>());
	W.push_back(std::vector<double>());
}

bool snet::Network::hasNode(std::string node) {
	return nodes.count(node) > 0;
}

void snet::Network::validateNode(int s) {
	if (s < 0 or s >= n_nodes) {
		throw "Node index doesn't exist";
	}
}

void snet::Network::validateNode(std::string s) {
	if (nodes.count(s) == 0) {
		throw "Node " + s + " doesn't exist in the network.";
	} 
}

void snet::Network::addIEdge(int s, int t, double w) {
	validateNode(s);
	EE[s][t] += w;
}

void snet::Network::addEdge(int s, int t, double w) {
	validateNode(s);
	E[s].push_back(t);
	W[s].push_back(t);
}


void snet::Network::addEdge(std::string s, std::string t, double w) {
	validateNode(s);
	validateNode(t);
	addEdge(nodes[s], nodes[t], w);
}

void snet::Network::addIEdge(std::string s, std::string t, double w) {
	validateNode(s);
	validateNode(t);
	addIEdge(nodes[s], nodes[t], w);
}

void snet::Network::loadRAW(std::string filename) {
	int n, m;

	std::ifstream f(filename.c_str(), std::ios::in);
	f >> n >> m;
	
	for (int i = 0; i < n; ++i) {
		std::string s;
		f >> s;
		this->addNode(s);
	}
	for (int i = 0; i < m; ++i) {
		std::string a, b;
		double w;
		f >> a >> b >> w;
		this->addEdge(a, b, w);
	}
} 

void snet::Network::readRAW() {
	int n, m;

	std::cin >> n >> m;
	
	for (int i = 0; i < n; ++i) {
		std::string s;
		std::cin >> s;
		this->addNode(s);
	}
	for (int i = 0; i < m; ++i) {
		std::string a, b;
		double w;
		std::cin >> a >> b >> w;
		this->addEdge(a, b, w);
	}
} 

double snet::Network::dijkstra(std::string s, std::string t) {
	validateNode(s);
	validateNode(t);
	return dijkstra(nodes[s], nodes[t]);
}	


double snet::Network::dijkstra(int s, int t) {
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

bool snet::Network::isInf(double val) {
	return fabs(val - inf) < EPS;
}


double snet::Network::attentionIndex(std::vector<std::vector<int> > O, double inf) {


	changeWeights( [=] (double w) -> double {
			if (fabs(w) < EPS) {
				throw "Weight 0";
			}
			return 1/w;
		});

	double res = 0.0;
	int tot = 0;
	for (int i = 0; i < O.size(); ++i) {
		for (int j = i + 1; j < O.size(); ++j) {
			for (int k = 0; k < O[i].size(); ++k) {
				for (int l = 0; l < O[j].size(); ++l) {
					tot += 1;
					double d = dijkstra(O[i][k], O[j][l]);
					if (isInf(d)) d = inf;
					res += d;
				}
			}
		}
	}

	if (tot == 0) return 0.0;
	return res/tot; 	
}

 
void snet::Network::changeIWeights(std::function<double(double)> transform) {
	for (auto edgeList : EE) {
		for (auto& pair : edgeList.second) {
			pair.second = transform(pair.second);
		}
	}
}

void snet::Network::changeWeights(std::function<double(double)> transform) {
	for (auto weightList : W) {
		for (auto weight : weightList)
			weight = transform(weight);
	}
}

void snet::Network::addHashtags(Json::Value root) {
	std::vector <std::string> tags; 
	for (auto hashtag : root["hashtags"]) {
		tags.push_back(hashtag.asString());
		addNode(tags.back()); 
	}
	for (int i = 0; i < tags.size(); ++i) {
		for (int j = i + 1; j < tags.size(); ++j) {
			addIEdge(tags[i], tags[j], 1);
		}
	}
}