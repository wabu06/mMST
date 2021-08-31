#include<fstream>

#include "mst.h"



int main(int argc, char** argv)
{
	ifstream fin("g4gGraph.txt"); // open file and connect it to a stream
	
	if ( fin.bad() )
	{
		cerr << "Error opening file!!" << endl;
		return 1;
	}
	
	int gsize;
	
	fin >> gsize; //cout << gsize << endl;
	
	int v1, v2, w;
	
	vectOfTuples edgeW;
	
	while( fin.good() )
	{
		fin >> v1 >> v2 >> w;
		
		edgeW.push_back( intTup{v1, v2, w} );
	}
	
	fin.close();
	
	mst mstG{ graph(gsize, edgeW) };
	
	for(auto& V: mstG.getMinTree() )
		cout << "(" << V.edge[0] << ", " << V.edge[1] << ")\t" << V.cost << '\t';
		
	cout << endl;
	
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
	
	mstG = mst{ graph(edgeW) };
	
	for(auto& V: mstG.getMinTree() )
		cout << "(" << V.edge[0] << ", " << V.edge[1] << ")\t" << V.cost << '\t';
		
	cout << endl;
	
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
	
	for(int i{0}; i < gsize; ++i)
		cout << "EDGE " << i+1 << "\tCOST\t";
	
	cout << endl;
	
	int total{0};
	
	for(auto& V: mstG.getMinTree() )
	{
		cout << "(" << V.edge[0] << ", " << V.edge[1] << ")\t" << V.cost << '\t';
		total += V.cost;
	}
		
	cout << "TOTAL COST: " << total << endl;
	
	//char word; cin >> word; cout << static_cast<int>(word) << endl;

	return 0;
}
