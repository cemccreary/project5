#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <string>
using namespace std;

class Node {
public: 
	string name;
	vector<Node *> children;

	Node(string name){ this->name = name; } 

	vector<string> depthFirstSearch(vector<string> *array) {
		array->push_back(this->name);
		for (unsigned int i = 0; i < this->children.size(); i++){
			cout << i << " " << children[i]->name << endl;
			children[i]->depthFirstSearch(array);
		}
		return *array;
	}

	Node *addChild(string name){
		Node *child = new Node(name);
		children.push_back(child);
		return this;
	}
};
#endif