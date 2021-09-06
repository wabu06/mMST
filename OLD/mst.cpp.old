#include "mst.h"


	// returns true if given node is in the closed set
bool mst::nodeInClosedSet(int n)
{
	for(auto& V: closedSet)
	{
		if (V.node == n)
			return true;
	}
	
	return false;
}

	// method to find minimum spanning tree, taking a start node as input
	// algorithm utilized is  based on Jarnik-Prim
vector<nodeEdge> mst::getMinTree(int n)
{
		// initialize open and closed sets, to empty
	openSet.emptyPQ();
	closedSet.clear();
	
	openSet.insert( nodeEdge(n) ); // place start node in open set
	
	nodeEdge ce; // current edge being examined
	
	vector<int> nodeNeighbors;
	
	int ev; // edge value between a node and a neighbor
	
	int idx; // index of a nodeEdge
	
	vector<nodeEdge> neV;
	
	while( openSet.notEmpty() )
	{
		ce = openSet.getMin();
		closedSet.push_back(ce);
		
		nodeNeighbors = mstGraph.getNeighbors( ce.node );
		
			// if a node has no neighbors then a minimum spanning tree cannot
			// be found
		if (nodeNeighbors.size() == 0)
			return vector<nodeEdge>{ nodeEdge(-1, array<int, 2>{-1, -1}, -1) };
		
		for(auto& N: nodeNeighbors)
		{
			if( cMap[ mstGraph.getEdgeColor(ce.node, N) ] )
				continue;
			
			if( nodeInClosedSet(N) )
				continue;
			
			ev = mstGraph.getEdgeValue(ce.node, N);
			
			idx = openSet.contains(N);
			
				// if edge is not already in open set, add it to open set, if
				// edge is in open set, update it if the newly found edge value
				// is lower
			if (idx < 0)
				openSet.insert( nodeEdge(N, array<int, 2>{ce.node, N}, ev) );
			else
			{
				neV = openSet.getQueContents();
				
				if (ev < neV[idx].cost)
				{
					openSet.decreaseKey(idx, ev);
					
						// need to find new index, after decreasing the PQ key
						// the keys in question are the edge cost
					idx = openSet.contains(N);
					
					openSet.modVal(idx, nodeEdge(N, array<int, 2>{ce.node, N}, ev) );
				}
			}
		}
	}
		// checks to see if a minimum spanning tree could be found, a valid 
		// minimum spanning tree is found if the node count in the closed set
		// matches the node count of the graph, so if a valid minimum spanning
		// tree is found return it, if not return some representation
		// indicating that one was not found
	if( mstGraph.getVertexCount() == closedSet.size() )
	{
		auto itr = closedSet.begin(); closedSet.erase(itr);
		return closedSet;
	}
	else
		return vector<nodeEdge>{ nodeEdge(-1, array<int, 2>{-1, -1}, -1) };
}
