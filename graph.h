#ifndef MST
#define MST

#include<iostream>
#include<vector>
#include<array>
#include<tuple>

using namespace std;

#endif


class edge
{
	public:
		int vertex; // vertex endpoint of an edge
		int weight; // edge weight (distance)
		
		edge(int V = 1, int W = 0): vertex(V), weight(W) {}
};

	// encapsulates the info for a particular vertex
class vertexElem
{
	public:
		int vertexID;
		vector<edge> edgeList;
		
		vertexElem( int ID = 0, vector<edge> EL = vector<edge>() ):
					vertexID(ID), edgeList(EL) {}
};

using vertElemItr = vector< vertexElem >::iterator;

using intTup = tuple<int, int, int>;
using vectOfTuples = vector< tuple<int, int, int> >;

class graph
{
	int size; // current graph size (amount of nodes/vertices)
	
		// graph implemented via adjacency list
	vector< vertexElem > vertices;
	
	public:
			// default constructor creates a graph of just one unconnected
			// vertex
		graph(int S = 1)
			{ size = S; vertices = vector< vertexElem >(size); }

			// constuctor overloaded to create graph by specifying size,
			// edge density, and distance range:
			// S = size, density = edge density, maxd = distance range
		graph(int S, double density, int maxd);
		
		graph( vector<int> vrtx );
		
		graph(int vrtx, vectOfTuples EG);
		
		graph(vectOfTuples EG);
		
			// add a vertex to the graph
		//void addVertex() 
			//{ size++; vertices.push_back( vector<edge>() ); }
		
		// delVertex();
			// first remove edges, from the adjacency list
		
			// total vertex count
		int getVertexCount() { return size; }
		
			// total edge count
		int getEdges();
		
			// returns pointer to node if node "n" exists, returns nullptr if 
			// node is nonexistent
		vector< vertexElem >::iterator nodeExist(int n);
		
		bool nodeFound(int x);
		
			// returns true if there's an edge from node x to y
		bool isAdjacent(int x, int y);
		
			// get all vertices connected to x
		vector<int> getNeighbors(int x);
		
			// adds edge between x & y, if one is currently nonexistent
			// returns true if edge was added, if not return false
		bool addEdge(int x, int y, int d = 1);
		
			// if there's an edge between x & y, delete it and return true
			// else return false
		bool deleteEdge(int x, int y);
		
			// get edge weight/distance from x to y,
			// if there is no edge return -1
		int getEdgeValue(int x, int y);
		
			// get the average path length of all the nodes connected to
			// node "n"
		double avePathLength(int n);
};
