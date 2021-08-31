#ifndef MST
#define MST

#include<iostream>
#include<vector>
#include<array>
#include<tuple>

using namespace std;

#endif

#include "graph.h"
#include "priorityQueue.h"



	// minimum spanning tree class
class mst
{
	priorityQueue openSet;
	graph mstGraph;
	vector<nodeEdge> closedSet;
	
		// returns true if given node is in the closed set
	bool nodeInClosedSet(int n);
	
	public:
			// constructor to appropriately initialize an instance of the 
			// minimum spanning tree class
		mst( graph G = graph(),
			priorityQueue OS = priorityQueue(),
			vector<nodeEdge> CS = vector<nodeEdge>() ):
								mstGraph(G), openSet(OS), closedSet(CS) {}
		
			// method to find minimum spanning tree taking a start node as
			// input, algorithm utilized is based on Jarnik-Prim
		vector<nodeEdge> getMinTree(int n = 0);
};
