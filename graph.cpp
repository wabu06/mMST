#include "graph.h"



	// calculates probablity of edges between vertices
inline double prob()
	{ return static_cast<double>( rand() ) / static_cast<double>(RAND_MAX); }
	
	// calculates distance between edges
inline int getDistance(int drange) { return rand() % drange + 1; }

	// constuctor overloaded to create graph by specifying size, edge density,
	// and distance range:
	// S = size, density = edge density, maxd = distance range
graph::graph(int S, double density, int maxd)
{
	srand( time(nullptr) );
	
	size = S;
	
	vertices = vector< vertexElem >(size);
	
	int vID = 1;
	
	for(auto& V: vertices)
	{
		V = vertexElem(vID);
		vID++;
	}
	
	int d; // edge distance
	int i = 0;
	
	for(auto& V: vertices)
	{
		for(int j = i; j < size; j++)
		{
			if (j != i)
			{
				if (prob() < density)
				{
					d = getDistance(maxd);
					
					addEdge(i+1, j+1, d);
				} 
			}
		}

		i++;
	}
}

graph::graph( vector<int> vrtx )
{
	size = 0;
	
	vertices = vector< vertexElem >();
	
	for(auto& V: vrtx)
	{
		vertices.push_back(vertexElem(V));
		size++;
	}
}

graph::graph(int vrtx, vectOfTuples EG)
{
	size = 0;
	
	vertices = vector< vertexElem >();
	
	for(int i = 0; i < vrtx; ++i)
	{
		vertices.push_back( vertexElem(i) );
		++size;
	}
	
	for(auto& e: EG)
		addEdge( get<0>(e), get<1>(e), get<2>(e) );
}

graph::graph(vectOfTuples EG)
{
	size = 0;
	
	vertices = vector< vertexElem >();
	
	for(auto& e: EG)
	{
		if ( !nodeFound( get<0>(e) ) )
		{
			vertices.push_back( vertexElem( get<0>(e) ) );
			++size;
		}
		
		if ( !nodeFound( get<1>(e) ) )
		{
			vertices.push_back( vertexElem( get<1>(e) ) );
			++size;
		}
		
		addEdge( get<0>(e), get<1>(e), get<2>(e) );
	}
	
	//cout << "size: " << size << endl;
}

	// total edge count
int graph::getEdges()
{
	int count = 0;
	
	for(int i = 0; i < size; i++)
	{
		for(auto& E: vertices[i].edgeList)
		{
			if(E.vertex > vertices[i].vertexID)
				count++;
		}
	}
	
	return count;
}

	// returns pointer to node if node "n" exists, returns nullptr if 
	// node is nonexistent
vertElemItr graph::nodeExist(int n)
{
	for(auto itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		if(itr->vertexID == n)
			return itr;
	}
	
	//return vertices.end();
	return static_cast< vertElemItr >(nullptr);
}

bool graph::nodeFound(int x)
{
	vertElemItr xptr = nodeExist(x);
	
	return xptr != static_cast< vertElemItr >(nullptr) ? true: false;
}

	// returns true if there's an edge from node x to y
bool graph::isAdjacent(int x, int y)
{
	vertElemItr xptr = nodeExist(x);
	vertElemItr yptr = nodeExist(y);
	
	bool xfound = xptr != static_cast< vertElemItr >(nullptr) ? true: false;
	bool yfound = yptr != static_cast< vertElemItr >(nullptr) ? true: false;
	
	if ( xfound  && yfound )
	{
		for(auto& E: xptr->edgeList)
		{
			if (E.vertex == y)
				return true;
		}
		
		return false;
	}
	else
		return false;
}

	// get all vertices connected to x
vector<int> graph::getNeighbors(int x)
{
	vertElemItr xptr = nodeExist(x);
	
	bool xfound = xptr != static_cast< vertElemItr >(nullptr) ? true: false;
	
	vector<int> neighbors = vector<int>(0);
	
	if ( xfound )
	{
		for(auto& E: xptr->edgeList)
			neighbors.push_back(E.vertex);
	}
	
	return neighbors;
}

	// adds edge between x & y, if one is currently nonexistent
	// returns true if edge was added, if not return false
bool graph::addEdge(int x, int y, int d)
{
	auto xptr = nodeExist(x);
	auto yptr = nodeExist(y);
	
	bool xfound = xptr != static_cast< vertElemItr >(nullptr) ? true: false;
	bool yfound = yptr != static_cast< vertElemItr >(nullptr) ? true: false;
	
	if ( xfound  && yfound )
	{
		if ( isAdjacent(x, y) && isAdjacent(y, x) )
			return false;
		else
		{
			xptr->edgeList.push_back( edge(y, d) );
			yptr->edgeList.push_back( edge(x, d) );
		
			return true;
		}
	}
	else
		return false;
}

	// if there's an edge between x & y, delete it and return true
	// else return false
bool graph::deleteEdge(int x, int y)
{
	auto xptr = nodeExist(x);
	auto yptr = nodeExist(y);
	
	bool xfound = xptr != static_cast< vertElemItr >(nullptr) ? true: false;
	bool yfound = yptr != static_cast< vertElemItr >(nullptr) ? true: false;
	
	if ( xfound  && yfound )
	{
		if ( isAdjacent(x, y) && isAdjacent(y, x) )
		{
			for (auto itr = xptr->edgeList.begin(); itr != xptr->edgeList.end(); itr++)
			{
				if (itr->vertex == y)
				{
					xptr->edgeList.erase(itr);
					break;
				}
			}
		
			for (auto itr = yptr->edgeList.begin(); itr != yptr->edgeList.end(); itr++)
			{
				if (itr->vertex == x)
				{
					yptr->edgeList.erase(itr);
					break;
				}
			}
		
			return true;
		}
		else
			return false;
	}
	else
		return false;
}


	// get edge weight/distance from x to y, if there is no edge return -1
int graph::getEdgeValue(int x, int y)
{
	auto xptr = nodeExist(x);
	auto yptr = nodeExist(y);
	
	bool xfound = xptr != static_cast< vertElemItr >(nullptr) ? true: false;
	bool yfound = yptr != static_cast< vertElemItr >(nullptr) ? true: false;
	
	if ( xfound  && yfound )
	{
		for(auto& V: xptr->edgeList)
		{
			if (V.vertex == y)
				return V.weight;
		}
		
		return -1;
	}
	else
		return -1;
}


	// get the average path length of all the nodes connected to node "n"
double graph::avePathLength(int n)
{
	double total = 0;
	
	int eSize = 0;
	
	for(auto& V: vertices)
	{
		if (V.vertexID == n)
		{
			eSize = V.edgeList.size();
			
			for(auto& E: V.edgeList)
				total += static_cast<double>(E.weight);
			
			break;
		}
	}
	
	return total / static_cast<double>( eSize );
}
