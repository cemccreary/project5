#include "DataSource.h"
#include "Edge.h"
#include "Graph.h"
#include "TreeNode.h"
#include "Vertex.h"

#include <iostream>
#include <fstream>
#include <map> 
#include <algorithm> 
#include <iomanip>
#include <set>
#include <stack>
 

using namespace std;

//typedef struct vertex_struct {
//	int vertex;
//	bool visited;
//} vertex;

//// A utility function to add an edge in an 
//// undirected graph. 
//void addEdge(vector<int> adj[], int u, int v)
//{
//	adj[u].push_back(v);
//	adj[v].push_back(u);
//}
//
//// A utility function to do DFS of graph 
//// recursively from a given vertex u. 
//void DFSUtil(int u, vector<int> adj[],
//	vector<bool> &visited)
//{
//	visited[u] = true;
//	cout << u << " ";
//	for (unsigned int i = 0; i<adj[u].size(); i++)
//		if (visited[adj[u][i]] == false)
//			DFSUtil(adj[u][i], adj, visited);
//}
//
//// This function does DFSUtil() for all  
//// unvisited vertices. 
//void DFS(vector<int> adj[], int V)
//{
//	vector<bool> visited(V, false);
//	for (int u = 0; u<V; u++)
//		if (visited[u] == false)
//			DFSUtil(u, adj, visited);
//}

typedef struct NodeStruct_struct {
	string nodeName;
	vector<string> adjNodes;
	float distance;
	NodeStruct_struct* predV;
} NodeStruct;
//Removes duplicates from a vector
vector<string> Uniquelizer(vector<string> UniquilizeThis){
	sort(UniquilizeThis.begin(), UniquilizeThis.end());
	UniquilizeThis.erase(unique(UniquilizeThis.begin(), UniquilizeThis.end()), UniquilizeThis.end());
	return UniquilizeThis;
}

//Finds the vertices that are connected to a string
vector<string> VertexFinder(string start, vector<string> followed, vector<string> follower){
	vector<string> vertexVector;
	for (unsigned int i = 0; i < followed.size(); i++){
		if (followed.at(i) == start){
			vertexVector.push_back(follower.at(i));
		}
		if (follower.at(i) == start){
			vertexVector.push_back(followed.at(i));
		}
	}
	return vertexVector;
}

//NodeStruct* FindVertex(vector<NodeStruct> *nodeStructVector, string start){
//	for (unsigned int i = 0; i < nodeStructVector->size(); i++){
//		if (nodeStructVector->at(i).nodeName == start){
//			return &nodeStructVector->at(i);
//		}
//	}
//	return NULL;
//}

NodeStruct* PopMin(vector<NodeStruct*> *unvisitedQ){
	int j = 0;
	NodeStruct* min = unvisitedQ->at(0);
	for (unsigned int i = 0; i < unvisitedQ->size(); i++){
		if (min->distance > unvisitedQ->at(i)->distance){
			min = unvisitedQ->at(i);
			j = i;
		}
	}
	unvisitedQ->erase(unvisitedQ->begin() + j);
	return min;
}

void ShortestPath(vector<NodeStruct> *nodeStructVector, string start, map<string, NodeStruct*> *TheMap){
	vector<NodeStruct*> unvisitedQ;
	NodeStruct* startV = TheMap->at(start);
	for (unsigned int i = 0; i < nodeStructVector->size(); i++){
		unvisitedQ.push_back(&nodeStructVector->at(i));
	}
	startV->distance = 0;
	NodeStruct* currentV = NULL;
	while (unvisitedQ.size() != 0){
		currentV = PopMin(&unvisitedQ);
		for (unsigned int i = 0; i < currentV->adjNodes.size(); i++){
			float alternativePathDistance = currentV->distance + 1;
			NodeStruct* FastBoy = TheMap->at(currentV->adjNodes.at(i));
			if (alternativePathDistance < FastBoy->distance){
				FastBoy->distance = alternativePathDistance;
				FastBoy->predV = currentV;
			}
		}
	}
}

