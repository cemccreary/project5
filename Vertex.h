#ifndef VERTEX_H
#define VERTEX_H

#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <stdio.h>
#include <iostream>

using namespace std;

class Vertex{
public:
	Vertex();
	~Vertex();
	vector <Vertex*> getFollowers();
	vector <Vertex*> getFollowing();
	void addFollow();
	void addFollowing();

	string name;
	vector <Vertex*> following;
	vector <Vertex*> followers;

	//
	Vertex(string str);
	vector<string> getEdges();
	pair<string, string> getEdgeVertices();
	vector<string> vertexStringVector;
};
#endif