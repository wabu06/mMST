#include<fstream>
#include<iomanip>

#include "mst.h"



int main(int argc, char** argv)
{
	ifstream fin("graph.dat"); // open file and connect it to a stream
	
	if ( fin.bad() )
	{
		cerr << "Error opening file!!" << endl;
		return 1;
	}
	
	int gsize; // node count
	
	fin >> gsize; // read in from the file the node count
	
	int v1, v2, w; // node pairs and their edge cost
	
	vectOfTuples edgeW; // vector to store the edges and their costs
	
		// read in from the file the edges and the cost associated with each
		// edge, and store that into a vector
	while( fin.good() )
	{
		fin >> v1 >> v2 >> w;
		
		edgeW.push_back( intTup{v1, v2, w} );
	}
	
	fin.close();
	
		// create an instance of the minimum spanning tree class,
		// with a graph instance as input, the graph instance has as it's input
		// the vector from above
	mst mstG{ graph(edgeW) };
	
 	cout << "EDGE\t\tCOST" << endl;
	
	int total{0}; // used to calculate edge cost total
	
		// find the minimum spanning tree and display it
	for(auto& V: mstG.getMinTree() )
	{
		cout << "(" << V.edge[0] << ", " << V.edge[1] << ")";
		cout << setw(12) << setfill(' ') << right << V.cost  << '\n';
		total += V.cost;
 	}
 		
 	cout << "TOTAL EDGE COST: " << total << endl; 

	
	/********* graph *********/
	
	edgeW.clear();
	
	fin.open("graph.txt");
	
	if ( fin.bad() )
	{
		cerr << "Error opening file!!" << endl;
		return 1;
	}
	
	fin >> gsize;
	
	while( fin.good() )
	{
		fin >> v1 >> v2 >> w;
		
		edgeW.push_back( intTup{v1, v2, w} );
	}
	
	fin.close();
	
	mstG = mst{ graph(edgeW) }; mstG.setColor(eCLR::YLLW, true);
	
	cout << "\nEDGE\t\tCOST" << endl; total = 0;
	
	for(auto& V: mstG.getMinTree() )
	{
		cout << "(" << V.edge[0] << ", " << V.edge[1] << ")\t\t";
		cout << V.cost << '\n';
		total += V.cost;
	}
		
	cout << "TOTAL EDGE COST: " << total << endl;
	
	/********* graph 1 *********/
	
	edgeW.clear();
	
	fin.open("graph1.txt");
	
	if ( fin.bad() )
	{
		cerr << "Error opening file!!" << endl;
		return 1;
	}
	
	fin >> gsize;
	
	while( fin.good() )
	{
		fin >> v1 >> v2 >> w;
		
		edgeW.push_back( intTup{v1, v2, w} );
	}
	
	mstG = mst{ graph(edgeW) }; --gsize;
	
	//for(int i{0}; i < gsize; ++i)
		//cout << "EDGE " << i+1 << "\tCOST\t";
	
	cout << "\nEDGE" << "\t\tCOST" << endl;
	
	total = 0; mstG.setColor(eCLR::RED, true);
	
	for(auto& V: mstG.getMinTree() )
	{
		cout << "(" << V.edge[0] << ", " << V.edge[1] << ")\t\t";
		cout << V.cost << '\n';
		total += V.cost;
	}
		
	cout << "TOTAL EDGE COST: " << total << endl;
	
	//char word; cin >> word; cout << static_cast<int>(word) << endl;

	return 0;
}
