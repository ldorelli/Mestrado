#include <Network.hpp>
#include <Json.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>

using namespace std;
using namespace snet;

bool proceed = true;

void ignoreHandler(int param){
	proceed = false;
}


void cascade (string filename) {

	ifstream f(filename);

	std::string line;
	Network userNetwork;
	map <string, Network> cascades;

	while (getline(f, line) and proceed) {
		if (line.size() == 0) {
			continue;
		}
		// Reads the input
		Json::Value root;
		Json::Reader reader;
		bool parsing = reader.parse(line, root);
		
		if (!parsing) {
			std::cout << "Failed to parse " <<  reader.getFormattedErrorMessages() << std::endl;
		}  else {
			// Load Mentions
			userNetwork.loadMentions(root, true);
			if (root["entities"] == 0 or root["entities"]["hashtags"] == 0) continue;
			for (auto hashtag : root["entities"]["hashtags"]) {
				string topic = hashtag["text"].asString();
				// Per-topic network-cascade (Hoping this will not cycle)
				cascades[topic].loadMentions(root, false);
			}
		}
	}

	for (auto net : cascades) {
		int sz = net.second.n_nodes;
		int ee = net.second.n_edges;
		if (sz > 50) {
			cout << net.first << " has " <<  sz << " with " << ee << " links " << endl;
			net.second.writeDotFormat("./DOT/" + net.first + ".dot");
		}
	}

	cout << "Users  has " <<  userNetwork.n_nodes << " with " << userNetwork.n_edges << " links " << endl;
	userNetwork.writeDotFormat("./DOT/users.dot");

	// Tie-str
	cout <<  "Tie strenght " << endl;
	userNetwork.topologicalTieStrenght();
	for (int i = 0; i < userNetwork.n_nodes; ++i) {
		for (int j = 0; j < userNetwork.E[i].size(); ++j) {
			cout << userNetwork.tieStrenght[i][j] << " ";
		}
		cout << endl;
	}

}


int main (int argc, char * argv[]) {

	signal (SIGINT, ignoreHandler);

	if (argc < 2) { 
		cerr << "No algorithm asked for. We done boys!:) \n";
		return 0;
	}

	if (string(argv[1]) == "c") { 
		// Cascadade
		if (argc < 3) {
			cerr << "Missing file name\n";
		} else { 
			cascade(string(argv[2]));
		}
	}

	return 0;
}