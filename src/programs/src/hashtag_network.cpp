#include <Network.hpp>
#include <Json.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;
using namespace snet;

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

// 
int main (int argc, char * argv[]) {

	std::cout << "Starting procedure " << endl;
	std::string line;
	// Each line

	//  Graph 
	Network g; 

	while (getline(cin, line)) {
		if (g.nodes.size()%1000 == 0) {
			cout << g.nodes.size() << endl;
			// cout << g.att
		}
		if (line.size() == 0) {
			continue;
		}
		Json::Value root;
		Json::Reader reader;
		bool parsing = reader.parse(line, root);
		if (!parsing) {
			cout << line << endl;
			std::cout << "Failed to parse " <<  reader.getFormattedErrorMessages() << std::endl;
		} else {
			if (root["hashtags"].size() > 1) {
				cout << "Adding hashtags: ";
				for (auto x : root["hashtags"]) {
					cout << x.asString() << " ";
				}
				cout << g.size() << " " << endl;
				cout << endl;
			}
			g.addHashtags(root);
		}
	}

	return 0;

	// printf("%.5lf\n", res/n);

}