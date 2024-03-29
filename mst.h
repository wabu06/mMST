#ifndef MST
#define MST

#include<iostream>
#include<vector>
#include<array>
#include<tuple>
#include<map>

using namespace std;

#endif

#include "graph.h"
#include "priorityQueue.h"



	// minimum spanning tree class
class mst
{
	priorityQueue openSet;
	graph mstGraph;
	map<int, nodeEdge> closedSet;
	
		// color map to determine whether or not and edge is used in the
		// shortest path calculation
	map<eCLR, bool> cMap;
		
	public:
			// constructor to appropriately initialize an instance of the 
			// minimum spanning tree class
		mst( graph G = graph(), priorityQueue OS = priorityQueue(),
			map<int, nodeEdge> CS = map<int, nodeEdge>{},
			map<eCLR, bool> M = map<eCLR, bool> { {eCLR::RED, false},
												{eCLR::YLLW, false},
												{eCLR::GRN, false} }
			): mstGraph(G), openSet(OS), closedSet(CS), cMap(M) {}

		
			// method to find minimum spanning tree taking a start node as
			// input, algorithm utilized is based on Jarnik-Prim
		map<int, nodeEdge> getMinTree(int n = 0);
		
		void setColor(eCLR C, bool B) { cMap[C] = B; }
		bool getColor(eCLR C) { return cMap[C]; }
};
