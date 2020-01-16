#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
// declaration of type to permit returning by pointer
class Graph;

class DataSource {
public:
    // create the source, and open the file, but do
    // not do any processing
	DataSource( ){ }
    DataSource(string filename, string start, string end);
    // Processes the input file, and returns a pointer
    // to the Graph object that was created. whomever calls
    // this function is responsible for deleting the Graph
    // when they are done.
    // If there are errors opening or reading the file, then
    // the result should be NULL
    Graph * buildGraph( );

	
protected:

    ifstream *contents;
};


#endif // DATASOURCE_H

