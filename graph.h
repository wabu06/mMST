#ifndef MST
#define MST

#include<iostream>
#include<vector>
#include<array>
#include<tuple>
#include<map>

using namespace std;

#endif



enum class eCLR {NONE, RED, YLLW, GRN}; // edge color

ostream& operator<<(ostream& out, eCLR c);

class edge
{
	public:
		int vertex; // vertex endpoint of an edge
		int weight; // edge weight (distance)
		eCLR color;
		
		edge(int V = 0, int W = 0, eCLR C = eCLR::GRN):
								vertex(V), weight(W), color(C) {}
};

using intTup = tuple<int, int, int>;
using vectOfTuples = vector< tuple<int, int, int> >;

class graph
{
	int size; // current graph size (amount of nodes/vertices)
	
		// graph implemented via adjacency list
	map< int, vector<edge> > vertices;
	
	unsigned short seeds[3];
	
	void initSeeds();
	
	double prob() { return erand48(seeds); }

		// calculates distance between edges
	int getDistance(int drange) { return nrand48(seeds) % drange + 1; }

	eCLR getColor();
	
	public:
			// default constructor creates a graph of just one unconnected
			// vertex
		graph(int S = 1)
			{ size = S; vertices = map< int, vector<edge> >{ {0, vector<edge>()} }; }

			// constuctor overloaded to create graph by specifying size,
			// edge density, and distance range:
			// S = size, density = edge density, maxd = distance range
		graph(int S, double density, int maxd);
		
		graph( vector<int> vrtx );
		
		graph(int vrtx, vectOfTuples EG);
		
		graph(vectOfTuples EG);
		
			// adds a vertex to the graph, returns true if successful
		bool addVertex(int n); 
		
			// deletes vertex <n> from graph, returns true if successful
		bool delVertex(int n);
		
			// total vertex count
		int getVertexCount() { return size; }
		
			// total edge count
		int getEdges();
		
			// returns true if node "n" exists
		bool nodeExist(int n) { return vertices.count(n) == 1 ? true: false; }
		
			// returns true if there's an edge from node x to y
		bool isAdjacent(int x, int y);
		
			// get all vertices connected to x
		vector<int> getNeighbors(int x);
		
			// adds edge between x & y, if one is currently nonexistent
			// returns true if edge was added, if not return false
		bool addEdge(int x, int y, int d, eCLR c = eCLR::GRN);
		
			// if there's an edge between x & y, delete it and return true
			// else return false
		bool deleteEdge(int x, int y);
		
			// get edge weight/distance from x to y,
			// if there is no edge return -1
		int getEdgeValue(int x, int y);
		
			// get the average path length of all the nodes connected to
			// node "n"
		double avePathLength(int n);
		
		eCLR getEdgeColor(int x, int y);
};
