#include <DisjointSet.hpp>
#include <iostream>

using namespace std;

snet::DisjointSet::DisjointSet(int n) {
	sets = vector<int> (n);
	for (int i = 0; i < sets.size(); ++i) {
		sets[i] = -1;
	}
	nSets = n;
}

void snet::DisjointSet::join(int A, int B) {
	validate(A);
	validate(B);
	int aa = find(A);
	int bb = find(B);
	if (aa != bb) {
		// set aa is bigger than set bb
		if (sets[aa] < sets[bb]) {
			sets[aa] += sets[bb];
			sets[bb] = aa;
		} else {
			sets[bb] += sets[aa];
			sets[aa] = bb;
		}
		nSets--;
	}
}

int snet::DisjointSet::find(int A) {
	validate(A);
	return internalFind(A);
}

int snet::DisjointSet::internalFind(int A) {
	if (sets[A] < 0) return A;
	return sets[A] = find(sets[A]);
}

int snet::DisjointSet::count() {
	return nSets;
}

void snet::DisjointSet::validate(int i) {
	if (i > sets.size() or i < 0) {
		throw "Query element out of range";
	} 
}

int snet::DisjointSet::countSet(int A) {
	validate(A);
	return -sets[A];
}