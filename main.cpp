#include<fstream>
#include<iomanip>

#include "mst.h"



bool getFileData(const char* fn, vectOfTuples& VoT, int& gs)
{
	ifstream fin(fn); // open file and connect it to a stream
	
	if ( fin.bad() )
		return false;
	
	fin >> gs; // read in from the file the node count
	
	int v1, v2, w; // node pairs and their edge cost
	
		// read in from the file the edges and the cost associated with
		// each edge, and store that into a vector
	while( fin.good() )
	{
		fin >> v1 >> v2 >> w;
		
		VoT.push_back( intTup{v1, v2, w} );
	}
	
	return true;
}

void showMinTree(graph G, int& gs, eCLR C = eCLR::NONE)
{
		// create an instance of the minimum spanning tree class,
		// with a graph instance as input, the graph instance has as it's input
		// the vector from above
	mst mstG{ G };
	
	if ( C != eCLR::NONE)
		mstG.setColor(C, true);
		
 	cout << "\nEDGE\t\tCOST" << endl;
	
	int total{0}; // used to calculate edge cost total
	
		// find the minimum spanning tree and display it
	for(auto& M: mstG.getMinTree() )
	{
		cout << "(" << M.second.edge[0] << ", " << M.second.edge[1] << ")";
		cout << "\t\t" << M.second.cost  << '\n';
		total += M.second.cost;
 	}
 		
 	cout << "TOTAL EDGE COST: " << total << endl; 
}
 

int main(int argc, char** argv)
{
	vectOfTuples edgeW; // vector to store the edges and their costs
	
	int gsize; // node count
	
	if ( !getFileData("g4gGraph.txt", edgeW, gsize) )
	{
		cerr << "Error opening file!!" << endl;
		return 1;
	}
	
	showMinTree( graph(edgeW), gsize );
	
	/********* graph *********/
	
	edgeW.clear();
	
	if ( !getFileData("graph.txt", edgeW, gsize) )
	{
		cerr << "Error opening file!!" << endl;
		return 1;
	}
	
	showMinTree( graph(edgeW), gsize, eCLR::YLLW );
		
	//mstG = mst{ graph(edgeW) }; mstG.setColor(eCLR::YLLW, true);
	
	
	/********* graph 1 *********/
	
	edgeW.clear();
	
	if ( !getFileData("graph1.txt", edgeW, gsize) )
	{
		cerr << "Error opening file!!" << endl;
		return 1;
	}
	
	showMinTree( graph(edgeW), gsize, eCLR::RED );
		
	//mstG.setColor(eCLR::RED, true);
	
	return 0;
}
