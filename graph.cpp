#include "graph.h"


void graph::initSeeds()
{
	seeds[0] = time(nullptr);
	seeds[1] = 2 * seeds[0];
	seeds[2] = 3 * seeds[1];
}

eCLR graph::getColor()
{
	int c = nrand48(seeds) % 3;
	
	switch(c)
	{
		case 0:
			return eCLR::RED;
		case 1:
			return eCLR::YLLW;
		case 2:
			return eCLR::GRN;
		default:
			return eCLR::GRN;
	}
}

ostream& operator<<(ostream& out, eCLR c)
{
	switch(c)
	{
		case eCLR::RED:
			out << "RED";
			break;
		case eCLR::YLLW:
			out << "YELLOW";
			break;
		case eCLR::GRN:
			out << "GREEN";
			break;
		default:
			out << "NONE";
	}
	
	return out;
}

	// constuctor overloaded to create graph by specifying size, edge density,
	// and distance range:
	// S = size, density = edge density, maxd = distance range
graph::graph(int S, double density, int maxd)
{
	initSeeds();
	
	size = S;
	
	for(int vID = 0; vID < size; ++vID)
		vertices[vID] = vector<edge>();
	
	int d; // edge distance
	int i = 0;
	
	eCLR c;
	
	for(auto& V: vertices)
	{
		for(int j = i; j < size; j++)
		{
			if (j != i)
			{
				if (prob() < density)
				{
					d = getDistance(maxd);
					c = getColor();
					
					//V.second.push_back( edge(j, d, c) );
					//vertices[j].push_back( edge(i, d, c) );
					
					addEdge(i, j, d, c);
				}
			}
		}

		i++;
	}
}

graph::graph( vector<int> vrtx )
{
	size = 0;
	
	vertices = map< int, vector<edge> >{};
	
	for(auto& V: vrtx)
	{
		vertices[V] = vector<edge>();
		size++;
	}
}

graph::graph(int vrtx, vectOfTuples EG)
{
	initSeeds();
	
	size = 0;
	
	vertices = map< int, vector<edge> >{};
	
	for(int i = 0; i < vrtx; ++i)
	{
		vertices[i] = vector<edge>();
		++size;
	}
	
	for(auto& e: EG)
		addEdge( get<0>(e), get<1>(e), get<2>(e), getColor() );
}

graph::graph(vectOfTuples EG)
{
	initSeeds();
	
	size = 0;
	
	vertices = map< int, vector<edge> >{};
	
	for(auto& e: EG)
	{
		if ( !nodeExist( get<0>(e) ) )
		{
			vertices[ get<0>(e) ] = vector<edge>();
			++size;
		}
		
		if ( !nodeExist( get<1>(e) ) )
		{
			vertices[ get<1>(e) ] = vector<edge>();
			++size;
		}
		
		addEdge( get<0>(e), get<1>(e), get<2>(e), getColor() );
	}
	
	//cout << "size: " << size << endl;
}

	// add a vertex/node to graph
bool graph::addVertex(int n) 
{ 
	if( nodeExist(n) )
		return false;
	else
	{
		vertices[n] = vector<edge>(); size++; 
		return true;
	}
}

	// deletes a vertex/node from graph
bool graph::delVertex(int n)
{
	vector<edge>::iterator V;
	
	if( nodeExist(n) )
	{
		for(auto& E: vertices[n])
		{
			for(auto itr = vertices[E.vertex].begin(); itr->vertex != n; ++itr)
				V = itr;
			
			vertices[E.vertex].erase(V);
		}
		
		vertices.erase(n);
		
		size--;
		
		return true;
	}
	else
		return false;
}

	// total edge count
int graph::getEdges()
{
	int count = 0;
	
	for(int i = 0; i < size; i++)
	{
		for(auto& E: vertices[i])
		{
			if(E.vertex > i)
				count++;
		}
	}
	
	return count;
}

	// returns true if there's an edge from node x to y
bool graph::isAdjacent(int x, int y)
{	
	if ( nodeExist(x) && nodeExist(y) )
	{
		for(auto& E: vertices[x])
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
	vector<int> neighbors = vector<int>();
	
	if ( nodeExist(x) )
	{
		for(auto& E: vertices[x])
			neighbors.push_back(E.vertex);
	}
	
	return neighbors;
}

	// adds edge between x & y, if one is currently nonexistent
	// returns true if edge was added, if not return false
bool graph::addEdge(int x, int y, int d, eCLR c)
{
	if ( nodeExist(x) && nodeExist(y) )
	{
		if ( isAdjacent(x, y) && isAdjacent(y, x) )
			return false;
		else
		{
			vertices[x].push_back( edge(y, d, c) );
			vertices[y].push_back( edge(x, d, c) );
		
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
	if ( nodeExist(x) && nodeExist(y) )
	{
		if ( isAdjacent(x, y) && isAdjacent(y, x) )
		{
			for (auto itr = vertices[x].begin(); itr != vertices[x].end(); ++itr)
			{
				if (itr->vertex == y)
				{
					vertices[x].erase(itr);
					break;
				}
			}
		
			for (auto itr = vertices[y].begin(); itr != vertices[y].end(); ++itr)
			{
				if (itr->vertex == x)
				{
					vertices[y].erase(itr);
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
	if ( nodeExist(x) && nodeExist(y) )
	{
		for(auto& E: vertices[x])
		{
			if (E.vertex == y)
				return E.weight;
		}
		
		return -1;
	}
	else
		return -1;
}

bool graph::setEdgeValue(int x, int y, int ev)
{
	if ( nodeExist(x) && nodeExist(y) )
	{
		if ( isAdjacent(x, y) && isAdjacent(y, x) )
		{
			for(auto& E: vertices[x])
			{
				if (E.vertex == y)
				{
					E.weight = ev;
					break;
				}
			}
			
			for(auto& E: vertices[y])
			{
				if (E.vertex == x)
				{
					E.weight = ev;
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

eCLR graph::getEdgeColor(int x, int y)
{	
	if ( nodeExist(x) && nodeExist(y) )
	{
		for(auto& E: vertices[x])
		{
			if (E.vertex == y)
				return E.color;
		}
		
		return eCLR::NONE;
	}
	else
		return eCLR::NONE;
}

	// get the average path length of all the nodes connected to node "n"
double graph::avePathLength(int n)
{
	double total = 0.0;
	
	int eCount;
	
	if ( nodeExist(n) )
	{
		eCount = vertices[n].size();
		
		for(auto& E: vertices[n])
			total += static_cast<double>(E.weight);

		return total / static_cast<double>(eCount);
	}
	else
		return 0.0;
}