int main(int argc, char* arg[]){
	ifstream inF(arg[1]);
	if (!inF){
		cout << "Usage: " << endl;
		return EXIT_FAILURE;
	}
	
	string start = arg[2];
	string end = arg[3];
	int startCheck = 0;
	int endCheck = 0;
	string line;
	string tempStringSrc;
	string tempStringDst;
	vector<string> srcStringVector;
	vector<string> dstStringVector;
	vector<int> dupIndexVector;
	vector<NodeStruct> nodeStructVector;
	
	while (getline(inF, line)) {
		string stringSrc;
		string stringDst;
		istringstream ss(line);
		ss >> stringSrc >> stringDst;
		srcStringVector.push_back(stringSrc);
		dstStringVector.push_back(stringDst);
		if (start == stringSrc || start == stringDst){
			startCheck++;
		}
			if (end == stringSrc || end == stringDst){
			endCheck++;
		}
	}
	//Checking for start and end from file exits of non existant
	/*for (unsigned int i = 0; i < srcStringVector.size(); i++){
		if (start == srcStringVector.at(i) || start == dstStringVector.at(i)){
			startCheck++;
		}
		if (end == srcStringVector.at(i) || end == dstStringVector.at(i)){
			endCheck++;
		}
	}*/
	if (startCheck == 0){
		cout << "Error: user " << start << " not found in input file " << arg[1] << "." << endl;
		return 0;
	}
	if (endCheck == 0){
		cout << "Error: user " << end << " not found in input file " << arg[1] << "." << endl;
		return 0;
	}
	//finding the indices of duplicate edges between src and dst vectors
	for (unsigned int i = 0; i < srcStringVector.size(); i++){
		tempStringSrc = srcStringVector.at(i);
		tempStringDst = dstStringVector.at(i);
		for (unsigned int j = i + 1; j < srcStringVector.size(); j++){
			if (tempStringSrc == dstStringVector.at(j) && tempStringDst == srcStringVector.at(j)){
				dupIndexVector.push_back(j);
			}
			else if (tempStringSrc == srcStringVector.at(j) && tempStringDst == dstStringVector.at(j)){
				dupIndexVector.push_back(j);
			}
		}
	}
	//Removing duplicate integers from dupIndexVector
	sort(dupIndexVector.begin(), dupIndexVector.end());
	dupIndexVector.erase(unique(dupIndexVector.begin(), dupIndexVector.end()), dupIndexVector.end());
	//Erasing duplicates from Src and Dst vectors
	for (unsigned int i = 0; i < dupIndexVector.size(); i++){
		srcStringVector.erase(srcStringVector.begin() + dupIndexVector.at(i));
		dstStringVector.erase(dstStringVector.begin() + dupIndexVector.at(i));
		//cout << endl << "DUPLICATE ERASED " << dupIndexVector.at(i);
		for (unsigned int j = 1; j < dupIndexVector.size(); j++){
			dupIndexVector.at(j) = dupIndexVector.at(j) - 1;
		}
	}

	vector<string> SrcDstStringVector;
	for (unsigned int i = 0; i < srcStringVector.size(); i++){
		SrcDstStringVector.push_back(srcStringVector.at(i));
		SrcDstStringVector.push_back(dstStringVector.at(i));
	}

	SrcDstStringVector = Uniquelizer(SrcDstStringVector);
	
	vector<vector<string>> nodesAttached;
	for (unsigned int i = 0; i < SrcDstStringVector.size(); i++){
		nodesAttached.push_back(VertexFinder(SrcDstStringVector.at(i), srcStringVector, dstStringVector));
		nodeStructVector.push_back({ SrcDstStringVector.at(i), nodesAttached.at(i), 1000000, NULL });
	}

	//Algorithms
	map<string, NodeStruct*> TheMap;
	for (unsigned int i = 0; i < nodeStructVector.size(); i++){
		TheMap.emplace(nodeStructVector.at(i).nodeName, &nodeStructVector.at(i));
	}
	ShortestPath(&nodeStructVector, start, &TheMap);
	NodeStruct* LinkedList;
	LinkedList = TheMap.at(end);
	stack<string> stringStack;
	while (LinkedList != NULL){
		stringStack.push(LinkedList->nodeName);
		LinkedList = LinkedList->predV;
	}
	cout << "The Kevin Bacon path between " << start << " and " << end << " is:" << endl; 
	for (unsigned int i = 0; i < stringStack.size(); i++){
		cout << stringStack.top() << endl;
		stringStack.pop();
		i--;
	}

	return 0;
}

	